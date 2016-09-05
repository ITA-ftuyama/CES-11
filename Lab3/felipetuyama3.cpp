/****************************************************/
/*  Felipe Tuyama de Faria Barbosa - Turma 1        */
/*  Exercício 3                          	        */
/*  Compilado com Microsoft Visual C++ 2010 Express */
/****************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define N 51
/*-----------------------------------------------------------------------------------------------*/
struct pilha   // A pilha for implementada utilizando a estutura de um vetor.
{              // Embora parte de seu espaço alocado seja desperdiçado, há grande
	char S[N]; // ganho na agilidade de suas funções de manipulação dos elementos
	int t;     // (empilhar, desempilhar e ler o conteúdo da pilha).
};			   // Além do mais, uma palavra comum não excede 50 letras, memória ínfima.
struct node    // O node é a estutura principal de cada elemento da árvore. É formado de:
{
	char letra;       // Uma letra;
	int cont;         // Um contador, para indicar o número de palavras.
	node *filhos[26]; // 26 ponteiros, um para cada próxima letra do alfabeto,
};					  // para os outros nodes da árvore.
/*-----------------------------------------------------------------------------------------------*/
typedef node *arvore, *posicao;
int ascii (char letra) { return letra-'a'; }  // Função que associa uma letra minúscula a um número inteiro.
void inicNode (node *p)        // Essa função tem como finalidade iniciar os parâmetros de um novo node:
{
	for (int i = 0; i<26; i++) // Todos os seus ponteiros começam apontando para NULL.
		p->filhos[i] = NULL;
	p->cont = 0;               // E o contador do node começa em 0.
}
/*-----------------------------------------------------------------------------------------------*/
void inicPilha (pilha *P) { P->t=-1; }                   // Função para iniciar uma nova pilha.
int sizePilha (pilha P) { return P.t+1; }                // Função que retorna o tamanho da pilha.
void push (pilha *P, char c) { P->t++; P->S[P->t] = c; } // Função que insere uma letra na pilha.
void pop (pilha *P) { P->t--; }                          // Função que retira um elemento da pilha.
/*-----------------------------------------------------------------------------------------------*/
void PreOrdem (FILE *saida, pilha *P, arvore T)          // Função que imprime em pré-ordem uma árvore.
{
	if (T!=NULL) // Se a árvore não for vazia:
	{
		push (P, T->letra); // Colocar a letra do primeiro node na pilha.
		if (T->cont!=0)     // Se o contador desse node for diferente de zero,
		{                   // é porque há uma palavra na pilha P. Assim, imprimimos essa palavra:
			P->S[sizePilha(*P)] = '\0';                // Um "\0" é inserido ao final dessa pilha
			fprintf (saida, "%d %s\n", T->cont, P->S); // E o conteúdo da pilha é impresso no arquivo de saída.
		}
		for (int i=0; i<26; i++) // Chamada recursiva da função para todos os filhos do node atual.
			PreOrdem (saida, P, T->filhos[i]);
		pop (P); // Ao final, desempilhar o caractere da pilha.
	}
}
/*-----------------------------------------------------------------------------------------------*/
void main ()
{
	char c;
	bool word;
	posicao p;
	pilha P;        // Declaração de uma pilha P.
	inicPilha (&P); // Inicialização da pilha P.
	arvore T = (arvore)malloc(sizeof(node)); // Alocando um node líder para a árvore.
	inicNode (T);                            // Iniciar o node utilizando a função "inicNode".
	FILE *entrada = fopen ("entrada.txt", "r");
	if (!entrada) exit(1);
	FILE *saida = fopen ("saida.txt", "w");
	word = false; 
	// "word" é uma variável auxiliar na leitura das palavras da seguinte forma:
	// Se "word" é "true", então o programa está executando a leitura de uma palavra.
	// Se "word" é "false", então o programa terminou a leitura de uma palavra e está
	// preparado para a leitura da próxima palavra.
	while (fscanf(entrada, "%c", &c)>0) // Enquanto o arquivo não acabar, ler caracteres.
	{
		if (c>0 && c<255 && isalpha(c)) // Se o caractere for uma letra:
		{
			c = tolower(c); // Transforma a letra para minúscula.
			if (!word)      // Se essa for a primeira letra da palavra:
			{
				p = T;       // O ponteiro "p" aponta para a raiz da árvore.
				word = true; // A leitura da palavra começa.
			}
			if (p->filhos[ascii(c)]==NULL) // Se o node da letra não tiver sido alocada:
			{
				p->filhos[ascii(c)] = (posicao)malloc(sizeof(node)); //Alocar o node da letra.
				p->filhos[ascii(c)]->letra = c; // Preencher o conteúdo do node com a letra.
				inicNode (p->filhos[ascii(c)]); // Chama a função inicNode para o node da letra.
			}
			p = p->filhos[ascii(c)]; // O ponteiro de posição aponta para o node criado.
		}
		else if (word) // Se o caractere não for uma letra, mas uma palavra tiver sido iniciada,
		{
			word = false; // A leitura da palavra se encerra.
			p->cont++;    // E o contador da última letra da palavra é incrementado.
		}
	}
	for (int i=0; i<26; i++) // Chamada da função para imprimir árvore em pré-ordem.
		PreOrdem (saida, &P, T->filhos[i]);
	fclose (entrada);
	fclose (saida);
}