/****************************************************
* Estrutura de Dados 1 - Trabalho Prático           * 
* Aluno: Daniel Augusto Pires de Castro RA: 2240246 *
****************************************************/

#include "cartas.h"

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
        vetorID[13*i + 10].numero_1  = 'J';
        vetorID[13*i + 11].numero_1  = 'Q';
        vetorID[13*i + 12].numero_1  = 'K';
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
