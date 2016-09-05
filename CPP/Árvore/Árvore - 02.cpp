/**********************************/
/*       CES 11 - Árvores         */
/*                                */
/*  Implementação usando          */
/* estrutura Contígua Melhorada   */
/*                                */
/*                  by Tuyama     */
/**********************************/
#include <stdio.h>
#include <stdlib.h>
const int MAX = 100;
typedef int node;
struct celula 
{ 
	char info; 
	int grau, pai;
};
struct arvore 
{ 
	celula Elemento[MAX+1]; 
	int ncel; 
};
void erro ()
{
	printf ("Erro");
	system ("pause");
}
node Raiz (arvore A)
{
	if (A.ncel == 0) return NULL;
	else return 1;
}
bool Vazia (arvore A) 
{ 
	return (A.ncel == 0); 
}
void Esvaziar (arvore *A) 
{ 
	A->ncel = 0; 
}
char Elemento (node n, arvore A)
{
	if (n<=0 || n>A.ncel) erro();
	else return A.Elemento[n].info;
}
node FilhoEsquerdo (node n, arvore A)
{
	if (n<=0 || n>A.ncel) erro();
	else if (A.Elemento[n].grau == 0) return NULL;
	else return n+1;
}
node Pai (node n, arvore A)
{
	if (n<=0 || n>A.ncel) erro();
	else if (n==1) return NULL;
	else return A.Elemento[n].pai;
}
node IrmaoDireito (node n, arvore A)
{
	if (n<=0 || n>A.ncel) erro();
	else if (n+1>A.ncel) return NULL;
	else if (A.Elemento[n].pai == A.Elemento[n+1].pai) return n+1;
	else return NULL;
}
void main ()
{


}