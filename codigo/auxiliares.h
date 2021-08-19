#ifndef _AUXILIARES_H_
#define _AUXILIARES_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Uso principal da TAD Pilha
typedef struct pilha{
    struct pilha *prox;
    int elem;
}Pilha;

//Dados os endereços de memória de dois elementos, eles são trocados
void trocarElementos(int *elem1, int *elem2);

int* copiaVetor(int *v, int tam);

//Imprime um vetor genérico dado até qual índice de tamanho imprimir
void imprimeVetor(int *v, int tam);

//Função para ordenar três números dados
void ordenaTresNumeros(int *n1, int *n2, int *n3);

//Cria uma pilha atribuindo-lhe um valor inicial nulo
Pilha* criarPilha();

//Desaloca todos os elementos de uma pilha
void desalocarPilha(Pilha *p);

//Adiciona um elemento no topo da pilha
Pilha* pushPilha(Pilha *p, int elem);

//Remove um elemento do topo da pilha
Pilha* popPilha(Pilha *p);

//Retorna o elemento do topo da pilha
int topPilha(Pilha *p);

//Confere se uma pilha está vazia
int pilhaVazia(Pilha *p);

//Imprime a pilha
void imprimePilha(Pilha *p);

//Retorna quantos elementos há na pilha
int tamanhoPilha(Pilha *p);

//Copia pilha
Pilha* copiaPilha(Pilha* p);

#endif