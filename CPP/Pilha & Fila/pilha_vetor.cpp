# include <stdio.h>
# include <stdlib.h>
#define N 100
struct pilha { int S[N],t; };
void Erro ()
{
	printf ("ERRO");
	system ("pause");
	exit (1);
}
void iniPilha (pilha *P) { P->t=-1; }
int size (pilha P) { return P.t+1; }
bool isEmpty (pilha P) { return (P.t<0); }
int top (pilha P)
{
	if (isEmpty(P)) Erro();
	return P.S[P.t];
}
void push (pilha *P, int x)
{
	if (size(*P) == N) Erro();
	P->t++;
	P->S[P->t] = x;
}
void pop (pilha *P)
{
	if (isEmpty (*P)) Erro ();
	P->t--;
}
void show (pilha P)
{
	printf ("\t %d Elementos: \n\n", P.t+1);
	for (int i=P.t; i>=0; i--)
		printf ("\t\t%d \n", P.S[i]);
}
void main ()
{
	int x;

	pilha P;
	iniPilha(&P);
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
			case 1 : iniPilha (&P); break;
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