/****************************************************
* Estrutura de Dados 1 - Trabalho Prático           * 
* Aluno: Daniel Augusto Pires de Castro RA: 2240246 *
****************************************************/

#include "operacoes.h"

int* geraDeck(int tam){
    int* deck = (int*)malloc(tam*sizeof(int));
    int i;
    //Preenche o vetor de tamanho 104 com números referentes ao índice do vetor de IDs
    for (i = 0; i < 52; i++){
        deck[i] = i;
        //Em um baralho de pifpaf, a mesma carta existe duas vezes, por isso é atribuído ao índice 52 à frente
        deck[i+52] = i; 
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

void compraCartaDeck(int *m, int *tamM, int *d, int *tamD){

    //Inicialmente um vetor com tamanho da mão compra uma carta do topo do deck
    m[*tamM] = d[*tamD - 1];

    //O topo da mão é incrementado enquanto o topo do deck é decrementado
    (*tamM)++;
    (*tamD)--;
}

void compraCartaCemiterio(int *m, int *tamM, Pilha **c){

    //Tamanho da mão incrementado
    (*tamM)++;

    //O índice do topo da mão recebe o topo do cemitério
    m[*tamM -1] = topPilha(*c);

    //O cemitério remove o elemento da cabeça
    *c = popPilha(*c);
}

void descartaCarta(int *m, int *tamM, Pilha **c, int car){

    int indice = 0;

    //Percorre os índices do vetor até encontrar a carta
    while (m[indice] != car)
        indice++;

    //Dada uma carta em um índice da mão, é descartada 
    trocarElementos(&m[indice], &m[*tamM - 1]);

    //O cemitério passado de referência é pushado com o elemento descartado.
    *c = pushPilha(*c, m[*tamM - 1]);

    (*tamM)--;
}

int* geraMao(int *d, int *tamD, int *tamM, int tamMMax){
    int *mao = (int*)malloc(tamMMax*sizeof(int));
    int i;
    //Faz o ato de comprar cartas enquanto a mão não estiver cheia
    for (i = 0; i < tamMMax - 1; i++)
        compraCartaDeck(mao, tamM, d, tamD);

    return mao;    
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

int confereDupla(int id1, int id2){
    //Se as cartas forem idênticas, imcarsível de fazer combinação.
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

int trincaRepetida(int id1, int id2, int id3, Pilha *p){
    //Cópias de ids para percorrer a pilha
    int cid1, cid2, cid3;
    Pilha *paux = p;

    //Ordena temporariamente os ids conferidos
    ordenaTresNumeros(&id1, &id2, &id3);

    //Esse laço percorre toda a pilha (evitando ficar nulo) e copia valores
    while (paux != NULL && tamanhoPilha(paux) >= 3){
        cid1 = paux->elem;
        paux = paux->prox;
        cid2 = paux->elem;
        paux = paux->prox;
        cid3 = paux->elem;
        paux = paux->prox;
        
        //Ordena e confere se são iguais, se forem quer dizer que é repetida e retornara verdadeiro
        ordenaTresNumeros(&cid1, &cid2, &cid3);
        if (cid1 == id1 && cid2 == id2 && cid3 == id3)
            return 1;
    }
    return 0;
}

int duplaRepetida(int id1, int id2, Pilha *p){
    //Cópias de ids para percorrer a pilha    
    int cid1, cid2;
    Pilha *paux = p;

    //Ordena temporariamente de um jeito simples
    if (id1 > id2)
        trocarElementos(&id1, &id2);

    //Esse laço percorre toda a pilha (evitando ficar nulo) e copia valores
    while (paux != NULL && tamanhoPilha(paux) >= 2){
        cid1 = paux->elem;
        paux = paux->prox;
        cid2 = paux->elem;
        paux = paux->prox;

        //Ordena e confere se são iguais, se forem quer dizer que é repetida e retornara verdadeiro
        if (cid1 > cid2)
            trocarElementos(&cid1, &cid2);
        if (cid1 == id1 && cid2 == id2)
            return 1;
    }
    return 0;
}

void backtrackingTrinca(int *v, int tam, Pilha *cartemp, Pilha **cardef ){

    int i, j, k;

    //Enquanto ainda for possível encontrar combinações de trincas na pilha
    if (tam >= 3){
        //Laços de repetição aninhados de tal modo a permitir combinações (aprendi com a Leyza <3)
        for (i = 0; i < tam; i++){
            for (j = i + 1; j < tam; j++){
                for (k = j + 1; k < tam; k++){
                    //Caso for favorável a combinação, já pode prosseguir para gerar recursão
                    if (confereTrinca(v[i], v[j], v[k]) && !trincaRepetida(v[i], v[j], v[k], *cardef)){
                        //Criado vetor de cópia
                        int *vaux = copiaVetor(v, tam);

                        //Os elementos favoráveis são colocados atrás na pilha
                        trocarElementos(&vaux[i], &vaux[tam-1]);
                        trocarElementos(&vaux[j], &vaux[tam-2]);
                        trocarElementos(&vaux[k], &vaux[tam-3]);
                        
                        //A pilha de cartas temporárias pusha esses elementos favoráveis
                        cartemp = pushPilha(cartemp, v[i]);
                        cartemp = pushPilha(cartemp, v[j]);
                        cartemp = pushPilha(cartemp, v[k]);

                        //Entra em uma recursão, dessa vez diminuindo o tamanho
                        //passando o vetor auxiliar e a pilha temporária
                        backtrackingTrinca(vaux, tam - 3, cartemp, &*cardef);
                        
                        //São tirados os elementos favoráveis para as próximas possibilidades de combinação
                        cartemp = popPilha(cartemp);
                        cartemp = popPilha(cartemp);
                        cartemp = popPilha(cartemp);

                        //Desalocado para as próximas possilidades de combinação
                        free(vaux);
                    }
                }
            }
        }
    }
    //Ao chegar no final da recursão, é conferido o tamanho dessa pilha temporária se ultrapassou
    //o tamanho da pilha definitiva. Assim, é armazenada a melhor combinação possível
    if (tamanhoPilha(cartemp) > tamanhoPilha(*cardef))
        *cardef = copiaPilha(cartemp);
   
}

void backtrackingDupla(int *v, int tam, Pilha *cartemp, Pilha **cardef ){

    int i, j;

    //Enquanto ainda for possível encontrar combinações de duplas na pilha
    if (tam > 2){
        //Laços de repetição aninhados de tal modo a permitir combinações
        for (i = 0; i < tam; i++){
            for (j = i + 1; j < tam; j++){
                    //Caso for favorável a combinação, já pode prosseguir para gerar recursão
                    if (confereDupla(v[i], v[j]) && !duplaRepetida(v[i], v[j], *cardef)){
                        //Criado vetor de cópia
                        int *vaux = copiaVetor(v, tam);
                        
                        //Os elementos favoráveis são colocados atrás na pilha
                        trocarElementos(&vaux[i], &vaux[tam-1]);
                        trocarElementos(&vaux[j], &vaux[tam-2]);
                        
                        //A pilha de cartas temporárias pusha esses elementos favoráveis
                        cartemp = pushPilha(cartemp, v[i]);
                        cartemp = pushPilha(cartemp, v[j]);

                        //Entra em uma recursão, dessa vez diminuindo o tamanho
                        //passando o vetor auxiliar e a pilha temporária
                        backtrackingDupla(vaux, tam - 2, cartemp, &*cardef);
                        
                        //São tirados os elementos favoráveis para as próximas possibilidades de combinação
                        cartemp = popPilha(cartemp);
                        cartemp = popPilha(cartemp);

                        //Desalocado para as próximas possilidades de combinação
                        free(vaux);
                    }
                
            }
        }
    }

    //Ao chegar no final da recursão, é conferido o tamanho dessa pilha temporária se ultrapassou
    //o tamanho da pilha definitiva. Assim, é armazenada a melhor combinação possível
    if (tamanhoPilha(cartemp) > tamanhoPilha(*cardef))
        *cardef = copiaPilha(cartemp);
}

void reorganizaMao(int *v, int *tam, Pilha **p){
    int i = 0, j, tamp = tamanhoPilha(*p), aux;

    for (j = 0; j < tamp; j++){
        aux = topPilha(*p);
        i = 0;
        //Percorre índices do vetor até encontrar o elemento
        while (v[i] != aux)
            i++;
        //Troca elementos para o final e dá pop no que não for mais necessário
        trocarElementos(&v[i], &v[*tam-1]);
        (*tam)--;
        *p = popPilha(*p);
    }  
   
}