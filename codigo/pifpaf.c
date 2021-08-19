#include "operacoes.h"

int main (){

    srand(time(NULL));

    //printf("Bem-vindo jogador");

    Carta *vetorID = geraVetorIDs();
    int tamanho_deck = TAMD, 
        tamanho_mao = 0, 
        tamanho_mao_max = TAMM;

    int *deck = geraDeck(tamanho_deck);

    embaralhaDeck(deck, tamanho_deck);

    int *mao = geraMao(deck, &tamanho_deck, &tamanho_mao, tamanho_mao_max);

    int copia_tamanho_mao, descartaveis_anterior = 9, topo_cemiterio;

    int venceu = 0, decisao = 1, indicadora, indice, rodada = 0;

    Pilha *cemiterio = criarPilha();

    Pilha *cartas_definitivas = criarPilha(), *cartas_temporarias = criarPilha(),
          *duplas = criarPilha(), *trincas = criarPilha();


    while (!venceu && decisao == 1){
        rodada++;

        indicadora = 1;

        printf("\n--------------RODADA %d---------------\n\n", rodada);
        printf("Cartas na sua mão antes da compra:\n");
        imprimeCartas(vetorID, mao, tamanho_mao);

        if (!pilhaVazia(cemiterio)){

            printf("Carta no topo do cemitério:\n");
            imprimePilhaCartas(vetorID, cemiterio, 1);
            topo_cemiterio = topPilha(cemiterio);

            compraCartaCemiterio(mao, &tamanho_mao, &cemiterio);

            copia_tamanho_mao = tamanho_mao;

            backtrackingTrinca(mao, copia_tamanho_mao, cartas_temporarias, &cartas_definitivas);
            trincas = copiaPilha(cartas_definitivas);
            reorganizaMao(mao, &copia_tamanho_mao, &cartas_definitivas);

            backtrackingDupla(mao, copia_tamanho_mao, cartas_temporarias, &cartas_definitivas);
            duplas = copiaPilha(cartas_definitivas);
            reorganizaMao(mao, &copia_tamanho_mao, &cartas_definitivas);

            if (copia_tamanho_mao < descartaveis_anterior){
                printf("Carta comprada do topo do cemitério.\n\n");
                indicadora = 0;
            }
            else{
                descartaCarta(mao, &tamanho_mao, &cemiterio, topo_cemiterio);
                desalocarPilha(trincas);
                desalocarPilha(duplas);
            }
        }
        if (indicadora){

            compraCartaDeck(mao, &tamanho_mao, deck, &tamanho_deck);

            copia_tamanho_mao = tamanho_mao;

            backtrackingTrinca(mao, copia_tamanho_mao, cartas_temporarias, &cartas_definitivas);
            trincas = copiaPilha(cartas_definitivas);
            reorganizaMao(mao, &copia_tamanho_mao, &cartas_definitivas);
            
            backtrackingDupla(mao, copia_tamanho_mao, cartas_temporarias, &cartas_definitivas);
            duplas = copiaPilha(cartas_definitivas);
            reorganizaMao(mao, &copia_tamanho_mao, &cartas_definitivas);

            printf("Carta comprada do deck.\n\n");
            printf("Cartas na sua mão após a compra:\n");
            imprimeCartas(vetorID, mao, tamanho_mao);
        }

        if (!pilhaVazia(trincas)){
            printf("Trincas formadas:\n");
            imprimePilhaCartas(vetorID, trincas, tamanhoPilha(trincas));
            if (tamanhoPilha(trincas) == 9){
                venceu = 1;
                break;
            }
        }
        if (!pilhaVazia(duplas)){
            printf("Duplas formadas\n");
            imprimePilhaCartas(vetorID, duplas, tamanhoPilha(duplas));
        }
        printf("Cartas descartáveis na sua mão:\n");
        imprimeCartas(vetorID, mao, copia_tamanho_mao);

        printf("Como descartar?\n[1] Escolha\t [2] Aleatório\n");
        scanf("%d", &decisao);

        if (decisao == 1){
            printf("Escolha qual carta (1 a primeira, 2 a segunda, e assim por diante):\n");
            scanf("%d", &indice);
            indice--;
        }
        else{
            indice = rand()%copia_tamanho_mao;
        }
        descartaCarta(mao, &tamanho_mao, &cemiterio, mao[indice]);

        printf("Próxima rodada?\n[1] Sim\t [2] Não\n");   
        scanf("%d", &decisao);

        desalocarPilha(trincas);
        desalocarPilha(duplas);

        descartaveis_anterior = copia_tamanho_mao;
    }

    if (venceu)
        printf("\nVocê venceu!\n\n");
    else 
        printf("\nVocê perdeu!\n\n");

 
/*
[A_C]00 [2_C]01 [3_C]02 [4_C]03 [5_C]04 [6_C]05 [7_C]06 [8_C]07 [9_C]08 [10C]09 [V_C]10 [D_C]11 [R_C]12
[A_E]13 [2_E]14 [3_E]15 [4_E]16 [5_E]17 [6_E]18 [7_E]19 [8_E]20 [9_E]21 [10E]22 [V_E]23 [D_E]24 [R_E]25
[A_O]26 [2_O]27 [3_O]28 [4_O]29 [5_O]30 [6_O]31 [7_O]32 [8_O]33 [9_O]34 [10O]35 [V_O]36 [D_O]37 [R_O]38
[A_P]39 [2_P]40 [3_P]41 [4_P]42 [5_P]43 [6_P]44 [7_P]45 [8_P]46 [9_P]47 [10P]48 [V_P]49 [D_P]50 [R_P]51
*/

    return 0;
}



