//Tensaocorrente.cpp

#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include "Tensaotensao.h"

using namespace std;

//E<nome> <nóV+> <nóV-> <nóv+> <nóv-> <Av>
Tensaotensao::Tensaotensao(ifstream &arq)
{
	m_erro = false;
	int i = 0;
    for(int k=0; k<8; k++)
    {
        m_Av[k] = 0;
    }
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
            case 5: arq >> m_Av[0];		break;
            case 6: arq >> m_Av[1];		break;
            case 7: arq >> m_Av[2];		break;
            case 8: arq >> m_Av[3];		break;
            case 9: arq >> m_Av[4];		break;
            case 10: arq >> m_Av[5];		break;
            case 11: arq >> m_Av[6];		break;
            case 12: arq >> m_Av[7];		break;
            default:arq >> m_ignora;		break;
		}
		i++;
	}
	arq.ignore();
    if(i>13)
	{
		cout<< m_nome <<": Numero de parametros errado " << i << "/6"<<endl;
		arq.close();
		m_erro = true;
	}
	cout<<m_nome<<":"<<m_nome_a<<" "<<m_nome_b
		<<" "<<m_nome_c
		<<" "<<m_nome_d
        <<" ";
    for (int i=0; i<8; i++)
    {
        cout << m_Av[i] << " ";
    }
    cout << endl;
}

void Tensaotensao::associaMatriz(Matriz *matriz)
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
	
}

void Tensaotensao::estampaPO()
{
	estampaPrimE(m_a,m_b,m_c,m_d,m_x,m_Av);
}

void Tensaotensao::estampaBE(double tempo, double passo)
{
	estampaPrimE(m_a,m_b,m_c,m_d,m_x,m_Av);
}

void Tensaotensao::estampaGEAR(double tempo, double passo)
{
	estampaPrimE(m_a,m_b,m_c,m_d,m_x,m_Av);
}
