/**********************************/
/*       CES 11 - Árvores         */
/*                                */
/*  Implementação usando          */
/* estrutura Encadeada Direta     */
/*                                */
/*                  by Tuyama     */
/**********************************/
#include <stdio.h>
#include <stdlib.h>
const int MaxFil = 5;
struct celula 
{ 
	char info; 
	celula *filhos[MaxFil];
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
void Esvaziar (arvore *A) 
{ 
	A=NULL; 
}
char Elemento (node n, arvore A)
{
	return n->info;
}
node FilhoEsquerdo (node n, arvore A)
{
	return n->filhos[0];
}
void main ()
{


}