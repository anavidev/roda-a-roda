// programa para rodar o jogo

/* bibliotecas */
#include <locale.h>
#include "rodada.c"

/* corpo do programa */

int main(void){
	
	setlocale(LC_ALL, "");
	srand(time(NULL));
	
	sorteio_palavra(5);
	rodada();

	return 0;
}
