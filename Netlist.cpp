//NETLIST.C

#include <iostream>
#include <fstream>
#include <list>
#include <cmath>
#include <string>

#include "Netlist.h"
#include "Elemento.h"

#include "Resistor.h"
#include "Capacitor.h"
#include "Indutor.h"
#include "Acoplamento.h"

#include "Diodo.h"
#include "Mos.h"
#include "Ampop.h"

#include "Tensao.h"
#include "Corrente.h"

#include "Tensaotensao.h"
#include "Tensaocorrente.h"

#include "Correntecorrente.h"
#include "Correntetensao.h"
#include "Matriz.h"

using namespace std;

Netlist::Netlist()
{
}

bool Netlist::carregar(ifstream &arq)
{
	arq.ignore(MAX_LINHA,'\n');
	while(arq.good())
	{
		Elemento *elemento = NULL;
		switch(arq.peek())
		{
			case '.':
				carregarParametros(arq);
				break;
			case 'R':
				//arq.ignore();
				elemento = new Resistor(arq);
				break;
			
			case 'L':
				//arq.ignore();
				elemento = new Indutor(arq);
				break;
			case 'C':
				//arq.ignore();
				elemento = new Capacitor(arq);
				break;
			case 'O':
				//arq.ignore();
				elemento = new Ampop(arq);
				break;
			case 'V':			
				//arq.ignore();
				elemento = new Tensao(arq);
				break;
			case 'I':			
				//arq.ignore();
				elemento = new Corrente(arq);
				break;
			
			case 'E':			
				//arq.ignore();
				elemento = new Tensaotensao(arq);
				break;
			case 'F':			
				//arq.ignore();
				elemento = new Correntecorrente(arq);
				break;
			case 'G':			
				//arq.ignore();
				elemento = new Correntetensao(arq);
				break;
			case 'H':			
				//arq.ignore();
				elemento = new Tensaocorrente(arq);
				break;

			case 'W':
			case 'M':			
				//arq.ignore();
				elemento = new Mos(arq);
				break;
            case 'K':
                //arq.ignore();
                elemento = new Acoplamento(arq);
                break;
			case 'D':			
				//arq.ignore();
				elemento = new Diodo(arq);
				break;
			default:
				arq.ignore(MAX_LINHA,'\n');
				break;
		}
		if(elemento)
		{
			if(elemento->getErro())
				return false;
			elemento->associaMatriz(&m_matriz);
			m_elementos.push_back(elemento);		
		}
		elemento = NULL;
	}

	cout<<"O Circuito possui "<<m_elementos.size()<<" elemento(s) e "<<m_matriz.m_numVariaveis<<" variaveis"<<endl;

	cout<<"Variaveis:"<<endl;

	for(int i=1;i<=m_matriz.m_numVariaveis;i++)
	{
		cout<<i<<":"<<m_matriz.getNomeVariavel(i)<<endl;
	}

	string metodo;
	if(m_metodo == GEAR)
		metodo = "GEAR";
	else if(m_metodo == BE)
		metodo = "BE";
	else if(m_metodo == TRAP)
		metodo = "TRAP";

	cout<<"metodo="<<metodo<<",passo="<<m_passo<<",passos internos="<<m_passosInternos<<",tempo de analise="<<m_t<<endl;
	cout<<endl;

	return true;
}

