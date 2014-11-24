/**
 * Trabalho de Circuitos Eletricos II - 2014/2
 */

#include <iostream>
#include <fstream>
#include <string>
#include "Matriz.h"
#include "Netlist.h"

s_indutores g_listaIndutores[TAM_MAX];
int g_t;

int main(int argc, char **argv)
{

    //Limpando lista de indutores
	using namespace std;
    int i; extern int g_t;
    for(i=0; i<TAM_MAX; i++)
    {
        g_listaIndutores[i].m_nome = "";
        g_listaIndutores[i].m_no_x = 0;
        g_listaIndutores[i].m_l = 0;
    }
    g_t = 0;


	cout<<"Programa de analise de circuitos no tempo"<<endl;
    cout<<"Trabalho de Circuitos Eletricos II. 2014/2"<<endl<<endl;
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
