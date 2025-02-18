// arquivo que contem funcoes e variaveis relacionadas a dinamica do jogo

/* bibliotecas */
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "sorteio.c"


/* definicao dos tipos de dados */
typedef struct{
	char nome[9+1];
	float saldo;
} Jogador;


/* variaveis globais */

Jogador jogadores[] = {
	{"Jogador 1", 0.00},
	{"Jogador 2", 0.00},
	{"Jogador 3", 0.00},
};

int qtd_letra_encontrada = 0, jogador_atual = 0, tentativas_falhas = 0;
char letra, palavra[11+1];


/* funcoes */

// funcao para imprimir informacoes dos jogadores
void info_jogadores(void){
	
	// imprimir nome dos jogadores na tela
	printf("\t\t\t\t");
	for (i = 0; i < 3; i++){
		printf("%-20s",jogadores[i].nome);
	}
	printf("\n");
	
    printf(" \t\t\t  ");
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 20; j++) {  // 20 = largura de cada nome
            printf("=");
        }
    }

	// imprimir o saldo dos jogadores na tela
	printf("\n");
	printf("  \t\t\t\t");
	for (i = 0; i < 3; i++){
		printf(" %-20.2f",jogadores[i].saldo);
	}	
}

// funcao para adivinhar letras que estao na palavra sorteada
void adivinhar_palavra(char letra_escolhida) {
	
    printf("\t\t\t\t\t\t");

    // verificacao se a letra esta presente na palavra sorteada
    for (i = 0; i < strlen(palavra_sorteada); i++) {
    	int qtd_letra_rodada = 0;
        if (letra_escolhida == palavra_sorteada[i]) {
            letras_adivinhadas[i] = letra_escolhida; // adicionar letra que pertence a palavra ao vetor
            qtd_letra_encontrada++;
            qtd_letra_rodada++;
            jogadores[jogador_atual].saldo += premio_sorteado * qtd_letra_rodada;
        }
    }

    // imprimir array com letras adivinhadas
    for (i = 0; i < strlen(palavra_sorteada); i++) {
        if (letras_adivinhadas[i] == '\0') {
            printf(" _ ");
        } else {
            printf(" %c ", letras_adivinhadas[i]);
        }
    }
    printf("\n");
    
    // mensagem caso a letra nao seja encontrada
    if (qtd_letra_encontrada == 0) {
        printf("\nNão existe '%c' na palavra.\n", letra_escolhida);
        jogadores[jogador_atual].saldo = jogadores[jogador_atual].saldo;
    }

}

// funcao para mostrar sublinhados ou letras a cada rodada
void exibir_progresso_palavra(void) {
    printf("\t\t\t\t\t\t");
    for (i = 0; i < strlen(palavra_sorteada); i++) {
        if (letras_adivinhadas[i] == '\0') {
            printf(" _ ");
        } else {
            printf(" %c ", letras_adivinhadas[i]);
        }
    }
    printf("\n\n");
}

// funcao para imprimir a pista e a palavra a ser adivinhada
void cabecalho(void){
	
	printf("\t\t\t\t\t");
	printf("A palavra está associada com: %s\n",dados_palavras[numero_sorteado].pista);
	printf("\t\t\t\t\t");
	printf(" A palavra sorteada foi: %s\n\n\n",palavra_sorteada);
	exibir_progresso_palavra();
	
}

// funcao para digitar uma letra
void digitar_letra(void){
	
	fflush(stdin); letra = getch();
	while (!isalpha(letra)){
		printf("\n\nEscolha uma LETRA: ");
		fflush(stdin); letra = getch();
	}
	
	// transformar e imprimir na tela letra digitada em maiusculo
	letra = toupper(letra);
	printf("%c\n",letra);
	adivinhar_palavra(letra);
	
}

// funcao para digitar a palavra
void digitar_palavra(void){
	int chance = 3;
		
	fflush(stdin); scanf("%s",&palavra);

    // verificar se todos os caracteres sao letras
    for (i = 0; i < strlen(palavra); i++) {
        while (!isalpha(palavra[i])) {
            printf("\n\nEscreva apenas LETRAS: ");
            fflush(stdin); scanf("%s",&palavra);
        }
    }	

    // converter para maiusculas
    for (i = 0; i < strlen(palavra); i++) {
        palavra[i] = toupper(palavra[i]);
    }

    // verificar se a palavra digitada esta em dados_palavras
	if (strcmp(palavra, palavra_sorteada) == 0) {
		system("cls");
		cabecalho();
		info_jogadores();
    	printf("\n%s VENCEU!\n",jogadores[jogador_atual].nome);
    	jogadores[jogador_atual].saldo += premio_sorteado + jogadores[jogador_atual].saldo;
    	printf("\nFIM DE JOGO.");
    	exit(0);
	} else {
    	printf("\nERRADO\n");
    	jogador_atual++;
    	tentativas_falhas++;
	}
	
	if (tentativas_falhas == 3) {
	    printf("\n\nNINGUÉM ganhou o jogo.\n");
	    printf("A palavra sorteada foi %s.\n", palavra_sorteada);
	    exit(0);
	}
	return;
}

// funcao que realiza a dinamica da rodada
void rodada(void) {
    system("cls");
    cabecalho();
    int chance = 3;

    while (strlen(letras_adivinhadas) < strlen(palavra_sorteada)) {
        printf("\n");
        info_jogadores();
        if (jogador_atual > 2) {
            jogador_atual = 0;
        }
        printf("\n\nVez do %s", jogadores[jogador_atual].nome);
        printf("\n");
        if (qtd_letra_encontrada < strlen(palavra_sorteada) - 3) {
            sorteio_premio(11); // sorteio do premio da rodada
            // aplicacão da regra do prêmio (R$0.00 = passa a vez | R$0.01 = perde tudo)
            premio_sorteado = dados_premios[numero_sorteado];
            printf("\nRoda a Roda!\n");
            switch (numero_sorteado) {
                case 0:
                    printf("PASSA A VEZ\n");
                    printf("A vez será passada para o próximo jogador.\n");
                    jogador_atual++;
                    exibir_progresso_palavra();
                    system("cls");
                    cabecalho();
                    break;
                case 1:
                    printf("PERDEU TUDO\n");
                    printf("A vez será passada para o próximo jogador.\n");
                    jogadores[jogador_atual].saldo = 0.00;
                    jogador_atual++;
                    exibir_progresso_palavra();
                    system("cls");
                    cabecalho();
                    break;
                default:
                    sorteio_premio(11);
                    printf("Escolha uma letra valendo R$%.2f: ", premio_sorteado);
                    digitar_letra();
                    jogador_atual++;
                    system("cls");
                    cabecalho();
            }
        } else {
            printf("\nFaltam menos de 4 letras para completar a palavra.\n");
            printf("Você tem 5 segundos para pensar e depois digitar a palavra.\n");
            sorteio_premio(11);
            printf("Escolha uma palavra valendo R$%.2f: ", premio_sorteado + jogadores[jogador_atual].saldo);
            digitar_palavra();
            system("cls");
            cabecalho();
        }
    }
}
