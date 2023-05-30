#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

// Estrutura para representar uma entrada de página na tabela de páginas
typedef struct {
    unsigned int endereco;
    char operacao;
    int presente;
    int modificado;
} Pagina;


void check_algoritmo_subsituicao(char *algoritmo_check) {
    // O programa utiliza 4 algoritmos de substituição: 2a, fifo, lru ou random
    // Essa função confere se essa entrada feita por linha de comando do nome do algoritmo
    // é valida
    if(strcmp(algoritmo_check, "2a") || strcmp(algoritmo_check, "fifo") || strcmp(algoritmo_check, "random") || strcmp(algoritmo_check, "lru")) {
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
    int tamanho_quadro_memoria_aux = atoi(argv[3]);
    // Tamanho em bytes da página (binary)
    int tamanho_quadro_memoria = tamanho_quadro_memoria_aux * pow(2,10);
    // Tamanho em bytes da página (binary)
    int tamanho_memoria_total_aux = atoi(argv[4]);
    int tamanho_memoria_total  = tamanho_memoria_total_aux * pow(2,10);

    // Funções para validação das entradas 
    // Cancela a execução do programa caso alguma entrada não seja validada
    check_algoritmo_subsituicao(algoritmo_substitucao);
    check_arquivo_entrada(arquivo_entrada_memoria);
    check_tamanho_quadro_memoria(tamanho_quadro_memoria);
    check_tamanho_memoria_total(tamanho_memoria_total);
	
    // Abertura do arquivo de entrada com extensão .log no modo leitura
    FILE *fptr = fopen(arquivo_entrada_memoria, "r");
    // Aponta o erro e encerra o programa caso a leitura do arquivo acima não funcione corretamente 
    if(fptr== NULL){
        printf("Erro na abertura do arquivo de memória de entrada. Favor verificar seu arquivo!\n");
        exit(0);
    }

    // Alocar memória para para o processo
    // Para alocar a memoria, é necessário saber o número de linhas do arquivo de entrada.
    // Assim, essa função soma 1 à variável numero_linhas (setada em 0 inicialmente) a cada linha lida do arquivo de entrada
    int numero_linhas = 0;
    char linha;
    while ((linha = fgetc(fptr)) != EOF) {
        if (linha == '\n') {
            numero_linhas++;
        }
    } 

    // Reposicione o ponteiro do arquivo para o início
    fseek(fptr, 0, SEEK_SET);

    // Aloque memória para armazenar as entradas do arquivo
    Pagina* paginas = (Pagina*)malloc(numero_linhas * sizeof(Pagina));
    if (paginas == NULL) {
        printf("Erro ao alocar memória.\n");
        fclose(fptr);
    }

    // Leia as entradas do arquivo e armazene-as na memória
    for (int i = 0; i < numero_linhas; i++) {
        fscanf(fptr, "%x %c", &paginas[i].endereco, &paginas[i].operacao);
        paginas[i].presente = 0;
        paginas[i].modificado = 0;
    };

    // Criação da memória física
    Pagina* memoria_fisica = (Pagina*)malloc(tamanho_memoria_total * sizeof(Pagina));
    if (memoria_fisica == NULL) {
        printf("Erro ao alocar memória para a memória física.\n");
    };

    // Inicialização da memória física
    for (int i = 0; i < tamanho_memoria_total; i++) {
        memoria_fisica[i].presente = 0;
        memoria_fisica[i].modificado = 0;
    }

    // Variáveis para coletar estatísticas
    int acessos_totais = 0;
    int acessos_leitura = 0;
    int acessos_escrita = 0;

    // unsigned addr;
    // char rw;
    // while(fscanf(fptr, "%x %c", &addr, &rw) != EOF) {
    // }

    printf("Executando simulador ...\n");
    // Processamento dos acessos à memória
    for (int i = 0; i < numero_linhas; i++) {
        // Contar o numero de acessos totais e de leitura e escrita
        acessos_totais++;
        if(paginas[i].operacao == 'R' || paginas[i].operacao == 'r') {
            acessos_leitura++;
        };
        if(paginas[i].operacao == 'W' || paginas[i].operacao == 'w') {
            acessos_escrita++;
        };
        // Verificar se a página está presente na memória física
        if (paginas[i].presente == 0) {
            paginas[i].presente = 1;

            // Verificar se há um quadro livre na memória física
            int quadroLivre = -1;
            for (int j = 0; j < tamanho_memoria_total; j++) {
                if (memoria_fisica[j].presente == 0) {
                    quadroLivre = j;
                    break;
                }
            }

            // Se não houver quadro livre, aplicar o algoritmo de substituição
            if (quadroLivre == -1) {
                // Aplicar o algoritmo de substituição de páginas (exemplo: FIFO)
                // Implemente aqui a lógica do algoritmo de substituição de páginas
                // Atualize o valor de quadroLivre com o índice do quadro que será substituído
                // Atualize as estatísticas conforme necessário
            }

            // Carregar a página do arquivo de paginação para a memória física
            // Implemente aqui a lógica de carregamento da página do arquivo de paginação
            // Atualize as estatísticas conforme necessário
        }

        // Atualizar o bit de modificado se a operação for de escrita
        if (paginas[i].operacao == 'W') {
            //acessos_escrita++;
            paginas[i].modificado = 1;
        }
    }

    // Função para apresentar o relatório com parâmetros de entrada e estatísitcas geradas durante a execução do simulador
    relatorio_estatisticas(arquivo_entrada_memoria, tamanho_quadro_memoria, tamanho_memoria_total, algoritmo_substitucao, acessos_totais,
                            acessos_leitura, acessos_escrita);

    // Liberar a memória alocada
    free(memoria_fisica);
    free(paginas);

    // Fechamento do arquivo
    fclose(fptr);

 

    return 0;
}