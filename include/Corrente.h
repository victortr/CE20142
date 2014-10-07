#ifndef CORRENTE_H
#define CORRENTE_H

#include <fstream>
#include <string>
#include "Elemento.h"


//DC <valor> (para fonte DC)
//SIN (<nivel contínuo> <amplitude> <frequencia (Hz)> <atraso> <fator de atenuação> <ângulo> <número de ciclos>)
//PULSE (<amplitude 1> <amplitude 2> <atraso> <tempo de subida> <tempo de descida> <tempo ligada> <período> <número de ciclos>)

class Corrente : public Elemento
{
	double m_DC;
	double m_amplitude,m_amplitude2;
	double m_freq;
	double m_atraso;
	double m_atenuacao;
	double m_angulo;
	double m_t_subida;
	double m_t_descida;
	double m_t_ligada;
	double m_periodo;
	double m_ciclos;
	std::string m_tipo;

	void carregaParamDC(std::ifstream &arq);
	void carregaParamSIN(std::ifstream &arq);
	void carregaParamPULSE(std::ifstream &arq);
		
public:
	Corrente(std::ifstream &arq);

	double calcValor(double t);

	//*****METODOS VIRTUAIS*****
	void associaMatriz(Matriz *matriz);
	void estampaPO();
	void estampaBE(double tempo, double passo);
	void estampaGEAR(double tempo, double passo);
	//void estampaTRAP(Matriz *matriz,);
};

#endif