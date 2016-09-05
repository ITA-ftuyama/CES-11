# include <stdio.h>
# include <stdlib.h>
# include <string.h>
#define N 100
struct pilha { char S[N],t; };
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
void push (pilha *P, char x)
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
	bool palindromo = true;
	char palavra[50];
	pilha P;
	iniPilha(&P);
	scanf ("%s", palavra);
	for (int i=0; i<strlen(palavra); i++)
		if (i<strlen(palavra)/2)
			push (&P,palavra[i]);
		else
		{
			if (i<strlen(palavra)/2+1 && strlen(palavra)%2!=0);
			else if (palavra[i]!=top(P)) palindromo = false;
			else pop(&P);
		}
	printf ("\n\nEH palindromo %d\n", palindromo);
	system ("pause");
}