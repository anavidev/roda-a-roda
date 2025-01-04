// programa em linguagem C para criar e armazenar dados nos arquivos necessarios para o jogo

/* bibliotecas */
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

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

FILE *arq;

int i;

/* funcoes */

// funcao para verificar possibilidade de abrir arquivo
void verificacao_arquivo(FILE *nome_arquivo){
	
	if(!nome_arquivo){
		printf("Erro ao abrir o arquivo.\n");
		exit(1);
	}	

}

// funcao para criar arquivo 'palavras.dat' e armazenar as pistas
void criar_arquivo_palavras(void){

	Palavras dados_palavras[] = {
        {"Comida", 2, {"MACARRÃO", "CENOURA"}},
        {"Animal", 3, {"BALEIA", "RINOCERONTE", "TAMANDUÁ"}},
        {"Roupa", 3, {"JAQUETA", "MOLETOM", "BERMUDA"}},
        {"Objeto", 1, {"TESOURA"}},
        {"Cor", 2, {"AMARELO", "LILÁS"}}
	};

	// abrir arquivo
	arq = fopen("./assets/PALAVRAS.DAT", "w+b");
	
	verificacao_arquivo(arq);

	// escrever dados no arquivo
	fwrite(&dados_palavras, sizeof(Palavras), 5, arq);

	// fechar arquivo
	fclose(arq);
		
}

void consultar_arquivo_palavras(void){
	Palavras dados_palavras[5];

	arq = fopen("./assets/PALAVRAS.DAT", "r+b");
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
        for (int j = 0; j < dados_palavras[i].qtd; j++) {
            printf("%-16s", dados_palavras[i].vetpalavras[j]);
        }
        printf("\n");
    }

	printf("\n\n\n");

}

// funcao para criar arquivo premios.dat e armazenar os valores dos premios
void criar_arquivo_premios(void){

	Premios dados_premios = {0.00, 0.01, 100.00, 250.00, 500.00, 750.00, 1000.00, 2500.00, 5000.00, 7500.00, 10000.00};

	arq = fopen("./assets/PREMIOS.DAT", "w+b");
	verificacao_arquivo(arq);
	fwrite(&dados_premios,sizeof(Premios), 1, arq);

	fclose(arq);
}

void consultar_arquivo_premios(void){
	Premios dados_premios[1];

	arq = fopen("./assets/PREMIOS.DAT", "r+b");
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


/* corpo do programa */
int main(void){
	
	setlocale(LC_ALL, "");

	criar_arquivo_palavras();
	criar_arquivo_premios();
	consultar_arquivo_palavras();
	consultar_arquivo_premios();

	return 0;	
}
