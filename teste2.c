#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    int page_referenced;      // Flag para indicar se a página está na memória física
    int last_access_time;     // Tempo do último acesso à página
} Frame;
int fifo_replacement(Frame *page_table, Frame *physical_memory, int page) {
    // Implementação do algoritmo FIFO (First-In, First-Out)
    int frame_replaced = physical_memory[0].page_referenced;

    // Deslocar todos os quadros para a esquerda
    for (int i = 1; i < num_frames; i++) {
        physical_memory[i - 1].page_referenced = physical_memory[i].page_referenced;
    }

    // Substituir o último quadro pelo novo
    physical_memory[num_frames - 1].page_referenced = page;

    return frame_replaced;
}

int lru_replacement(Frame *page_table, Frame *physical_memory, int page) {
    // Implementação do algoritmo LRU (Least Recently Used)
    int frame_replaced = physical_memory[0].page_referenced;
    int min_access_time = physical_memory[0].last_access_time;
    int min_index = 0;

    // Encontrar o quadro com o menor tempo de acesso
    for (int i = 1; i < num_frames; i++) {
        if (physical_memory[i].last_access_time < min_access_time) {
            min_access_time = physical_memory[i].last_access_time;
            min_index = i;
        }
    }

    // Substituir o quadro encontrado pelo novo
    physical_memory[min_index].page_referenced = page;

    return frame_replaced;
}

int random_replacement(Frame *page_table, Frame *physical_memory, int page) {
    // Implementação do algoritmo aleatório
    int frame_replaced = physical_memory[rand() % num_frames].page_referenced;

    // Substituir um quadro aleatório pelo novo
    physical_memory[rand() % num_frames].page_referenced = page;

    return frame_replaced;
}

int segunda_chance_replacement(Frame *page_table, Frame *physical_memory, int page) {
    // Implementação do algoritmo Segunda Chance (Second Chance)
    int frame_replaced = -1;
    int i = 0;

    while (frame_replaced == -1) {
        int current_frame = physical_memory[i].page_referenced;
        if (page_table[current_frame].page_referenced == 0) {
            frame_replaced = current_frame;
        } else {
            page_table[current_frame].page_referenced = 0;
        }

        i = (i + 1) % num_frames;  // Circular para o próximo quadro
    }

    // Substituir o quadro selecionado pelo novo
    physical_memory[frame_replaced].page_referenced = page;

    return frame_replaced;
}

int main(int argc, char *argv[]) {
    // Verifica se foram fornecidos os argumentos corretos
    if (argc < 5) {
        printf("Uso: tp2virtual <algoritmo> <arquivo.log> <tamanho_pagina> <tamanho_memoria>\n");
        return 1;
    }

    // Obtém os argumentos
    char *algorithm = argv[1];
    char *logfile = argv[2];
    int page_size = atoi(argv[3]);
    int memory_size = atoi(argv[4]);

    // Calcula o número de quadros na memória física
    int num_frames = memory_size / page_size;

    // Aloca espaço para a tabela de páginas
    Frame *page_table = (Frame *) malloc(sizeof(Frame) * (1 << 21));

    // Inicializa a tabela de páginas
    memset(page_table, 0, sizeof(Frame) * (1 << 21));

    // Aloca espaço para a memória física
    Frame *physical_memory = (Frame *) malloc(sizeof(Frame) * num_frames);

    // Inicializa a memória física
    memset(physical_memory, 0, sizeof(Frame) * num_frames);

    // Abre o arquivo de log
    FILE *file = fopen(logfile, "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo de log.\n");
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

    // Loop principal para processar os acessos à memória
    while (!feof(file)) {
        unsigned addr;
        char rw;

        // Lê o endereço e a operação (R ou W)
        fscanf(file, "%x %c", &addr, &rw);

        // Calcula o número da página a partir do endereço
        int page = addr >> (32 - s);

        // Verifica se a página está na memória física
        if (!page_table[page].page_referenced) {
            num_page_faults++;

            // Verifica se há um quadro vazio na memória física
            int frame_replaced = -1;
            for (int i = 0; i < num_frames; i++) {
                if (physical_memory[i].page_referenced == -1) {
                    frame_replaced = i;
                    break;
                }
            }

            // Se não há um quadro vazio, utiliza o algoritmo de substituição correspondente
            if (frame_replaced == -1) {
                if (strcmp(algorithm, "fifo") == 0) {
                    frame_replaced = fifo_replacement(page_table, physical_memory, page);
                } else if (strcmp(algorithm, "lru") == 0) {
                    frame_replaced = lru_replacement(page_table, physical_memory, page);
                } else if (strcmp(algorithm, "random") == 0) {
                    frame_replaced = random_replacement(page_table, physical_memory, page);
                } else if (strcmp(algorithm, "2a") == 0) {
                    frame_replaced = segunda_chance_replacement(page_table, physical_memory, page);
                }
            } else {
                // Há um quadro vazio na memória física
                frame_replaced = i;
            }

            // Atualiza a tabela de páginas
            page_table[page].page_referenced = 1;
            page_table[page].last_access_time = current_time;

            // Atualiza o quadro na memória física
            physical_memory[frame_replaced].page_referenced = page;
            physical_memory[frame_replaced].last_access_time = current_time;
        }

        // Incrementa o contador de tempo
        current_time++;
    }

    // Fecha o arquivo de log
    fclose(file);

    // Libera a memória alocada
    free(page_table);
    free(physical_memory);

    // Exibe as estatísticas
    printf("Número de acessos: %d\n", num_accesses);
    printf("Número de page faults: %d\n", num_page_faults);
    printf("Número de dirty pages escritas: %d\n", num_dirty_pages_written);

    return 0;
}
