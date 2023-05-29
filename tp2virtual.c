#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void check_algoritmo_subsituicao(char *algoritmo_check) {
    // O programa utiliza 3 algoritmos de substituição: 2a, fifo, lru ou random
    // Essa função confere se essa entrada feita por linha de comando do nome do algoritmo
    // é valida
    if(strcmp(algoritmo_check, "2a") || strcomp(algoritmo_check, "fifo") || strcmp(algoritmo_check, "random") || strcmp(algoritmo_check, "lru")) {
       return;
    }
    else {
        printf("Alagoritmo de substituição inválido!\n Favor executar novamente escolhendo '2A', 'FIFO', 'LRU' ou 'RANDOM' como algortimo.\n");
        exit(0);  
    };
}

void check_arquivo_entrada(char *arquivo_check) {
    // O programa deve ler um arquivo de entrada com extensão .log
    // Os arquivos disponíveis são: compilador.log, compressor.log, matriz.log e simulador.log
    // Essa função confere se essa entrada feita por linha de comando do nome do arquivo
    // é valida
    if(strcmp(arquivo_check, "compilador.log") || strcmp(arquivo_check, "compressor.log") ||
        strcmp(arquivo_check, "") || strcmp(arquivo_check, "simulador.log")) {
       return;
    }
    else {
        printf("Arquivo de entrada de memória inválido!\n Favor executar novamente escolhendo 'compilador.log', 'compressor.log', 'matriz.log' ou 'simulador.log' como arquivo de entrada.\n");
        exit(0);  
    };
}

void check_tamanho_quadro_memoria(int check_tamanho_quadro) {
    // O tamanho do quadro da memória deve ser um valor positivo maior que zero e múltiplo de 2
    // Além disso, um tamanho razoável para o quadro de memória está na faixa de 2KB a 64KB
    // Esta função valida se essa entrada está dentro destas duas faixas
  	if(!(check_tamanho_quadro % 2) & check_tamanho_quadro >= 2 & check_tamanho_quadro <= 64){
  		return;
  	}
	else {
        printf("Tamanho de quadro de memória inválido!\n");
        if(check_tamanho_quadro < 2 || check_tamanho_quadro > 64){
            printf("Valor fora da faixa razoável! Favor entrar com um valor maior ou igual a 2KB e menor ou igual a 64KB.\n");
        }
        if(check_tamanho_quadro % 2){
            printf("Valor não múltiplo de 2. Favor entrar com um valor que seja divisível por 2.\n");
        }
        if(check_tamanho_quadro < 0){
            printf("Valor negativo. Favor entrar com um valor que seja maior que zero.\n");
        }
		exit(1);  
    };
	}
void check_tamanho_memoria_total(int check_tamanho_memoria) {
    // O tamanho da memória total deve ser um valor positivo maior que zero e múltiplo de 2
    // Além disso, um tamanho razoável paraa memória total está na faixa de 128KB a 16384KB
    // Esta função valida se essa entrada está dentro destas duas faixas
  	if(!(check_tamanho_memoria % 2) & check_tamanho_memoria >= 128 & check_tamanho_memoria <= 16384){
  		return;
  	}
	else {
        printf("Tamanho de memória total inválido!\n");
        if(check_tamanho_memoria < 128 || check_tamanho_memoria > 16384){
            printf("Valor fora da faixa razoável! Favor entrar com um valor maior ou igual a 2KB e menor ou igual a 64KB.\n");
        }
        if(check_tamanho_memoria % 2){
            printf("Valor não múltiplo de 2. Favor entrar com um valor que seja divisível por 2.\n");
        }
        if(check_tamanho_memoria < 0){
            printf("Valor negativo. Favor entrar com um valor que seja maior que zero.\n");
        }
		exit(1);  
    };
	}


void relatorio_estatisticas(char *arquivo_entrada, int tamanho_quadro, int tamanho_memoria, char *algoritmo_substituicao,
                            int acessos_leitura, int acessos_escrita) {
    // Esta funcao imprime no terminal os parâmetros de entrada do programa e as estatísiticas coletadas durante a execução do simulador
    int acessos_totais = acessos_leitura + acessos_escrita;
    printf("Parametros de entrada:\n");
    printf("--------------------------------");
    printf("Arquivo de entrada: %s\n", arquivo_entrada);
    printf("Tamanho da memoria: %d KB\n", tamanho_memoria);
    printf("Tamanho das páginas: %d KB\n", tamanho_quadro);
    printf("Tecnica de reposição: %s\n", algoritmo_substituicao);
    printf("--------------------------------");
    printf("Estatísitcas :\n");
    printf("--------------------------------");
    // printf("Acessos de leitura à memória: %s\n" acessos_leitura);
    // printf("Acessos de escrita à memória: %s\n" acessos_escrita);
    printf("Acessos totais à memória: %s\n", acessos_totais);
    printf("Páginas lidas: %d\n", acessos_leitura);
    printf("Paginas escritas: %d\n", acessos_escrita);
    printf("--------------------------------");
}

