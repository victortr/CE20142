#include <iostream>
#include "Elemento.h"
#include "Matriz.h"
/* 
*	Define a classe que represanta um elemento do netlist
*/

Elemento::~Elemento()
{
}

//resistor
void Elemento::estampaPrimR(int a,int b, double R)
{
	m_matriz->m_elemento[a][a] +=  1/R;
	m_matriz->m_elemento[b][b] +=  1/R;
	m_matriz->m_elemento[a][b] += -1/R;
	m_matriz->m_elemento[b][a] += -1/R;
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