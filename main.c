/* bibliotecas */
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include <string.h>

/* variaveis globais */

// criacao do tipo 'Palavras' para armazenar pista, quantidade de palavras e palavras
typedef struct{
	char pista[8+1];
	int qtd;
	char vetpalavras[5][11+1]; // palavras ligadas a pista
} Palavras;

char palavra_sorteada[11+1], letra, letras_adivinhadas[11+1], palavra[11+1];;

// definição dos premios
float dados_premios[11] = {0.00, 0.01, 100.00, 250.00, 500.00,
750.00, 1000.00, 2500.00, 5000.00, 7500.00, 10000.00};

float premio_sorteado;

// criacao e definicao do tipo 'Jogador'
typedef struct{
	char nome[9+1];
	float saldo;
} Jogador;

Jogador jogadores[] = {
	{"Jogador 1", 0.00},
	{"Jogador 2", 0.00},
	{"Jogador 3", 0.00},
};

FILE *arq;
int i,j, numero_sorteado, qtd_letra_encontrada = 0, jogador_atual = 0, tentativas_falhas = 0;;


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

// funcao para verificar possibilidade de abrir arquivo
void verificacao_arquivo(FILE *nome_arquivo){
	
	if(!nome_arquivo){
		printf("Erro ao abrir o arquivo.\n");
		exit(1);
	}	

}

// funcao para criar arquivo 'PALAVRAS.DAT' e armazenar as pistas
void criar_arquivo_palavras(void){

	Palavras dados_palavras[] = {
        {"Alimento", 2, {"JABUTICABA", "CENOURA"}},
        {"Animal", 3, {"BALEIA", "RINOCERONTE", "GOLFINHO"}},
        {"Roupa", 3, {"JAQUETA", "MOLETOM", "BERMUDA"}},
        {"Objeto", 1, {"TESOURA"}},
        {"Cor", 2, {"AMARELO", "TURQUESA"}}
	};

	// abrir arquivo
	arq = fopen("assets/PALAVRAS.DAT", "w+b");
	
	verificacao_arquivo(arq);

	// escrever dados no arquivo
	fwrite(&dados_palavras, sizeof(Palavras), 5, arq);

	// fechar arquivo
	fclose(arq);
		
}

// funcao para consultar o conteudo de 'PALAVRAS.DAT'
void consultar_arquivo_palavras(void){
	Palavras dados_palavras[5];

	arq = fopen("assets/PALAVRAS.DAT", "r+b");
	verificacao_arquivo(arq);

	// ler dados do arquivo
	fread(&dados_palavras,sizeof(Palavras),5,arq);
	fclose(arq);

	// imprimir dados na tela
	printf("============================= PISTAS E PALAVRAS =============================\n");
	printf("PISTA		QTD.	PALAVRA 1	PALAVRA 2	PALAVRA 3\n");
	printf("=============================================================================\n");
    for (i = 0; i < 5; i++) {
        printf("%-16s%-8d", dados_palavras[i].pista, dados_palavras[i].qtd);
        for (j = 0; j < dados_palavras[i].qtd; j++) {
            printf("%-16s", dados_palavras[i].vetpalavras[j]);
        }
        printf("\n");
    }

	printf("\n\n\n");

}

// funcao para criar arquivo 'PREMIOS.DAT' e armazenar os valores dos premios
void criar_arquivo_premios(void){

	arq = fopen("assets/PREMIOS.DAT", "w+b");
	verificacao_arquivo(arq);
	fwrite(&dados_premios,sizeof(float), 1, arq);

	fclose(arq);
}

