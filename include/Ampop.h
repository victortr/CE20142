#ifndef AMPOP_H
#define AMPOP_H

#include <fstream>
#include <string>
#include "Elemento.h"

//O<nome> <no1> <no2> <vi1> <vi2>
class Ampop : public Elemento
{
	double m_C;
		
public:
	Ampop(std::ifstream &arq);

	//*****METODOS VIRTUAIS*****
	void associaMatriz(Matriz *matriz);
	void estampaPO();
	void estampaBE(double tempo, double passo);
	void estampaGEAR(double tempo, double passo);
	//void estampaTRAP(Matriz *matriz,);
};

#endif