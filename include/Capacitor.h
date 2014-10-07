#ifndef CAPACITOR_H
#define CAPACITOR_H

#include <fstream>
#include <string>
#include "Elemento.h"

//C<nome> <nó1> <nó2> <Capacitância>
class Capacitor : public Elemento
{
	double m_C;
		
public:
	Capacitor(std::ifstream &arq);

	//Criado para o transitor MOS (ou como outros capacitores parasitas)
	Capacitor(int a, int b, double C, Matriz *matriz);

	//*****METODOS VIRTUAIS*****
	void associaMatriz(Matriz *matriz);
	void estampaPO();
	void estampaBE(double tempo, double passo);
	void estampaGEAR(double tempo, double passo);
	//void estampaTRAP(Matriz *matriz,);
};

#endif