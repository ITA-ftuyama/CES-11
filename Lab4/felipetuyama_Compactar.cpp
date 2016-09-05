/****************************************************/
/*  Felipe Tuyama de Faria Barbosa - Turma 1        */
/*  Exercício 4 - Compactação                       */
/*  Compilado com Microsoft Visual C++ 2010 Express */
/****************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "felipetuyama_Codigo.cpp"

/*----------------------- Implementação de Pilha e suas funções -------------------------*/

struct pilha { unsigned char S[N]; int t; };						// Pilha de 0's e 1's.
void inicPilha (pilha *P) { P->t=-1; }								// Inicializa pilha.
int sizePilha (pilha P) { return P.t+1; }							// Retorna tamanho da pilha
void push (pilha *P, unsigned char c) { P->t++; P->S[P->t] = c; }	// Adiciona novo elemento.
void pop (pilha *P) { P->t--; }										// Remove elemento.

/*----------------------- Implementação do Heap e suas funções --------------------------*/

void trocar (nodeHeap *a, nodeHeap *b) { nodeHeap aux = *a; *a = *b; *b = aux; } // Troca valores de duas variáveis.

void Sift (int i, int n, heap *v) // Reorganiza “para baixo” o heap  alterado na posição i:
{
    int esq = 2*i;
    int dir = 2*i+1;
    int menor = i;
    if (esq <= n && Vet[esq].Hz < Vet[menor].Hz)
		menor = esq;
    if (dir <= n && Vet[dir].Hz < Vet[menor].Hz)
		menor = dir;
    if (menor != i) {
		trocar (&Vet[i], &Vet[menor]);
        Sift (menor, n, v);
    }
}
nodeHeap Min (heap *v) // Retorna o menor elemento do Heap de mínimo, o primeiro elemento.
{ 
	return Vet[1]; 
}
nodeHeap ExtractMin (heap *v) // Remove o primeiro elemento do Heap e então o reorganiza.
{
	nodeHeap min = Vet[1];
	Vet[1] = Vet[v->n--];
	Sift (1, v->n, v);
	return min;
}
void Modify (int k, nodeHeap x, heap *v) // Modifica um elemento do Heap e então o reorganiza.
{
	Vet[k] = x;
	while (k > 1 && Vet[k/2].Hz > Vet[k].Hz) //conserta para cima
	{ 
		trocar (&Vet[k], &Vet[k/2]);
		k = k/2;
	}
	Sift (k, v->n, v); // ou conserta para baixo
}
void Insert (nodeHeap x, heap *v) // Insere um novo elemento no Heap e o reorganiza.
{
    Modify(++v->n, x, v);
}
void newNode (heap *v, int freq, unsigned char c) // Cria um novo nodeHeap e o insere no Heap.
{
	nodeHeap *novoNode;
	novoNode = (nodeHeap*)malloc(sizeof(nodeHeap));				// Aloca um novo nodeHeap.
	novoNode->info = (nodeArvore*)malloc(sizeof(nodeArvore));	// Aloca um nodeArvore deste nodeHeap.
	novoNode->Hz = freq;										// Preenche o node com a sua frequência.
	novoNode->chr= c;											// Preenche o node com o seu char associado.
	novoNode->fesq = novoNode->fdir = NULL;						// Reseta os seus filhos como NULL.
	Insert (*novoNode, v);										// E finalmente insere o novo node no Heap.
}

/*------------------- Implementação da Árvore Heap e suas funções -----------------------*/

void encadear (heap *v)
{
	nodeHeap *elem = (nodeHeap*)malloc(sizeof(nodeHeap));
	elem->info = (nodeArvore*)malloc(sizeof(nodeArvore));
	elem->Hz = Min(v).Hz;
	elem->info->dir = ExtractMin(v).info;
	elem->Hz += Min(v).Hz;
	elem->info->esq = ExtractMin(v).info;
	Insert (*elem, v);
}
void codificar (nodeArvore *T, pilha *P, codigo *code) // Percorre a Árvore Heap para criar a codificação de Huffman.
{
	if (T!=NULL) // A condição de parada é a chegada a um ponteiro NULL. A árvore é percorrida em profundidade.
	{
		if (T->esq==NULL && T->dir==NULL)	// Se o node é raiz, associar codificação à letra encontrada.
		{
			code->size[T->caractere] = sizePilha(*P);			// O tamanho do código é igual ao tamanho da pilha.
			for (int i=0; i<sizePilha(*P); i++)					// Percorrer os elementos da pilha (sem alterá-los),
				code->code[T->caractere][i] =  (P->S[i]=='1');  // copiando a codificação para a estrutura "code".
		}
		push (P, '0'); codificar (T->esq, P, code); pop (P); // Adiciona "0" à pilha e chama filho esquerdo do node.
		push (P, '1'); codificar (T->dir, P, code); pop (P); // Adiciona "1" à pilha e chama filho direito do node
	}
}

