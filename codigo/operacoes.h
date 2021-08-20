/****************************************************
* Estrutura de Dados 1 - Trabalho Prático           * 
* Aluno: Daniel Augusto Pires de Castro RA: 2240246 *
****************************************************/

//"operacoes" se refere a funções do jogo e do algoritmo específicas para esse código em questão,
//utilizando funções auxiliares genéricas em muitos casos

#ifndef _OPERACOES_H_
#define _OPERACOES_H_

#include "cartas.h"

/********************************Estão dentro da pipaf.c*************************************/

//Faz ser jogado o modo de jogo solo
void pifePafeSolo();

//Faz ser jogado o modo de jogo contra o computador, dado o nível de dificuldade
void pifePafeComputador();

/********************************Estão dentro da pipaf.c**************************************/

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

//Função que, dados três ids de cartas, confere se é uma combinação de três cartas válida
int confereTrinca(int id1, int id2, int id3);

//Função que, dados dois ids de cartas, confere se é uma combinação de duas cartas válida
int confereDupla(int id1, int id2);

//Função criada para caso já tenha sido empilhada a combinação válida evitando entrar em outra recursão
int trincaRepetida(int id1, int id2, int id3, Pilha *p);

//A mesma utilidade que a função anterior mas para duplas
int duplaRepetida(int id1, int id2, Pilha *p);

//Realiza um backtracking de Trinca, dada uma pilha que indica as cartas temporárias
void backtrackingTrinca(int *v, int tam, Pilha *cartemp, Pilha **cardef );

//Realiza um backtracking de Dupla, dada uma pilha que indica as cartas temporárias
void backtrackingDupla(int *v, int tam, Pilha *cartemp, Pilha **cardef );

//As cartas válidas armazenadas pela pilha são assimiladas no vetor e colocadas no final
void reorganizaMao(int *v, int *tam, Pilha **p); 

#endif