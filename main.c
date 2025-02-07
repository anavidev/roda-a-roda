/* bibliotecas */
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include <string.h>


/* variaveis globais */

// criacao do tipo 'Palavras' para armazenar pista, quantidade de palavras e palavras
typedef struct{
	char pista[7+1];
	int qtd;
	char vetpalavras[5][11+1]; // palavras ligadas a pista
} Palavras;

// criacao do tipo 'Premios' para armazenar pista, quantidade de palavras e palavras
typedef struct{
	float valor[11];
} Premios;

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
int i,j;


/* funcoes */

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
        {"Comida", 2, {"MACARRÃO", "CENOURA"}},
        {"Animal", 3, {"BALEIA", "RINOCERONTE", "TAMANDUÁ"}},
        {"Roupa", 3, {"JAQUETA", "MOLETOM", "BERMUDA"}},
        {"Objeto", 1, {"TESOURA"}},
        {"Cor", 2, {"AMARELO", "LILÁS"}}
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

	Premios dados_premios = {0.00, 0.01, 100.00, 250.00, 500.00, 750.00, 1000.00, 2500.00, 5000.00, 7500.00, 10000.00};

	arq = fopen("assets/PREMIOS.DAT", "w+b");
	verificacao_arquivo(arq);
	fwrite(&dados_premios,sizeof(Premios), 1, arq);

	fclose(arq);
}

// funcao para consultar o conteudo de 'PREMIOS.DAT'
void consultar_arquivo_premios(void){
	Premios dados_premios[1];

	arq = fopen("assets/PREMIOS.DAT", "r+b");
	verificacao_arquivo(arq);

	fread(&dados_premios,sizeof(Premios), 1, arq);
	fclose(arq);

	printf("======= VALORES DOS PRÊMIOS =======\n");
	printf("VALORES (R$)\n");
	printf("===================================\n");
    for(i = 0; i < 11; i++){
        printf("%.2f\n",dados_premios[0].valor[i]);
    }

	printf("\n\n\n");
}


// funcao para realizar o sorteio da pista e da palavra
void sorteio(int limite_palavras){
	Palavras dados_palavras[5];
	char palavra_sorteada[11+1];

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
	printf(" A palavra sorteada foi: %s\n",palavra_sorteada);
	
	// omissao da palavra sorteada
	printf("\n\n\t");
	int tamanho_palavra_sorteada = strlen(palavra_sorteada);
	for (i = 0; i < tamanho_palavra_sorteada; i++){
		printf("_  ");	
	}
	
	
}

// funcao para definir o premio da rodada
void premio_rodada(int limite_premios){
	Premios dados_premios;

	// abrir arquivo contendo os valores dos premios armazenados
	arq = fopen("assets/PREMIOS.DAT", "r+b");
	verificacao_arquivo(arq);
	fread(&dados_premios,sizeof(Premios),1,arq);
	fclose(arq);

	// sorteio do premio
	int numero_sorteado = rand() % limite_premios;
	printf("Roda a roda!\n\n");
	for (i = 1; i <= 5; i++){
		sleep(1);
		printf(". ");
	}
	printf("\n\n");
	
	// aplicacao da regra do premio (R$0.00 = passa a vez | R$0.01 = perde tudo)
	float premio_sorteado = dados_premios.valor[numero_sorteado];
	switch(numero_sorteado){
		case 0:
			printf("PASSA A VEZ\n");
			printf("A vez será passada para o próximo jogador.");
			break;
		case 1:
			printf("PERDEU TUDO\n");
			printf("A vez será passada para o próximo jogador.");
			break;
		default:			
			printf("Escolha uma letra valendo R$%.2f:\n",premio_sorteado);
	}

}


int main(void){
	
	setlocale(LC_ALL, "");
	srand(time(NULL));
	
	// tela inicial do jogo
	sorteio(5); // sorteio das pistas e palavras
	printf("\n\n");

	// imprimir nome dos jogadores na tela
	printf("\t\t\t\t");
	for (i=0; i<3; i++){
		printf("%-20s",jogadores[i].nome);
	}
	printf("\n");

	// imprimir o saldo dos jogadores na tela
	printf("\t\t\t\t");
	for (i=0; i<3; i++){
		printf(" %-20.2f",jogadores[i].saldo);
	}
	
	printf("\n\n");
	premio_rodada(11); // sorteio do premio da rodada

	return 0;
}
