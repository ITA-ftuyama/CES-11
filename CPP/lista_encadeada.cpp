#include <stdio.h>
#include <stdlib.h>
#define N 10
typedef int vet[N];
struct node { int elem; node *prox; };
void imprimir (node* L)
{
	printf ("L : ");
	for (node *p=L->prox; p!=NULL; p=p->prox) 
		printf (" %d ", p->elem);
}
void inserir (node* L, vet v)
{
	for (int i=0; i<N; i++)
	{
		node *p, *q, *k;
		k = (node*)malloc(sizeof(node));
		k->elem = v[i]; k->prox = NULL;
		for (p=q=L; q!=NULL && q->elem<v[i]; q=q->prox) p = q;
		if (p==q) { k->prox=L; L=k; }
		else { k->prox=p->prox; p->prox=k; }
	}
}
void main ()
{
	vet v = {5,10,6,-3,24,7,15};
	node *L = (node*)malloc(sizeof(node));
	L->prox=NULL;
	inserir (L, v);
	imprimir (L);
	getchar ();
}