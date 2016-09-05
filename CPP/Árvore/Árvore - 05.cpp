/**********************************/
/*       CES 11 - Árvores         */
/*                                */
/*  Implementação usando          */
/* estrutura Encadeamento de      */
/*             pais e irmãos      */
/*                                */
/*                  by Tuyama     */
/**********************************/
#include <stdio.h>
#include <stdlib.h>
const int MAX = 50;
struct celula 
{
	char info;
	celula *pai, *fesq, *idir;
};
typedef celula *node;
typedef celula *arvore;
void erro ()
{
	printf ("Erro");
	system ("pause");
}
node Raiz (arvore A)
{
	return A;
}
bool Vazia (arvore A) 
{ 
	return (A==NULL); 
}
void Esvaziar (node *n) 
{ 
	if (*n == NULL) return;
	Esvaziar (&(*n)->fesq);
	Esvaziar (&(*n)->idir);
	free(*n);
	*n=NULL;
}
char Elemento (node n, arvore A)
{
	return n->info;
}
node Pai (node n, arvore A)
{
	return n->pai;
}
node FilhoEsquerdo (node n, arvore A)
{
	return n->fesq;
}
node IrmaoDireito (node n, arvore A)
{
	return n->idir;
}
void main ()
{


}