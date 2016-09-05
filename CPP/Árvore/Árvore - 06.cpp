#include <stdio.h>
#include <stdlib.h>
#define N 32
#define VETOR {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32}
struct celula 
{
	int elem;
	celula *fesq, *fdir;
};
typedef celula *Dicionario;
bool search (int x, Dicionario T)
{
	if (T == NULL) return false;
	else if (x > T->elem) search (x, T->fdir);
	else if (x < T->elem) search (x, T->fesq);
	else return true;
}
void inserir (int x, Dicionario *T)
{
	if (*T == NULL)
	{
		*T = (celula*)malloc(sizeof(celula));
		(*T)->fesq = (*T)->fdir = NULL;
		(*T)->elem = x;
	}
	else if (x > (*T)->elem) inserir (x, &(*T)->fdir);
	else if (x < (*T)->elem) inserir (x, &(*T)->fesq);
}
int eliminarMin (Dicionario *T) 
{
   celula *p;
   int ret;
   if ((*T)->fesq == NULL) 
   {
		ret = (*T)->elem;
		p = *T;
		*T = (*T)->fdir;
		free(p);
   }
   else ret = eliminarMin (&(*T)->fesq);
   return ret;
}
void eliminar (int x, Dicionario *T) 
{
   celula *p;
   if (*T != NULL) 
   {
      if (x < (*T)->elem) eliminar (x, &(*T)->fesq);
      else if (x > (*T)->elem) eliminar(x, &(*T)->fdir);
      else if ((*T)->fesq == NULL && (*T)->fdir == NULL) 
	  {
          free (*T);
          *T = NULL;
      }
      else if ((*T)->fesq == NULL)
	  {
		  p = *T;
          *T = (*T)->fdir;
		free (p);
      }
      else if ((*T)->fdir == NULL)
	  {
          p = (*T);
          *T = (*T)->fesq;
          free (p);
      }
      else (*T)->elem = eliminarMin (&(*T)->fdir); 
   } 
}
void insert (int v[], Dicionario *T)
{
	for (int j=2; N/j>=1; j*=2)
		for (int i=N/j; i<N; i+=N/j)
		{
			inserir (v[i], T);
			if (i>1) inserir (v[i-1], T);
			if (i<N-1) inserir (v[i+1], T);
		}
	inserir (v[0], T);
}
void print (int n, Dicionario T)
{
	if (T!=NULL)
	{
		print (n+1, T->fdir);
		printf ("\t%*d\n", 2*n, T->elem);
		print (n+1, T->fesq);
	}
	else printf ("\t%*c\n", 2*n, 124);
}
void printPreOrdem (int n, Dicionario T)
{
	if (T!=NULL)
	{
		printf ("\t%*d\n", 2*n, T->elem);
		printPreOrdem (n+1, T->fdir);
		printPreOrdem (n+1, T->fesq);
	}
	else printf ("\t%*c\n",2*n, 124);
}
void cadeia (Dicionario T)
{
	if (T!=NULL)
	{
		printf ("(%d", T->elem);
		cadeia (T->fdir);
		cadeia (T->fesq);
		printf (")");
	}
}
void main ()
{
	int v[] = VETOR;
	Dicionario T = NULL;
	for (int n=0, x; n!=9; n=n)
	{
		printf ("\n\n\t\t    ::: ARVORE BINARIA ::: ");
		printf ("\n\t___________________________________________");
		printf ("\n\t| 1 - Search.  2 - Inserir. 3 - Eliminar. |");
		printf ("\n\t| 4 - Print    5 - MultIn   6 - Cadeia    |");
		printf ("\n\t| 7 - PrintPre              9 - Exit      |");
		printf ("\n\tMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM\n\n");
		printf ("\tComando>> "); scanf ("%d", &n);
		if (n>0 && n<4) { printf ("Digite o valor: "); scanf ("%d", &x); }
		switch (n)
		{
			case 1 : if (search (x, T)) printf ("Esta na Lista"); break;
			case 2 : inserir (x, &T); break;
			case 3 : eliminar (x, &T); break;
			case 4 : print (1, T); break;
			case 5 : insert (v, &T); break;
			case 6 : printf ("\tCadeia>> "); cadeia (T); break;
			case 7 : printf ("\tArvore:\n"); printPreOrdem (1,T); break;
			case 9 : exit(1); break;
		}
		getchar ();
	}
}