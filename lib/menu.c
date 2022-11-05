#include <stdio.h>
#include "menu.h"

void exibirMenu() {
    printf("\nFiltros disponíveis:");
	printf("\n1 - Aplicar borda");
	printf("\n2 - Efeito negativo");
	printf("\n3 - Efeito preto e branco");
	printf("\n4 - Efeito de brilho");
	printf("\n5 - Gira (ponta cabeça)");
	printf("\n6 - Espelhar");
	printf("\n7 - Gira (90 graus)");
	printf("\n0 - Sair do programa");

	printf("\nQual filtro deseja aplicar? -> ");
}

void exibirMenuFormatos(){
	printf("\nFormatos disponíveis:");
	printf("\n1 - PGM");
	printf("\n2 - BMP");
	printf("\nQual formato deseja utilizar? -> ");
}

void exibirMenuPGM(){
	printf("\nRotacoes:\n");
	printf("1 -> girar 90 para direita\n");
	printf("2 -> girar 90 para esquerda\n");
	printf("3 -> girar 180\n");
	printf("0 -> Para sair do programa\n");
	printf("\nQual rotacao deseja aplicar? -> ");
}