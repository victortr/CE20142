#ifndef ACOPLAMENTO_H
#define ACOPLAMENTO_H

#include <fstream>
#include <string>
#include "Elemento.h"
#include "Indutor.h"

class Acoplamento : public Elemento
{
    double m_k;
    std::string m_l1;
    std::string m_l2;
    int l1x, l2x;
    double l1l, l2l;

		
public:
    Acoplamento(std::ifstream &arq);

	//*****METODOS VIRTUAIS*****
    void associaMatriz(Matriz *matriz);
    void estampaPO();
	void estampaBE(double tempo, double passo);
	void estampaGEAR(double tempo, double passo);
	//void estampaTRAP(Matriz *matriz,);
};

#endif
