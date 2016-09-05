/****************************************************/
/*  Felipe Tuyama de Faria Barbosa - Turma 1        */
/*  Exercício 4 - Descompactação                    */
/*  Compilado com Microsoft Visual C++ 2010 Express */
/****************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "felipetuyama_codigo.cpp"

/*------------------- Implementação da Árvore Heap e suas funções -----------------------*/

void inicArvore (heap *v) // Função que inicializa uma nova Árvore.
{
	Vet[1].info = (nodeArvore*)malloc(sizeof(nodeArvore)); // Aloca o nodeArvore Raiz.
	Vet[1].fesq = Vet[1].fdir = NULL;                      // Reseta os filhos da raiz como NULL.
}
void createNode (nodeArvore *T, nodeArvore x, codigo code, int i, unsigned char c) // Insere nodeArvore na Árvore Heap.
{
	// A estratégia é percorrer a árvore segundo a codificação de Huffman até o local de inserção do novo nodeArvore.
	if (code.code[c][i])		 // Se o caractere for "1":
	{
		if (i+1==code.size[c])	// Se a código relacionado ao caractere tiver chegado ao final:
		{
			T->dir = (nodeArvore*)malloc(sizeof(nodeArvore));		// Alocar espaço na Árvore Heap.
			*T->dir = x;											// Inserir nodeArvore.
		}
		else					// Se o código ainda não tiver chegado ao final:
		{
			if (T->dir==NULL)	// Se o filho direito for nulo,
			{														// Deve-se criar um node de conexão (sem conteúdo).
				T->dir = (nodeArvore*)malloc(sizeof(nodeArvore));	// Alocar um novo nodeArvore.
				T->dir->esq = T->dir->dir = NULL;					// E setar seus filhos como NULL.
			}
			createNode (T->dir, x, code, i+1, c);	// Mergulhar no filho direito, continuando a percorrer a Árvore.
		}
	}
	else						// Se o caractere for "0":
	{
		if (i+1==code.size[c])	// Se o código ainda não tiver chegado ao final:
		{
			T->esq = (nodeArvore*)malloc(sizeof(nodeArvore));		// Alocar espaço na Árvore Heap.
			*T->esq = x;											// Inserir nodeArvore.
		}
		else 
		{
			if (T->esq==NULL)	// Se o filho esquerdo for nulo,
			{														// Deve-se criar um node de conexão (sem conteúdo).
				T->esq = (nodeArvore*)malloc(sizeof(nodeArvore));	// Alocar um novo nodeArvore.
				T->esq->esq = T->esq->dir = NULL;					// E setar seus filhos como NULL.
			}
			createNode (T->esq, x, code, i+1, c);					// Mergulhar no filho esquerdo, continuando a percorrer a Árvore.
		}
	}
}

void inserir (heap *v, unsigned char c, codigo code) // Cria estrutura de um novo nodeArvore e a insere na Árvore Heap.
{
	nodeArvore *novoNode;								// Alocando novo nodeArvore.
	novoNode = (nodeArvore*)malloc(sizeof(nodeArvore));
	novoNode->caractere = c;							// Associando nodeArvore ao seu caractere correspondente.
	novoNode->esq = novoNode->dir = NULL;				// Resetando os seus filhos como sendo NULL.
	createNode (Vet[1].info, *novoNode, code, 0, c);	// Chama função que insere o nodeArvore na Árvore Heap.
}

/*---------------------------------------------------------------------------------------*/

void main ()
{
	/*------------------ Declaração das variáveis do problema -------------------*/

	int k;					// Variáveis auxiliares.
	char lixo[max];
	unsigned char c, bol;	
	nodeArvore *T;			// Ponteiro auxiliar para nodeArvore.
	codigo code;			// Estrutura do código de Huffman.
	Bit bit;				// Inicializando "vetor de bits" bit.
	inicBit(&bit);
	heap vetor;				// Inicializando heap vetor.
	inicArvore (&vetor);
	FILE *entrada = fopen ("codificado.bin","rb");	// Arquivo de entrada.
	if (!entrada) exit(1);	// Caso não haja arquivo de entrada, finalizar o programa.
	FILE *saida = fopen ("texto.txt","w");	// Arquivo de saída.

	/*---------------------- Construindo a Árvore Heap --------------------------*/

	fscanf (entrada, "%d", &k);					// k guarda o número de caracteres codificadas.
	for (int i=0; i<k; i++)						// Para cada caractere codificado:
	{
		fgets (lixo, max, entrada);				// Pula a leitura para a próxima linha.
		fscanf (entrada, "%c", &c);				// Lê a letra e o tamanho do código a ser lido.
		fscanf (entrada, "%d", &code.size[c]);
		fgets (lixo, max, entrada);				// Pula a leitura para a próxima linha.
		for (int i=0; i<code.size[c]; i++)		// Leitura letra a letra do código de binário:
		{
			fscanf (entrada, "%c", &bol);
			code.code[c][i] = (bol=='1');		// Atribuição da codificação da letra.
		}
		inserir (&vetor, c, code);				// Insere letra lida e seu código na Árvore Heap.
	}

	/*------------------ Decodificando o arquivo compactado -------------------*/

	fscanf (entrada, "%d", &k);		// Leitura do número de bits do arquivo codificado.
	fgets (lixo, max, entrada);		// Pula a leitura para a próxima linha.
	T=vetor.elementos[1].info;		// O ponteiro T aponta para a raiz da Árvore Heap.
	while (bit.n<=k)				// Enquanto o arquivo codificado não tiver acabado:
	{													// Percorrer a árvore para decodificar o conteúdo codificado.
		if (T->esq==NULL && T->dir==NULL)				// Ao chegar a uma folha,
		{
			fprintf (saida, "%c", T->caractere);		// Imprimir o conteúdo do caractere do nodeArvore.
			T=vetor.elementos[1].info;					// Voltar o ponteiro para a raiz da árvore.
		}
		if (bit.n%8==0)									// Ao acabar a leitura de um "vetor de bits", 
			fscanf (entrada, "%c", &bit.v);				// ler um novo caractere "vetor de bits.
		c = bit.v;										// "c" é variável auxiliar que recebe o "vetor de bits".
		for (int i=8; i>7-bit.n%8; i--)					// Mecanismo para ver se o próximo bit do "vetor de bits"
			if (c>=pow(2,(float)(i)))					// é um bit "1" ou um bit "0".
				c-=pow(2,(float)(i));
		if (c>=pow(2,(float)(7-bit.n++%8))) T=T->dir;	// Se o bit for "1", continuar percorrendo a Árvore pelo filho direito.
		else T=T->esq;									// Se o bit for "0", continuar percorrendo a Árvore pelo filho esquerdo.
	}

	/*---------------------------------- Fim ------------------------------------*/
	fclose (entrada);
	fclose (saida);
}