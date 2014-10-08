
#include <stdio.h>
#include <iostream>
#include <fstream>
#include "Acoplamento.h"
#include "Netlist.h"
#include "Matriz.h"

using namespace std;

//K<nome> <l1> <l2> <k>
//Indutância Mútua
//Acoplamento::Acoplamento(ifstream &arq)
//{
//    this->nome = arq;
//    this->l1 = l1;
//    this->l2 = l2;
//    this->k = k;
//}


//K<nome> <l1> <l2> <fator>
Acoplamento::Acoplamento(ifstream &arq)
{
    m_erro = false;
    int i = 0;
    while(arq.good() && arq.peek() != '\n')
    {
        //ignora espacos
        if(arq.peek() == ' ')
        {
            arq.ignore();
            continue;
        }
        switch(i)
        {
            case 0: arq >> m_nome;		break;
            case 1: arq >> m_l1;        break;
            case 2: arq >> m_l2;        break;
            case 3: arq >> m_k;			break;
            default:arq >> m_ignora;	break;
        }
        i++;
    }
    arq.ignore();
    if(i!=4)
    {
        cout<< m_nome <<": Numero de parametros errado " << i << "/4"<<endl;
        arq.close();
        m_erro = true;
    }
}


void Acoplamento::associaMatriz(Matriz *matriz)
{
    extern s_indutores g_listaIndutores[TAM_MAX];
    int i = 0;
    for(i = 0; i < TAM_MAX; i++)
    {
        if (m_l1 == g_listaIndutores[i].m_nome)
        {
            l1x = g_listaIndutores[i].m_no_x;
            l1l = g_listaIndutores[i].m_l;
        }
        if (m_l2 == g_listaIndutores[i].m_nome)
        {
            l2x = g_listaIndutores[i].m_no_x;
            l2l = g_listaIndutores[i].m_l;
        }
    }
}

void Acoplamento::estampaPO()
{

}

void Acoplamento::estampaBE(double tempo, double passo)
{
    double aux = ((m_k*sqrt(l1l * l2l))/passo); // [k * sqrt(L1 * L2)]/t
    double V1, V2, J01, J02;


    m_matriz->m_elemento[l1x][l2x] += aux;
    m_matriz->m_elemento[l2x][l1x] += aux;

    J01 = m_matriz->getSolucao(1)[l1x];
    J02 = m_matriz->getSolucao(1)[l2x];

    V1 = aux*J01;
    V2 = aux*J02;

    m_matriz->m_elemento[l1x][m_matriz->m_numVariaveis+1] += -V2;
    m_matriz->m_elemento[l2x][m_matriz->m_numVariaveis+1] += -V1;
}

void Acoplamento::estampaGEAR(double tempo, double passo)
{
	estampaPO();
}
