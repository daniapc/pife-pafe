#ifndef _CARTAS_H_
#define _CARTAS_H_

#include "auxiliares.h"

#define TAMD 104
#define TAMM 10

//Registo que serve para representar cada carta de um baralho
typedef struct carta{
    char numero_1, underline; // Usarei o char dos números em ascii
    char naipe;               // Copas, Espadas, Ouros e Paus
} Carta;

//Função para associar cada carta a um ID numérico, facilitando o processo de identificação da carta especificada
Carta* geraVetorIDs();

//Função para gerar um deck de baralho, no qual cada espaço armazena um ID de carta
int* geraDeck(int tam);

//Função que embaralha deck utilizando função rand()
void embaralhaDeck(int *d, int tam);

//Função que imprime cartas dado o deck com números e seus respectivos IDs
void imprimeCartas(Carta *vetorID, int *deck, int tam);

//Função que recebe um vetor de deck e um vetor de mão com seus respectivos tamanhos para transferir um elemento para o outro
void compraCarta(int *m, int *tamM, int *d, int *tamD);

//Função que recebe um vetor de mão com seu tamanho para descartar um elemento designado pelo índice.
//Além disso, o cemitério é passado como ponteiro para ponteiro pois será atualizado sendo pilha
void descartaCarta(int *m, int *tamM, Pilha **c, int indice);

//Função que gera uma mão de nove cartas
int* geraMao(int *d,  int *tamD, int *tamM, int tamMMax);

//Função que, dados dois ids de cartas, confere se é uma combinação de duas cartas válida
int confereDupla(int id1, int id2);

//Função que, dados três ids de cartas, confere se é uma combinação de três cartas válida
int confereTrinca(int id1, int id2, int id3);

void backtrackingTrinca(int *v, int tam, Pilha *postemp, Pilha **posdef );

void backtrackingDupla(int *v, int tam, Pilha *postemp, Pilha **posdef );

void reorganizaMao(int *v, int *tam, Pilha **p); 

#endif