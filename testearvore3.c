/* Este programa lê os dados de um arquivo texto para um vetor,
 * gera uma árvore Rubro Negra com os elementos desse vetor e mostra a altura da árvore.
 * Além disso ele mede o tempo que o algoritmo levou para executar. */

#include <stdio.h> //Biblioteca padrão de E/S
#include <time.h> //Biblioteca para rotinas de tempo
#include <math.h>
#include <stdlib.h>
#include "arvores.h"
#include "misc.h"

int compara2(int *a, int *b) {
	if (*a < *b) return -1;
	else if (*a==*b) return 0;
	else return 1;
}

int main() {
	
	FILE *file; // Declara dois arquivos
	unsigned int a[MAXLISTA], i, n = 0;
	clock_t ct_i, ct_f;
	
	nodo *ptaux;
	nodo *arvore = NULL;
	int alterado=0;
	
	char nome[20] = "lista.txt";
	//char nome[20] = "listaordenada.txt";
	
	// Abre os arquivos, um para a leitura e outra para a escrita
	if (! (file = fopen(nome, "r")) ) {
		printf("Lista não encontrada!\nCriando lista...");
		geralista(MAXLISTA);
		printf("Ok\n");
		file = fopen(nome, "r");
	}
	
	// Leitura do arquivo no vetor
	for (i =0; i<MAXLISTA;  i++) {
		fscanf(file, "%d", &a[i]);
	}
		
	printf("Começando a criar...\n");
	
	// Tempo antes da operação
	
	ct_i = clock();
	
	ptaux = arvore;
	
	for (i=0; i<(MAXLISTA); i++) {
		ptaux = arvore;
		if (buscabinaria(a[i], &ptaux) != 1) {
			inserenodo(a[i], &arvore);
			n++;
		}
	}
	
	printf("%d\n", n);
		
	
	ct_f = clock();
	// Tempo depois da operação
	
	
	printf("Árvore binária construída!\n");
	
	//simet(arvore);
	ptaux = arvore;
	

	
	calculaalturas(arvore);
	
	//simet(arvore);
	
	printf("A altura da árvore é %d \n", arvore->altura);
	
	// Escreve a diferença da tela
	printf("Levou %lf segundos para operar a árvore com %d elementos.\n", ((float)(ct_f - ct_i) / CLOCKS_PER_SEC), n);
		
	printf("Começando a criar árvore balanceada...\n");
		
	
	ct_i = clock();
	
	n = 0;
	
	nodo *raiz, *noatual, *nopai, *noavo;
	raiz = NULL;
	
	for (i=0; i<(MAXLISTA); i++) {
		noatual = NULL;
		nopai = NULL;
		noavo = NULL;
		alterado = 1;
		
		if (insereRN(a[i], &raiz, &raiz, &nopai, &noavo, &alterado) == 0) {
			n++;
			//printf("%d\n", n);
		}
	}
	
	//printf("%d\n", n);
		
	
	ct_f = clock();
	// Tempo depois da operação

	
	printf("Árvore binária balanceada construída!\n");
	
	//simet(arvore);
	
	calculaalturas(raiz);
	
	//simet(arvore);
	
	printf("A altura da árvore balanceada é %d \n", raiz->altura);
	
	// Escreve a diferença da tela
	printf("Levou %lf segundos para operar a árvore balanceada com %d elementos.\n", ((float)(ct_f - ct_i) / CLOCKS_PER_SEC), n);
	
	printf("Ordenando lista...\n");
	
	qsort(a, MAXLISTA, sizeof(int),compara2);
	
	printf("Começando a criar nova árvore...\n");
		
	ct_i = clock();
	
	n = 0;
	
	//Zerando árvore
	nodo *raiz2; 
	
	
	raiz2 = NULL;
	
	for (i=0; i<(MAXLISTA); i++) {
		noatual = NULL;
		nopai = NULL;
		noavo = NULL;
		alterado = 1;
		
		if (insereRN(a[i], &raiz2, &raiz2, &nopai, &noavo, &alterado) == 0) {
			n++;
			//printf("%d\n", n);
		}
	}
	
	//printf("%d\n", n);
		
	
	ct_f = clock();
	// Tempo depois da operação

	
	printf("Árvore binária balanceada com lista ordenada construída!\n");
	
	//simet(arvore);
	
	calculaalturas(raiz2);
	
	//simet(arvore);
	
	printf("A altura da árvore balanceada com lista ordenada é %d \n", raiz2->altura);
	
	// Escreve a diferença da tela
	printf("Levou %lf segundos para operar a árvore balanceada com %d elementos.\n", ((float)(ct_f - ct_i) / CLOCKS_PER_SEC), n);
		
	// Fecha os arquivos
	fclose(file);
	
	/* Note que mesmo com MAXLISTA = 100000 os procedimentos de
	 * leitura e escrita são quase imperceptíveis */
	
	return 0;
}
	
