#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <time.h>

// Estrutura para representar um quadro de memoria na memória física
typedef struct {
    int indice;           // Número da página que ocupa o quadro
    int ultimo_acesso;    // Tempo do último acesso ao quadro
    int ocupado;          // Flag para indicar se o quadro está ocupado    
} Quadro;

// Estrutura para representar uma entrada de página na tabela de páginas
typedef struct {
    int referencia;       // Flag para indicar se a página está na memória física
    int ultimo_acesso;    // Tempo do último acesso à página
    int suja;             // Flag que indica se a página está limpa ou suja
} Pagina;

void check_algoritmo_substituicao(char *algoritmo_check) {
    // O programa utiliza 4 algoritmos de substituição: 2a, fifo, lru ou random
    // Essa função confere se essa entrada feita por linha de comando do nome do algoritmo
    // é valida
    if(strcmp(algoritmo_check, "2a") == 0 || strcmp(algoritmo_check, "fifo") == 0 || strcmp(algoritmo_check, "random") == 0 || strcmp(algoritmo_check, "lru") == 0) {
        return;
    }
    else {
        printf("Algoritmo de substituição inválido!\n Favor executar novamente escolhendo '2A', 'FIFO', 'LRU' ou 'RANDOM' como algoritmo.\n");
        exit(0);  
    };
}

