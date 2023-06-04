#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <time.h>

// Estrutura para representar uma entrada de página na tabela de páginas
typedef struct {
    int referencia;      // Flag para indicar se a página está na memória física
    int ultimo_acesso;     // Tempo do último acesso à página
} Frame;

void check_algoritmo_substituicao(char *algoritmo_check) {
    // O programa utiliza 4 algoritmos de substituição: 2a, fifo, lru ou random
    // Essa função confere se essa entrada feita por linha de comando do nome do algoritmo
    // é valida
    if(strcmp(algoritmo_check, "2a") == 0 || strcmp(algoritmo_check, "fifo") == 0|| strcmp(algoritmo_check, "random") == 0 || strcmp(algoritmo_check, "lru") == 0) {
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
    if(strcmp(arquivo_check, "compilador.log") == 0 || strcmp(arquivo_check, "compressor.log") == 0 ||
        strcmp(arquivo_check, "matriz.log") == 0 || strcmp(arquivo_check, "simulador.log")== 0) {
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



void relatorio_estatisticas(char *arquivo_entrada, int tamanho_quadro, int tamanho_memoria, char *algoritmo_substituicao, int acessos_totais,
                            int acessos_leitura, int acessos_escrita) {
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
    printf("Páginas lidas: %d\n", acessos_leitura);
    printf("Paginas escritas: %d\n", acessos_escrita);
    printf("--------------------------------\n");
}

int fifo_replacement(Frame *page_table, Frame *physical_memory, int page, int num_frames) {
    // Implementação do algoritmo FIFO (First-In, First-Out)
    int frame_replaced = physical_memory[0].referencia;

    // Deslocar todos os quadros para a esquerda
    for (int i = 1; i < num_frames; i++) {
        physical_memory[i - 1].referencia = physical_memory[i].referencia;
    }

    // Substituir o último quadro pelo novo
    physical_memory[num_frames - 1].referencia = page;

    return frame_replaced;
}

int lru_replacement(Frame *page_table, Frame *physical_memory, int page, int num_frames) {
    // Implementação do algoritmo LRU (Least Recently Used)
    int frame_replaced = physical_memory[0].referencia;
    int min_access_time = physical_memory[0].ultimo_acesso;
    int min_index = 0;

    // Encontrar o quadro com o menor tempo de acesso
    for (int i = 1; i < num_frames; i++) {
        if (physical_memory[i].ultimo_acesso < min_access_time) {
            min_access_time = physical_memory[i].ultimo_acesso;
            min_index = i;
        }
    }

    // Substituir o quadro encontrado pelo novo
    physical_memory[min_index].referencia = page;

    return frame_replaced;
}
int random_replacement(Frame *page_table, Frame *physical_memory, int page, int num_frames) {
    // Implementação do algoritmo aleatório
    int frame_replaced = physical_memory[rand() % num_frames].referencia;

    // Substituir um quadro aleatório pelo novo
    physical_memory[rand() % num_frames].referencia = page;

    return frame_replaced;
}

int segunda_chance_replacement(Frame *page_table, Frame *physical_memory, int page, int num_frames) {
    // Implementação do algoritmo Segunda Chance (Second Chance)
    int frame_replaced = -1;
    int i = 0;

    while (frame_replaced == -1) {
        int current_frame = physical_memory[i].referencia;
        if (page_table[current_frame].referencia == 0) {
            frame_replaced = current_frame;
        } else {
            page_table[current_frame].referencia = 0;
        }

        i = (i + 1) % num_frames;  // Circular para o próximo quadro
    }

    // Substituir o quadro selecionado pelo novo
    physical_memory[frame_replaced].referencia = page;

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
    char *algoritmo_substitucao = argv[1];
    
    // Tratamento caso a entrada do nome do algoritmo não esteja como siga
    //if (strcmp(algoritmo_substitucao, "segunda chance") || strcmp(algoritmo_substitucao, "segundachance")) {
        //algoritmo_substitucao = "2a";
    //};
    char *arquivo_entrada_memoria = argv[2];
   
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
    check_algoritmo_substituicao(algoritmo_substitucao);
    //check_arquivo_entrada(arquivo_entrada_memoria);
    check_tamanho_quadro_memoria(tamanho_quadro_memoria);
    check_tamanho_memoria_total(tamanho_memoria_total);

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
    tmp = tamanho_quadro_memoria;
    s = 0;
    while (tmp > 1) {
        tmp = tmp >> 1;
        s++;
    }
    //printf("%d\n", s);
    //printf("%d\n", tamanho_memoria_total);
    //printf("%d\n", tamanho_quadro_memoria);
    
   
    // Calcula o número de quadros na memória física
    int num_frames = tamanho_memoria_total / tamanho_quadro_memoria;
    //printf("%d\n", num_frames);

    // Aloca espaço para a tabela de páginas
    Frame *page_table = (Frame *) malloc(sizeof(Frame) * (1 << 21));

    // Inicializa a tabela de páginas
    memset(page_table, 0, sizeof(Frame) * (1 << 21));

    // Aloca espaço para a memória física
    Frame *physical_memory = (Frame *) malloc(sizeof(Frame) * num_frames);

    // Inicializa a memória física
    memset(physical_memory, 0, sizeof(Frame) * num_frames);

     // Abertura do arquivo de entrada com extensão .log no modo leitura
    FILE *fptr = fopen(arquivo_entrada_memoria, "r");
    // Aponta o erro e encerra o programa caso a leitura do arquivo acima não funcione corretamente 
    if(fptr== NULL){
        printf("Erro na abertura do arquivo de memória de entrada. Favor verificar seu arquivo!\n");
        return 1;
    }

    // Variáveis para estatísticas
    int num_accesses = 0;
    int num_page_faults = 0;
    int num_dirty_pages_written = 0;

    // Variáveis de controle
    int current_time = 0;

    // Seed para geração de números aleatórios
    srand(time(NULL));

    // Variáveis para coletar estatísticas
    int acessos_totais = 0;
    int acessos_leitura = 0;
    int acessos_escrita = 0;

    unsigned addr;
    char rw;

    printf("Executando simulador ...\n");
    // Loop principal para processar os acessos à memória

    while (fscanf(fptr, "%x %c\n", &addr, &rw) == 2) {
        acessos_totais++;
        
        // Lê o endereço e a operação (R ou W)
        
        if (rw == 'W') {
        acessos_escrita++;
        printf("testeW\n");
        }  
        if (rw == 'R') {
        acessos_leitura++;
        printf("testeL\n");
        }   
        // Calcula o número da página a partir do endereço
        int page = addr >> (32 - s);
        
        // Verifica se a página está na memória física
        if (!page_table[page].referencia) {
            printf("aqui1\n");
            num_page_faults++;

            // Verifica se há um quadro vazio na memória física
            int frame_replaced = -1;
            for (int i = 0; i < num_frames; i++) {
                if (physical_memory[i].referencia == -1) {
                    printf("aqui3\n");
                    frame_replaced = i;
                    break;
                    
                }
            }
            // Se não há um quadro vazio, utiliza o algoritmo de substituição correspondente
            if (frame_replaced == -1) {
                if (strcmp(algoritmo_substitucao, "fifo") == 0) {
                    frame_replaced = fifo_replacement(page_table, physical_memory, page, num_frames);
                } else if (strcmp(algoritmo_substitucao, "lru") == 0) {
                    frame_replaced = lru_replacement(page_table, physical_memory, page, num_frames);
                } else if (strcmp(algoritmo_substitucao, "random") == 0) {
                    frame_replaced = random_replacement(page_table, physical_memory, page, num_frames);
                } else if (strcmp(algoritmo_substitucao, "2a") == 0) {
                    frame_replaced = segunda_chance_replacement(page_table, physical_memory, page, num_frames);
                }
            } else {
                //Há um quadro vazio na memória física
                frame_replaced = 0;
            }

            // Atualiza a tabela de páginas
            page_table[page].referencia = 1;
            page_table[page].ultimo_acesso = current_time;

            // Atualiza o quadro na memória física
            physical_memory[frame_replaced].referencia = page;
            physical_memory[frame_replaced].ultimo_acesso = current_time;
        }
        // Incrementa o contador de tempo
        current_time++;
    };

    // Função para apresentar o relatório com parâmetros de entrada e estatísitcas geradas durante a execução do simulador
    relatorio_estatisticas(arquivo_entrada_memoria, tamanho_quadro_memoria, tamanho_memoria_total, algoritmo_substitucao, acessos_totais,
                            acessos_leitura, acessos_escrita);

    // Liberar a memória alocada
    free(page_table);
    free(physical_memory);

    // Fechamento do arquivo
    fclose(fptr);

    return 0;
}