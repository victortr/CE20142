#ifndef CORRENTETENSAO_H
#define CORRENTETENSAO_H

#include "Elemento.h"
#include "Matriz.h"
//Corrente controlada por corrente
class Correntetensao : public Elemento
{
    double m_Gm[8];
	
public:
	Correntetensao(std::ifstream &arq);
	

	//*****METODOS VIRTUAIS*****
	void associaMatriz(Matriz *matriz);
	void estampaPO();
	void estampaBE(double tempo, double passo);
	void estampaGEAR(double tempo, double passo);
	//void estampaTRAP(Matriz *matriz,);
};

#endif
