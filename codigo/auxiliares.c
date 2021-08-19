#include "auxiliares.h"

void trocarElementos(int *elem1, int *elem2){
    int aux = *elem1;
    *elem1 = *elem2;
    *elem2 = aux;
}

int* copiaVetor(int *v, int tam){
    int *vaux = (int*)malloc(tam*sizeof(int));
    int i;
    for (i = 0; i < tam; i++)
        vaux[i] = v[i];
    
    return vaux;
}

void imprimeVetor(int *v, int tam){
    int i;
    for (i = 0; i < tam; i++){
        printf("%d ", v[i]);
    }
    printf("\n\n");
}

void ordenaTresNumeros(int *n1, int *n2, int *n3){
    int aux;
    if (*n2 > *n3){
        trocarElementos(&*n2, &*n3);
    }
    if (*n1 > *n2){
        trocarElementos(&*n1, &*n2);
        if (*n2 > *n3){
            trocarElementos(&*n2, &*n3);
        }
    }
}

Pilha* criarPilha(){
    Pilha *p = NULL;
    return p;
}

void desalocarPilha(Pilha *p){
    Pilha* paux = NULL;
    while (p != NULL){
        paux = p;
        p = p->prox;
        free(paux);
    }
    p = NULL;
}

Pilha* pushPilha(Pilha *p, int elem){
    Pilha *paux = (Pilha*)malloc(sizeof(Pilha));
    paux->prox = p;
    paux->elem = elem;
    return paux;
}

Pilha* popPilha(Pilha *p){
    Pilha *paux = p;
    p = p->prox;
    free(paux);
    return p;
}

int topPilha(Pilha *p){
    return p->elem;
}

int pilhaVazia(Pilha *p){
    if (p == NULL)
        return 1;
    else
        return 0;
}

void imprimePilha(Pilha *p){
    Pilha *paux = p;
    while (paux != NULL){
        printf("%d ", paux->elem);
        paux = paux->prox;
    }
    printf("\n\n");
}

int tamanhoPilha(Pilha *p){
    Pilha *paux = p;
    //printf(("\nAntes de bugar\n"));
    int i = 0;
    while (paux != NULL){
        i++;
        paux = paux->prox;
    }
    return i;
}

Pilha* copiaPilha(Pilha* p){
    Pilha *paux1 = p, *paux2 = criarPilha();

    while (paux1 != NULL){
        paux2 = pushPilha(paux2, paux1->elem);
        paux1 = paux1->prox;
    }

    return paux2;    
}