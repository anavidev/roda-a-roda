# Lógica de Programação 1 - Projeto Semestral
O objetivo deste projeto semestral é programar um jogo inspirado no programa de televisão *Roda a Roda*.

## Estrutura do Repositório

- `assets/`: Contém os arquivos binários utilizados no jogo.
  - `PALAVRAS.DAT`: Arquivo binário contendo pistas e palavras para o jogo.
  - `PREMIOS.DAT`: Arquivo binário contendo os valores dos prêmios disponíveis.
- `arquivos.c`: Responsável pela manipulação dos arquivos do jogo.
- `sorteio.c`: Contém as funções para sorteio de palavras e prêmios.
- `rodada.c`: Implementa a lógica do jogo e a interação com os jogadores.
- `main.c`: Arquivo principal que inicializa e executa o jogo.
- `README.md`: Documento que descreve o projeto, sua estrutura e funcionalidades.

## Funcionalidades

- **Criação e manipulação de arquivos**: Armazena e recupera informações sobre palavras, pistas e prêmios.
- **Sorteio de palavras e prêmios**: Define aleatoriamente a palavra e o prêmio da rodada.
- **Dinâmica de jogo**:
  - Apresenta uma pista associada à palavra.
  - Permite que os jogadores tentem adivinhar a palavra letra por letra.
  - Atualiza os saldos dos jogadores com base nas letras corretas adivinhadas.
  - Controla o fluxo do jogo até que a palavra seja completamente adivinhada.

## Conceitos de Programação

- **Manipulação de arquivos binários**: Utilização de `fopen`, `fwrite`, `fread` e `fclose` para armazenar e recuperar dados.
- **Estruturas de controle:** Uso de loops e condicionais para verificar as tentativas do jogador.
- **Estruturas de dados**: Uso de `struct` e arrays multidimensionais (matrizes) para armazenar informações das pistas, palavras e jogadores.
- **Uso de funções e modularização**: Código separado em arquivos distintos para melhor organização e reutilização do código.

## Tecnologias Utilizadas

- **Linguagem C**: Utilizada para desenvolver toda a lógica do jogo.
- **Bibliotecas da Linguagem C**:
  - `<stdio.h>`: Manipulação de arquivos e entrada/saída de dados.
  - `<stdlib.h>`: Alocação de memória e controle de execução.
  - `<string.h>`: Manipulação de strings.
  - `<time.h>`: Inicialização do gerador de números aleatórios.
  - `<locale.h>`: Configuração da localidade para garantir a correta formatação de caracteres.
