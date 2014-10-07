//Resistor.cpp

#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include "const.h"
#include "Mos.h"
#include "Capacitor.h"
#include "Diodo.h"

using namespace std;


//M<nome> <no d> <no g> <no s> <no b> NMOS|PMOS [L=<comprimento> W=<largura>] [<K> <Vt0> <lamb> <gama> <fi>]
Mos::Mos(ifstream &arq)
{
	m_W = m_L = 1e-6;
	m_K = 0.1e-3;
	m_Vt0 = 1;
	m_lamb = 0.01;
	m_fi = 0.6;
	m_gama = 0.3;
	
	m_erro = false;
	int i = 0;
	string buf;
	while(arq.good() && arq.peek() != '\n')
	{
		//Ignora os espacos
		if (arq.peek() == ' ')
		{
			arq.ignore();
			continue;
		}
		switch(i)
		{
			case 0: 
				arq >> m_nome;
				break;
			case 1: 
				arq >> m_nome_a;
				break;
			case 2: 
				arq >> m_nome_b;
				break;
			case 3: 
				arq >> m_nome_c;
				break;
			case 4:
				arq >> m_nome_d;
				break;
			case 5: 
				arq>>m_tipo;
				if(m_tipo != "NMOS" && m_tipo != "PMOS")
				{
					cout<< m_nome <<": Tipo invalido - "<<m_tipo<<endl;
					arq.close();
					m_erro = true;
				}
				break;
			case 6:
				if(arq.peek() != 'L')
				{
					i = 8;
					continue;
				}
				//ignora "L="
				arq.ignore(2);
				arq>>m_L;
				break;
			case 7:
				//ignora "W="
				arq.ignore(2);
				arq>>m_W;
				break;
			case 8:
				arq>>m_K;
				break;
			case 9:
				arq>>m_Vt0;
				break;
			case 10:
				arq>>m_lamb;
				break;
			case 11:
				arq>>m_gama;
				break;
			case 12:
				arq>>m_fi;
				break;
			default:
				arq>>m_ignora;
				break;
		}
		i++;
	}
	arq.ignore();
	if(i!=6 && i!=8 && i!=13)
	{
		cout<< m_nome <<": Numero de parametros errado " << i << "/6-8-13"<<endl;
		arq.close();
		m_erro = true;
	}

	cout<<m_nome<<": "<<m_nome_a<<" "<<m_nome_b
		<<" "<<m_nome_c
		<<" "<<m_nome_d
		<<" "<<m_tipo
		<<" "<<m_L
		<<" "<<m_W
		<<" "<<m_K
		<<" "<<m_Vt0
		<<" "<<m_lamb
		<<" "<<m_gama
		<<" "<<m_fi<<endl;

	cout<<"Cgs=Ggd="<<calcCgs()<<endl;

	//caso seja PMOS, m_lamb tem q ser negativo
	if(m_tipo == "PMOS")
	{
		m_Vt0 = - fabs(m_Vt0);
		m_lamb = -fabs(m_lamb);
	}
}


void Mos::associaMatriz(Matriz *matriz)
{
	m_matriz = matriz;
	m_a = matriz->adVariavel(m_nome_a);
	m_b = matriz->adVariavel(m_nome_b);

	m_c = matriz->adVariavel(m_nome_c);
	m_d = matriz->adVariavel(m_nome_d);
}

