/**
 * Trabalho de Circuitos Eletricos II - 2009/2
 * Alexandre Faria de Melo
 */

#include <iostream>
#include <fstream>
#include <string>
#include "Matriz.h"
#include "Netlist.h"

int main(int argc, char **argv)
{
	using namespace std;

	/*
	Matriz matriz;

	matriz.m_elemento[1][1] = 1;
	matriz.m_elemento[1][2] = 1;
	matriz.m_elemento[1][3] = 3;

	matriz.m_elemento[2][1] = 1;
	matriz.m_elemento[2][2] = -1;
	matriz.m_elemento[2][3] = 1;

	matriz.adVariavel("x");
	matriz.adVariavel("y");

	matriz.resolver();
	
	//matriz.gravaSolucao();
	matriz.mostrarSolucao();

	double *sol = matriz.getSolucao(0);
	for(int i = 0;i<=matriz.m_numVariaveis;i++)
	{
		cout<<sol[i]<<endl;
	}

	sol = new double[matriz.m_numVariaveis+1];

	matriz.gravaSolucao();
	matriz.copiaSolucao(1,sol);

	//sol = matriz.getSolucao(0);
	for(i = 0;i<=matriz.m_numVariaveis;i++)
	{
		cout<<sol[i]<<endl;
	}
	*/
	///*
	cout<<"Programa de analise de circuitos no tempo"<<endl;
	cout<<"Trabalho de Circuitos Eletricos II. 2009/2"<<endl;
	cout<<"Aluno: Alexandre Faria de Melo"<<endl<<endl;
		
	cout<<"Digite o arquivo que contem o netlist: ";

	string ArqIn,ArqOut;

	cin>>ArqIn;

	ArqOut = ArqIn.substr(0,ArqIn.find(".")).append(".tab");
		
	ifstream ifs (ArqIn.c_str(), ifstream::in );
	
	if(!ifs)
	{
		cout<<"Arquivo nao encontrado."<<endl;
		cout<<endl<<"Aperte enter para fechar."<<endl;
	
		cin.sync();
		cin.get();
		exit(-1);
	}
	
	ofstream ofs (ArqOut.c_str(), ofstream::out);
	Netlist net;

	if(!net.carregar(ifs))
	{
		cout<<endl<<"Aperte enter para fechar."<<endl;
		cin.sync();
		cin.get();
		exit(-1);
	}

	cout<<"Calculando ponto de operacao..."<<endl;
	net.calculaPO();
	
	cout<<"Iniciando analise..."<<endl;
	net.analiseTempo(ofs);

	ofs.close();
	ifs.close();

	cout<<"Analise finalizada com sucesso. Dados salvos em:"<<endl<<ArqOut<<endl;
	cout<<endl<<"Aperte enter para fechar."<<endl;
	
	cin.sync();
	cin.get();	
	//*/

	return 0;
}