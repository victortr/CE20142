//Diodo.cpp

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <cmath>
#include "Diodo.h"

using namespace std;

//Utilizado para o transistor MOS (ou outdos diodos parasitas)
Diodo::Diodo(int anodo,int catodo, Matriz *matriz)
{
	//parametros default
	m_Vt = 0.025;
	m_Is = 0.001/(exp(0.6/0.025) - 1);

	m_a = anodo;
	m_b = catodo;

	m_erro = false;
	m_matriz = matriz;
}

//Diodo: D<nome> <nó anodo> <nó catodo> [<Is> <Vt>]
Diodo::Diodo(ifstream &arq)
{
	//Sem parâmetros dados, devem conduzir 1 mA com v = 0.6 V, e ter Vt = 25 mV.
	m_Vt = 0.025;
	m_Is = 0.001/(exp(0.6/0.025) - 1);

	m_erro = false;
	int i = 0;
	while(arq.good() && arq.peek() != '\n')
	{
		//ignora espacos
		if(arq.peek() == ' ')
		{
			arq.ignore();
			continue;
		}
		switch(i)
		{
			case 0: arq >> m_nome;		break;
			case 1: arq >> m_nome_a;	break;
			case 2: arq >> m_nome_b;	break;
			case 3: arq >> m_Is;		break;
			case 4: arq >> m_Vt;		break;
			
			default:arq >> m_ignora;	break;
		}
		i++;
	}
	arq.ignore();
	if(i!=3 && i!=5)
	{
		cout<< m_nome <<": Numero de parametros errado " << i << "/3-5"<<endl;
		arq.close();
		m_erro = true;
	}

	cout<<m_nome<<": "<<m_nome_a<<" "<<m_nome_b<<" "<<m_Is<<" "<<m_Vt<<endl;
}	

void Diodo::associaMatriz(Matriz *matriz)
{
	m_matriz = matriz;
	m_a = matriz->adVariavel(m_nome_a);
	m_b = matriz->adVariavel(m_nome_b);
}

void Diodo::estampaPO()
{
	//condutancia e corrente para modelo de newton-raphson
	double G0,I0;

	//tensao na iteracao anterior
	double Vn;
	
	Vn = m_matriz->getSolucao(0)[m_a] - m_matriz->getSolucao(0)[m_b];

	if(Vn/m_Vt > MAX_EXP_DIODO)
		Vn = MAX_EXP_DIODO*m_Vt;
	
	G0 = (m_Is/m_Vt)*exp(Vn/m_Vt);
	I0 = m_Is * ( exp(Vn/m_Vt) - 1 ) - G0*Vn; 

	estampaPrimR(m_a,m_b,1/G0);
	estampaPrimI(m_a,m_b,I0);
}

void Diodo::estampaBE(double tempo, double passo)
{
	estampaPO();
}

void Diodo::estampaGEAR(double tempo, double passo)
{
	estampaPO();
}
