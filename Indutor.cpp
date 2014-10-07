//Indutor.cpp

#include <stdio.h>
#include <iostream>
#include <fstream>
#include "Indutor.h"

using namespace std;

//L<nome> <nó1> <nó2> <Indutância>
Indutor::Indutor(ifstream &arq)
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
			case 3: arq >> m_L;			break;
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

	cout<<m_nome<<": "<<m_nome_a<<" "<<m_nome_b<<" "<<m_L<<endl;
}

void Indutor::associaMatriz(Matriz *matriz)
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

void Indutor::estampaPO()
{
	//Substituir por resistor de 1 nOhm
	//Como a variavel m_x foi setada, o melhor é
	//utilizar a estampa V com valor 0 e restior em serie de 1nOhm
	estampaPrimV(m_a,m_b,m_x,0,1E-9);
}

void Indutor::estampaBE(double tempo, double passo)
{
	//Modelo BE do Indutor como resistor + fonte tensao
	double R,V,J0;

	//J0 representa a corrente em t = t0
	J0 = m_matriz->getSolucao(1)[m_x];

	R = m_L/passo;
	V = (m_L/passo)*J0;

	estampaPrimV(m_a,m_b,m_x,-V,R);

}

void Indutor::estampaGEAR(double tempo, double passo)
{
	//primeiro passo aplica BE
	if(tempo==0)
	{
		estampaBE(tempo,passo);
		return;
	}
	
	//Modelo GEAR do Indutor como resistor + fonte tensao
	double R,V,J0,J1;

	//J0 e J1 representam as correntes em t = t0 e t= t0 - "passo", respectivamente
	J0 = m_matriz->getSolucao(1)[m_x];
	J1 = m_matriz->getSolucao(2)[m_x];

	//Tensao e Resistor do modelo GEAR de ordem 2
	R = (3*m_L)/(2*passo);
	V = (2*m_L*J0)/passo - (m_L*J1)/(2*passo);
	
	
	estampaPrimV(m_a,m_b,m_x,-V,R);
}
