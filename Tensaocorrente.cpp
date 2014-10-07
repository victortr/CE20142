//Tensaocorrente.cpp

#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include "Tensaocorrente.h"

using namespace std;

//H<nome> <nóV+> <nóV-> <nói+> <nói-> <Rm>
Tensaocorrente::Tensaocorrente(ifstream &arq)
{
	
	m_erro = false;
	int i = 0;
	while(arq.peek() != '\n')
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
			case 5: arq >> m_Rm;		break;
			default:arq >> m_ignora;		break;
		}
		i++;
	}
	arq.ignore();
	if(i!=6)
	{
		cout<< m_nome <<": Numero de parametros errado " << i << "/6"<<endl;
		arq.close();
		m_erro = true;
	}
	cout<<m_nome<<":"<<m_nome_a<<" "<<m_nome_b
		<<" "<<m_nome_c
		<<" "<<m_nome_d
		<<" "<<m_Rm<<endl;
}

void Tensaocorrente::associaMatriz(Matriz *matriz)
{
	m_matriz = matriz;
	m_a = matriz->adVariavel(m_nome_a);
	m_b = matriz->adVariavel(m_nome_b);
	m_c = matriz->adVariavel(m_nome_c);
	m_d = matriz->adVariavel(m_nome_d);

	
	//char nome[8];
	//sprintf(nome,"j%0.3d%0.3d",m_a,m_b);
	
	string nomeVar = "j";
	nomeVar.append(m_nome);
	m_x = matriz->adVariavel(nomeVar);

	nomeVar = "jy";
	nomeVar.append(m_nome);
	m_y = matriz->adVariavel(nomeVar);
}

void Tensaocorrente::estampaPO()
{
	estampaPrimH(m_a,m_b,m_c,m_d,m_x,m_y,m_Rm);
}

void Tensaocorrente::estampaBE(double tempo, double passo)
{
	estampaPrimH(m_a,m_b,m_c,m_d,m_x,m_y,m_Rm);
}

void Tensaocorrente::estampaGEAR(double tempo, double passo)
{
	estampaPrimH(m_a,m_b,m_c,m_d,m_x,m_y,m_Rm);
}