void Mos::estampaBase(double tempo,double passo)
{
	//pega a solucao da iteracao anterior
	double *sol = m_matriz->getSolucao(0);
	
	double Vgs = sol[m_b] - sol[m_c];
	double Vds = sol[m_a] - sol[m_c];
	double Vbs = sol[m_d] - sol[m_c];

	double Gm = calcGm(Vgs,Vds,Vbs);
	double Gmb = calcGmb(Vgs,Vds,Vbs);
	double Gds = calcGds(Vds,Vds,Vbs);

	double Ig = calcId(Vgs,Vds,Vbs) - Gm*Vgs - Gmb*Vbs - Gds*Vds;

	if(m_tipo == "NMOS")
	{
		//fontes controladas por Tensao de D(m_a) para S(m_c)
		estampaPrimG(m_a,m_c,m_b,m_c,Gm);
		estampaPrimG(m_a,m_c,m_a,m_c,Gds);
		estampaPrimG(m_a,m_c,m_d,m_c,Gmb);

		//fonte independente de D para S
		estampaPrimI(m_a,m_c,Ig);
	}
	//PMOS as correntes trocam de direcao
	else if(m_tipo == "PMOS")
	{
		//fontes controladas por Tensao de S(m_c) para D(m_a)
		estampaPrimG(m_a,m_c,m_b,m_c,-Gm);
		estampaPrimG(m_a,m_c,m_a,m_c,-Gds);
		estampaPrimG(m_a,m_c,m_d,m_c,-Gmb);

		//fonte independente de D para S
		estampaPrimI(m_a,m_c,-Ig);
	}

	//DIODOS
	if(m_tipo == "NMOS")
	{
		//Diodo BD
		Diodo BD(m_d,m_a,m_matriz);
		BD.estampaGEAR(tempo,passo);

		//Diodo BS
		Diodo BS(m_d,m_c,m_matriz);
		BS.estampaGEAR(tempo,passo);
	}
	else if(m_tipo == "PMOS")
	{
		//Diodo DB
		Diodo DB(m_a,m_d,m_matriz);
		DB.estampaGEAR(tempo,passo);

		//Diodo SB
		Diodo SB(m_c,m_d,m_matriz);
		SB.estampaGEAR(tempo,passo);
	}
}

void Mos::estampaPO()
{
	
	estampaBase(0,0);
	
	double C = calcCgs();

#ifdef MOS_CAP
	Capacitor Cgs(m_b,m_c,C,m_matriz);
	Cgs.estampaPO();

	Capacitor Cgd(m_b,m_a,C,m_matriz);
	Cgd.estampaPO();
#endif
}

void Mos::estampaBE(double tempo, double passo)
{
	estampaBase(tempo,passo);

	double C = calcCgs();

#ifdef MOS_CAP
	Capacitor Cgs(m_b,m_c,C,m_matriz);
	Cgs.estampaGEAR(tempo,passo);

	Capacitor Cgd(m_b,m_a,C,m_matriz);
	Cgd.estampaGEAR(tempo,passo);
#endif
}

void Mos::estampaGEAR(double tempo, double passo)
{
	
	if(tempo ==0)
	{
		estampaBE(tempo,passo);
		return;
	}

	estampaBase(tempo,passo);

	double C = calcCgs();

#ifdef MOS_CAP
	Capacitor Cgs(m_b,m_c,C,m_matriz);
	Cgs.estampaGEAR(tempo,passo);

	Capacitor Cgd(m_b,m_a,C,m_matriz);
	Cgd.estampaGEAR(tempo,passo);
#endif
}

double Mos::calcCgs()
{
	double mi = 0;
	if(m_tipo == "NMOS")
		mi = 0.05;
	else if (m_tipo == "PMOS")
		mi = 0.02;

	return m_W*m_L*m_K/mi;
}

double Mos::calcId(double Vgs,double Vds,double Vbs)
{
	double Vt = calcVt(Vbs);
	if(m_tipo == "NMOS")
	{
		//corte
		if(Vgs < Vt)
			return 0;
		//triodo
		if(Vds <= Vgs - Vt)
			return (m_K*m_W/m_L)*( 2*(Vgs - Vt)*Vds - pow(Vds,2) )*(1+m_lamb*Vds);
		//saturacao
		return (m_K*m_W/m_L)*pow(Vgs - Vt,2)*(1+m_lamb*Vds);
		
	}
	else if(m_tipo == "PMOS")
	{
		//corte
		if(Vgs > Vt)
			return 0;
		//triodo
		if(Vds >= Vgs - Vt)
			return (m_K*m_W/m_L)*( 2*(Vgs - Vt)*Vds - pow(Vds,2) )*(1+m_lamb*Vds);
		//saturacao
		return (m_K*m_W/m_L)*pow(Vgs - Vt,2)*(1+m_lamb*Vds);
	}
	return 0;
}

