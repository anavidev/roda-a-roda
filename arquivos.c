// arquivo que contem funcoes relacionadas a criacao e utilizacao dos arquivos utilizados no jogo

/* bibliotecas */
#include <stdio.h>
#include <stdlib.h>


/* definicao tipos de dados */

typedef struct{
	char pista[8+1];
	int qtd;
	char vetpalavras[5][11+1]; // palavras ligadas a pista
} Palavras;


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
	FILE *arq;

	Palavras dados_palavras[] = {
        {"Alimento", 2, {"JABUTICABA", "CENOURA"}},
        {"Animal", 3, {"BALEIA", "RINOCERONTE", "GOLFINHO"}},
        {"Roupa", 3, {"JAQUETA", "MOLETOM", "BERMUDA"}},
        {"Objeto", 1, {"TESOURA"}},
        {"Cor", 2, {"AMARELO", "TURQUESA"}}
	};

	arq = fopen("assets/PALAVRAS.DAT", "w+b");
	verificacao_arquivo(arq);
	fwrite(&dados_palavras, sizeof(Palavras), 5, arq);
	fclose(arq);
		
}

// funcao para consultar o conteudo de 'PALAVRAS.DAT'
void consultar_arquivo_palavras(void){
	Palavras dados_palavras[5];
	FILE *arq;
	int i,j;

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
	float dados_premios[11] = {0.00, 0.01, 100.00, 250.00, 500.00, 750.00, 1000.00, 2500.00, 5000.00, 7500.00, 10000.00};
	FILE *arq;

	arq = fopen("assets/PREMIOS.DAT", "w+b");
	verificacao_arquivo(arq);
	fwrite(&dados_premios,sizeof(float), 1, arq);

	fclose(arq);
}

// funcao para consultar o conteudo de 'PREMIOS.DAT'
void consultar_arquivo_premios(void){
	float dados_premios[0];
	FILE *arq;
	int i;

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
}