void Netlist::newtonRaphson(bool po, double t,double passo)
{
	list<Elemento*>::iterator itr;

	bool convergiu = false;
	int iter_nr,nr;
	
	nr = 0;
    //cout<<"NR"<<endl;
	while (!convergiu && nr < MAX_NR)
	{
		
        //cout<<"Tentativa "<<nr<<":"<<endl;
		
		//RECALCULA APROXIMACAO DA SOLUCAO INICIAL
		if(nr!=0)
			m_matriz.resetSolucao();


		//CALCULA A SOLUCAO POR NEWTON-RAPHSON
		iter_nr = 0;
		double *solAnterior = new double[m_matriz.m_numVariaveis+1];
		while(!convergiu && iter_nr < MAX_ITR_NR)
		{
            //cout<<"Iteracao "<<iter_nr<<":"<<endl;
			
			m_matriz.copiaSolucao(0,solAnterior);
			m_matriz.reset();
			for(itr = m_elementos.begin(); itr != m_elementos.end(); itr++)
			{
				if(po)
					(*itr)->estampaPO();
				else
				{
					switch(m_metodo)
					{

						case GEAR:
							(*itr)->estampaGEAR(t,passo);
							break;
						case BE:
							(*itr)->estampaBE(t,passo);
							break;
						//case TRAP:
						//  (*itr)->estampaTRAP(t,passo);
						//	break;
						default:
							break;
					}
				}
			}		
			convergiu = m_matriz.resolver();
			for(int i=1; convergiu && i<=m_matriz.m_numVariaveis;i++)
			{
				double dif;
				dif = m_matriz.getSolucao(0)[i] - solAnterior[i];

				if(fabs(dif/solAnterior[i]) > LIMITE_NR)
					convergiu = false;
			}
			iter_nr++;

<<<<<<< HEAD
    //        m_matriz.mostrar();

     //       m_matriz.mostrarSolucao();
    //        cin.sync();cin.get();

		}
        m_matriz.mostrar();
        cout << endl << endl;
        m_matriz.mostrarSolucao();
=======
            //m_matriz.mostrarSolucao();
            //cin.sync();cin.get();

		}
        //m_matriz.mostrarSolucao();
>>>>>>> origin/master
		nr++;
	}
	if(!convergiu)
	{
		cout<<"Newton-Raphson nao convergiu apos "<<MAX_NR<<" tentativas e "<<MAX_ITR_NR<<" iteracoes"<<endl;
		cout<<endl<<"Aperte enter para fechar."<<endl;
		cin.sync();

		cin.get();
		exit(-1);
	}
	m_matriz.gravaSolucao();
}

void Netlist::calculaPO()
{
	m_matriz.resetSolucao();
	newtonRaphson(true);
}

void Netlist::analiseTempo(ofstream &arq)
{	
	double t;
	double passo = m_passo/m_passosInternos;
	int numPasso,i;
	
	//IMPRIME O CABECALHO COM OS NOMES DAS VARIAVEIS
    arq<<"t ";
    for(i=1;i<=m_matriz.m_numVariaveis;i++)
    {
        arq<<m_matriz.getNomeVariavel(i)<<" ";
    }
    arq<<endl;

	for(t=0,numPasso=0; t<= m_t; t+=passo,numPasso++)
	{
		newtonRaphson(false,t,passo);
 //       cout << "estou aqui antes de td" << endl;
		
		//IMPRIME SOLUCAO
//        cout << numPasso << endl;
//        cout << m_passosInternos << endl;
		if(numPasso%m_passosInternos == 0)
		{
			arq<<t<<" ";
 //           cout << "estou aqui antes do for" << endl;
            for(i=1;i<=m_matriz.m_numVariaveis;i++)
			{
                arq<<m_matriz.getSolucao(1)[i]<<" ";
 //               cout << "estou aqui dentro do for"  << endl;

			}
            arq<<endl;
            //debug
           // m_matriz.mostrarSolucao();
		}
	}
}

//.tran <tempo final> <passo> <GEAR> <passos internos>
void Netlist::carregarParametros(ifstream &arq)
{
	string buffer;

	arq>>buffer;
	arq>>m_t;
	arq>>m_passo;
	arq>>buffer;
	
	if(buffer == "GEAR")
		m_metodo = GEAR;
	else if(buffer == "BE")
		m_metodo = BE;
	else if(buffer == "TRAP")
		m_metodo = TRAP;
	arq>>m_passosInternos;
}

