#include <stdio.h>
#include <stdlib.h>
struct node {int elem; node *prox;};
struct fila {node *fr, *tr;};
void inicFila (fila *F)
{
	node *lider = (node*)malloc(sizeof(node));
	F->fr = F->tr = lider;
	lider->prox = NULL;
}
bool isEmpty (fila F)
{
	return (F.fr == F.tr);
}
int first (fila F)
{
	if (!isEmpty(F)) return F.fr->prox->elem;
	else printf ("\t\t ERRO"); return 0;

}
void enqueue (fila *F, int x)
{
	node *p = (node*)malloc(sizeof(node));
	p->elem = x; 
	p->prox = NULL;
	F->tr->prox = p;
	F->tr = p;
}
void dequeue (fila *F)
{
	node *q = F->fr->prox;
	if (isEmpty(*F)) printf ("\t\tERRO");
	else
	{
		if (q->prox==NULL) F->tr = F->fr;
		F->fr->prox = q->prox;
		free(q);
	}
}
void print (fila F)
{
	node *p;
	printf ("\t\t => F : ");
	for (p = F.fr->prox; p!=NULL; p=p->prox)
		printf ("%d ",p->elem);
}
void main ()
{
	int x;
	fila F;
	inicFila(&F);
	for (int n=0; n!=9; n=n)
	{
		printf ("\n\n\t\t      ::: FILA ::: ");
		printf ("\n\n\t\t\t::MENU::\n");
		printf ("\n\t________________________________________");
		printf ("\n\t| 1 - inicFila. 2 - isEmpty. 3 - first |");
		printf ("\n\t| 4 - enqueue.  5 - dequeue. 9 - exit  |");
		printf ("\n\tMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM\n\n\t");
		scanf ("%d", &n);
		switch (n)
		{
			case 1 : inicFila (&F); break;
			case 2 : printf ("\n\tEmpty : %d\n",isEmpty(F)); break;
			case 3 : printf ("\n\tFist : %d\n", first(F)); break;
			case 4 : scanf ("%d", &x); enqueue (&F,x); break;
			case 5 : dequeue (&F); break;
			case 6 : scanf ("%d", &n); for (int j=0; j<n; j++) {scanf("%d",&x); enqueue (&F,x);}
		}
		print (F);
		getchar ();
	}
}