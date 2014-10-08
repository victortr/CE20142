#include <iostream>
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
void Elemento::estampaPrimE(int a, int b, int c, int d, int x, double Av[], double R_serie)
{
    if (Av[1] == 0 && Av[2] == 0 && Av[3] == 0 && Av[4] == 0 && Av[5] == 0 && Av[6] == 0 && Av[7] == 0)
    {
	m_matriz->m_elemento[a][x] +=  1;
	m_matriz->m_elemento[b][x] += -1;

	m_matriz->m_elemento[x][a] += -1;
	m_matriz->m_elemento[x][b] +=  1;

    m_matriz->m_elemento[x][c] +=  Av[0];
    m_matriz->m_elemento[x][d] += -Av[0];

	m_matriz->m_elemento[x][x] += R_serie;
    }
    else
    {
        double A0 = 0;
        double V0 = 0;
        double *solucao = m_matriz->getSolucao(0);

        A0 += Av[1]*(solucao[c]-solucao[d]);
        V0 += Av[0] + Av[1]*(solucao[c]-solucao[d]);

        for(int i=2; i<8; i++)
        {
            A0 += Av[i]*i*pow(solucao[c] - solucao[d], i-1);
            V0 += Av[i]*pow(solucao[c] - solucao[d], i);
        }

     V0 -= A0*(solucao[c] - solucao[d]);

     m_matriz->m_elemento[a][x] +=  1;
     m_matriz->m_elemento[b][x] += -1;

     m_matriz->m_elemento[x][a] += -1;
     m_matriz->m_elemento[x][b] +=  1;

     m_matriz->m_elemento[x][c] +=  A0;
     m_matriz->m_elemento[x][d] += -A0;

     m_matriz->m_elemento[x][m_matriz->m_numVariaveis+1] +=   -V0;
     m_matriz->m_elemento[x][x] += R_serie;

    }
}
	
//fonte de corrente controlada a corrente
void Elemento::estampaPrimF(int a, int b, int c, int d, int x, double Ai[])
{
    if (Ai[1] == 0 && Ai[2] == 0 && Ai[3] == 0
            && Ai[4] == 0 && Ai[5] == 0 && Ai[6] == 0 && Ai[7] == 0)
    {
    m_matriz->m_elemento[a][x] +=  Ai[0];
    m_matriz->m_elemento[b][x] += -Ai[0];

	m_matriz->m_elemento[c][x] +=  1;
	m_matriz->m_elemento[d][x] += -1;

    m_matriz->m_elemento[x][c] += -1;
    m_matriz->m_elemento[x][d] +=  1;
    }
    else
    {
        double B0 = 0;
        double I0 = 0;
        double *solucao = m_matriz->getSolucao(0);


        B0 += Ai[1]*(solucao[x]);
        I0 += Ai[0] + Ai[1]*(solucao[x]);
        for (int i = 2; i < 8; ++i)
        {
              B0 += Ai[i]*i*pow(solucao[x], i-1);
              I0 += Ai[i]*pow(solucao[x], i);
        }

        I0 -= B0*(solucao[x]);

        m_matriz->m_elemento[a][x] +=  B0;
        m_matriz->m_elemento[b][x] += -B0;

        m_matriz->m_elemento[c][x] +=  1;
        m_matriz->m_elemento[d][x] += -1;

        m_matriz->m_elemento[x][c] += -1;
        m_matriz->m_elemento[x][d] +=  1;

        m_matriz->m_elemento[a][m_matriz->m_numVariaveis+1] +=   -I0;
        m_matriz->m_elemento[b][m_matriz->m_numVariaveis+1] +=    I0;

    }
}
	
//fonte de corrente controlada a tensao
void Elemento::estampaPrimG(int a, int b, int c, int d, double Gm[])
{
    if (Gm[1] == 0 && Gm[2] == 0 && Gm[3] == 0 && Gm[4] == 0 && Gm[5] == 0 && Gm[6] == 0 && Gm[7] == 0)
    {
        m_matriz->mostrar();
    m_matriz->m_elemento[a][c] +=  Gm[0];
    m_matriz->m_elemento[b][d] +=  Gm[0];
    m_matriz->m_elemento[a][d] += -Gm[0];
    m_matriz->m_elemento[b][c] += -Gm[0];
    cout << endl << endl;
    m_matriz->mostrar();
    }

    else
    {
        double Gm0 = 0;
        double I0  = 2;
        double *solucao = m_matriz->getSolucao(0);

        Gm0 += Gm[1]*(solucao[c]-solucao[d]);
        I0 += Gm[0] + Gm[1]*(solucao[c]-solucao[d]);
          for (int i = 2; i < 8; ++i)
           {
              Gm0 += Gm[i]*i*pow(solucao[c] - solucao[d], i-1);
              I0 += Gm[i]*pow(solucao[c] - solucao[d], i);
           }

      I0 -= Gm0*(solucao[c] - solucao[d]);

      m_matriz->m_elemento[a][c] +=  Gm0;
      m_matriz->m_elemento[b][d] +=  Gm0;
      m_matriz->m_elemento[a][d] += -Gm0;
      m_matriz->m_elemento[b][c] += -Gm0;

      m_matriz->m_elemento[a][m_matriz->m_numVariaveis+1] +=   -I0;
      m_matriz->m_elemento[b][m_matriz->m_numVariaveis+1] +=    I0;

    }
}

//fonte de tensao controlada a corrente
void Elemento::estampaPrimH(int a, int b, int c, int d, int x, int y, double Rm[])
{
    if (Rm[1] == 0 && Rm[2] == 0 && Rm[3] == 0 && Rm[4] == 0 && Rm[5] == 0 && Rm[6] == 0 && Rm[7] == 0)
    {
	m_matriz->m_elemento[a][x] +=  1;
	m_matriz->m_elemento[b][x] += -1;

	m_matriz->m_elemento[c][y] +=  1;
	m_matriz->m_elemento[d][y] += -1;

	m_matriz->m_elemento[x][a] += -1;
	m_matriz->m_elemento[x][b] +=  1;

	m_matriz->m_elemento[y][c] += -1;
	m_matriz->m_elemento[y][d] +=  1;

    m_matriz->m_elemento[x][y] +=  Rm[0];

    }

    else
    {
        double Rm0 = 0;
        double V0  = 0;
        double *solucao = m_matriz->getSolucao(0);

        Rm0 += Rm[1]*(solucao[y]);
        V0 += Rm[0] + Rm[1]*(solucao[y]);
        for (int i = 2; i < 8; ++i)
        {
              Rm0 += Rm[i]*i*pow(solucao[y], i-1);
              V0 += Rm[i]*pow(solucao[y], i);
        }

      V0 -= Rm0*(solucao[y]);

      m_matriz->m_elemento[a][x] +=  1;
      m_matriz->m_elemento[b][x] += -1;

      m_matriz->m_elemento[c][y] +=  1;
      m_matriz->m_elemento[d][y] += -1;

      m_matriz->m_elemento[x][a] += -1;
      m_matriz->m_elemento[x][b] +=  1;

      m_matriz->m_elemento[y][c] += -1;
      m_matriz->m_elemento[y][d] +=  1;

      m_matriz->m_elemento[x][y] +=  Rm0;
      m_matriz->m_elemento[x][m_matriz->m_numVariaveis+1] +=   -V0;

    }
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
