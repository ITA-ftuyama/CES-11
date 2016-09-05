#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 30
typedef struct noh noh;
typedef char string[MAX];
struct noh	{ noh *prox; char chr;};
bool BemFormada (string s)
{
	int lista=0;
	noh *L = NULL;
	for(int pos=0; s[pos]!='\0' || pos<MAX; pos++)
	{
		if (s[pos]=='{' || s[pos]=='(')
		{
			noh *novo = (noh*)malloc(sizeof(noh));
			novo->chr = s[pos];
			novo->prox = L;
			L = novo;
			lista++;
		}
		else if (s[pos]=='}' || s[pos]==')')
		{
			if (L!=NULL && (s[pos]=='}' && '{'==L->chr || s[pos]==')' && '('==L->chr))
			{
				noh *aux = L->prox;
				free(L);
				L = aux;
				lista--;
			}
			else return 0;
		}
	}
	return (lista==0);
}
void main ()
{
	string expr;
	while (strcmp(expr,"exit")!=0)
	{
		scanf ("%s",expr);
		if (BemFormada(expr)) printf ("Bem Formada \n");
		else printf ("Mal Formada \n");
		getchar();
	}
}