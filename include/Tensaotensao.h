#ifndef TENSAOTENSAO_H
#define TENSAOTENSAO_H



#include "Elemento.h"
#include "Matriz.h"
//Corrente controlada por corrente
class Tensaotensao : public Elemento
{
    double m_Av[8];
	
public:
	Tensaotensao(std::ifstream &arq);
	

	//*****METODOS VIRTUAIS*****
	void associaMatriz(Matriz *matriz);
	void estampaPO();
	void estampaBE(double tempo, double passo);
	void estampaGEAR(double tempo, double passo);
	//void estampaTRAP(Matriz *matriz,);
};


#endif
