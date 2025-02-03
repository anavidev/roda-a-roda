// programa em linguagem C para criar e armazenar dados nos arquivos necessarios para o jogo

/* bibliotecas */
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>


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
	arq = fopen("./assets/PALAVRAS.DAT", "w+b");
	
	verificacao_arquivo(arq);

	// escrever dados no arquivo
	fwrite(&dados_palavras, sizeof(Palavras), 5, arq);

	// fechar arquivo
	fclose(arq);
		
}

// funcao para consultar o conteudo de 'PALAVRAS.DAT'
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

// funcao para criar arquivo 'PREMIOS.DAT' e armazenar os valores dos premios
void criar_arquivo_premios(void){

	Premios dados_premios = {0.00, 0.01, 100.00, 250.00, 500.00, 750.00, 1000.00, 2500.00, 5000.00, 7500.00, 10000.00};

	arq = fopen("./assets/PREMIOS.DAT", "w+b");
	verificacao_arquivo(arq);
	fwrite(&dados_premios,sizeof(Premios), 1, arq);

	fclose(arq);
}

// funcao para consultar o conteudo de 'PREMIOS.DAT'
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


// funcao para realizar o sorteio da pista e da palavra
void sorteio(int limite_palavras){
	Palavras dados_palavras[5];
	int limite_qtd_palavras;

	arq = fopen("./assets/PALAVRAS.DAT", "r+b");
	verificacao_arquivo(arq);
	fread(&dados_palavras,sizeof(Palavras),5,arq);
	fclose(arq);
	
	int numero_sorteado = rand() % limite_palavras;
	printf("A palavra está associada com: %s\n",dados_palavras[numero_sorteado].pista);

	limite_qtd_palavras = dados_palavras[numero_sorteado].qtd;
	int numero_palavra_sorteada = rand() % limite_qtd_palavras;
	printf("A palavra sorteada foi: %s\n",dados_palavras[numero_sorteado].vetpalavras[numero_palavra_sorteada]);		
}

// funcao para definir o premio da rodada
void premio_rodada(int limite_premios){
	Premios dados_premios;

	arq = fopen("./assets/PREMIOS.DAT", "r+b");
	verificacao_arquivo(arq);
	fread(&dados_premios,sizeof(Premios),1,arq);
	fclose(arq);

	int numero_sorteado = rand() % limite_premios;
	printf("Escolha uma letra valendo R$%.2f:\n\n",dados_premios.valor[numero_sorteado]);
}


int main(void){
	
	setlocale(LC_ALL,"");
	srand(time(0)); // gerar numeros diferentes a cada execucao

	consultar_arquivo_palavras();
    consultar_arquivo_premios();

	sorteio(5);
	premio_rodada(11);

	return 0;	
}
