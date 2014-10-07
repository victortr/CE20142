#ifndef MOS_H
#define MOS_H

#include <fstream>
#include <string>
#include "Elemento.h"


//M<nome> <no d> <no g> <no s> <no b> NMOS|PMOS [L=<comprimento> W=<largura>] [<K> <Vt0> <lamb> <gama> <fi>]
class Mos : public Elemento
{
	double m_L,m_W;
	double m_K;
	double m_Vt0;
	double m_lamb;
	double m_gama;
	double m_fi;

	std::string m_tipo;
	
public:
	Mos(std::ifstream &arq);

	double calcId(double Vgs,double Vds,double Vbs);

	double calcGm(double Vgs,double Vds,double Vbs);

	double calcGmb(double Vgs,double Vds,double Vbs);

	double calcGds(double Vgs,double Vds,double Vbs);

	double calcVt(double Vbs);

	double calcCgs();

	void estampaBase(double tempo, double passo);

	//*****METODOS VIRTUAIS*****
	void associaMatriz(Matriz *matriz);
	void estampaPO();
	void estampaBE(double tempo, double passo);
	void estampaGEAR(double tempo, double passo);
	//void estampaTRAP(Matriz *matriz,);
};

#endif