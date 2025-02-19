// arquivo que contem funcoes e variaveis relacionadas aos sorteios das pistas, palavras e premios

/* bibliotecas */
#include <string.h>
#include "arquivos.c"


/* variaveis globais */
char palavra_sorteada[11+1], letras_adivinhadas[11+1];
int numero_sorteado;
float premio_sorteado;


/* funcoes */

// funcao para realizar o sorteio da pista e da palavra
void sorteio_palavra(int limite_palavras){
	Palavras dados_palavras[5];
	FILE *arq;

	// abrir arquivo contendo as palavras armazenadas
	arq = fopen("assets/PALAVRAS.DAT", "r+b");
	verificacao_arquivo(arq);
	fread(&dados_palavras,sizeof(Palavras),5,arq);
	fclose(arq);
	
	// sorteio da pista
	numero_sorteado = rand() % limite_palavras;
	
	// sorteio da palavra
	int limite_qtd_palavras = dados_palavras[numero_sorteado].qtd;
	int numero_palavra_sorteada = rand() % limite_qtd_palavras;
	strcpy(palavra_sorteada, dados_palavras[numero_sorteado].vetpalavras[numero_palavra_sorteada]);
	
	// inicializar o array de letras adivinhadas com '\0'
    memset(letras_adivinhadas, '\0', sizeof(letras_adivinhadas));
	
}

// funcao para definir o premio da rodada
int sorteio_premio(int limite_premios){
	float dados_premios[11] = {0.00, 0.01, 100.00, 250.00, 500.00, 750.00, 1000.00, 2500.00, 5000.00, 7500.00, 10000.00};
	FILE *arq;

	// abrir arquivo contendo os valores dos premios armazenados
	arq = fopen("assets/PREMIOS.DAT", "r+b");
	verificacao_arquivo(arq);
	fread(&dados_premios,sizeof(float),1,arq);
	fclose(arq);

	// sorteio do premio
	numero_sorteado = rand() % limite_premios;
	
	return numero_sorteado;

}


