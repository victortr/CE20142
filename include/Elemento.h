#ifndef ELEMENTO_H
#define ELEMENTO_H


#include <list>
#include <fstream>
#include <string>
#include "const.h"
#include "matriz.h"
/* 
*	Define a classe que represanta um elemento do netlist
*/

struct s_indutores {
    std::string m_nome;
    int m_no_x;
    double m_l;
    };

class Elemento
{
protected:
	std::string m_nome;
	
	int m_a,m_b,m_c,m_d,m_x,m_y;
	std::string m_nome_a,m_nome_b,m_nome_c,m_nome_d,m_nome_x,m_nome_y;

	bool m_erro;
	Matriz *m_matriz;

	std::string m_ignora;

public:

	~Elemento();

	//resistor
    void estampaPrimR(int a, int b, double R[8]);

	//fonte tensao controlada a tensao
	void estampaPrimE(int a, int b, int c, int d, int x, double Av, double R_serie = 0);
	
	//fonte de corrente controlada a corrente
	void estampaPrimF(int a, int b, int c, int d, int x, double Ai);
	
	//fonte de corrente controlada a tensao
	void estampaPrimG(int a, int b, int c, int d, double Gm);
	
	//fonte de tensao controlada a corrente
	void estampaPrimH(int a, int b, int c, int d, int x, int y, double Rm);

	//fonte de corrente
	void estampaPrimI(int a, int b, double I);
	
	//fonte de Tensao
	void estampaPrimV(int a, int b, int x, double V, double R_serie = 0);

    //Acoplamento
    void estampaPrimK(int x2, int x1, double V1, double V2, double M);

	//verifica se o elemento foi carregado corretamente
	bool getErro();
	
	//*****METODOS VIRTUAIS*****
	//Elemento(std::ifstream &arq);
	virtual void associaMatriz(Matriz *matriz) = 0;
	virtual void estampaPO() = 0;
	virtual void estampaBE(double tempo, double passo) = 0;
	virtual void estampaGEAR(double tempo, double passo) = 0;
	//virtual void estampaTRAP(Matriz *matriz,) = 0;
	
};



#endif
