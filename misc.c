/* Este programa gera uma lista de números inteiros aleatória
 * e armazena esta lista em um arquivo de texto simples. Ele deverá
 * ser usado como entrada para os vários algoritmos de estrutura 
 * de dados que serão estudadas e também servem como base para
 * versão mais especializados que poderão ser mais convenientes */
 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "misc.h"

int geralista(int tam) {
	
	FILE *file;
	int i, num;
	
	if (tam > MAXLISTA) tam = MAXLISTA;
	
	file = fopen("lista.txt", "w");
	
	// muda a semente dos números aleatórios
	srand((unsigned) time(NULL)/2);
	
	for (i = 0; i< tam; i++) {
		num = rand();
		fprintf(file, "%d\n", num);
	}
	
	fclose(file);
	return 0;
}
