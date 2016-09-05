#include <stdio.h>
#include <stdlib.h>
#define N 100
typedef int vet[N];
struct fila {vet elem; int fr,tr; };
void inicFila (fila *F)
{ 
	F->fr = F->tr = 0;
}
bool isEmpty (fila F)
{
	return (F.fr == F.tr);
}
int first (fila F)
{
	if (!isEmpty(F)) return F.elem[F.fr];
	else printf ("\t\t ERRO"); return 0;
}
int prox (int i)
{
	return (i+1)%N;
}
void enqueue (fila *F, int x)
{
	if (prox(F->tr) == F->fr)  printf ("\t\tERRO");
	else 
	{
		F->elem[F->tr] = x;
		F->tr = prox (F->tr);
	}
}
void dequeue (fila *F)
{
	if (isEmpty(*F)) printf ("\t\tERRO");
	else F->fr = prox (F->fr);
}
void print (fila F)
{
	printf ("\t\t => F : ");
	for (int i = F.fr; i<F.tr; i++)
		printf ("%d ", F.elem[i]);
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