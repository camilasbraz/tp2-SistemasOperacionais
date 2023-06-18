#ifndef TP2VIRTUAL_H
#define TP2VIRTUAL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <time.h>
#include <stdint.h>

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
    int bit_ref;          // Flag que indica se a página foi referenciada
} Pagina;

void check_algoritmo_substituicao(char *algoritmo_check);
void check_arquivo_entrada(char *arquivo_check);
void check_tamanho_quadro_memoria(int check_tamanho_quadro);
void check_tamanho_memoria_total(int check_tamanho_memoria);
void relatorio_estatisticas(char *arquivo_entrada, int tamanho_quadro, int tamanho_memoria, char *algoritmo_substituicao, int acessos_totais,
                            int acessos_leitura, int acessos_escrita, int num_page_faults, int num_dirty_pages);
int determinar_pagina(int tamanho_quadro_memoria, unsigned addr);
int substituicao_fifo(Pagina *tabela_de_paginas, Quadro *memoria_fisica, int indice_pagina, int numero_quadros);
int substituicao_lru(Pagina *tabela_de_paginas, Quadro *memoria_fisica, int indice_pagina, int numero_quadros, int tempo_atual);
int substituicao_random(Pagina *tabela_de_paginas, Quadro *memoria_fisica, int indice_pagina, int numero_quadros);
int substituicao_segunda_chance(Pagina *tabela_de_paginas, Quadro *memoria_fisica, int indice_pagina, int numero_quadros);

#endif  // TP2VIRTUAL_H
