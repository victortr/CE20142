#ifndef ACOPLAMENTO_H
#define ACOPLAMENTO_H

#include <fstream>
#include <string>
#include "Elemento.h"
#include "Indutor.h"

//C<nome> <n�1> <n�2> <Capacit�ncia>
class Acoplamento : public Elemento
{
	double m_C;
		
public:
	Acoplamento(QString nome, Indutor* l1, Indutor* l2, double m);

	//*****METODOS VIRTUAIS*****
	void estampaPO();
	void estampaBE(double tempo, double passo);
	void estampaGEAR(double tempo, double passo);
	//void estampaTRAP(Matriz *matriz,);
};

#endif