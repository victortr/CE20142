#ifndef MATRIZ_H
#define MATRIZ_H

#include <list>
#include <string>
#include "const.h"
/* 
 * Define a classe Matriz, que representa um sistema na forma matricial.
 */


class Matriz 
{
	std::string m_variavel[MAX_NOS+1];

	std::list<double*> m_solAnteriores;

	void setSolucao(double *sol);

public:

	double m_elemento[MAX_NOS+1][MAX_NOS+2];
	int m_numVariaveis;

	Matriz();

	~Matriz();
	
	void gravaSolucao();

	void copiaSolucao(int i,double *saida);

	bool resolver();

	void mostrar();

	void mostrarSolucao();

	/*getSolucao(0) retorna valor da ultima iteracao de NR.
	 os outros indices representam solucoes anteriores.
	 quanto menor i mais atual a solucao*/
	double *getSolucao(int i);

	std::string getNomeVariavel(int i);

	void resetSolucao();

	int adVariavel(std::string nome);

	void reset();
};

#endif