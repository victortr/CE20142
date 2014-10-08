﻿#include <iostream>
#include "Elemento.h"
#include "Matriz.h"
#include <math.h>
/* 
*	Define a classe que represanta um elemento do netlist
*/
using namespace std;

Elemento::~Elemento()
{
}

//resistor
void Elemento::estampaPrimR(int a, int b, double R[])
{
    if (R[1] == 0 && R[2] == 0 && R[3] == 0 && R[4] == 0 && R[5] == 0 && R[6] == 0 && R[7] == 0)
	{
	m_matriz->m_elemento[a][a] +=  1/R[0];
	m_matriz->m_elemento[b][b] +=  1/R[0];
	m_matriz->m_elemento[a][b] += -1/R[0];
	m_matriz->m_elemento[b][a] += -1/R[0];
	}

	else
	{
        double G0 = 0;
        double I0 = 0;
        double *solucao = m_matriz->getSolucao(0);

        for(int i = 1; i<4; i++)
        {
            std::cout << solucao[i] << std::endl;
        }

//        std::cout << std::endl << std::endl;
//        cout << "solucao [" << a << "]" << endl;
//        cout << solucao[a] << endl;
//        cout << "solucao [" << b << "]" << endl;
//        cout << solucao[b] << endl;

        for (int i = 0; i < 8; ++i)
		{
              G0 += R[i]*i*pow(solucao[a] - solucao[b], i-1);
              I0 += R[i]*pow(solucao[a] - solucao[b], i);
		}

      I0 -= G0*(solucao[a] - solucao[b]);

        std::cout << "G0 :" << G0 << std::endl<< "I0 :" << I0 << std::endl << std::endl;

	m_matriz->m_elemento[a][a] +=  G0;
	m_matriz->m_elemento[b][b] +=  G0;
	m_matriz->m_elemento[a][b] += -G0;
	m_matriz->m_elemento[b][a] += -G0;

    m_matriz->m_elemento[a][m_matriz->m_numVariaveis+1] +=   -I0;
    m_matriz->m_elemento[b][m_matriz->m_numVariaveis+1] +=    I0;

	}
}

//fonte tensao controlada a tensao
void Elemento::estampaPrimE(int a, int b, int c, int d, int x, double Av, double R_serie)
{
	m_matriz->m_elemento[a][x] +=  1;
	m_matriz->m_elemento[b][x] += -1;

	m_matriz->m_elemento[x][a] += -1;
	m_matriz->m_elemento[x][b] +=  1;

	m_matriz->m_elemento[x][c] +=  Av;
	m_matriz->m_elemento[x][d] += -Av;

	m_matriz->m_elemento[x][x] += R_serie;
}
	
//fonte de corrente controlada a corrente
void Elemento::estampaPrimF(int a, int b, int c, int d, int x, double Ai)
{
	m_matriz->m_elemento[a][x] +=  Ai;
	m_matriz->m_elemento[b][x] += -Ai;

	m_matriz->m_elemento[c][x] +=  1;
	m_matriz->m_elemento[d][x] += -1;

	m_matriz->m_elemento[x][c] +=  1;
	m_matriz->m_elemento[x][d] += -1;
}
	
//fonte de corrente controlada a tensao
void Elemento::estampaPrimG(int a, int b, int c, int d, double Gm)
{
	m_matriz->m_elemento[a][c] +=  Gm;
	m_matriz->m_elemento[b][d] +=  Gm;
	m_matriz->m_elemento[a][d] += -Gm;
	m_matriz->m_elemento[b][c] += -Gm;
}
	
//fonte de tensao controlada a corrente
void Elemento::estampaPrimH(int a, int b, int c, int d, int x, int y, double Rm)
{
	m_matriz->m_elemento[a][x] +=  1;
	m_matriz->m_elemento[b][x] += -1;

	m_matriz->m_elemento[c][y] +=  1;
	m_matriz->m_elemento[d][y] += -1;

	m_matriz->m_elemento[x][a] += -1;
	m_matriz->m_elemento[x][b] +=  1;

	m_matriz->m_elemento[y][c] += -1;
	m_matriz->m_elemento[y][d] +=  1;

	m_matriz->m_elemento[x][y] +=  Rm;
}
	
//fonte de tensao
void Elemento::estampaPrimI(int a, int b, double I)
{
	m_matriz->m_elemento[a][m_matriz->m_numVariaveis+1] += -I;
	m_matriz->m_elemento[b][m_matriz->m_numVariaveis+1] +=  I;
}
	
//fonte de corrente
void Elemento::estampaPrimV(int a, int b, int x, double V, double R_serie)
{
	m_matriz->m_elemento[a][x] +=  1;
	m_matriz->m_elemento[b][x] += -1;

	m_matriz->m_elemento[x][a] += -1;
	m_matriz->m_elemento[x][b] +=  1;

	m_matriz->m_elemento[x][x] += R_serie;
	m_matriz->m_elemento[x][m_matriz->m_numVariaveis+1] += -V;
}

bool Elemento::getErro()
{
	return m_erro;
}
