#include <stdlib.h>

struct pag {
	int chave;
	struct pag *filho;
	struct pag *prox;
};

typedef struct pag pagina;

struct node {
	int chave;
	int altura;
	int balanco;
	struct node *esq;
	struct node *dir;
};

typedef struct node nodo;

void buscaB(int x, pagina **ptraiz, pagina *pt, int *f, int *g);

void visita(nodo *pt);

void simet(nodo *pt);

int buscabinaria(int x, nodo **pt);

void altura(nodo *pt);

void calculaalturas(nodo *pt);

int inserenodo(int x, nodo **ptraiz);

void iniciano(int x, nodo **pt);

void caso1(nodo **pt, int *alterado);

void caso2(nodo **pt, int *alterado);

void insereAVL(int x, nodo **pt, int *alterado);

void rotaRN(nodo **ptraiz, nodo **ptatual, nodo **ptpai, nodo **ptavo, nodo **ptbisavo, int *a);

int insereRN(int x, nodo **ptraiz, nodo **ptatual, nodo **ptpai, nodo **ptavo, int *a);
	
