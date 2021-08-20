/****************************************************
* Estrutura de Dados 1 - Trabalho Prático           * 
* Aluno: Daniel Augusto Pires de Castro RA: 2240246 *
****************************************************/

#include "cartas.h"

/********************************Carta respectiva a cada ID*************************************//*

[A_C]00 [2_C]01 [3_C]02 [4_C]03 [5_C]04 [6_C]05 [7_C]06 [8_C]07 [9_C]08 [10C]09 [V_C]10 [D_C]11 [R_C]12
[A_E]13 [2_E]14 [3_E]15 [4_E]16 [5_E]17 [6_E]18 [7_E]19 [8_E]20 [9_E]21 [10E]22 [V_E]23 [D_E]24 [R_E]25
[A_O]26 [2_O]27 [3_O]28 [4_O]29 [5_O]30 [6_O]31 [7_O]32 [8_O]33 [9_O]34 [10O]35 [V_O]36 [D_O]37 [R_O]38
[A_P]39 [2_P]40 [3_P]41 [4_P]42 [5_P]43 [6_P]44 [7_P]45 [8_P]46 [9_P]47 [10P]48 [V_P]49 [D_P]50 [R_P]51

*//******************************Carta respectiva a cada ID*************************************/

//Vetor de ID gera cartas respectivas ao id seguindo lógicas de atribuição em índices
Carta* geraVetorIDs(){
    int i, j;
    
    //Aloca inicialmente
    Carta *vetorID = (Carta*)malloc(52*sizeof(Carta));

    //Coloca o underline do meio
    for (i = 0; i < 52; i++)
        vetorID[i].underline = '_';
    //É atribuído o número de 1 a 9
    for (i = 2; i <= 9; i++)
        for (j = 0; j < 4; j++)
            vetorID[13*j + i - 1].numero_1 = i + '0';
    //Caracteres à parte são colocados no final
    for (i = 0; i < 4; i++){
        vetorID[13*i +  0].numero_1  = 'A';
        vetorID[13*i +  9].numero_1  = '1';
        vetorID[13*i +  9].underline = '0';
        vetorID[13*i + 10].numero_1  = 'V';
        vetorID[13*i + 11].numero_1  = 'D';
        vetorID[13*i + 12].numero_1  = 'R';
    }
    //Colocando cada naipe
    for (i = 13*0; i < 13*1; i++)
        vetorID[i].naipe = 'C';
    for (i = 13*1; i < 13*2; i++)
        vetorID[i].naipe = 'E';
    for (i = 13*2; i < 13*3; i++)
        vetorID[i].naipe = 'O';
    for (i = 13*3; i < 13*4; i++)
        vetorID[i].naipe = 'P';

   return vetorID;
}

//Dada as cartas e o respectivo vetor de IDs, é "convertido" o número referente ao seu naipe no vetor
void imprimeCartas(Carta *vetorID, int *deck, int tam){
    int i;
    //Laço que itera pelo vetor inteiro 
    for (i = 0; i < tam; i++)
        printf("[%c%c%c] ", vetorID[deck[i]].numero_1, vetorID[deck[i]].underline, vetorID[deck[i]].naipe);
    printf("\n\n");
}

//Dada as cartas e o respectivo vetor de IDs, é "convertido" o número referente ao seu naipe na pilha
void imprimePilhaCartas(Carta *vetorID, Pilha *p, int tam){
    Pilha *paux = p;
    int i;

    //Itera até o índice limite da pilha (não necessariamente o final dela)
    for (i = 0; i < tam; i++){
        printf("[%c%c%c] ", vetorID[paux->elem].numero_1, vetorID[paux->elem].underline,
                        vetorID[paux->elem].naipe);
        paux = paux->prox;
    }
    printf("\n\n");
}
