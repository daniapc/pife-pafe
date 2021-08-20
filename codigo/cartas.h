/****************************************************
* Estrutura de Dados 1 - Trabalho Prático           * 
* Aluno: Daniel Augusto Pires de Castro RA: 2240246 *
****************************************************/

//"cartas" se refere a funções e algoritmos ligados ao sistema de conversão de cartas de acordo com
//os ids que eu elaborei

/********************************Carta respectiva a cada ID*************************************//*

[A_C]00 [2_C]01 [3_C]02 [4_C]03 [5_C]04 [6_C]05 [7_C]06 [8_C]07 [9_C]08 [10C]09 [J_C]10 [Q_C]11 [K_C]12
[A_E]13 [2_E]14 [3_E]15 [4_E]16 [5_E]17 [6_E]18 [7_E]19 [8_E]20 [9_E]21 [10E]22 [J_E]23 [Q_E]24 [K_E]25
[A_O]26 [2_O]27 [3_O]28 [4_O]29 [5_O]30 [6_O]31 [7_O]32 [8_O]33 [9_O]34 [10O]35 [J_O]36 [Q_O]37 [K_O]38
[A_P]39 [2_P]40 [3_P]41 [4_P]42 [5_P]43 [6_P]44 [7_P]45 [8_P]46 [9_P]47 [10P]48 [J_P]49 [Q_P]50 [K_P]51

*//******************************Carta respectiva a cada ID*************************************/

#ifndef _CARTAS_H_
#define _CARTAS_H_

#include "auxiliares.h"

//Tamanho do deck
#define TAMD 104
//Tamanho máximo da mão
#define TAMM 10

//Registo que serve para representar cada carta de um baralho
typedef struct carta{
    char numero_1, underline; // Usarei o char dos números em ascii
    char naipe;               // Copas, Espadas, Ouros e Paus
} Carta;

//Função para associar cada carta a um ID numérico, facilitando o processo de identificação da carta especificada
Carta* geraVetorIDs();

//Função que imprime cartas em um vetor dado o limite e o deck com números e seus respectivos IDs
void imprimeCartas(Carta *vetorID, int *deck, int tam);

//Função que imprime cartas em uma pilha dado o limite e o deck com números e seus respectivos IDs
void imprimePilhaCartas(Carta *vetorID, Pilha *p, int tam);

#endif