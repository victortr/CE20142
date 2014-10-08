// MATRIZ.C

#include <stdlib.h>
#include <stdio.h>
#include <cmath>
#include <ctime>
#include <string.h>
#include "matriz.h"

Matriz::Matriz()
{
	int i,j;
	for(i=0;i<MAX_NOS+1;i++)
		for(j=0;j<MAX_NOS+2;j++)
			m_elemento[i][j] = 0;
	m_numVariaveis = 0;
}

Matriz::~Matriz()
{
}



bool Matriz::resolver()
{
  int i,j,l, a;
  double t, p;
  double *sol;

  for (i=1; i<=m_numVariaveis; i++) {
    t=0.0;
    a=i;
    for (l=i; l<=m_numVariaveis; l++) {
      if (fabs(m_elemento[l][i])>fabs(t)) {
	a=l;
	t=m_elemento[l][i];
      }
    }
    if (i!=a) {
      for (l=1; l<=m_numVariaveis+1; l++) {
	p= m_elemento[i][l];
	m_elemento[i][l]=m_elemento[a][l];
	m_elemento[a][l]=p;
      }
    }
    if (fabs(t)<TOLG) {
//		printf("Sistema singular.\n");
		return false;
    }
    for (j=m_numVariaveis+1; j>i; j--) {  /* Ponha j>0 em vez de j>i para melhor visualizacao */
      m_elemento[i][j] /= t;
      p=m_elemento[i][j];
      for (l=1; l<=m_numVariaveis; l++) {
	if (l!=i)
	  m_elemento[l][j]-=m_elemento[l][i]*p;
      }
    }
  }
  
  sol = new double[m_numVariaveis+1];

  sol[0] = 0;
  for(i=1; i <= m_numVariaveis; i++)
  {
		sol[i] = m_elemento[i][m_numVariaveis+1];
		//printf("sol: %g\n",sol[i]);
  }
  setSolucao(sol);
  return true;
}

void Matriz::setSolucao(double *sol)
{
	if(m_solAnteriores.size() >0)
	{
		delete m_solAnteriores.front();
		m_solAnteriores.pop_front();
	}
	
	m_solAnteriores.push_front(sol);
}

void Matriz::gravaSolucao()
{
	double *sol = new double [m_numVariaveis+1];
	
	copiaSolucao(0,sol);
	
	m_solAnteriores.push_front(sol);
	
	if(m_solAnteriores.size() > MAX_ORDEM_GEAR+1)
	{
		delete m_solAnteriores.back();
		m_solAnteriores.pop_back();
	}

	//resetSolucao();
}

void Matriz::mostrar()
{
	int k,j;
	for (k=1; k<=m_numVariaveis; k++) {
      for (j=1; j<=m_numVariaveis+1; j++)
        if (m_elemento[k][j]!=0) printf("%+3.1f ",m_elemento[k][j]);
        else printf(" ... ");
      printf("\n");
    }
}


void Matriz::mostrarSolucao()
{
	int i;
	int nv = m_numVariaveis;
	
	for (i=1; i <= nv; i++) {
		printf("%s: %g\n",m_variavel[i].c_str(),m_elemento[i][nv+1]);
	}
}

int Matriz::adVariavel(std::string nome)
{
	int i,nv;
	bool achou;

	nv = m_numVariaveis;
	i=1; achou=0;
	
	//NO DE REFERENCIA
	if(nome == "0")
		return 0;
	
	while (!achou && i<= nv)
	{
		achou = (nome == m_variavel[i]);
		if (!achou)
			i++;
	}
	if (!achou) {
		if (nv==MAX_NOS) {
			printf("Maximo de variaves excedido.\n");
			exit(-1);
		}
		m_numVariaveis++;
		m_variavel[m_numVariaveis] = nome;
		return m_numVariaveis;
	}
	else {
		return i; /* no ja conhecido */
	}
}


void Matriz::copiaSolucao(int i,double *saida)
{
	double *sol = getSolucao(i);
	int count;

	for(count = 0; count<=m_numVariaveis; count++)
	{
		saida[count] = sol[count];
	}

}

double* Matriz::getSolucao(int i)
{
	std::list<double*>::iterator itr;
	int cont;

	cont=0;
	for(itr = m_solAnteriores.begin(); itr != m_solAnteriores.end(); itr++)
	{
		if(i==cont)
			return (*itr);
		cont++;
	}
	return NULL;
}

std::string Matriz::getNomeVariavel(int i)
{
	return m_variavel[i]; 
}

void Matriz::resetSolucao()
{
	int i;
	double *sol;
	
	if(m_solAnteriores.size()==0)
	{
		sol = new double [m_numVariaveis+1];
		m_solAnteriores.push_front(sol);
		//for(i=0; i <= m_numVariaveis; i++)
		//sol[i] = 0;
	}
	//else
	//{
		sol = m_solAnteriores.front();
		sol[0]  = 0;
		for(i=1; i <= m_numVariaveis; i++)
			sol[i] = (rand()%100)/1.0;
	//}
}

void Matriz::reset()
{
	int i,j;
	for(i=0;i<MAX_NOS+1;i++)
		for(j=0;j<MAX_NOS+2;j++)
			m_elemento[i][j] = 0;
}
