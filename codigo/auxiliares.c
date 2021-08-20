/****************************************************
* Estrutura de Dados 1 - Trabalho Prático           * 
* Aluno: Daniel Augusto Pires de Castro RA: 2240246 *
****************************************************/

#include "auxiliares.h"

//Função que apenas chama o "limpar tela" dependendo do sistema operacional
void limparTela(){
    system("clear");
    //system("cls"); //Se for windows:
}

void trocarElementos(int *elem1, int *elem2){
    //Criação de variável auxiliar para trocar elementos    
    int aux = *elem1;
    *elem1 = *elem2;
    *elem2 = aux;
}

int* copiaVetor(int *v, int tam){
    //Aloca vetor inicialmente
    int *vaux = (int*)malloc(tam*sizeof(int));
    int i;
    //Cada valor do índice é atribuído
    for (i = 0; i < tam; i++)
        vaux[i] = v[i];
    
    return vaux;
}

void imprimeVetor(int *v, int tam){
    int i;
    //Cada valor do índice até o limite é impresso
    for (i = 0; i < tam; i++)
        printf("%d ", v[i]);
    printf("\n\n");
}

void ordenaTresNumeros(int *n1, int *n2, int *n3){
    int aux;
    //Troca elementos caso o segundo for maior que o terceiro
    if (*n2 > *n3)
        trocarElementos(&*n2, &*n3);
    //Troca elementos caso o primeiro for maior que o segundo, para trocar o segundo e o terceiro novamente, se necessário
    if (*n1 > *n2){
        trocarElementos(&*n1, &*n2);
        if (*n2 > *n3)
            trocarElementos(&*n2, &*n3);
    }
}

Pilha* criarPilha(){
    //É declarada pilha NULL e retornada
    Pilha *p = NULL;
    return p;
}

void desalocarPilha(Pilha *p){
    //Cada elemento da pilha é desalocado com free
    Pilha* paux = NULL;
    while (p != NULL){
        paux = p;
        p = p->prox;
        free(paux);
    }
    p = NULL;
}

Pilha* pushPilha(Pilha *p, int elem){
    //Cria pilha auxiliar, aloca ela, para setá-la no início da fila e atribuir-lhe o elemento pushado
    Pilha *paux = (Pilha*)malloc(sizeof(Pilha));
    paux->prox = p;
    paux->elem = elem;
    return paux;
}

Pilha* popPilha(Pilha *p){
    //Remove o elemento da pilha e desaloca o espaço relativo a ele
    Pilha *paux = p;
    p = p->prox;
    free(paux);
    return p;
}

int topPilha(Pilha *p){
    //Retorna o elemento do topo da pilha
    return p->elem;
}

int pilhaVazia(Pilha *p){
    //Retorna true ou false de acordo com o resultado dessa comparação
    return (p == NULL);
}

void imprimePilha(Pilha *p){
    //Percorre todos os elementos da pilha com um ponteiro imprimindo-os
    Pilha *paux = p;
    while (paux != NULL){
        printf("%d ", paux->elem);
        paux = paux->prox;
    }
    printf("\n\n");
}

int tamanhoPilha(Pilha *p){
    //Retorna o tamanho da pilha através de contadora até que se chegue no elemento fina com o ponteiro
    Pilha *paux = p;
    int i = 0;
    while (paux != NULL){
        i++;
        paux = paux->prox;
    }
    return i;
}

Pilha* copiaPilha(Pilha* p){
    //Dada uma pilha, cria-se uma nova para copiar todos os elementos nela através de pushs
    Pilha *paux1 = p, *paux2 = criarPilha();
    while (paux1 != NULL){
        paux2 = pushPilha(paux2, paux1->elem);
        paux1 = paux1->prox;
    }
    return paux2;    
}