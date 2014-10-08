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

    for(int k=0; k<8; k++)
    {
        m_R[k] = 0;
    }

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
            case 0: arq >> m_nome;      	break;
            case 1: arq >> m_nome_a;        break;
            case 2: arq >> m_nome_b;        break;
            case 3: arq >> m_R[0]; m_R[1] = 1;          break;
 //           case 4: arq >> m_R[1];          break;


//            if (arq >> m_R[1])
//            {
//                if (arq >> m_R[2])
//                {
//
//                }
//                else {m_R[2] =0;}
//            }
//            else {m_R[1] = 0;}
//                            m_R[1] = 1;
//                            m_R[2] = 0.0;
//                            m_R[3] = 0.0;
//                            m_R[4] = 0.0;
//                            m_R[5] = 0.0;
//                            m_R[6] = 0.0;
//                            m_R[7] = 0.0;
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

    cout<<m_nome<<": "<<m_nome_a<<" "<<m_nome_b<<" ";

    for (int i=0; i<8; i++)
    {
        cout << m_R[i] << " ";
    }
    cout << endl;
}

void Resistor::associaMatriz(Matriz *matriz)
{
	m_matriz = matriz;
	m_a = matriz->adVariavel(m_nome_a);
	m_b = matriz->adVariavel(m_nome_b);
}

void Resistor::estampaPO()
{
    estampaPrimR(m_a,m_b,m_R);
}

void Resistor::estampaBE(double tempo, double passo)
{
    estampaPrimR(m_a,m_b,m_R);
}

void Resistor::estampaGEAR(double tempo, double passo)
{
    estampaPrimR(m_a,m_b,m_R);
}
