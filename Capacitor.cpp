//Capacitor.cpp

#include <stdio.h>
#include <iostream>
#include <fstream>
#include "Capacitor.h"

using namespace std;

// Para capacitancias parasitas
Capacitor::Capacitor(int a, int b, double C, Matriz *matriz) 
{
	m_a = a;
	m_b = b;
	m_C = C;

	m_erro = false;
	m_matriz = matriz;
}

//C<nome> <nó1> <nó2> <Capacitância>
Capacitor::Capacitor(ifstream &arq)
{
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
			case 3: arq >> m_C;			break;
			default:arq >> m_ignora;	break;
		}
		i++;
	}
	arq.ignore();
	if(i!=4)
	{
		cout<< m_nome <<": Numero de parametros errado " << i << "/4"<<endl;
		arq.close();
		m_erro = true;
	}

	cout<<m_nome<<": "<<m_nome_a<<" "<<m_nome_b<<" "<<m_C<<endl;
}

void Capacitor::associaMatriz(Matriz *matriz)
{
	m_matriz = matriz;
	m_a = matriz->adVariavel(m_nome_a);
	m_b = matriz->adVariavel(m_nome_b);
}

void Capacitor::estampaPO()
{
    double R[8] = {1E9, 0, 0, 0, 0, 0, 0, 0};
    estampaPrimR(m_a,m_b,R);
}

void Capacitor::estampaBE(double tempo, double passo)
{
	//Modelo BE do Capacitor como resistor//fonte de corrente
	double R,I,V0;

	//V0 representa a tensao em t = t0
	V0 = m_matriz->getSolucao(1)[m_a] - m_matriz->getSolucao(1)[m_b];

	R = passo/m_C;
	I = m_C*V0/passo;

   double R1[8] = {R, 0, 0, 0, 0, 0, 0, 0};

    estampaPrimR(m_a,m_b,R1);
	//corrente no sentido b->a
    estampaPrimI(m_a,m_b,-I);

}

void Capacitor::estampaGEAR(double tempo, double passo)
{
	//primeiro passo aplica BE
	if(tempo==0)
	{
		estampaBE(tempo,passo);
		return;
	}
	
	//Modelo GEAR do Capacitor como resistor//fonte corrente
	double R,I,V0,V1;

	//V0 e V1 representam as tensoes em t = t0 e t= t0 - "passo", respectivamente
	V0 = m_matriz->getSolucao(1)[m_a] - m_matriz->getSolucao(1)[m_b];
	V1 = m_matriz->getSolucao(2)[m_a] - m_matriz->getSolucao(2)[m_b];

	//Corrente e Resistor do modelo GEAR de ordem 2
	R = (2*passo)/(3*m_C);
	I = (2*m_C*V0)/passo - (m_C*V1)/(2*passo);
	
    double R1[8] = {R, 0, 0, 0, 0, 0, 0, 0};

    estampaPrimR(m_a,m_b,R1);
	//A fonte de corrente aparece no sentido b->a
	estampaPrimI(m_a,m_b,-I);
}
