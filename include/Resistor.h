#ifndef RESISTOR_H
#define RESISTOR_H

#include "Elemento.h"


class Resistor : public Elemento
{
	double m_R[8];
	
public:
	Resistor(std::ifstream &arq);
	

	//*****METODOS VIRTUAIS*****
	void associaMatriz(Matriz *matriz);
	void estampaPO();
	void estampaBE(double tempo, double passo);
	void estampaGEAR(double tempo, double passo);
	//void estampaTRAP(Matriz *matriz,);
};


#endif