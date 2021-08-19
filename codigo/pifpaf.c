#include "operacoes.h"

int main (){

    srand(time(NULL));

    int modo, jogando = 1;

    printf("\tPIFE-PAFE\nJogo implementado por Daniel Castro\n\n");
    printf("Bem-vindo jogador.\n\n"); 

    while (jogando == 1){
        printf("--------------NOVO JOGO--------------\n\n");
        printf("Escolha seu modo de jogo:\n[1] Solo\t [2] Contra o Computador\n");
        scanf("%d", &modo);

        if (modo == 1){
            pifePafeSolo();
        }
        else{
            pifePafeComputador();
        }
        printf("Jogar novamente?\n[1] Sim\t [2] Não\n");
        scanf("%d", &jogando);
    }

    return 0;
}

void pifePafeSolo(){
    Carta *vetorID = geraVetorIDs();
    int tamanho_deck = TAMD, 
        tamanho_mao = 0, 
        tamanho_mao_max = TAMM;

    int *deck = geraDeck(tamanho_deck);

    embaralhaDeck(deck, tamanho_deck);

    int *mao = geraMao(deck, &tamanho_deck, &tamanho_mao, tamanho_mao_max);

    int copia_tamanho_mao, descartaveis_anterior = 9;

    int venceu = 0, decisao = 1, indicadora, indice, topo_cemiterio, rodada = 0;

    Pilha *cemiterio = criarPilha();

    Pilha *cartas_definitivas = criarPilha(), *cartas_temporarias = criarPilha(),
          *duplas = criarPilha(), *trincas = criarPilha();

    while (!venceu && decisao == 1){
        rodada++;

        indicadora = 1;

        printf("\n--------------RODADA %d---------------\n\n", rodada);
        printf("Cartas na sua mão antes da compra:\n");
        imprimeCartas(vetorID, mao, tamanho_mao);

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
            if (indice < 0 || indice >= copia_tamanho_mao)
                indice = rand()%copia_tamanho_mao;
        }
        else{
            indice = rand()%copia_tamanho_mao;
        }

        descartaCarta(mao, &tamanho_mao, &cemiterio, mao[indice]);
        printf("Carta descartada:\n");
        imprimePilhaCartas(vetorID, cemiterio, 1);

        printf("Próxima rodada?\n[1] Sim\t [2] Não\n");   
        scanf("%d", &decisao);

        desalocarPilha(trincas);
        desalocarPilha(duplas);

        descartaveis_anterior = copia_tamanho_mao;
    }
    if (venceu)
        printf("\nVocê venceu!\n\n");
    else 
        printf("\nNinguém venceu!\n\n");

    free(vetorID);
    free(deck); 
    free(mao); 
    desalocarPilha(cemiterio);
}

