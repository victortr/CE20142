//Correntecorrente.cpp

#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include "Correntecorrente.h"

using namespace std;

//F<nome> <nóI+> <nóI-> <nói+> <nói-> <Ai>
Correntecorrente::Correntecorrente(ifstream &arq)
{
	m_erro = false;
	int i = 0;

    for(int k=0; k<8; k++)
    {
        m_Ai[k] = 0;
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
            case 5: arq >> m_Ai[0];		break;
            case 6: arq >> m_Ai[1];		break;
            case 7: arq >> m_Ai[2];		break;
            case 8: arq >> m_Ai[3];		break;
            case 9: arq >> m_Ai[4];		break;
            case 10: arq >> m_Ai[5];		break;
            case 11: arq >> m_Ai[6];		break;
            case 12: arq >> m_Ai[7];		break;
            default:arq >> m_ignora;		break;
		}
		i++;
	}
	arq.ignore();
    if(i > 13)
	{
		cout<< m_nome <<": Numero de parametros errado " << i << "/6"<<endl;
		arq.close();
		m_erro = true;
	}
    cout<<m_nome<<": "<<m_nome_a<<" "<<m_nome_b
		<<" "<<m_nome_c
		<<" "<<m_nome_d
        <<" ";
    for (int i=0; i<8; i++)
    {
        cout << m_Ai[i] << " ";
    }
    cout <<endl;

}

void Correntecorrente::associaMatriz(Matriz *matriz)
{
	m_matriz = matriz;
	m_a = matriz->adVariavel(m_nome_a);
	m_b = matriz->adVariavel(m_nome_b);
	m_c = matriz->adVariavel(m_nome_c);
	m_d = matriz->adVariavel(m_nome_d);

	//char nome[8];
	//sprintf(nome,"j%0.3d%0.3d",m_c,m_d);
	
	string nomeVar = "j";
	nomeVar.append(m_nome);
	m_x = matriz->adVariavel(nomeVar);
}

void Correntecorrente::estampaPO()
{
	estampaPrimF(m_a,m_b,m_c,m_d,m_x,m_Ai);
}

void Correntecorrente::estampaBE(double tempo, double passo)
{
    estampaPrimF(m_a,m_b,m_c,m_d,m_x, m_Ai);
}

void Correntecorrente::estampaGEAR(double tempo, double passo)
{
	estampaPrimF(m_a,m_b,m_c,m_d,m_x,m_Ai);
}
