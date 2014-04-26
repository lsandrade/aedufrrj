#include <stdio.h>
#include <stdlib.h>
#include "arvores.h"


void buscaB(int x, pagina **ptraiz, pagina *pt, int *f, int *g) {
	/*int i,m;
	pagina *p, *pp;
	p = *ptraiz;
	pt = NULL;
	*f = 0;
	
	while (p != NULL) {
		pp = p->prox;
		i = 1;
		*g = 1;
		pt = p;
		m = p->chave;
		while (i <= m) {
			if (x > pp->chave) {
				i++;
				(*g)++;
				p = pp;
				pp = pp->prox;
			} else {
				if (x == pp->chave) {
					p = NULL;
					*f = 1;
				} else {
					p = p->filho; 
				}
				i = m + 2;
			}
		}
		if (i == m + 1) {
			p = pp->filho;
		}
	}*/
	return;
}

void visita(nodo *pt) {
	printf("%d\n", pt->chave);
}

void simet(nodo *pt) {
	if (pt->esq != NULL) simet(pt->esq);
	visita(pt);
	if (pt->dir != NULL) simet(pt->dir);
}

int buscabinaria(int x, nodo **pt) {
	int res;
		
	if (*pt == NULL) {
		// Retorna 0 se a árvore está vazia
		res = 0;
	} else {
		if (x == (*pt)->chave) {
			// Retorna 1 se a chave é encontrada
			res = 1;
		} else if (x < (*pt)->chave) {
			if ((*pt)->esq == NULL) {
				// Retorna 2 se a chave não é encontrada
				// mas deve ser inserido com um filho esquerdo
				res = 2;
			} else {
				*pt = (*pt)->esq;
				res = buscabinaria(x, pt);
			}
		} else {
			if ((*pt)->dir == NULL) {
				// Retorna 3 se a chave não é encontrada
				// mas deve ser inserida com um filho direito
				res = 3;
			} else {
				*pt = (*pt)->dir;
				res = buscabinaria(x, pt);
			}
		}
	}
	return res;
}

void altura(nodo *pt) {
	int alt1, alt2;
	if (pt->esq != NULL) {
		alt1 = (pt->esq)->altura;
	} else alt1 = 0;
	if (pt->dir != NULL) {
		alt2 = (pt->dir)->altura;
	} else alt2 = 0;
	if (alt1>alt2) pt->altura = alt1 + 1;
	else pt->altura = alt2 + 1;
}

void calculaalturas(nodo *pt) {
	if (pt->esq != NULL) calculaalturas(pt->esq);
	if (pt->dir != NULL) calculaalturas(pt->dir);
	altura(pt);
}

int inserenodo(int x, nodo **ptraiz) {
	nodo *pt;
	nodo *ptnovo;

	pt = *ptraiz;
	
	int res;
	
	res = buscabinaria(x, &pt);

	if (res == 1) {
		printf("Inserção Inválida: %d\n", x);
		return 0;
	} else {
		(ptnovo) = (nodo *) malloc(sizeof(nodo));
		(ptnovo)->chave = x;
		(ptnovo)->esq = NULL;
		(ptnovo)->dir = NULL;
		if (res == 0) {
			printf("Cria raiz\n");
			*ptraiz = ptnovo;
		} else if (res == 2) {
			pt->esq = ptnovo;
		} else pt->dir = ptnovo;
	}

	return 1;
}

void iniciano(int x, nodo **pt) {
	nodo *ptnovo;
	
	ptnovo = (nodo *) malloc(sizeof(nodo));
	ptnovo->chave = x;
	ptnovo->esq = NULL;
	ptnovo->dir = NULL;
	ptnovo->balanco = 0;
	ptnovo->altura = 0;
	*pt = ptnovo;
} 	

//Rotação esquerda da operação de rebalanceamento da árvore aVL
void caso1(nodo **pt, int *alterado){
	nodo *ptu,*ptv;
	
	ptu = (*pt)->esq;
 
	if (ptu->balanco == -1) {
		(*pt)->esq=ptu->dir;
		ptu->dir=*pt;
		(*pt)->balanco=0;
		*pt=ptu;
	} else { 
		ptv=ptu->dir;
		ptu->dir=ptv->esq;
		ptv->esq=ptu;
		(*pt)->esq=ptv->dir;
		ptv->dir=*pt;
		if (ptv->balanco == -1) {
			(*pt)->balanco=1;
		} else {
			(*pt)->balanco=0;
		}
		if (ptv->balanco == 1) {
			ptu->balanco=-1;
		} else {
			ptu->balanco=0;
		}
		*(pt)=ptv;
	}
	(*pt)->balanco = 0;
	*alterado = 0;
}

void caso2(nodo **pt, int *alterado){
	nodo *ptu,*ptv;
	
	ptu=(*pt)->dir;
	
	if (ptu->balanco==1) {
		//printf("Teste 2.1\n");
		(*pt)->dir=ptu->esq;
		ptu->esq=*pt;
		(*pt)->balanco=0;
		*pt=ptu;
	} else {
		//printf("Teste 2.2\n");
		ptv=ptu->esq;
		ptu->esq=ptv->dir;
		ptv->dir=ptu;
		(*pt)->dir=ptv->esq;
		ptv->esq=*pt;
		if (ptv->balanco == 1) {
			(*pt)->balanco=-1;
		} else {
			(*pt)->balanco=0;
		}
		if (ptv->balanco == -1) {
			ptu->balanco=1;
		} else {
			ptu->balanco=0;
		}
		*(pt)=ptv;
	}
	(*pt)->balanco=0;
	*alterado=0;
	//printf("Teste 2 saiu\n");
}

void insereA2VL(int x, nodo **pt, int *alterado) {
	if (*pt == NULL) {
		iniciano(x, pt);
		*alterado = 1;
	} else {
		if (x == (*pt)->chave) return;
		if (x < (*pt)->chave) {
			insereAVL(x, &((*pt)->esq), alterado);
			if (*alterado) {
				switch ((*pt)->balanco) {
				case 1: (*pt)->balanco = 0;
						*alterado = 0;
						break;
				case 0:	(*pt)->balanco=-1;
						break;
				case -1:caso1(pt, alterado);
				}
			}
		} else {
			insereAVL(x, &((*pt)->dir), alterado);
			if (*alterado) {
				switch((*pt)->balanco){
				case -1:(*pt)->balanco=0;
						*alterado=0;
						break;
				case 0:	(*pt)->balanco=1;
						break;
				case 1:	caso2(pt,alterado);
				}
			}
		}
	}
}


	
