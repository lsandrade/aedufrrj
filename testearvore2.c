/* Este programa lê os dados de um arquivo texto para um vetor,
 * gera uma árvore AVL com os elementos desse vetor e mostra a altura da árvore.
 * Além disso ele mede o tempo que o algoritmo levou para executar. */

#include <stdio.h> //Biblioteca padrão de E/S
#include <time.h> //Biblioteca para rotinas de tempo
#include <math.h>
#include <stdlib.h>
#include "arvores.h"
#include "misc.h"

#define D	2 // Ordem da árvore B

int main() {
	
	FILE *file; // Declara dois arquivos
	unsigned int a[MAXLISTA], i, n = 0;
	long t_i, t_f;
	clock_t ct_i, ct_f;
	
	nodo *ptaux, *ptaux2;
	nodo *arvore = NULL, *arvore2 =NULL;
	int alterado=0;
	
	// Abre os arquivos, um para a leitura e outra para a escrita
	if (! (file = fopen("lista.txt", "r")) ) {
		printf("Lista não encontrada!\nCriando lista...");
		geralista(MAXLISTA);
		printf("Ok\n");
		file = fopen("lista.txt", "r");
	}
	
	// Leitura do arquivo no vetor
	for (i =0; i<MAXLISTA;  i++) {
		fscanf(file, "%d", &a[i]);
	}
		
	printf("Começando a criar...\n");
	
	// Tempo antes da operação
	t_i = time(NULL);
	ct_i = clock();
	
	ptaux = arvore;
	
	for (i=0; i<MAXLISTA; i++) {
		ptaux = arvore;
		if (buscabinaria(a[i], &ptaux) != 1) {
			inserenodo(a[i], &arvore);
			n++;
		}
	}
	
	printf("%d\n", n);
		
	
	ct_f = clock();
	// Tempo depois da operação
	t_f = time(NULL);
	
	printf("Árvore binária construída!\n");
	
	//simet(arvore);
	ptaux = arvore;
	

	
	calculaalturas(arvore);
	
	//simet(arvore);
	
	printf("A altura da árvore é %d \n", arvore->altura);
	
	// Escreve a diferença da tela
	printf("Levou %lf segundos para operar a árvore com %d elementos.\n", ((float)(ct_f - ct_i) / CLOCKS_PER_SEC), n);
		
	printf("Começando a criar...\n");
		
	t_i = time(NULL);
	ct_i = clock();
	
	ptaux2 = arvore2;
	
	n = 0;
	
	for (i=0; i<MAXLISTA; i++) {
		ptaux2 = arvore2;
		if (buscabinaria(a[i], &ptaux2) != 1) {
			insereAVL(a[i], &arvore2, &alterado);
			n++;
		}
	}
	
	printf("%d\n", n);
		
	
	ct_f = clock();
	// Tempo depois da operação
	t_f = time(NULL);
	
	printf("Árvore binária balanceada construída!\n");
	
	//simet(arvore);
	ptaux2 = arvore2;
	

	
	calculaalturas(arvore2);
	
	//simet(arvore);
	
	printf("A altura da árvore balanceada é %d \n", arvore2->altura);
	
	// Escreve a diferença da tela
	printf("Levou %lf segundos para operar a árvore balanceada com %d elementos.\n", ((float)(ct_f - ct_i) / CLOCKS_PER_SEC), n);
	// Fecha os arquivos
	fclose(file);
	
	/* Note que mesmo com MAXLISTA = 100000 os procedimentos de
	 * leitura e escrita são quase imperceptíveis */
	
	return 0;
}
	
