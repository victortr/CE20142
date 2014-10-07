
#include <stdio.h>
#include <iostream>
#include <fstream>
#include "Acoplamento.h"

using namespace std;

//K<nome> <l1> <l2> <k>
//Indutância Mútua
Acoplamento::Acoplamento(QString nome, Indutor* l1, Indutor* l2, double k)
{
    this->nome = nome;
    this->l1 = l1;
    this->l2 = l2;
    this->k = k;
}

void Acoplamento::estampaPO(double tempo, double passo) //(double w, Complexo** m, Complexo*)
{
    double aux = ((k*sqrt(l1->getIndutancia() * l2->getIndutancia()))/passo); // [k * sqrt(L1 * L2)]/passo
    double V1, V2;


    m_matriz->m_elemento[l1->getMx()][l2->getMx()] += aux;
    m_matriz->m_elemento[l2->getMx()][l1->getMx()] += aux;

    J01 = m_matriz->getSolucao(1)[l1->getMx()];
    J02 = m_matriz->getSolucao(1)[l2->getMx()];

    V1 = aux*J01;
    V2 = aux*J02;

    m_matriz->m_elemento[l1->getMx()][m_matriz->m_numVariaveis+1] += -V2;
    m_matriz->m_elemento[l2->getMx()][m_matriz->m_numVariaveis+1] += -V1;
}


void Acoplamento::estampaBE(double tempo, double passo)
{
	estampaPO();
}

void Acoplamento::estampaGEAR(double tempo, double passo)
{
	estampaPO();
}
