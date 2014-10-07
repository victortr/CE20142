//Resistor.cpp

#include <stdio.h>
#include <iostream>
#include <fstream>
#include "Resistor.h"

using namespace std;

//Resistor: <nome> <nó1> <nó2> <Resistência>
Resistor::Resistor(ifstream &arq)
{
	m_erro = false;
	int i = 0;
	m_R[8] = {0};
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
			case 3: arq >> m_R[0];			break;
			case 5: arq >> m_R[1];			break;
			case 6: arq >> m_R[2];			break;
			case 7: arq >> m_R[3];			break;
			case 8: arq >> m_R[4];			break;
			case 9: arq >> m_R[5];			break;
			case 10: arq >> m_R[6];			break;
			case 11: arq >> m_R[7];			break;
			default:arq >> m_ignora;		break;
		}
		i++;
	}
	arq.ignore();
	if(i > 12)
	{
		cout<< m_nome <<": Numero de parametros errado " << i << "/1"<<endl;
		arq.close();
		m_erro = true;
	}

	cout<<m_nome<<": "<<m_nome_a<<" "<<m_nome_b<<" "<<m_R<<endl;
}

void Resistor::associaMatriz(Matriz *matriz)
{
	m_matriz = matriz;
	m_a = matriz->adVariavel(m_nome_a);
	m_b = matriz->adVariavel(m_nome_b);
}

void Resistor::estampaPO()
{
	estampaPrimR(m_a,m_b,m_R[8]);
}

void Resistor::estampaBE(double tempo, double passo)
{
    estampaPrimR(m_a,m_b,m_R[8]);
}

void Resistor::estampaGEAR(double tempo, double passo)
{
	estampaPrimR(m_a,m_b,m_R[8]);
}
