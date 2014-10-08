#ifndef CORRENTECORRENTE_H
#define CORRENTECORRENTE_H

#include "Elemento.h"
#include "Matriz.h"
//Corrente controlada por corrente
class Correntecorrente : public Elemento
{
    double m_Ai[8];
	
public:
	Correntecorrente(std::ifstream &arq);
	

	//*****METODOS VIRTUAIS*****
	void associaMatriz(Matriz *matriz);
	void estampaPO();
	void estampaBE(double tempo, double passo);
	void estampaGEAR(double tempo, double passo);
	//void estampaTRAP(Matriz *matriz,);
};

#endif
