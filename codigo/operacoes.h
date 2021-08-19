#ifndef _OPERACOES_H_
#define _OPERACOES_H_

#include "cartas.h"

//Função para gerar um deck de baralho, no qual cada espaço armazena um ID de carta
int* geraDeck(int tam);

//Função que embaralha deck utilizando função rand()
void embaralhaDeck(int *d, int tam);

//Função que recebe um vetor de deck e um vetor de mão com seus respectivos tamanhos para transferir um elemento para o outro
void compraCartaDeck(int *m, int *tamM, int *d, int *tamD);

void compraCartaCemiterio(int *m, int *tamM, Pilha **c);

//Função que recebe um vetor de mão com seu tamanho para descartar um elemento designado pelo índice.
//Além disso, o cemitério é passado como ponteiro para ponteiro pois será atualizado sendo pilha
void descartaCarta(int *m, int *tamM, Pilha **c, int car);

//Função que gera uma mão de nove cartas
int* geraMao(int *d,  int *tamD, int *tamM, int tamMMax);

//Função que, dados dois ids de cartas, confere se é uma combinação de duas cartas válida
int confereDupla(int id1, int id2);

//Função que, dados três ids de cartas, confere se é uma combinação de três cartas válida
int confereTrinca(int id1, int id2, int id3);

//Realiza um backtracking de Trinca, dada uma pilha que indica as cartas temporárias
void backtrackingTrinca(int *v, int tam, Pilha *cartemp, Pilha **cardef );

//Realiza um backtracking de Dupla, dada uma pilha que indica as cartas temporárias
void backtrackingDupla(int *v, int tam, Pilha *cartemp, Pilha **cardef );

//As cartas válidas armazenadas pela pilha são assimiladas no vetor e colocadas no final
void reorganizaMao(int *v, int *tam, Pilha **p); 

#endif