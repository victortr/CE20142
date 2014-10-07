//Resistor.cpp

#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include "Tensao.h"

using namespace std;

//Fonte de tensão: <nome> <nó+> <nó-> <Parâmetros>

//DC <valor> (para fonte DC)
//SIN (<nivel contínuo> <amplitude> <frequencia (Hz)> <atraso> <fator de atenuação> <ângulo> <número de ciclos>)
//PULSE (<amplitude 1> <amplitude 2> <atraso> <tempo de subida> <tempo de descida> <tempo ligada><período> <número de ciclos>)

Tensao::Tensao(ifstream &arq)
{
	m_erro = false;
	int i = 0;
	string buf;
	while(arq.good() && arq.peek() != '\n')
	{
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
				arq>>m_tipo;
				if(m_tipo == "DC")
					carregaParamDC(arq);
				else if(m_tipo == "SIN")
					carregaParamSIN(arq);
				else if(m_tipo == "PULSE")
					carregaParamPULSE(arq);
				else
				{
					cout<< m_nome <<": Tipo invalido - "<<m_tipo<<endl;
					arq.close();
					m_erro = true;
				}
				break;
			default:
				arq>>m_ignora;
				break;
		}
		i++;
	}
	arq.ignore();
	if(i!=4)
	{
		cout<< m_nome <<": Numero de parametros errado <PARAMETROS> = 1 parametro " << i << "/4"<<endl;
		arq.close();
		m_erro = true;
	}

}

//DC <valor> (para fonte DC)
void Tensao::carregaParamDC(ifstream &arq)
{
	int i = 0;
	while(arq.good() && arq.peek() != '\n')
	{
		switch(i)
		{
			case 0: 
				arq >> m_DC;
				break;
			default:
				arq>>m_ignora;
				break;
		}
		i++;
	}
	if(i!=1)
	{
		cout<< m_nome <<" DC: Numero de parametros errado" << i << "/1"<<endl;
		arq.close();
		m_erro = true;
	}
	cout<<m_nome<<" DC: "<<m_nome_a<<" "<<m_nome_b<<" "<<m_DC<<endl;
}


//SIN (<nivel contínuo> <amplitude> <frequencia (Hz)> <atraso> <fator de atenuação> <ângulo> <número de ciclos>)
void Tensao::carregaParamSIN(ifstream &arq)
{
	int i = 0;
	while(arq.good() && arq.peek() != '\n')
	{
		//ignora os parenteses
		if (arq.peek() == ' ' || arq.peek() == '(' || arq.peek() == ')')
		{
			arq.ignore();
			continue;
		}
		switch(i)
		{
			case 0: 
				arq >> m_DC;
				break;
			case 1: 
				arq >> m_amplitude;
				break;
			case 2: 
				arq >> m_freq;
				break;
			case 3: 
				arq >> m_atraso;
				break;
			case 4: 
				arq >> m_atenuacao;
				break;
			case 5: 
				arq >> m_angulo;
				break;
			case 6: 
				arq >> m_ciclos;
				break;
			default:
				arq >>m_ignora;
				break;
		}
		i++;
	}
	if(i!=7)
	{
		cout<< m_nome <<" SIN: Numero de parametros errado" << i << "/7"<<endl;
		arq.close();
		m_erro = true;
	}

	cout<<m_nome<<" SIN:"<<m_nome_a<<" "<<m_nome_b
		<<" "<<m_DC
		<<" "<<m_amplitude
		<<" "<<m_freq
		<<" "<<m_atraso
		<<" "<<m_atenuacao
		<<" "<<m_angulo
		<<" "<<m_ciclos<<endl;

}

//PULSE (<amplitude 1> <amplitude 2> <atraso> <tempo de subida> <tempo de descida> <tempo ligada> <período> <número de ciclos>)
void Tensao::carregaParamPULSE(ifstream &arq)
{
	int i = 0;
	while(arq.good() && arq.peek() != '\n')
	{
		//ignora os parenteses
		if (arq.peek() == ' ' || arq.peek() == '(' || arq.peek() == ')')
		{
			arq.ignore();
			continue;
		}
		switch(i)
		{
			case 0: 
				arq >> m_amplitude;
				break;
			case 1: 
				arq >> m_amplitude2;
				break;
			case 2: 
				arq >> m_atraso;
				break;
			case 3: 
				arq >> m_t_subida;
				break;
			case 4: 
				arq >> m_t_descida;
				break;
			case 5: 
				arq >> m_t_ligada;
				break;
			case 6: 
				arq >> m_periodo;
				break;
			case 7: 
				arq >> m_ciclos;
				break;
			default:
				arq >> m_ignora;
				break;
		}
		i++;
	}
	if(i!=8)
	{
		cout<< m_nome <<" PULSE: Numero de parametros errado" << i << "/8"<<endl;
		arq.close();
		m_erro = true;
	}

	cout<<m_nome<<" PULSE:"<<m_nome_a<<" "<<m_nome_b
		<<" "<<m_amplitude
		<<" "<<m_amplitude2
		<<" "<<m_atraso
		<<" "<<m_t_subida
		<<" "<<m_t_descida
		<<" "<<m_t_ligada
		<<" "<<m_periodo
		<<" "<<m_ciclos<<endl;
}

void Tensao::associaMatriz(Matriz *matriz)
{
	m_matriz = matriz;
	m_a = matriz->adVariavel(m_nome_a);
	m_b = matriz->adVariavel(m_nome_b);

	//char nome[8];
	//sprintf(nome,"j%0.3d%0.3d",m_a,m_b);
	
	string nomeVar = "j";
	nomeVar.append(m_nome);
	m_x = matriz->adVariavel(nomeVar);
}

void Tensao::estampaPO()
{
	estampaPrimV(m_a,m_b,m_x,0);
}

void Tensao::estampaBE(double tempo, double passo)
{
	estampaPrimV(m_a,m_b,m_x,calcValor(tempo));
}

void Tensao::estampaGEAR(double tempo, double passo)
{
	estampaPrimV(m_a,m_b,m_x,calcValor(tempo));
}

double Tensao::calcValor(double t)
{
	if(m_tipo == "DC")
		return m_DC;

	if(m_tipo == "SIN")
	{
		int ciclo_atual = floor((t-m_atraso)*m_freq); 
		if(t<=m_atraso || ciclo_atual>=m_ciclos)
			return m_DC + sin(M_PI*m_angulo/180 );
		
		return m_DC + m_amplitude * 
						exp((t-m_atraso)*m_atenuacao) * 
						sin(2*M_PI*m_freq*(t-m_atraso) + M_PI*m_angulo/180);
	}

	if(m_tipo == "PULSE")
	{	
		if(t<m_atraso)
			return m_amplitude;
		
		int ciclo_atual = floor((t-m_atraso)/m_periodo);
		
		if(ciclo_atual>=m_ciclos)
			return m_amplitude;
		//calcula o tempo relativo ao inicio do ciclo autal
		double t_rel = t - (m_atraso + ciclo_atual*m_periodo);
		
		
		if(t_rel<m_t_subida)
		{
			double a = (m_amplitude2 - m_amplitude)/m_t_subida;
			
			return m_amplitude + a*(t_rel);
		}

		if(t_rel<m_t_subida + m_t_ligada)
		{
			return m_amplitude2;
		}

		if(t_rel< m_t_subida + m_t_ligada + m_t_descida)
		{
			double a = (m_amplitude - m_amplitude2)/m_t_descida;
			
			return m_amplitude2 + a*(t_rel - (m_t_subida + m_t_ligada));
		}

		return m_amplitude;
	}

	return 0;
}