void pifePafeComputador(){

    Carta *vetorID = geraVetorIDs();
    int tamanho_deck = TAMD, 
        tamanho_mao = 0,
        tamanho_mao2 = 0,
        tamanho_mao_max = TAMM;

    int *deck = geraDeck(tamanho_deck);

    embaralhaDeck(deck, tamanho_deck);

    int *mao = geraMao(deck, &tamanho_deck, &tamanho_mao, tamanho_mao_max);
    int *mao2 = geraMao(deck, &tamanho_deck, &tamanho_mao2, tamanho_mao_max);

    int copia_tamanho_mao = tamanho_mao_max, descartaveis_anterior = 9;
    int copia_tamanho_mao2, descartaveis_anterior2 = 9;
    int numero_trincas = 0, numero_trincas2 = 0;

    int venceu = 0, decisao = 1, indicadora, indice, topo_cemiterio, 
        rodada = 0, dificuldade, computador_inicia = 0;

    Pilha *cemiterio = criarPilha();

    Pilha *cartas_definitivas = criarPilha(), *cartas_temporarias = criarPilha(),
          *duplas = criarPilha(), *trincas = criarPilha();

    printf("Escolha a dificuldade:\n[1] Fácil (com sugestões de ações)\t [2] Difícil (sem)\n");
    scanf("%d", &dificuldade);

    printf("Escolha quem iniciar:\n[1] Você\t [2] Computador\t [3] Aleatório\n");
    scanf("%d", &decisao);
    if (decisao == 1)
        computador_inicia = 0;
    else if (decisao == 2)
        computador_inicia = 1;
    else
        computador_inicia = rand()%2;

    decisao = 1;

    while (!venceu && decisao == 1){
        rodada++;

        printf("\n--------------RODADA %d---------------\n\n", rodada);

        indicadora = 1;

        //Caso o computador vá primeiro
        if (computador_inicia){
            printf("Vez do computador de jogar.\n\n");
            
            if (!pilhaVazia(cemiterio)){

                topo_cemiterio = topPilha(cemiterio);

                compraCartaCemiterio(mao2, &tamanho_mao2, &cemiterio);

                copia_tamanho_mao2 = tamanho_mao2;

                backtrackingTrinca(mao2, copia_tamanho_mao2, cartas_temporarias, &cartas_definitivas);
                trincas = copiaPilha(cartas_definitivas);
                reorganizaMao(mao2, &copia_tamanho_mao2, &cartas_definitivas);

                backtrackingDupla(mao2, copia_tamanho_mao2, cartas_temporarias, &cartas_definitivas);
                duplas = copiaPilha(cartas_definitivas);
                reorganizaMao(mao2, &copia_tamanho_mao2, &cartas_definitivas);

                if (copia_tamanho_mao2 < descartaveis_anterior2 || numero_trincas2 < tamanhoPilha(trincas)){
                    printf("Computador comprou do topo do cemitério.\n\n");
                    indicadora = 0;
                }
                else{
                    descartaCarta(mao2, &tamanho_mao2, &cemiterio, topo_cemiterio);
                    desalocarPilha(trincas);
                    desalocarPilha(duplas);
                }
            }
            if (indicadora){
                compraCartaDeck(mao2, &tamanho_mao2, deck, &tamanho_deck);
                copia_tamanho_mao2 = tamanho_mao2;

                backtrackingTrinca(mao2, copia_tamanho_mao2, cartas_temporarias, &cartas_definitivas);
                trincas = copiaPilha(cartas_definitivas);
                reorganizaMao(mao2, &copia_tamanho_mao2, &cartas_definitivas);
                
                backtrackingDupla(mao2, copia_tamanho_mao2, cartas_temporarias, &cartas_definitivas);
                duplas = copiaPilha(cartas_definitivas);
                reorganizaMao(mao2, &copia_tamanho_mao2, &cartas_definitivas);

                printf("Computador comprou do topo deck.\n\n");
            }

            if (!pilhaVazia(trincas)){
                numero_trincas2 = tamanhoPilha(trincas);
                if (numero_trincas2 == tamanho_mao_max- 1){
                    venceu = 2;
                    break;
                }
            }
            descartaCarta(mao2, &tamanho_mao2, &cemiterio, mao2[rand()%copia_tamanho_mao2]);

            desalocarPilha(trincas);
            desalocarPilha(duplas);
        }

        indicadora = 1;

        computador_inicia = 1;
        
        printf("Sua vez de jogar.\n\n");

        printf("Cartas na sua mão antes da compra:\n");
        imprimeCartas(vetorID, mao, tamanho_mao);

        //Vez do jogador
        if (!pilhaVazia(cemiterio)){

            printf("Carta no topo do cemitério:\n");
            imprimePilhaCartas(vetorID, cemiterio, 1);
            topo_cemiterio = topPilha(cemiterio);

            if (dificuldade == 1){
                compraCartaCemiterio(mao, &tamanho_mao, &cemiterio);

                copia_tamanho_mao = tamanho_mao;

                backtrackingTrinca(mao, copia_tamanho_mao, cartas_temporarias, &cartas_definitivas);
                trincas = copiaPilha(cartas_definitivas);
                reorganizaMao(mao, &copia_tamanho_mao, &cartas_definitivas);

                backtrackingDupla(mao, copia_tamanho_mao, cartas_temporarias, &cartas_definitivas);
                duplas = copiaPilha(cartas_definitivas);
                reorganizaMao(mao, &copia_tamanho_mao, &cartas_definitivas);

                if (copia_tamanho_mao < descartaveis_anterior || numero_trincas < tamanhoPilha(trincas))
                    printf("É recomendável comprar carta no topo do cemitério.\n\n");
                else
                    printf("Não é recomendável comprar carta no topo do cemitério.\n\n");
            }

            printf("Comprar carta do topo do cemitério?\n[1] Sim\t [2] Não\n");   
            scanf("%d", &decisao);

            if (decisao == 1){
                indicadora = 0;
                if (dificuldade == 2)
                    compraCartaCemiterio(mao, &tamanho_mao, &cemiterio);
                printf("Carta comprada do topo do cemitério.\n\n");
            }
            else if (dificuldade == 1){
                descartaCarta(mao, &tamanho_mao, &cemiterio, topo_cemiterio);
                desalocarPilha(trincas);
                desalocarPilha(duplas);
            }
        }
        if (indicadora){

            compraCartaDeck(mao, &tamanho_mao, deck, &tamanho_deck);

            if (dificuldade == 1){

                copia_tamanho_mao = tamanho_mao;

                backtrackingTrinca(mao, copia_tamanho_mao, cartas_temporarias, &cartas_definitivas);
                trincas = copiaPilha(cartas_definitivas);
                reorganizaMao(mao, &copia_tamanho_mao, &cartas_definitivas);
                
                backtrackingDupla(mao, copia_tamanho_mao, cartas_temporarias, &cartas_definitivas);
                duplas = copiaPilha(cartas_definitivas);
                reorganizaMao(mao, &copia_tamanho_mao, &cartas_definitivas);

            }

            printf("Carta comprada do deck.\n\n");

        }

        printf("Cartas na sua mão após a compra:\n");
        imprimeCartas(vetorID, mao, tamanho_mao);

        if (!pilhaVazia(trincas)){
            numero_trincas = tamanhoPilha(trincas);
            if (numero_trincas == tamanho_mao_max- 1){
            //if (tamanhoPilha(trincas) == tamanho_mao_max - 1){
                venceu = 1;
                break;
            }
        }
        if (dificuldade == 1){
            if (!pilhaVazia(trincas)){
                printf("Trincas formadas:\n");
                imprimePilhaCartas(vetorID, trincas, tamanhoPilha(trincas));
            }
            
            if (!pilhaVazia(duplas)){
                printf("Duplas formadas\n");
                imprimePilhaCartas(vetorID, duplas, tamanhoPilha(duplas));
            }
            printf("Cartas descartáveis na sua mão:\n");
            imprimeCartas(vetorID, mao, copia_tamanho_mao);
        }

        printf("Como descartar?\n[1] Escolha\t [2] Aleatório\n");
        scanf("%d", &decisao);

        if (decisao == 1){
            printf("Escolha qual carta (1 a primeira, 2 a segunda, e assim por diante):\n");
            scanf("%d", &indice);
            indice--;
            if (indice < 0 || indice >= copia_tamanho_mao)
                indice = rand()%copia_tamanho_mao;
        }
        else{
            indice = rand()%copia_tamanho_mao;
        }
        descartaCarta(mao, &tamanho_mao, &cemiterio, mao[indice]);

        printf("Próxima rodada?\n[1] Sim\t [2] Não\n");   
        scanf("%d", &decisao);
         

        if (dificuldade == 1){
            desalocarPilha(trincas);
            desalocarPilha(duplas);
            descartaveis_anterior = copia_tamanho_mao;
        }
        descartaveis_anterior2 = copia_tamanho_mao2;
    }
    if (venceu == 1)
        printf("\nVocê venceu!\n\n");
    else if (venceu == 2){
        printf("\nComputador venceu!\n\n");
        printf("Trincas do computador:\n");
        imprimePilhaCartas(vetorID, trincas, tamanhoPilha(trincas));
    }
    else 
        printf("\nNinguém venceu!\n\n");

    free(vetorID);
    free(deck); 
    free(mao); 
    free(mao2); 
    desalocarPilha(cemiterio);
    if (!pilhaVazia(trincas))
        desalocarPilha(trincas);
    if (!pilhaVazia(duplas))
        desalocarPilha(duplas);
    
}