//Calcula Vt baseado em Vbs
double Mos::calcVt(double Vbs)
{
	if(m_tipo == "NMOS")
	{
		return m_Vt0 + m_gama*(sqrt(m_fi - Vbs) - sqrt(m_fi));
	}
	else if(m_tipo == "PMOS")
	{
		return m_Vt0 - m_gama*(sqrt(m_fi + Vbs) - sqrt(m_fi));
	}
	return 0;
	 
}

double Mos::calcGds(double Vgs,double Vds,double Vbs)
{
	double Vt = calcVt(Vbs);

	if(m_tipo == "NMOS")
	{
		//corte
		if(Vgs < Vt)
			return 0;
		//triodo
		if(Vds <= Vgs - Vt)
			return (m_K*m_W/m_L)*(2*(Vgs - Vt) - 2*Vds + 4*m_lamb*(Vgs-Vt)*Vds - 3*m_lamb*pow(Vds,2));
			//return (m_K*m_W/m_L) * ((1+m_lamb*Vds)*2*(Vgs-Vt-Vds) + m_lamb*(2*(Vgs-Vt)*Vds - pow(Vds,2)));
		//saturacao
		return (m_K*m_W/m_L)*pow(Vgs-Vt, 2)*m_lamb;
		
	}
	else if(m_tipo == "PMOS")
	{
		//corte
		if(Vgs > Vt)
			return 0;
		//triodo
		if(Vds >= Vgs - Vt)
			return (m_K*m_W/m_L)*(2*(Vgs - Vt) - 2*Vds + 4*m_lamb*(Vgs-Vt)*Vds - 3*m_lamb*pow(Vds,2));
		//saturacao
		return (m_K*m_W/m_L)*pow(Vgs-Vt, 2)*m_lamb;
	}
	return 0;
	
}
double Mos::calcGm(double Vgs,double Vds,double Vbs)
{
	double Vt = calcVt(Vbs);

	if(m_tipo == "NMOS")
	{
		//corte
		if(Vgs < Vt)
			return 0;
		//triodo
		if(Vds <= Vgs - Vt)
			return (m_K*m_W/m_L)*2*Vds*(1+m_lamb*Vds);
		//saturacao
		return (m_K*m_W/m_L)*2*(Vgs - Vt)*(1+m_lamb*Vds);
		
	}
	else if(m_tipo == "PMOS")
	{
		//corte
		if(Vgs > Vt)
			return 0;
		//triodo
		if(Vds >= Vgs - Vt)
			return (m_K*m_W/m_L)*2*Vds*(1+m_lamb*Vds);
		//saturacao
		return (m_K*m_W/m_L)*2*(Vgs - Vt)*(1+m_lamb*Vds);
	}
	return 0;
}
double Mos::calcGmb(double Vgs,double Vds,double Vbs)
{
	double Vt = calcVt(Vbs);
	
	//derivada de Vt em funcao de Vbs
	double dVt;
	if(m_tipo == "NMOS")
	{
		dVt = - 0.5*m_gama/sqrt(m_fi - Vbs);
		
		//corte
		if(Vgs < Vt)
			return 0;
		//triodo
		if(Vds <= Vgs - Vt)
			return -(m_K*m_W/m_L)*(2*Vds*dVt)*(1+m_lamb*Vds);
		//saturacao
		return -(m_K*m_W/m_L)*(2*(Vgs-Vt)*dVt)*(1+m_lamb*Vds);
		
	}
	else if(m_tipo == "PMOS")
	{
		dVt = - 0.5*m_gama/sqrt(m_fi + Vbs);

		//corte
		if(Vgs > Vt)
			return 0;
		//triodo
		if(Vds >= Vgs - Vt)
			return -(m_K*m_W/m_L)*(2*Vds*dVt)*(1+m_lamb*Vds);
		//saturacao
		return -(m_K*m_W/m_L)*(2*(Vgs-Vt)*dVt)*(1+m_lamb*Vds);
	}
	return 0;
}
