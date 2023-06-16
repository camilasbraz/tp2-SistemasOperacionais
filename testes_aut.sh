#!/bin/bash

indice_nome_arquivo=15    
indice_pages_fault=45
indice_paginas_escritas=48

arquivo_saida="saida.csv"

make

echo "Arquivo,Algoritmo,Tamanho da memória,Tamanho da página,Page faults,Páginas escritas,Tempo de execução (em segundos  ),Teste" > $arquivo_saida

declare -A algoritmos=(
  ["fifo"]="FIFO"
  ["lru"]="LRU"
  ["random"]="Random"
  ["2a"]="2A"
)

declare -A arquivo=(
  ["compilador.log"]="Compilador"
  ["compressor.log"]="Compressor"
  ["matriz.log"]="Matriz"
  ["simulador.log"]="Simulador"
)

declare -A testes=(
  ["primeiro_teste"]="128 256 512 1024 2048 4096 8192 16384"
  ["segundo_teste"]="2 4 8 16 32 64"
)

printf "Inicio dos testes\n"

for teste in "${!testes[@]}"; do
  for alg in "${!algoritmos[@]}"; do
    for arq in "${!arquivo[@]}"; do
      read -ra tamanhos <<< "${testes[$teste]}"
      for tamanho in "${tamanhos[@]}"; do
        inicio=$(date +%s.%N)
        if [[ $teste == "primeiro_teste" ]]; then
          saida=$(./tp2virtual $alg $arq 4 $tamanho)
          pagesize=4
          memsize=$tamanho
        else
          saida=$(./tp2virtual $alg $arq $tamanho 256)
          pagesize=$tamanho
          memsize=256
        fi
        saidaArr=(${saida//\\n/ })
        nome_arquivo=${saidaArr[indice_nome_arquivo]}
        algoritmo=${algoritmos[$alg]}
        pages_fault=${saidaArr[indice_pages_fault]}
        paginas_escritas=${saidaArr[indice_paginas_escritas]}
        fim=$(date +%s.%N)
        duracao=$(echo "$fim - $inicio" | bc)
        tempo_execucao=$(printf "%.3fs" $duracao)
        echo "$nome_arquivo,$algoritmo,$memsize,$pagesize,$pages_fault,$paginas_escritas,$tempo_execucao,$teste" >> $arquivo_saida
      done
    done
  done
done

printf "Fim dos testes\n"
