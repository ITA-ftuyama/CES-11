/**********************************/
/*       CES 11 - Árvores         */
/*                                */
/*  Implementação usando          */
/* estrutura Lista de Filhos      */
/*                                */
/*                  by Tuyama     */
/**********************************/
#include <stdio.h>
#include <stdlib.h>
const int MAX = 50;
typedef int node;
struct celfilho
{ 
	node filho; 
	celfilho *prox;
};
typedef celfilho *lista;
typedef celfilho *posicao;
struct celula 
{
	char info;
	node pai;
	lista listaFilhos;
};
struct arvore
{
	node raiz;
	celula Elementos[MAX+1];
	int ncel;
};
void erro ()
{
	printf ("Erro");
	system ("pause");
}
node Raiz (arvore A)
{
	if (A.ncel==0) return NULL;
	else return A.raiz;
}
bool Vazia (arvore A) 
{ 
	return (A.ncel==0); 
}
void Esvaziar (arvore *A) 
{ 
	A->raiz = NULL;
	A->ncel = 0;
}
char Elemento (node n, arvore A)
{
	if (n<=0 || n>A.ncel) erro();
	else return A.Elementos[n].info;
}
node Pai (node n, arvore A)
{
	if (n<=0 || n>A.ncel) erro();
	else if (n == Raiz(A)) return NULL;
	else return A.Elementos[n].pai;
}
node FilhoEsquerdo (node n, arvore A)
{
	if (n<=0 || n>A.ncel) erro();
	else if (A.Elementos[n].listaFilhos == NULL) return NULL;
	else return A.Elementos[n].listaFilhos->filho;
}
node IrmaoDireito (node n, arvore A)
{
	posicao idir, p;
	if (n<=0 || n>A.ncel) erro();
	else if (n == Raiz(A)) return NULL;
	else
	{
		p = A.Elementos[A.Elementos[n].pai].listaFilhos;
		while (p->filho!=n) p = p->prox;
		idir = p->prox;
		if (idir == NULL) return NULL;
		else return idir->filho;
	}
}
void main ()
{


}