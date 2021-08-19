//#include "cartas.c"
//#include "auxiliares.c"
#include "operacoes.h"

int* geraDeck(int tam){
    int* deck = (int*)malloc(tam*sizeof(int));
    int i;
    //Preenche o vetor de tamanho 104 com números referentes ao índice do vetor de IDs
    for (i = 0; i < 52; i++){
        deck[i] = i;
        deck[i+52] = i; //Em um baralho de pifpaf, repete-se uma vez o número de cartas
    }

    return deck;
}

void embaralhaDeck(int *d, int tam){

    int aux, indice;

    //Embaralha sorteando um índice aleatório e em seguida trocando o elemento com o da última posição do vetor
    for (tam; tam >= 1; tam--){
        indice = rand()%(tam);
        trocarElementos(&d[indice], &d[tam-1]);
    }
}

void compraCarta(int *m, int *tamM, int *d, int *tamD){

    //Inicialmente um vetor com tamanho da mão compra uma carta do topo do deck
    m[*tamM] = d[*tamD - 1];

    //O topo da mão é incrementado enquanto o topo do deck é decrementado
    (*tamM)++;
    (*tamD)--;
}

void descartaCarta(int *m, int *tamM, Pilha **c, int indice){
    int aux;
    
    //Dada uma carta em um índice da mão, é descartada 
    trocarElementos(&m[indice], &m[*tamM - 1]);

    //O cemitério passado de referência é pushado com o elemento descartado.
    *c = pushPilha(*c, aux);

    (*tamM)--;
}

int* geraMao(int *d, int *tamD, int *tamM, int tamMMax){
    int *mao = (int*)malloc(tamMMax*sizeof(int));
    int i;
    
    //Faz o ato de comprar cartas enquanto a mão não estiver cheia
    for (i = 0; i < tamMMax - 1; i++)
        compraCarta(mao, tamM, d, tamD);

    return mao;    
}

/*

[1_C]00 [2_C]01 [3_C]02 [4_C]03 [5_C]04 [6_C]05 [7_C]06 [8_C]07 [9_C]08 [10C]09 [V_C]10 [D_C]11 [R_C]12
[1_E]13 [2_E]14 [3_E]15 [4_E]16 [5_E]17 [6_E]18 [7_E]19 [8_E]20 [9_E]21 [10E]22 [V_E]23 [D_E]24 [R_E]25
[1_O]26 [2_O]27 [3_O]28 [4_O]29 [5_O]30 [6_O]31 [7_O]32 [8_O]33 [9_O]34 [10O]35 [V_O]36 [D_O]37 [R_O]38
[1_P]39 [2_P]40 [3_P]41 [4_P]42 [5_P]43 [6_P]44 [7_P]45 [8_P]46 [9_P]47 [10P]48 [V_P]49 [D_P]50 [R_P]51

*/

int confereDupla(int id1, int id2){
    //Se as cartas forem idênticas, impossível de fazer combinação.
    if (id1 != id2){
        //Caso forem de números iguais mas de naipes diferentes, é combinação.
        if (id1%13 == id2%13)
            return 1;
        //Caso forem de naipes iguais e estiverem 1 a 2 números de distância, é combinação.
        else if (id1/13 == id2/13){
            if (abs(id1%13 - id2%13) == 1 || abs(id1%13 - id2%13) == 2)
                return 1;
        }
    }
    return 0;
}

int confereTrinca(int id1, int id2, int id3){
    //Ja retorna falso caso duas das três cartas sejam idênticas
    if (id1 == id2 || id1 == id3 || id2 == id3){
        return 0;
    }
    else {
        //Caso forem de números iguais mas de naipes diferentes, é combinação.
        if (id1%13 == id2%13 && id1%13 == id3%13 && id2%13 == id3%13){
            return 1;
        }
        //Caso forem de naipes iguais, são ordenados para conferir se estão 1 número de distância do outro
        else if (id1/13 == id2/13 && id1/13 == id3/13 && id2/13 == id3/13){
            ordenaTresNumeros(&id1, &id2, &id3);
            if (id1 + 1 == id2 && id2 + 1 == id3)
                return 1;
        }
    }
    return 0;
}

void backtrackingTrinca(int *v, int tam, Pilha *postemp, Pilha **posdef ){

    int i, j, k;

    if (tam >= 3){
        for (i = 0; i < tam; i++){
            for (j = i + 1; j < tam; j++){
                for (k = j + 1; k < tam; k++){
                    if (confereTrinca(v[i], v[j], v[k])){
                        int *vaux = copiaVetor(v, tam);

                        trocarElementos(&vaux[i], &vaux[tam-1]);
                        trocarElementos(&vaux[j], &vaux[tam-2]);
                        trocarElementos(&vaux[k], &vaux[tam-3]);
                        
                        postemp = pushPilha(postemp, v[i]);
                        postemp = pushPilha(postemp, v[j]);
                        postemp = pushPilha(postemp, v[k]);

                        backtrackingTrinca(vaux, tam - 3, postemp, &*posdef);
                        
                        postemp = popPilha(postemp);
                        postemp = popPilha(postemp);
                        postemp = popPilha(postemp);

                        free(vaux);
                    }
                }
            }
        }
    }
    if (tamanhoPilha(postemp) > tamanhoPilha(*posdef)){
        *posdef = copiaPilha(postemp);
   }
}

void backtrackingDupla(int *v, int tam, Pilha *postemp, Pilha **posdef ){

    int i, j;

    if (tam > 2){
        for (i = 0; i < tam; i++){
            for (j = i + 1; j < tam; j++){
                    if (confereDupla(v[i], v[j])){
                        int *vaux = copiaVetor(v, tam);
                        
                        trocarElementos(&vaux[i], &vaux[tam-1]);
                        trocarElementos(&vaux[j], &vaux[tam-2]);
                        
                        postemp = pushPilha(postemp, v[i]);
                        postemp = pushPilha(postemp, v[j]);

                        backtrackingDupla(vaux, tam - 2, postemp, &*posdef);
                        
                        postemp = popPilha(postemp);
                        postemp = popPilha(postemp);

                        free(vaux);
                    }
                
            }
        }
    }
    if (tamanhoPilha(postemp) > tamanhoPilha(*posdef)){
        *posdef = copiaPilha(postemp);
    }
}

void reorganizaMao(int *v, int *tam, Pilha **p){
    int i, j, tamp = tamanhoPilha(*p), aux;
    for (j = 0; j < tamp; j++){
        aux = topPilha(*p);
        for (i = 0; i < *tam; i++){
            if (aux == v[i]){
                trocarElementos(&v[i], &v[*tam-1]);
                (*tam)--;
                *p = popPilha(*p);
                break;
            }
        }
    }
}