/*---------------------------------------------------------------------------------------*/

void add (bool c, Bit *bit)	// Função que adiciona um novo bit ao "vetor de bits".
{													// Se o bit a for adicionado for "0", não faz nada.
	if (c) bit->v+=pow(2,(float)(7-bit->n%8));		// Se o bit a for adicionado for "1", adicionar o bit à sua posição.
	bit->n++;										// Incrementa o número de bits utilizados do vetor.
}

void main ()
{
	/*------------------ Declaração das variáveis do problema -------------------*/

	pilha P;					// Inicializando pilha P.
	inicPilha (&P);
	Bit bit;					// Inicializando "vetor de bits" bit.
	inicBit(&bit);
	heap H;						// Inicializando heap H.
	H.n=0;
	codigo code;				// Estrutura do código de Huffman.
	unsigned char c;			// Variável auxiliar.
	int contador[max];			// Inicializando o contador de frequência de caracteres.
	for (int i=0; i<max; i++) 
		contador[i]=0;
	FILE *entrada = fopen ("entrada.txt","r");		// Arquivo de entrada.
	if (!entrada) exit(1);	// Caso não haja arquivo de entrada, finalizar o programa.
	FILE *saida = fopen ("codificado.bin","wb");	// Arquivo de saída.

	/*------------------ Contagem da frequência de cada caractere ---------------*/

	while (fscanf (entrada, "%c", &c)>0) contador[c]++;	// Ler arquivo e contar a frequência dos caracteres.
	for (int i=0; i<max; i++)							// Percorrer o vetor contador de frequência dos caracteres
		if (contador[i]>0)								// Se a frequência de um dado caractere for maior que 0:
			newNode (&H, contador[i], i);				// Incluir o caractere no Heap H, associado à sua frequência.
	fprintf (saida, "%d", H.n);							// Findado o processo, imprimir número de elementos total do Heap.

	/*---------------------- Construindo a Árvore Heap --------------------------*/

	while (H.n>1) encadear (&H);						// Recursão geradora da Árvore Heap.
	codificar (H.elementos[1].info, &P, &code);			// Elaborarando a codificação de Huffman a partir desta Árvore.

	/*------------------ Imprimindo a Codificação de Huffman --------------------*/
		
	for (int i=0; i<max; i++)								// Percorrer novamente o vetor contador de frequência.
		if (contador[i]>0)									// Se a frequência de um caractere for maior que 0:
		{
			fprintf (saida, "\n%c\n%d\n", i, code.size[i]);	// Imprimir o caractere e o número de bits que ele ocupa.
			for (int j=0; j<code.size[i]; j++)				// E então, imprimir numericamente a sequência de bits
				fprintf (saida, "%d", code.code[i][j]);		// associada a este caractere (dada em 0's e 1's).
		}	
	rewind(entrada);										// Retornar o ponteiro de leitura da entrada para o início.

	/*--------------------- Lendo o numero de bits do arquivo -------------------*/

	while (fscanf (entrada, "%c", &c)>0)					// Ler o arquivo e determinar o seu tamanho em bits após codificado.
		bit.n+=code.size[c];								// Somando o número de bits que a sua escrita exigiria na codificação.
	rewind(entrada);										// Retornar o ponteiro de leitura da entrada para o início.
	fprintf (saida, "\n%d\n", bit.n);						// Imprimindo o número total de bits do arquivo.
																	
	/*----------------------- Codificando o texto  ------------------------------*/

	inicBit(&bit);											// Reinicializando o "vetor de bits".
	while (fscanf (entrada, "%c", &c)>0)					// Ler mais uma vez o arquivo de entrada.
		for (int i=0; i<code.size[c]; i++)					// Para cada caractere do arquivo, acessar sua codificação de Huffman:
		{
			add (code.code[c][i], &bit);					// E manipulando bit a bit do "vetor de bits",
			if (bit.n%8==0)									// escrever o seu conteúdo sempre que ele estiver "cheio", ou seja,
			{												// quando os 8 bits de um unsigned char forem ocupados. Nesse momento,
				fprintf (saida, "%c", bit.v);				// Escrevendo na saída um texto compactado.
				bit.v='\0';									// E resetanto o "vetor de bits" para 0000.0000.
			}	
		}													// Ao final do arquivo, imprimir conteúdo do "vetor de bits",
	if (bit.n%8!=0) fprintf (saida, "%c", bit.v);			// desde que ele não esteja vazio.

	/*---------------------------------- Fim ------------------------------------*/

	fclose (entrada);
	fclose (saida);
}