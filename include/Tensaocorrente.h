#ifndef TENSAOCORRENTE_H
#define TENSAOCORRENTE_H


#include "Elemento.h"
#include "Matriz.h"
//Corrente controlada por corrente
class Tensaocorrente : public Elemento
{
	double m_Rm;
	
public:
	Tensaocorrente(std::ifstream &arq);
	

	//*****METODOS VIRTUAIS*****
	void associaMatriz(Matriz *matriz);
	void estampaPO();
	void estampaBE(double tempo, double passo);
	void estampaGEAR(double tempo, double passo);
	//void estampaTRAP(Matriz *matriz,);
};


#endif