void check_arquivo_entrada(char *arquivo_check) {
    // O programa deve ler um arquivo de entrada com extensão .log
    // Os arquivos disponíveis são: compilador.log, compressor.log, matriz.log e simulador.log
    // Essa função confere se essa entrada feita por linha de comando do nome do arquivo
    // é valida
    if(strcmp(arquivo_check, "compilador.log") == 0 || strcmp(arquivo_check, "compressor.log") == 0 ||
        strcmp(arquivo_check, "matriz.log") == 0 || strcmp(arquivo_check, "simulador.log") == 0) {
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
    if(!(check_tamanho_quadro % 2) && check_tamanho_quadro >= 2 && check_tamanho_quadro <= 64){
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
    if(!(check_tamanho_memoria % 2) && check_tamanho_memoria >= 128 && check_tamanho_memoria <= 16384){
        return;
    }
    else {
        printf("Tamanho de memória total inválido!\n");
        if(check_tamanho_memoria < 128 || check_tamanho_memoria> 16384){
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


void relatorio_estatisticas(char *arquivo_entrada, int tamanho_quadro, int tamanho_memoria, char *algoritmo_substituicao, int acessos_totais,
                            int acessos_leitura, int acessos_escrita, int num_page_faults, int num_dirty_pages) {
    // Esta funcao imprime no terminal os parâmetros de entrada do programa e as estatísiticas coletadas durante a execução do simulador
    printf("--------------------------------\n");
    printf("Parametros de entrada:\n");
    printf("Arquivo de entrada: %s\n", arquivo_entrada);
    printf("Tamanho da memoria: %d KB\n", tamanho_memoria);
    printf("Tamanho das páginas: %d KB\n", tamanho_quadro);
    printf("Tecnica de reposição: %s\n", algoritmo_substituicao);
    printf("--------------------------------\n");
    printf("Estatísitcas:\n");
    printf("Acessos totais à memória: %d\n", acessos_totais);
    printf("Acessos leitura: %d\n", acessos_leitura);
    printf("Acessos escrita: %d\n", acessos_escrita);
    printf("Page faults: %d\n", num_page_faults);
    printf("Dirty pages: %d\n", num_dirty_pages);
    printf("--------------------------------\n");
}

int determinar_pagina(int tamanho_quadro_memoria, unsigned addr){
    // Na linha int page = addr >> (32 - s);, a variável s representa o número de bits menos significativos a serem descartados do endereço addr para obter
    // o número da página correspondente.
    // A expressão (32 - s) calcula a quantidade de bits a serem mantidos no endereço, considerando que um endereço tem 32 bits no total. Subtraindo o valor 
    // de s de 32, obtemos a quantidade de bits a serem mantidos no endereço, que representa a parte relevante para determinar a página.
    // O operador >> realiza um deslocamento à direita dos bits do endereço addr. O deslocamento é determinado pelo valor de (32 - s). Isso significa que os bits menos
    // significativos (os s bits menos significativos) são descartados, e os bits restantes formam o número da página correspondente.
    // Por exemplo, se s for igual a 12 (para páginas de 4KB), então (32 - s) será igual a 20. Isso significa que os 20 bits mais significativos do endereço addr 
    // serão usados para determinar o número da página.
    
    // Calcular o valor de s
    unsigned s, tmp;
    tmp =  tamanho_quadro_memoria * 1024;
    s = 0;
    while (tmp > 1) {
        tmp = tmp >> 1;
        s++;
    }
    // Calcula o número da página a partir do endereço de 32 bits
    int pagina = addr >> s;
    return pagina;
 }

int fifo_replacement(Pagina *tabela_de_paginas, Quadro *memoria_fisica, int indice_pagina, int numero_quadros) {
    // Implementação do algoritmo FIFO (First-In, First-Out)
    int frame_replaced = memoria_fisica[0].indice;
    //printf("Fifo replacement: %d\n", frame_replaced);
    // Deslocar todos os quadros para a esquerda
    for (int i = 1; i < numero_quadros; i++) {
        memoria_fisica[i - 1].indice = memoria_fisica[i].indice;
    }
    // Substituir o último quadro pelo novo
    memoria_fisica[numero_quadros - 1].indice = indice_pagina;
    return frame_replaced;
}

int lru_replacement(Pagina *tabela_de_paginas, Quadro *memoria_fisica, int indice_pagina, int numero_quadros, int tempo_atual) {
    // Implementação do algoritmo LRU (Least Recently Used)
    // This variable will keep track of the index of the frame with the least recently used page.
    int min_index = 0;
    int min_access_time = memoria_fisica[0].ultimo_acesso;
    

    // Encontrar o quadro com o menor tempo de acesso
    // It checks if the next frame has a smaller ultimo_acesso value, indicating that it was accessed more recently.
    for (int i = 1; i < numero_quadros; i++) {
        //printf("Ultimo acesso controle: %d\n", min_access_time);
        if (memoria_fisica[i].ultimo_acesso < min_access_time) {
            min_access_time = memoria_fisica[i].ultimo_acesso;
            min_index = i;
        }
    }

    int frame_replaced = memoria_fisica[min_index].indice;

    // Substituir o quadro encontrado pelo novo
    memoria_fisica[min_index].indice = indice_pagina;
    memoria_fisica[min_index].ultimo_acesso = tempo_atual;

    return frame_replaced;
}
int random_replacement(Pagina *tabela_de_paginas, Quadro *memoria_fisica, int indice_pagina, int numero_quadros) {
    // Implementação do algoritmo aleatório
    int random_position = rand() % numero_quadros;
    int frame_replaced = memoria_fisica[random_position].indice;

    // Substituir um quadro aleatório pelo novo
    memoria_fisica[random_position].indice = indice_pagina;

    return frame_replaced;
}

int segunda_chance_replacement(Pagina *tabela_de_paginas, Quadro *memoria_fisica, int indice_pagina, int numero_quadros) {
    // Implementação do algoritmo Segunda Chance (Second Chance)
    int frame_replaced = -1;
    int i = 0;

    while (frame_replaced == -1) {
        int current_frame = memoria_fisica[i].indice;
        if (tabela_de_paginas[current_frame].referencia == 0) {
            frame_replaced = current_frame;
        } else {
            tabela_de_paginas[current_frame].referencia = 0;
        }

        i = (i + 1) % numero_quadros;  // Circular para o próximo quadro
    }

    // Substituir o quadro selecionado pelo novo
    memoria_fisica[frame_replaced].indice = indice_pagina;

    return frame_replaced;
}

int main (int argc, char *argv[]){
    // tp2virtual lru arquivo.log 4 128
    printf("Executando o programa %s\n", argv[0]);
    
    printf("--------------------------------\n");

    // Validar o número de parâmetros de entrada (linha de comando)
    if(argc != 5){
        printf("O programa requer 4 entradas. Favor executar novamente com o número correto de parâmetros!\n");
        exit(0);
    };
    
    // Parâmetros de entrada (linha de comando)
    // Os parâmetros argv[1] e argv[2] são transformados para o lowercase (função tolower()) para facilitar a conferência
    char *algoritmo_substituicao_aux = argv[1];
    char algoritmo_substituicao[20];
    strcpy(algoritmo_substituicao, algoritmo_substituicao_aux);
    for (int i = 0; algoritmo_substituicao[i]; i++) {
        algoritmo_substituicao[i] = tolower(algoritmo_substituicao[i]);
    }
    // Tratamento caso a entrada do nome do algoritmo não esteja como sigla
    if (strcmp(algoritmo_substituicao, "segunda chance") == 0 || strcmp(algoritmo_substituicao, "segundachance") == 0) {
        strcpy(algoritmo_substituicao, "2a");
    }
    char* arquivo_entrada_memoria_aux = argv[2];
    char arquivo_entrada_memoria[20];
    strcpy(arquivo_entrada_memoria, arquivo_entrada_memoria_aux);

    for (int i = 0; arquivo_entrada_memoria[i]; i++) {
        arquivo_entrada_memoria[i] = tolower(arquivo_entrada_memoria[i]);
    }

    // Os parâmetros argv[3] e argv[4] são transformados em int (função atoi()) pois serão tratados como numéricos
    // pela lógica do código
    int tamanho_quadro_memoria = atoi(argv[3]);
    // Tamanho em bytes da página (binary)
    //int tamanho_quadro_memoria = tamanho_quadro_memoria_aux * pow(2,10);
    // Tamanho em bytes da página (binary)
    int tamanho_memoria_total = atoi(argv[4]);
    // int tamanho_memoria_total  = tamanho_memoria_total_aux * pow(2,10);

    // Funções para validação das entradas 
    // Cancela a execução do programa caso alguma entrada não seja validada
    check_algoritmo_substituicao(algoritmo_substituicao);
    check_arquivo_entrada(arquivo_entrada_memoria);
    check_tamanho_quadro_memoria(tamanho_quadro_memoria);
    check_tamanho_memoria_total(tamanho_memoria_total);

    // Calcula o número de quadros na memória física
    int numero_quadros = tamanho_memoria_total / tamanho_quadro_memoria;

    // Aloca espaço para a tabela de páginas
    Pagina *tabela_de_paginas = (Pagina *) malloc(sizeof(Pagina) * (1 << 21));
    // Inicializa a tabela de páginas
    if (tabela_de_paginas != NULL) {
        memset(tabela_de_paginas, 0, sizeof(Pagina) * (1 << 21));
    } else {
        printf("Nâo foi possível alocar memória para tabela_de_paginas.\n");
        exit(1);
    }

    // Aloca espaço para a memória física
    Quadro *memoria_fisica = (Quadro *) malloc(sizeof(Quadro) * numero_quadros);
    // Inicializa a memória física
    if (memoria_fisica != NULL) {
        memset(memoria_fisica, 0, sizeof(Quadro) * numero_quadros);   
    } else {
        printf("Não foi possível alocar memoria para memoria_fisica.\n");
        exit(1);
    }

    // Abertura do arquivo de entrada com extensão .log no modo leitura
    FILE *fptr = fopen(arquivo_entrada_memoria, "r");
    // Aponta o erro e encerra o programa caso a leitura do arquivo acima não funcione corretamente 
    if(fptr== NULL){
        printf("Erro na abertura do arquivo de memória de entrada. Favor verificar seu arquivo!\n");
        exit(1);
    }

    // Variáveis de controle de ultimo acesso
    int current_time = 0;

    // Seed para geração de números aleatórios
    srand(time(NULL));

    // Variáveis para coletar estatísticas
    int acessos_totais = 0;
    int acessos_leitura = 0;
    int acessos_escrita = 0;
    int num_page_faults = 0;
    int num_dirty_pages = 0;

    printf("Executando simulador ...\n");
    // Loop principal para processar os acessos à memória
    unsigned addr;
    char rw;
    while (fscanf(fptr, "%x %c\n", &addr, &rw) == 2) {
        acessos_totais++;
        // Incrementa o contador de tempo
        current_time++;
        //printf("Operação: %c\n", rw);
        // Lê o endereço e a operação (R ou W)
        if (rw == 'W' || rw == 'w' ) {
        acessos_escrita++;
        }  
        if (rw == 'R'|| rw == 'r') {
        acessos_leitura++;
        }   
        
        int indice_pagina = determinar_pagina(tamanho_quadro_memoria, addr);
        //printf("Acessing page: %d\n", indice_pagina);
        //printf("Page ref: %d\n", tabela_de_paginas[page].referencia);

        // Verifica se a página está na memória física
        if (tabela_de_paginas[indice_pagina].referencia != 0){

            
            //printf("Pagina já está na memória fisica (Sem page fault). Esta alocada no quadro: %d\n", aux);
            // página na memória física
            // atualiza ultimo acesso
            int aux = -1;
            for(int i = 0; i <numero_quadros; i++){
                if(memoria_fisica[i].indice == indice_pagina){
                    aux = i;
                }
            }
            tabela_de_paginas[indice_pagina].ultimo_acesso = current_time;
            memoria_fisica[aux].ultimo_acesso = current_time;  
            if(rw == 'W'){
                //Teve que ser escrita de volta no disco
                // Operação de escrita em página na memória física
                num_dirty_pages++;
                tabela_de_paginas[indice_pagina].suja = 1;
            }
            
        } else {
            // pagina não está na memória física
            // printf("Pagina nao esta na memoria fisica! Page fault\n");
            num_page_faults++;

            // Verifica se há um quadro vazio na memória física
            int found_empty_frame = -1;
            for (int i = 0; i < numero_quadros; i++) {
            //printf("Memoria física no quadro %d está livre? %d\n",i, memoria_fisica[i].ocupado);
                if (memoria_fisica[i].ocupado == 0) {
                    //printf("Quadro vazio encontrado! ");
                    //("Memoria alocada ao quadro: %d\n", i);
                    // atualiza memoria fisica
                    memoria_fisica[i].ocupado = 1;
                    memoria_fisica[i].indice = indice_pagina;
                    memoria_fisica[i].ultimo_acesso = current_time;
                    found_empty_frame = 1;
                    break;
                }
            }
            // Se não há um quadro vazio, utiliza o algoritmo de substituição correspondente  
            int frame_replaced = -1;             
            if (found_empty_frame == -1) {
                //printf("Sem quadro vazio! Vamos usar uma técnica de reposição\n");
                if (strcmp(algoritmo_substituicao, "fifo") == 0) {
                    frame_replaced = fifo_replacement(tabela_de_paginas, memoria_fisica, indice_pagina, numero_quadros);
                } else if (strcmp(algoritmo_substituicao, "lru") == 0) {
                    frame_replaced = lru_replacement(tabela_de_paginas, memoria_fisica, indice_pagina, numero_quadros, current_time);
                } else if (strcmp(algoritmo_substituicao, "random") == 0) {
                    frame_replaced = random_replacement(tabela_de_paginas, memoria_fisica, indice_pagina, numero_quadros);
                } else if (strcmp(algoritmo_substituicao, "2a") == 0) {
                    frame_replaced = segunda_chance_replacement(tabela_de_paginas, memoria_fisica, indice_pagina, numero_quadros);
                } 

                if(tabela_de_paginas[frame_replaced].suja == 1 && rw == 'W'){
                     //Teve que ser escrita de volta no disco
                    // Operação de escrita em página na memória física
                    num_dirty_pages++;
                }

                //Atualiza a tabela de páginas e a memória com o processo que não está presente
                tabela_de_paginas[frame_replaced].referencia = 0;
                tabela_de_paginas[frame_replaced].ultimo_acesso = 0;
                //tabela_de_paginas[frame_replaced].suja = 0;
                //printf("Frame %d replaced\n", frame_replaced);
            }

            // Atualiza a tabela de páginas
            tabela_de_paginas[indice_pagina].referencia = 1;
            tabela_de_paginas[indice_pagina].ultimo_acesso = current_time;
            if(rw == 'W'){
                tabela_de_paginas[indice_pagina].suja = 1;
                }

            //printf("Dirty\n");
            //Página fica suja!
           // tabela_de_paginas[indice_pagina].suja = 1;         
        }             
                
    };

    // Função para apresentar o relatório com parâmetros de entrada e estatísitcas geradas durante a execução do simulador
    relatorio_estatisticas(arquivo_entrada_memoria, tamanho_quadro_memoria, tamanho_memoria_total, algoritmo_substituicao, acessos_totais,
                            acessos_leitura, acessos_escrita, num_page_faults,num_dirty_pages);

    // Liberar a memória alocada
    free(tabela_de_paginas);
    free(memoria_fisica);

    // Fechamento do arquivo
    fclose(fptr);

    return 0;
}