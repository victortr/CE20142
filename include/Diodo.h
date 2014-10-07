#ifndef DIODO_H
#define DIODO_H

#include "Elemento.h"


class Diodo : public Elemento
{
	double m_Is,m_Vt;
	
public:
	Diodo(std::ifstream &arq);

	//criado para o transistor MOS ( ou outros diodos parasitas)
	Diodo(int anodo,int catodo, Matriz *matriz);
	

	//*****METODOS VIRTUAIS*****
	void associaMatriz(Matriz *matriz);
	void estampaPO();
	void estampaBE(double tempo, double passo);
	void estampaGEAR(double tempo, double passo);
	//void estampaTRAP(Matriz *matriz,);
};

#endif