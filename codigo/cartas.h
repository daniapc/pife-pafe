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

//Função que imprime cartas dado o deck com números e seus respectivos IDs
void imprimeCartas(Carta *vetorID, int *deck, int tam);

#endif