#include "operacoes.c"

int main (){

    srand(time(NULL));

    Carta *vetorID = geraVetorIDs();
    int tamanho_deck = TAMD, 
        tamanho_mao = 0, 
        tamanho_mao_max = TAMM;

    int *deck = geraDeck(tamanho_deck);

    embaralhaDeck(deck, tamanho_deck);

    int *mao = geraMao(deck, &tamanho_deck, &tamanho_mao, tamanho_mao_max);

    int copia_tamanho_mao;

    int venceu = 0;

    int decisao = 1;

    Pilha *cemiterio = criarPilha();

    Pilha *posicoes_definitivas = criarPilha(), *posicoes_temporarias = criarPilha();

    //mao[0] = 18; mao[1] = 31; mao[2] = 32;  mao[3] = 33; mao[4] = 17;
    //mao[5] = 4; mao[6] = 47; mao[7] = 51; mao[8] = 48;

    while (!venceu && decisao == 1){

        imprimeVetor(mao, tamanho_mao);

        printf("Cartas na sua mão:\n");
        imprimeCartas(vetorID, mao, tamanho_mao);
        copia_tamanho_mao = tamanho_mao;

        backtrackingTrinca(mao, copia_tamanho_mao, posicoes_temporarias, &posicoes_definitivas);
        reorganizaMao(mao, &copia_tamanho_mao, &posicoes_definitivas);

        if (copia_tamanho_mao <= 1){
            venceu = 1;
        }
        else{
            backtrackingDupla(mao, copia_tamanho_mao, posicoes_temporarias, &posicoes_definitivas);
            reorganizaMao(mao, &copia_tamanho_mao, &posicoes_definitivas);
        }

        printf("Cartas descartáveis na sua mão:\n");
        imprimeCartas(vetorID, mao, copia_tamanho_mao);     

        printf("Próxima rodada?\n[1] Sim\t [2] Não\n");   
        scanf("%d", &decisao);
    }

    if (venceu)
        printf("\nVocê venceu!\n\n");
    else 
        printf("\nVocê perdeu!\n\n");


  //  imprimeVetor(mao, copia_tamanho);

    /*//Testes
    imprimeVetor(deck, tamanho_deck);
    imprimeVetor(mao, tamanho_mao);
    descartaCarta(mao, &tamanho_mao, &cemiterio, 0);
    imprimeVetor(mao, tamanho_mao);
    imprimePilha(cemiterio);
    */
    //compraCarta(mao, &tamanho_mao, deck, &tamanho_deck);

    //decartaCarta()
 
/*
[A_C]00 [2_C]01 [3_C]02 [4_C]03 [5_C]04 [6_C]05 [7_C]06 [8_C]07 [9_C]08 [10C]09 [V_C]10 [D_C]11 [R_C]12
[A_E]13 [2_E]14 [3_E]15 [4_E]16 [5_E]17 [6_E]18 [7_E]19 [8_E]20 [9_E]21 [10E]22 [V_E]23 [D_E]24 [R_E]25
[A_O]26 [2_O]27 [3_O]28 [4_O]29 [5_O]30 [6_O]31 [7_O]32 [8_O]33 [9_O]34 [10O]35 [V_O]36 [D_O]37 [R_O]38
[A_P]39 [2_P]40 [3_P]41 [4_P]42 [5_P]43 [6_P]44 [7_P]45 [8_P]46 [9_P]47 [10P]48 [V_P]49 [D_P]50 [R_P]51
*/

    return 0;
}



