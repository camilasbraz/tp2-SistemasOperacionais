# Carregar as bibliotecas necessárias
library(dplyr)
library(ggplot2)
library(stringr)

setwd("~/github/0tp2-SistemasOperacionais")

# Ler os dados do arquivo CSV
dados <- read.csv("saida.csv") %>% 
  rename(PageFaults = 'Page.faults',
         PaginasEscritas = 'Páginas.escritas',
         TempoExecucao = 'Tempo.de.execução',
         TamanhoMemoria = 'Tamanho.da.memória',
         TamanhoPagina = 'Tamanho.da.página') %>% 
  mutate(TempoExecucao = as.numeric(str_sub(TempoExecucao,start = 1, end = -2 )))


# Definir uma função para criar os gráficos por teste, arquivo e algoritmo
gerar_graficos <- function(dados_filtrados, var) {
  # Filtrar os dados para o teste, arquivo e algoritmo específicos

    # Gráfico para o primeiro teste
    if (teste == "primeiro_teste") {
      grafico <- ggplot(dados_filtrados, aes(x = TamanhoMemoria, y = get(var))) +
      labs(x = "Tamanho da Memória")
       #    subtitle="Primeiro Teste"  )
      if (var == "PageFaults"){
        grafico <- grafico +
          ylim(0, 100000)
      }
      if (var == "PaginasEscritas"){
        grafico <- grafico +
          ylim(0, 20000)
      }
      if (var == "TempoExecucao"){
        grafico <- grafico +
          ylim(0, 45)
      }
    }
    else if (teste == "segundo_teste") {
        grafico <- ggplot(dados_filtrados, aes(x = TamanhoPagina, y = get(var)))+
          labs(x = "Tamanho da Página")
          #  subtitle="Segundo Teste")
        if (var == "PageFaults"){
          grafico <- grafico +
            ylim(0, 400000)
        }
        if (var == "PaginasEscritas"){
          grafico <- grafico +
            ylim(0, 80000)
        }
        if (var == "TempoExecucao"){
          grafico <- grafico +
            ylim(0, 25)
        }

    }
       grafico <- grafico + 
        geom_point(size = 1.5, color = "grey60") +
        geom_smooth(method = lm, se = FALSE,
                    color = "firebrick", linewidth = 1.3)+
        facet_wrap(~Arquivo)+
         #theme_ipsum()+
         theme_light()+
         theme(panel.grid.minor = element_blank(),
               text=element_text(size=14,  family="Roboto", color = "grey50"),
               axis.text.x=element_blank(),
                axis.ticks.x=element_blank() ,
               axis.text.y=element_blank(),
               axis.ticks.y=element_blank() )+
         labs(y = paste(var ) 
              #,
              #title=algoritmo
              )+
         theme(strip.background =element_rect(fill="grey90"))+
         theme(strip.text = element_text(colour = '#4d4d4d', size = 13))
        
        # Imprimir o gráfico
        print(grafico)
        ggsave(paste0("./graphs_img/",teste,"_", algoritmo, "_", var,".png"), width = 20, height = 20, units = "cm")
              
}
          

variaveis <- c("PageFaults", "PaginasEscritas", "TempoExecucao")

# Loop para criar os gráficos para cada combinação de variavel, teste e algoritmo
for (var in variaveis) {
  for (teste in unique(dados$Teste)) {
      for (algoritmo in unique(dados$Algoritmo)) {
        dados_filtrados <- dados %>%
          filter(Teste == teste, Algoritmo == algoritmo) %>% 
          select(Teste, Arquivo, Algoritmo, all_of(var), TamanhoMemoria, TamanhoPagina) 
          gerar_graficos(dados_filtrados, var)
      }
    }
  }


