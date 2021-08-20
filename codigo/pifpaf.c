/****************************************************
* Estrutura de Dados 1 - Trabalho Prático           * 
* Aluno: Daniel Augusto Pires de Castro RA: 2240246 *
****************************************************/

#include "operacoes.h"
//Optei por deixar os protótipos das funções do jogo no operacoes.h 

int main (){

    limparTela();
    srand(time(NULL));

    //Variáveis flags que se alteram de acordo com escolhas do jogador
    int modo, jogando = 1;

    //Cabeçalho
    printf("\tPIFE-PAFE\nJogo implementado por Daniel Augusto Pires de Castro\n\n");
    printf("Bem-vindo jogador.\n\n"); 

    //Laço principal dos modos de jogo
    while (jogando == 1){
        printf("--------------NOVO JOGO--------------\n\n");

        //Escolha do jogador
        printf("Escolha seu modo de jogo:\n[1] Solo\t [2] Contra o Computador\n");
        scanf("%d", &modo);
        
        //Chama as funções correspondentes ao modo em questão
        if (modo == 1)
            pifePafeSolo();
        else
            pifePafeComputador();

        //Escolha do jogador
        printf("Jogar novamente?\n[1] Sim\t [2] Não\n");
        scanf("%d", &jogando);
        limparTela();
    }

    return 0;
}

