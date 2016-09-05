/************************************************************/
/*  Felipe Tuyama de Faria Barbosa - Turma 1                */
/*  Exerc�cio 4 - C�digo (Compactar.cpp e Descompactar.cpp) */
/*  Compilado com Microsoft Visual C++ 2010 Express         */
/************************************************************/
#define N 8             // N�mero total de bits utilizados (2^8 = 256)
#define max 256         // N�mero total de caracteres existentes.
#define fesq info->esq  // Algumas simplifica��es de nota��o:
#define fdir info->dir 
#define frequencia Hz
#define Vet v->elementos
#define chr info->caractere
/*----------------------- Implementa��o do Heap -----------------------------------------*/
struct nodeArvore 
{
	unsigned char caractere;    //caractere que queremos codificar
	nodeArvore * esq;  //filho esquerdo
	nodeArvore * dir;  //filho direito
};
struct nodeHeap 
{
	int frequencia;    //frequencia do caractere
	nodeArvore * info; //informa��o relacionada
};
struct heap 
{
	nodeHeap elementos[max+1]; //come�a da posi��o 1
	int n; //tamanho do heap
};
/*------------------------ Implementa��o do C�digo de Huffman ---------------------------*/
struct codigo 
{
	bool code[max][N]; // Vetor que armazena o c�digo bin�rio de cada caractere.
	int size[max];     // Guarda o tamanho do c�digo bin�rio de cada caractere.
};
/*----------------- Implementa��o do Caractere a ser manipulado bit a bit ---------------*/
struct Bit	// � uma esp�cie de "vetor de bits", da seguinte forma:
{
	unsigned char v; // � um char que ser� manipulado bit a bit a fim de realizar a compacta��o.
	int n;           // Indica quantos bits do char "v" j� foram utilizados.
};
void inicBit (Bit *b) // Inicializa a estrutura Bit para o seu devido uso.
{
	b->n=0;    // Inicializa o n�mero de bits utilizados do char como 0.
	b->v='\0'; // Inicializa a sua codifica��o como \0 = 0000.0000
}