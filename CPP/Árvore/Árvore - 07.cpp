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
#define FimDoMundo 0
#define DEFAULT "( A  (B  (E))   (C  (F)  (G))   (D  (H  (I) (J) (K))) )"
const int MAX = 100;
typedef int node;
typedef char string[MAX];
#pragma region typedefs
struct celula 
{  
	char info; 
	int grau, pai; 
};
struct arvore 
{ 
	celula Elemento[MAX+1]; 
	int ncel, ngrau;
};
struct nodef 
{
	node no; 
	nodef *prox;
};
struct pilha 
{ 
	node S[MAX], t; 
};
struct fila 
{
	nodef *fr, *tr;
};
void erro ()
{
	printf ("Erro");
	system ("pause");
}
int max (int x, int y)
{
	if (x>y) return x;
	else return y;
}
#pragma endregion;
/***********************************************/
/*                   FILA                      */
/***********************************************/
#pragma region Pilha
void inicFila (fila *F)
{
	nodef *lider = (nodef*)malloc(sizeof(node));
	F->fr = F->tr = lider;
	lider->prox = NULL;
}
bool isEmpty (fila F)
{
	return (F.fr == F.tr);
}
node first (fila F)
{
	if (!isEmpty(F)) return F.fr->prox->no;
	else printf ("\t\t ERRO"); return 0;

}
void enqueue (fila *F, node x)
{
	nodef *p = (nodef*)malloc(sizeof(nodef));
	p->no = x; 
	p->prox = NULL;
	F->tr->prox = p;
	F->tr = p;
}
void dequeue (fila *F)
{
	nodef *q = F->fr->prox;
	if (isEmpty(*F)) printf ("\t\tERRO");
	else
	{
		if (q->prox==NULL) F->tr = F->fr;
		F->fr->prox = q->prox;
		free(q);
	}
}
void print (fila F, arvore A)
{
	nodef *p;
	int i = 1;
	printf ("\n F : ");
	for (p = F.fr->prox; p!=NULL; p=p->prox)
		printf ("%2c,", A.Elemento[p->no].info);
	printf ("\n     ");
	for (p = F.fr->prox; p!=NULL; p=p->prox)
		printf ("%2d,", i++);
}
#pragma endregion;
/***********************************************/
/*                   PILHA                     */
/***********************************************/
#pragma region Pilha
void inicPilha (pilha *P) 
{ 
	P->t=-1; 
}
int size (pilha P) 
{ 
	return P.t+1; 
}
bool isEmpty (pilha P) 
{ 
	return (P.t<0); 
}
node top (pilha P)
{
	if (isEmpty(P)) return 0;
	return P.S[P.t];
}
void push (pilha *P, node x)
{
	if (size(*P) == MAX) erro();
	P->t++;
	P->S[P->t] = x;
}
void pop (pilha *P)
{
	if (isEmpty (*P)) erro ();
	P->t--;
}
#pragma endregion;
/***********************************************/
/*                  ÁRVORE                     */
/***********************************************/
#pragma region Arvore
node Raiz (arvore A)
{
	if (A.ncel == 0) return 0;
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
int Nelementos (arvore A)
{
	return A.ncel;
}
char Elemento (node n, arvore A)
{
	if (n<=0 || n>A.ncel) erro();
	else return A.Elemento[n].info;
}
node FilhoEsquerdo (node n, arvore A)
{
	if (n<=0 || n>A.ncel) erro();
	else if (A.Elemento[n].grau == 0) return 0;
	else return n+1;
}
node Pai (node n, arvore A)
{
	if (n<=0 || n>A.ncel) erro();
	else if (n==1) return 0;
	else return A.Elemento[n].pai;
}
node IrmaoDireito (node n, arvore A)
{
	if (n<=0 || n>A.ncel) erro();
	else if (n+1>A.ncel) return 0;
	else if (A.Elemento[n].pai == A.Elemento[n+1].pai) return n+1;
	else for (int i=1; i<A.ncel; i++)
			if (A.Elemento[i].pai == A.Elemento[n].pai)
				if (i>n) return i;
	return 0;
}
int AlturaNode (node n, arvore A)
{
	int i = 0;
	while (n!=0)
	{
		n = A.Elemento[n].pai;
		i++;
	}
	return i;
}
int AlturaArvore (arvore A)
{
	int max = 0;
	for (node p = 1; p<A.ncel; p++)
		if (AlturaNode(p,A)>max)
			max = AlturaNode(p,A);
	return max;
}
void printArvore (node n, arvore A)
{
	printf ("\t%2d: %*c\n", n, 2*AlturaNode(n,A), A.Elemento[n].info);
	for (node p = FilhoEsquerdo(n, A); p!=0; p = IrmaoDireito(p, A))
		printArvore (p, A);
}
void printa (arvore A)
{
	fila F;
	inicFila (&F);
	printf ("\n\n\t Arvore A: \n\n");
	printArvore (1, A);
}
void PreOrdem (char cadeia[], arvore *A, fila *F, pilha P)
{
	node n, m; n = m = 1;
	for (int i = 0; cadeia[i] != '\0'; i++)
	{
		if (cadeia[i] == ' ');
		else if (cadeia[i] =='(');
		else if (cadeia[i] ==')')
		{
			m = top(P);
			pop (&P);
			if (top(P)!=0) A->Elemento[top(P)].grau++;
			A->ngrau = max (A->ngrau, A->Elemento[top(P)].grau);
			A->Elemento[m].pai = top(P);
		}
		else
		{
			push (&P, n);
			A->Elemento[n].info = cadeia[i];
			enqueue (F, n++);
			A->ncel++;
		}
	}
}
void inicArvore (char cadeia[], arvore *A, fila *F)
{
	pilha P;
	inicPilha (&P);
	Esvaziar (A);
	for (int i = 0; i<MAX; i++) 
	{
		A->Elemento[i].info = '\0';
		A->Elemento[i].pai = 0;
		A->Elemento[i].grau = 0;
	}
	A->ncel = 0;
	A->ngrau = 0;
	PreOrdem (cadeia, A, F, P);
}
#pragma endregion;
/***********************************************/
/*                  CADEIA                     */
/***********************************************/
#pragma region Cadeia
void changeCadeia (char cadeia[], char c, int k)
{
	int n = 0;
	for (int i = 0; cadeia[i] != '\0'; i++)
		if (cadeia[i] == ' ');
		else if (cadeia[i] =='(') n++;
		else if (cadeia[i] == ')');
		else if (n == k) cadeia[i] = c;
}
void trim (char cadeia[])
{
	int n, a, b; n = a = b = 0;
	for (int i = 0; cadeia[i] != '\0'; i++)
		if (cadeia[i] == ' ');
		else
		{
			if (cadeia[i] == '(') a++;
			if (cadeia[i] == ')') b++;
			cadeia[n++] = cadeia[i];
		}
	if (a==b) cadeia[n]='\0';
	else cadeia[0] = '\0';
}
#pragma endregion
/***********************************************/
void intro (char cadeia[], arvore A, fila F)
{
	int n, k; char c;
	printf ("\n\n\t\t\t   ::: ARVORES :::   ");
	printf ("\n\t   ___________________________________________________");
	printf ("\n\t   | 1 - editar Cadeia. 2 - FilhoEsquerdo. 3 - Pai.   |");
	printf ("\n\t   | 4 - IrmaoDireito.  5 - Info.Node      6 - Cadeia |");
	printf ("\n\t   | 7 - Arvore         8 - Info.Arvore    0 - Cls.   |");
	printf ("\n\t   | -1- MudarInfo                         9 - exit.  |");
	printf ("\n\t   MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM");
	printf ("\n\n Cadeia : %s \n", cadeia);
	printf ("Comando>> "); scanf ("%d", &n);
	if ((n>=2 && n<=5) || n==-1)
	{ printf ("Qual node? "); scanf ("%d", &k); }
	switch (n)
	{
		case-1: printf ("Deseja mudar %c para? ", A.Elemento[k].info); fflush (stdin); scanf ("%c", &c); changeCadeia (cadeia, c, k); break;
		case 0: printf ("\n\t By Tuyama."); fflush (stdin); getchar (); system ("cls"); break;
		case 1: cadeia[0] = '\0'; scanf ("%s", cadeia); trim (cadeia); break;
		case 2:	if (FilhoEsquerdo(k,A)!=0) printf ("\n O Filho Esquerdo de %c eh %c \n", A.Elemento[k].info, A.Elemento[FilhoEsquerdo(k,A)].info); break;
		case 3: if (Pai(k,A)!=0) printf ("\n O Pai de %c eh %c \n", A.Elemento[k].info, A.Elemento[Pai(k,A)].info); break;
		case 4: if (IrmaoDireito(k,A)!=0) printf ("\n O Irmao Direito de %c eh %c \n", A.Elemento[k].info, A.Elemento[IrmaoDireito(k,A)].info); break;
		case 5: printf ("\n O noh %d eh %c, grau %d, nivel %d \n", k, A.Elemento[k].info, A.Elemento[k].grau, AlturaNode(k,A)); break;
		case 6: print (F, A); break;
		case 7: printa (A); break;
		case 8: printf ("\n\tNelementos: %d \n\tNgrau: %d \n\tAltura: %d", Nelementos(A), A.ngrau, AlturaArvore(A)); break;
		case 9: exit (1); break;
	}

}
void main ()
{
	char cadeia[] = DEFAULT;
	fila F;
	arvore A;
	trim (cadeia);
	while (!FimDoMundo)
	{
		inicFila (&F);
		inicArvore (cadeia, &A, &F);
		intro (cadeia, A, F);
		getchar ();
	}
}