int main (int argc, char *argv[]){

    // tp2virtual lru arquivo.log 4 128
    printf("Executando o programa %s\n", argv[0]);

    // Validar o número de parâmetros de entrada (linha de comando)
    if(argc != 5){
        printf("O programa requer 4 entradas. Favor executar novamente com o número correto de parâmetros!\n");
        exit(0);
    }
	
    // Parâmetros de entrada (linha de comando)
    // Os parâmetros argv[1] e argv[2] são transformados para o lowercase (função tolower()) para facilitar a conferência
    char *algoritmo_substitucao = tolower(argv[1]);
    char *arquivo_entrada_memoria = tolower(argv[2]);
    // Os parâmetros argv[3] e argv[4] são transformados em int (função atoi()) pois serão tratados como numéricos
    // pela lógica do código
    int tamanho_quadro_memoria = atoi(argv[3]);
    int tamanho_memoria_total = atoi(argv[4]);

    // Funções para validação das entradas 
    // Cancela a execução do programa caso alguma entrada não seja validada
    check_algoritmo_subsituicao(*algoritmo_substitucao);
    check_arquivo_entrada(*arquivo_entrada_memoria);
    check_tamanho_quadro_memoria(tamanho_quadro_memoria);
    check_tamanho_memoria_total(tamanho_memoria_total);
	
    // Abertura do arquivo de entrada com extensão .log no modo leitura
    FILE *fptr = fopen(arquivo_entrada_memoria,"r");
    // Aponta o erro e encerra o programa caso a leitura do arquivo acima não funcione corretamente 
    if(fptr== NULL){
        printf("Erro na abertura do arquivo de memória de entrada. Favor verificar seu arquivo!\n");
        exit(0);
    }


    // /*
    // Criar a tabela de páginas de acordo com o tamanho especificado.
    // */
    // tabela tabela;
    // criaTabela(&tabela, tamanho_pagina);
    
    // /*
    // Aloca memória para o processo
    // */
    // memoria_processo memoria_processo;
    // criaMemoriaProcesso(&memoria_processo, tamanho_memoria);

    // unsigned int tmpPOS;
    // int tamanho_pagina_real = tamanho_pagina * pow(2, 10); //tamanho da página em bytes

    //unsigned int indice;
    // unsigned int paginas_ = 0;
    int acessos_leitura = 0;
    int acessos_escrita = 0;

    unsigned addr;
    char rw;

    printf("Executando simulador ...\n");

    while(fscanf(fptr, "%x %c", &addr, &rw) != EOF) {
        // Contar o numero de acessos de leitura e escrita
        if(rw == "R") {
            acessos_leitura += 1;
        }
        if(rw == "W") {
            acessos_escrita += 1;
        }

    }
    // while(fscanf(arquivo,"%x %c\n", &tmpPOS, &tmpOP) != EOF){
    //     pulso_clock++;
    //     //incrementa o número de instruções lidas (semelhante aos pulsos de clock)
    //     indice = tmpPOS % tabela.num_entradas;
    //     //achei a pagina, agora vou acessar o conteudo dela

    //     if(tabela.paginas[indice].presente){
    //         //pagina esta na memoria principal e seu endereço é a moldura
    //         //redefinindo último acesso
    //         memoria_processo.molduras[tabela.paginas[indice].moldura].ultimo_acesso = pulso_clock;
    //         //página modificada
    //         memoria_processo.molduras[tabela.paginas[indice].moldura].pagina_modificada = tmpOP == 'W' ? 1 : 0; 
    //     }else{
    //         //pagina nao esta na memoria principal
    //         pageFault++;
    //         unsigned int indice_moldura;
    //         if(!strcmp("fifo", algoritmo_substituicao) || !strcmp("FIFO", algoritmo_substituicao)){
    //             //fifo, me dê a posição da moldura que eu possa fazer a substituição
    //             indice_moldura = fifo_escolha(&memoria_processo, pulso_clock);
    //         }else if(!strcmp("lru", algoritmo_substituicao) || !strcmp("LRU", algoritmo_substituicao)){
    //             //lru, me dê a posição da moldura que eu possa fazer a substituição
    //             indice_moldura = lru_escolha(&memoria_processo, pulso_clock);
    //         }else if(!strcmp("random", algoritmo_substituicao) || !strcmp("RANDOM", algoritmo_substituicao)){
    //              //random, me dê a posição da moldura que eu possa fazer a substituição
    //             indice_moldura = random_escolha(memoria_processo.num_entradas);
    //         }
    //         //a página que ocupava esta moldura não está mais presente
    //         if(memoria_processo.molduras[indice_moldura].pagina){
    //             memoria_processo.molduras[indice_moldura].pagina->presente = 0;
    //             memoria_processo.molduras[indice_moldura].pagina_modificada = 0;
    //         }
    //         //a página referenciada pelo endereço agora esta presente
    //         tabela.paginas[indice].presente = 1;
    //         //a moldura recebe a página e atualiza seus temporizadores
    //         memoria_processo.molduras[indice_moldura].pagina = &tabela.paginas[indice];
    //         memoria_processo.molduras[indice_moldura]._carregamento = pulso_clock;
    //         memoria_processo.molduras[indice_moldura].ultimo_acesso = pulso_clock;

    //     }
    // }

    // Função para apresentar o relatório com parâmetros de entrada e estatísitcas geradas durante a execução do simulador
    relatorio_estatisitcas(*arquivo_entrada_memoria, tamanho_quadro_memoria, tamanho_memoria_total, *algoritmo_substitucao,
                            acessos_leitura, acessos_escrita);

 

    return 0;
}