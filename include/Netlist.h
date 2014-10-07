#ifndef NETLIST_H
#define NETLIST_H

#include <list>
#include <fstream>
#include "const.h"
#include "Elemento.h"


enum Metodo 
{
	GEAR,
	BE,
	TRAP
};

class Netlist
{	
	
	std::list<Elemento*> m_elementos;
	Matriz m_matriz;

	double m_t,m_passo;
	int m_passosInternos;

	Metodo m_metodo;

public:

	Netlist();
	bool carregar(std::ifstream &arq);

	void newtonRaphson(bool po = false, double t = 0, double passo = 0);

	void calculaPO();

	void analiseTempo(std::ofstream &arq);

	void carregarParametros(std::ifstream &arq);

};



#endif