void pifePafeSolo(){
    
    //Vetor essencial para converter números a suas respectivas cartas
    Carta *vetorID = geraVetorIDs();

    //Tamanhos de referência
    int tamanho_deck = TAMD, 
        tamanho_mao_max = TAMM;
    
    //Cria deck para embarará-lho
    int *deck = geraDeck(tamanho_deck);
    embaralhaDeck(deck, tamanho_deck);

    //Controlam a mão
    int tamanho_mao = 0, copia_tamanho_mao;
    int *mao = geraMao(deck, &tamanho_deck, &tamanho_mao, tamanho_mao_max);

    //Variáveis que controlam eventos do jogo
    int venceu = 0, decisao = 1, indicadora, indice, rodada = 0;

    //Pilhas principais (cemitério) e auxiliares
    Pilha *cemiterio = criarPilha();
    Pilha *cartas_definitivas = criarPilha(), *cartas_temporarias = criarPilha(),
          *duplas = criarPilha(), *trincas = criarPilha();

    //Laço de repetição que define a persistência do jogo
    while (!venceu && decisao == 1){
        
        limparTela();
        rodada++;
        indicadora = 1;
        printf("\n--------------RODADA %d---------------\n\n", rodada);
        
        //Informação ao jogador
        printf("Cartas na sua mão antes da compra:\n");
        imprimeCartas(vetorID, mao, tamanho_mao);

        compraCartaDeck(mao, &tamanho_mao, deck, &tamanho_deck);

        //Necesário porque essa medida no final irá indicar o índice limite de cartas descartáveis
        copia_tamanho_mao = tamanho_mao;

        //Realiza o backtracking inicial que prioriza trincas
        backtrackingTrinca(mao, copia_tamanho_mao, cartas_temporarias, &cartas_definitivas);
        //Antes de copiar a pilha de trincas, é desalocada para liberar memória
        desalocarPilha(trincas);
        trincas = copiaPilha(cartas_definitivas);
        reorganizaMao(mao, &copia_tamanho_mao, &cartas_definitivas);
            
        //Realiza o backtracking inicial que prioriza duplas
        backtrackingDupla(mao, copia_tamanho_mao, cartas_temporarias, &cartas_definitivas);
        //Antes de copiar a pilha de duplas, é desalocada para liberar memória
        desalocarPilha(duplas);
        duplas = copiaPilha(cartas_definitivas);
        reorganizaMao(mao, &copia_tamanho_mao, &cartas_definitivas);
            
        //Informações ao jogador
        printf("Carta comprada do deck.\n\n");
        printf("Cartas na sua mão após a compra:\n");
        imprimeCartas(vetorID, mao, tamanho_mao);
        if (!pilhaVazia(trincas)){
            printf("Trincas formadas:\n");
            imprimePilhaCartas(vetorID, trincas, tamanhoPilha(trincas));
            //Confere se a quantidade de trincas chegou ao máximo para quebrar o laço e vencer
            if (tamanhoPilha(trincas) == tamanho_mao_max - tamanho_mao_max%3){
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

        //Dadas todas as informações ao jogador, é pedido para selecionar opções
        printf("Como descartar?\n[1] Escolha\t [2] Aleatório\n");
        scanf("%d", &decisao);

        //Se ele quiser escolher a carta, ele escolhe qual descartar da lista
        if (decisao == 1){
            printf("Escolha qual carta (1 a primeira, 2 a segunda, e assim por diante):\n");
            scanf("%d", &indice);
            indice--;
            //Caso for um índice inválido, a fim de evitar inconsistência, é usado um aleatório
            if (indice < 0 || indice >= copia_tamanho_mao)
                indice = rand()%copia_tamanho_mao;
        }
        else
            indice = rand()%copia_tamanho_mao;
        
        //Finalmente a escolhida é descartada
        descartaCarta(mao, &tamanho_mao, &cemiterio, mao[indice]);
        printf("Carta descartada:\n");
        imprimePilhaCartas(vetorID, cemiterio, 1);

        //Para poder sair ou não
        printf("Próxima rodada?\n[1] Sim\t [2] Não\n");   
        scanf("%d", &decisao);
    }

    //Caso o laço de repetição tenha sido quebrado de tal modo que o jogador tenha vencido ou não
    if (venceu)
        printf("Você venceu!\n\n");
    else 
        printf("Ninguém venceu!\n\n");

    //Desaloca tudo o que for necessário a fim de liberar memória
    free(vetorID);
    free(deck); 
    free(mao); 
    desalocarPilha(cemiterio);
    desalocarPilha(trincas);
    desalocarPilha(duplas);
}

void pifePafeComputador(){

    //Vetor essencial para converter números a suas respectivas cartas
    Carta *vetorID = geraVetorIDs();

    //Tamanhos de referência
    int tamanho_deck = TAMD, 
        tamanho_mao_max = TAMM;

    //Cria deck para embarará-lho
    int *deck = geraDeck(tamanho_deck);
    embaralhaDeck(deck, tamanho_deck);

    //Controlam a mão
    int tamanho_mao = 0, tamanho_mao2 = 0, copia_tamanho_mao = tamanho_mao_max, copia_tamanho_mao2;
    int *mao = geraMao(deck, &tamanho_deck, &tamanho_mao, tamanho_mao_max);
    int *mao2 = geraMao(deck, &tamanho_deck, &tamanho_mao2, tamanho_mao_max);

    //Controlam comparações para definir a continuidade do jogo
    int descartaveis_anterior = 0, descartaveis_anterior2 = 0,
        numero_trincas = 0, numero_trincas2 = 0, topo_cemiterio;

    //Variáveis flags ou que controlam eventos do jogo
    int venceu = 0, decisao = 1, indicadora, indice,  
        rodada = 0, dificuldade, computador_inicia = 0;

    //Pilhas principais (cemitério) e auxiliares
    Pilha *cemiterio = criarPilha(), *cartas_definitivas = criarPilha(), 
          *cartas_temporarias = criarPilha(), *duplas = criarPilha(), *trincas = criarPilha();

    //Opções do jogador
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

    //Volta a decisão para o valor default a fim de entrar no laço
    decisao = 1;

    while (!venceu && decisao == 1){
        
        limparTela();
        rodada++;
        printf("\n--------------RODADA %d---------------\n\n", rodada);
        indicadora = 1;

        //Caso o computador vá primeiro, é a vez dele
        if (computador_inicia){
            //Informação ao jogador
            printf("Vez do computador de jogar.\n\n");

            //Quando o jogo começa, a pilha está vazia, então isso evita de acontecer            
            if (!pilhaVazia(cemiterio)){
                
                //Armazena já que será descartado depois
                topo_cemiterio = topPilha(cemiterio);

                //Compra primeiro a carta do cemitério para analisar se vale a pena comprá-lo
                compraCartaCemiterio(mao2, &tamanho_mao2, &cemiterio);
                copia_tamanho_mao2 = tamanho_mao2;
                
                //Realiza o backtracking de trinca entre as cartas, incluindo o topo do cemitério
                backtrackingTrinca(mao2, copia_tamanho_mao2, cartas_temporarias, &cartas_definitivas);
                desalocarPilha(trincas);
                trincas = copiaPilha(cartas_definitivas);
                reorganizaMao(mao2, &copia_tamanho_mao2, &cartas_definitivas);

                //Realiza o backtracking de dupla entre as cartas, incluindo o topo do cemitério
                backtrackingDupla(mao2, copia_tamanho_mao2, cartas_temporarias, &cartas_definitivas);
                desalocarPilha(duplas);
                duplas = copiaPilha(cartas_definitivas);
                reorganizaMao(mao2, &copia_tamanho_mao2, &cartas_definitivas);

                //Se valer mesmo a pena ter comprado a carta do cemitério, ela persiste
                if (copia_tamanho_mao2 < descartaveis_anterior2 || numero_trincas2 < tamanhoPilha(trincas)){
                    //Informação ao jogador
                    printf("Computador comprou do topo do cemitério.\n\n");
                    indicadora = 0;
                }
                //Caso o contrário, a carta é descartada, e é comprada uma do deck
                else        
                    descartaCarta(mao2, &tamanho_mao2, &cemiterio, topo_cemiterio);
                
            }
            //Se tiver sido descartada a carta do cemitério (ou seja, a indicadora não tiver sido alterada)
            if (indicadora){

                //Compra carta e copia tamanho da mão
                compraCartaDeck(mao2, &tamanho_mao2, deck, &tamanho_deck);
                copia_tamanho_mao2 = tamanho_mao2;

                //Realiza backtracking de trinca e depois reorganiza mão
                backtrackingTrinca(mao2, copia_tamanho_mao2, cartas_temporarias, &cartas_definitivas);
                desalocarPilha(trincas);
                trincas = copiaPilha(cartas_definitivas);
                reorganizaMao(mao2, &copia_tamanho_mao2, &cartas_definitivas);

                //Realiza backtracking de dupla e depois reorganiza mão
                backtrackingDupla(mao2, copia_tamanho_mao2, cartas_temporarias, &cartas_definitivas);
                desalocarPilha(duplas);
                duplas = copiaPilha(cartas_definitivas);
                reorganizaMao(mao2, &copia_tamanho_mao2, &cartas_definitivas);

                //Informação ao jogador
                printf("Computador comprou do topo deck.\n\n");
            }

            if (!pilhaVazia(trincas)){
                //Armazenado para conferir na rodada seguinte se a compra do cemitério vale à pena
                numero_trincas2 = tamanhoPilha(trincas);
                //Confere se a quantidade de trincas chegou ao máximo para quebrar o laço e vencer
                if (numero_trincas2 == tamanho_mao_max - tamanho_mao_max%3){
                    venceu = 2;
                    break;
                }
            }

            //Descarta uma carta aleatória dentro das opções de cartas descartáveis
            descartaCarta(mao2, &tamanho_mao2, &cemiterio, mao2[rand()%copia_tamanho_mao2]);
        }

        //Redefine variáveis flags
        indicadora = 1;
        computador_inicia = 1;
        
        //Informações ao jogador
        printf("Sua vez de jogar.\n\n");
        printf("Cartas na sua mão antes da compra:\n");
        imprimeCartas(vetorID, mao, tamanho_mao);

        //Vez do jogador
        if (!pilhaVazia(cemiterio)){

            //Informações ao jogador
            printf("Carta no topo do cemitério:\n");
            imprimePilhaCartas(vetorID, cemiterio, 1);
            topo_cemiterio = topPilha(cemiterio);

            //A análise do cemitério só será feita caso o jogador tenha escolhido a dificuldade fácil
            if (dificuldade == 1){

                //Compra carta e copia tamanho da mão
                compraCartaCemiterio(mao, &tamanho_mao, &cemiterio);
                copia_tamanho_mao = tamanho_mao;

                //Realiza backtracking de trinca e depois reorganiza mão
                backtrackingTrinca(mao, copia_tamanho_mao, cartas_temporarias, &cartas_definitivas);
                desalocarPilha(trincas);
                trincas = copiaPilha(cartas_definitivas);
                reorganizaMao(mao, &copia_tamanho_mao, &cartas_definitivas);

                //Realiza backtracking de dupla e depois reorganiza mão
                backtrackingDupla(mao, copia_tamanho_mao, cartas_temporarias, &cartas_definitivas);
                desalocarPilha(duplas);
                duplas = copiaPilha(cartas_definitivas);
                reorganizaMao(mao, &copia_tamanho_mao, &cartas_definitivas);

                //Sugestões dadas ao jogador para decidir se deve comprar carta do cemitério
                if (copia_tamanho_mao < descartaveis_anterior || numero_trincas < tamanhoPilha(trincas))
                    printf("É recomendável comprar carta do topo do cemitério.\n\n");
                else
                    printf("É recomendável comprar carta do deck.\n\n");
            }

            //Escolha do jogador
            printf("Comprar carta do topo do cemitério?\n[1] Sim\t [2] Não\n");   
            scanf("%d", &decisao);

            if (decisao == 1){
                //Se valer mesmo a pena ter comprado a carta do cemitério, ela persiste
                indicadora = 0;
                //Caso a dificuldade for difícil, ela ainda não foi comprada, então faz-se necessário
                if (dificuldade == 2)
                    compraCartaCemiterio(mao, &tamanho_mao, &cemiterio);
                printf("Carta comprada do topo do cemitério.\n\n");
            }
            //Caso contrário, e ainda sendo a dificuldade, é descartada a carta comprada para análise
            else if (dificuldade == 1)
                descartaCarta(mao, &tamanho_mao, &cemiterio, topo_cemiterio);
            
        }
        //Se tiver sido descartada a carta do cemitério (ou seja, a indicadora não tiver sido alterada)
        if (indicadora){

            //Compra carta e copia tamanho da mão
            compraCartaDeck(mao, &tamanho_mao, deck, &tamanho_deck);
            copia_tamanho_mao = tamanho_mao;

            //Realiza backtracking de trinca para verificar se o jogo foi vencido
            backtrackingTrinca(mao, copia_tamanho_mao, cartas_temporarias, &cartas_definitivas);
            desalocarPilha(trincas);
            trincas = copiaPilha(cartas_definitivas);
            reorganizaMao(mao, &copia_tamanho_mao, &cartas_definitivas);

            //Realizará backtracking de trinca apenas caso a dificuldade for 1, para informar sugestões
            if (dificuldade == 1){
                backtrackingDupla(mao, copia_tamanho_mao, cartas_temporarias, &cartas_definitivas);
                desalocarPilha(duplas);
                duplas = copiaPilha(cartas_definitivas);
                reorganizaMao(mao, &copia_tamanho_mao, &cartas_definitivas);
            }
            //Informação ao jogador
            printf("Carta comprada do deck.\n\n");
        }

        //Informação ao jogador
        printf("Cartas na sua mão após a compra:\n");
        imprimeCartas(vetorID, mao, tamanho_mao);

        if (!pilhaVazia(trincas)){
            //Armazenado para conferir na rodada seguinte se a compra do cemitério vale à pena
            numero_trincas = tamanhoPilha(trincas);
            //Confere para ver venceu
            if (numero_trincas == tamanho_mao_max- tamanho_mao_max%3){
                venceu = 1;
                break;
            }
        }

        //Informações de sugestões serão passadas caso o jogador tenha escolhido fácil
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

        //Escolha do jogador
        printf("Como descartar?\n[1] Escolha\t [2] Aleatório\n");
        scanf("%d", &decisao);

        //Se ele quiser escolher a carta, ele escolhe qual descartar da lista
        if (decisao == 1){
            printf("Escolha qual carta (1 a primeira, 2 a segunda, e assim por diante):\n");
            scanf("%d", &indice);
            indice--;
            //Caso for um índice inválido, ele torna-se aleatório
            if (indice < 0 || indice >= copia_tamanho_mao)
                indice = rand()%copia_tamanho_mao;
        }
        //Escolhido índice aleatório de acordo com o quanto foi mudada a variável de tamanho da mão
        else
            indice = rand()%copia_tamanho_mao;
        
        descartaCarta(mao, &tamanho_mao, &cemiterio, mao[indice]);

        //Escolha do jogador
        printf("Próxima rodada?\n[1] Sim\t [2] Não\n");   
        scanf("%d", &decisao);

        //Valores armazenados para conferir se vale a pena comprar a carta do topo do cemitério
        descartaveis_anterior = copia_tamanho_mao;
        descartaveis_anterior2 = copia_tamanho_mao2;
    }

    //Caso o laço de repetição tenha sido quebrado de tal modo que o jogador tenha vencido ou não
    if (venceu == 1)
        printf("Você venceu!\n\n");
    else if (venceu == 2){
        printf("Computador venceu!\n\n");
        //Informações ao jogador
        printf("Trincas do computador:\n");
        imprimePilhaCartas(vetorID, trincas, tamanhoPilha(trincas));
    }
    else 
        printf("Ninguém venceu!\n\n");

    //Desaloca tudo o que for necessário a fim de liberar memória
    free(vetorID);
    free(deck); 
    free(mao); 
    free(mao2); 
    desalocarPilha(cemiterio);
    desalocarPilha(trincas);
    desalocarPilha(duplas);
}
