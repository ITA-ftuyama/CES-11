/************************************************************/
/*  Felipe Tuyama de Faria Barbosa - Turma 1                */
/*  Exercício 4 - Código (Compactar.cpp e Descompactar.cpp) */
/*  Compilado com Microsoft Visual C++ 2010 Express         */
/************************************************************/
#define N 8             // Número total de bits utilizados (2^8 = 256)
#define max 256         // Número total de caracteres existentes.
#define fesq info->esq  // Algumas simplificações de notação:
#define fdir info->dir 
#define frequencia Hz
#define Vet v->elementos
#define chr info->caractere
/*----------------------- Implementação do Heap -----------------------------------------*/
struct nodeArvore 
{
	unsigned char caractere;    //caractere que queremos codificar
	nodeArvore * esq;  //filho esquerdo
	nodeArvore * dir;  //filho direito
};
struct nodeHeap 
{
	int frequencia;    //frequencia do caractere
	nodeArvore * info; //informação relacionada
};
struct heap 
{
	nodeHeap elementos[max+1]; //começa da posição 1
	int n; //tamanho do heap
};
/*------------------------ Implementação do Código de Huffman ---------------------------*/
struct codigo 
{
	bool code[max][N]; // Vetor que armazena o código binário de cada caractere.
	int size[max];     // Guarda o tamanho do código binário de cada caractere.
};
/*----------------- Implementação do Caractere a ser manipulado bit a bit ---------------*/
struct Bit	// É uma espécie de "vetor de bits", da seguinte forma:
{
	unsigned char v; // É um char que será manipulado bit a bit a fim de realizar a compactação.
	int n;           // Indica quantos bits do char "v" já foram utilizados.
};
void inicBit (Bit *b) // Inicializa a estrutura Bit para o seu devido uso.
{
	b->n=0;    // Inicializa o número de bits utilizados do char como 0.
	b->v='\0'; // Inicializa a sua codificação como \0 = 0000.0000
}