// funcao para consultar o conteudo de 'PREMIOS.DAT'
void consultar_arquivo_premios(void){
	float dados_premios[0];

	arq = fopen("assets/PREMIOS.DAT", "r+b");
	verificacao_arquivo(arq);

	fread(&dados_premios,sizeof(float), 1, arq);
	fclose(arq);

	printf("======= VALORES DOS PRÊMIOS =======\n");
	printf("VALORES (R$)\n");
	printf("===================================\n");
    for(i = 0; i < 11; i++){
        printf("%.2f\n",dados_premios[i]);
    }

	printf("\n\n\n");
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

// funcao para realizar o sorteio da pista e da palavra
void sorteio_palavra(int limite_palavras){
	Palavras dados_palavras[5];

	// abrir arquivo contendo as palavras armazenadas
	arq = fopen("assets/PALAVRAS.DAT", "r+b");
	verificacao_arquivo(arq);
	fread(&dados_palavras,sizeof(Palavras),5,arq);
	fclose(arq);
	
	// sorteio da pista
	int numero_sorteado = rand() % limite_palavras;
	printf("\t\t\t\t\t");
	printf("A palavra está associada com: %s\n",dados_palavras[numero_sorteado].pista);
	
	// sorteio da palavra
	int limite_qtd_palavras = dados_palavras[numero_sorteado].qtd;
	int numero_palavra_sorteada = rand() % limite_qtd_palavras;
	strcpy(palavra_sorteada, dados_palavras[numero_sorteado].vetpalavras[numero_palavra_sorteada]);
	printf("\t\t\t\t\t");
	printf(" A palavra sorteada foi: %s\n\n\n",palavra_sorteada);
	
	// inicializar o array de letras adivinhadas com '\0'
    memset(letras_adivinhadas, '\0', sizeof(letras_adivinhadas));
	
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
    printf("\n");
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
    	printf("\n%s VENCEU!\n",jogadores[jogador_atual].nome);
    	jogadores[jogador_atual].saldo += premio_sorteado + jogadores[jogador_atual].saldo;
    	printf("\nFIM DE JOGO.");
    	exit(0);
	} else {
    	printf("ERRADO\n");
    	jogador_atual++;
    	tentativas_falhas++;
	}
	
	if (tentativas_falhas == 3) {
	    printf("\n\nNINGUÉM ganhou o jogo.\n");
	    printf("A palavra sorteada foi %s.\n", palavra_sorteada);
	    exit(0);
	} else{
		return;
	}
}

// funcao para definir o premio da rodada
int sorteio_premio(int limite_premios){

	// abrir arquivo contendo os valores dos premios armazenados
	arq = fopen("assets/PREMIOS.DAT", "r+b");
	verificacao_arquivo(arq);
	fread(&dados_premios,sizeof(float),1,arq);
	fclose(arq);

	// sorteio do premio
	numero_sorteado = rand() % limite_premios;
	
	return numero_sorteado;

}

void rodada(void){
	int chance = 3;
	
	exibir_progresso_palavra();

	while (strlen(letras_adivinhadas) < strlen(palavra_sorteada)){
		printf("\n");
		info_jogadores();
		if (jogador_atual > 2){
			jogador_atual = 0;	
		}
		printf("\n\nVez do %s",jogadores[jogador_atual].nome);
		printf("\n");
		if (qtd_letra_encontrada < strlen(palavra_sorteada) - 3){
			sorteio_premio(11); // sorteio do premio da rodada
			// aplicacao da regra do premio (R$0.00 = passa a vez | R$0.01 = perde tudo)
			premio_sorteado = dados_premios[numero_sorteado];
			printf("\nRoda a Roda!\n");
			/* for (i = 1; i <= 5; i++){
				sleep(1);
				printf(". ");
			} */
			switch(numero_sorteado){
				case 0:
					printf("\nPASSA A VEZ\n");
					printf("A vez será passada para o próximo jogador.\n");
					jogador_atual++;
					exibir_progresso_palavra();
					break;
				case 1:
					printf("\nPERDEU TUDO\n");
					printf("A vez será passada para o próximo jogador.\n");
					jogadores[jogador_atual].saldo = 0.00;
					jogador_atual++;
					exibir_progresso_palavra();
					break;
				default:
					sorteio_premio(11); // sorteio do premio da rodada
					printf("\nEscolha uma letra valendo R$%.2f: ",premio_sorteado);
					digitar_letra();
					jogador_atual++;
			}
			
		} else{
			printf("\n\nFaltam menos de 4 letras para completar a palavra.\n");
			printf("Você tem 5 segundos para pensar e depois digitar a palavra.\n");
			/* for (i = 1; i <= 5; i++){
				sleep(1);
				printf(". ");
			} */
			sorteio_premio(11); // sorteio do premio da rodada
			printf("\nEscolha uma palavra valendo R$%.2f: ",premio_sorteado + jogadores[jogador_atual].saldo);
			digitar_palavra();		
		}
	}	
}

int main(void){
	
	setlocale(LC_ALL, "");
	srand(time(NULL));
	
	// tela inicial do jogo
	sorteio_palavra(5); // sorteio das pistas e palavras
	printf("\n\n");
	
	printf("\n\n");
	rodada();

	return 0;
}
