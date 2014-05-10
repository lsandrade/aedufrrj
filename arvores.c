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

void insereAVL(int x, nodo **pt, int *alterado) {
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
void rotaRN(nodo **ptraiz, nodo **ptatual, nodo **ptpai, nodo **ptavo, nodo **ptbisavo, int *a) {
	nodo *ptaux, *pttio;
	
	*a = 2;
	//printf("Dentro da rotação\n");
	if ((*ptpai)->balanco == 0) {
		//printf("Checou pai\n");
		if (*ptpai == (*ptavo)->esq) {
			pttio = (*ptavo)->dir;
		} else pttio = (*ptavo)->esq;
		//printf("Checou avô e recuperou tio\n");
		if (pttio != NULL && pttio->balanco == 0) { // Caso 2.1
			//printf("Caso simples\n");
			(*ptpai)->balanco = 1;
			(*ptavo)->balanco = 0;
			pttio->balanco = 1;
			*a = 0;
		} else { // Caso 2.2
			(*ptavo)->balanco = 0;  // Aqui está o erro (=1)
			if (*ptatual == (*ptpai)->esq) {
				if (*ptpai == (*ptavo)->esq) { // Caso 2.2.1
					//printf("Rotação direita\n");
					ptaux = *ptpai;
					(*ptpai)->balanco = 1;
					(*ptavo)->esq = (*ptpai)->dir;
					(*ptpai)->dir = *ptavo;
				} else { //Caso 2.2.2
					//printf("Rotação dupla esquerda\n");
					ptaux = *ptatual;
					(*ptatual)->balanco = 1;
					(*ptavo)->dir = (*ptatual)->esq;
					(*ptpai)->esq = (*ptatual)->dir;
					(*ptatual)->esq = *ptavo;
					(*ptatual)->dir = *ptpai;
				} 
			} else {
				if (*ptpai == (*ptavo)->dir) { // Caso 2.2.3
					//printf("Rotação esquerda\n");
					ptaux = *ptpai;
					(*ptpai)->balanco = 1;
					(*ptavo)->dir = (*ptpai)->esq;
					(*ptpai)->esq = *ptavo;
					//printf("Fim da rotação esquerda\n");
				} else { //Caso 2.2.4
					//printf("Rotação dupla direita\n");
					ptaux = *ptatual;
					(*ptatual)->balanco = 1;
					(*ptavo)->esq = (*ptatual)->dir;
					(*ptpai)->dir = (*ptatual)->esq;
					(*ptatual)->dir = *ptavo;
					(*ptatual)->esq = *ptpai;
				} 
			}
			if (*ptbisavo != NULL) {
				if ((*ptatual)->chave < (*ptbisavo)->chave) {
					(*ptbisavo)->esq = ptaux;
				} else (*ptbisavo)->dir = ptaux;
			} else *ptraiz = ptaux;
		}
	}
	(*ptraiz)->balanco = 1;
	//printf("Saindo da rotação\n");
}


// o campo balanço é 0 se vermelho e 1 se preto
int insereRN(int x, nodo **ptraiz, nodo **ptatual, nodo **ptpai, nodo **ptavo, int *a) {
	nodo *ptnovo;
	int ret = 0;
	
	if (*ptatual == NULL) {
		iniciano(x, ptatual);
		if (*ptraiz == *ptatual) {//NULL) {
			//printf("Criando raiz\n");
			(*ptatual)->balanco = 1; //O valor 1 é referente a cor (1 NEGRO e 0 RUBRO)
			*ptraiz = *ptatual;
		} else if (x < (*ptpai)->chave) {
			//printf("Colocando filho esquerdo\n");
			(*ptpai)->esq = *ptatual;
		} else {
			//printf("Colocando filho direito\n");
			(*ptpai)->dir = *ptatual;
		}
	} else if (x != (*ptatual)->chave) {
		if ( x < (*ptatual)->chave ) {
			ptnovo = (*ptatual)->esq;
		} else {
			ptnovo = (*ptatual)->dir;
		}
		//printf("Recursão\n");
		ret = insereRN(x, ptraiz, &ptnovo, ptatual, ptpai, a);
		//printf("Voltando da recursão\n");
		if (*a == 1) {  //O valor 1 é referente ao balanço da árvore (1 desbalanceada e 0 balanceada)
			//printf("Rotacionando\n");
			rotaRN(ptraiz, &ptnovo, ptatual, ptpai, ptavo, a);
		} else if (*a == 0) { 
			*a = 1;
		}
	} else return 1;//printf("Inserção Inválida");
	return ret;
}
		
		
		



	
