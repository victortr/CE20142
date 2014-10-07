
#include <stdio.h>
#include <iostream>
#include <fstream>
#include "Ampop.h"

using namespace std;

//O<nome> <no1> <no2> <vi1> <vi2>
Ampop::Ampop(ifstream &arq)
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
			case 3: arq >> m_nome_c;	break;
			case 4: arq >> m_nome_d;	break;
			
			//ignora
			default: arq>>m_ignora;
				break;
		}
		i++;
	}
	arq.ignore();
	if(i!=5)
	{
		cout<< m_nome <<": Numero de parametros errado " << i << "/5"<<endl;
		arq.close();
		m_erro = true;
	}

	cout<<m_nome<<": "<<m_nome_a<<" "<<m_nome_b<<" "<<m_nome_c<<" "<<m_nome_d<<endl;
}

void Ampop::associaMatriz(Matriz *matriz)
{
	m_matriz = matriz;
	m_a = matriz->adVariavel(m_nome_a);
	m_b = matriz->adVariavel(m_nome_b);
	m_c = matriz->adVariavel(m_nome_c);
	m_d = matriz->adVariavel(m_nome_d);

	string nomeVar = "j";
	nomeVar.append(m_nome);
	m_x = matriz->adVariavel(nomeVar);
}

void Ampop::estampaPO()
{
	m_matriz->m_elemento[m_a][m_x] +=  1;
	m_matriz->m_elemento[m_b][m_x] += -1;

	m_matriz->m_elemento[m_x][m_c] += -1;
	m_matriz->m_elemento[m_x][m_d] +=  1;
}

void Ampop::estampaBE(double tempo, double passo)
{
	estampaPO();
}

void Ampop::estampaGEAR(double tempo, double passo)
{
	estampaPO();
}
