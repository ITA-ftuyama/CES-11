# include <stdio.h>
# include <stdlib.h>
struct node { int elem; node *prox; };
typedef node *pilha;
pilha P1;
void Erro ()
{
	printf ("ERRO");
	system ("pause");
	exit (1);
}
void inicPilha (pilha *P) { *P = NULL; }
int size (pilha P)
{
	int t = 0;
	for (node *v=P; v!=NULL; v=v->prox, t++);
	return t;
}
bool isEmpty (pilha P) { return (P==NULL); }
int top (pilha P) 
{ 
	if (isEmpty(P)) Erro();
	return P->elem; 
}
void push (pilha *P, int x)
{
	node *aux;
	aux = *P;
	*P = (node*)malloc(sizeof(node));
	(*P)->elem = x;
	(*P)->prox = aux;
}
void pop (pilha *P)
{
	node *aux;
	if (isEmpty(*P)) Erro ();
	aux = *P;
	*P=(*P)->prox;
	free (aux);
}
void show (pilha P)
{
	printf ("\t %d Elementos: \n\n", size(P));
	for (node *p=P; p!=NULL; p=p->prox)
		printf ("\t\t%d \n", p->elem);
}
void main ()
{
	int x;

	pilha P;
	inicPilha (&P);
	for (int n=0; n!=9; n=n)
	{
		printf ("\n\n\t\t      ::: PILHA ::: ");
		printf ("\n\n\t\t\t::MENU::\n");
		printf ("\n\t______________________________________");
		printf ("\n\t| 1 - iniPilha 2 - isEmpty 3 - top   |");
		printf ("\n\t| 4 -   push   5 -   pop   9 - exit  |");
		printf ("\n\tMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM\n\n\t");
		scanf ("%d", &n);
		switch (n)
		{
			case 1 : inicPilha (&P); break;
			case 2 : printf ("\n\tEmpty : %d\n",isEmpty(P)); break;
			case 3 : printf ("\n\tTop : %d\n", top(P)); break;
			case 4 : scanf ("%d", &x); push (&P,x); break;
			case 5 : pop (&P); break;
			case 6 : scanf ("%d", &n); for (int j=0; j<n; j++) {scanf("%d",&x); push (&P,x);}
		}
		show (P);
		getchar ();
	}
}