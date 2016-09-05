/*********************************************/
/*  Felipe Tuyama de Faria Barbosa - Turma 1 */
/*  Exercício 1                          	 */
/*  Programa compilado com Borland C++ 5.02  */
/*********************************************/
#include <stdio.h>
#include <stdlib.h>
typedef int *vetor;
typedef vetor *matriz;

matriz alocarMatriz (int n)
{	// Aloca Matriz de ordem n.
	matriz M;
	M = (matriz)malloc(n*sizeof(vetor));
	for (int i=0; i<n; i++)
		M[i] = (vetor)malloc(sizeof(int));
	return M;
}

void lerMatriz (matriz M, int n, FILE *entrada)
{	// Lê Matriz de ordem n.
	for (int i=0; i<n; i++)
		for (int j=0; j<n; j++)
			fscanf (entrada, "%d", &M[i][j]);
}

void escreverMatriz (matriz M, int n, FILE *saida)
{	// Escreve Matriz de ordem n.
	for (int i=0; i<n; i++)
	{
		for (int j=0; j<n; j++)
			fprintf (saida, "%d ", M[i][j]);
		fprintf (saida, "\n");
	}
	fprintf (saida, "\n");
}

void desalocarMatriz (matriz M, int n)
{	// Desaloca Matriz de ordem n.
	for (int i=0; i>n; i++)
		free(M[i]);
	free (M);
}

void copiaMatriz (matriz M, matriz N, int n, int m, int Size)
{	// Copia uma Matriz M para a Matriz N, elemento a elemento.
	if (m!=1) copiaMatriz (M,N,n,m-1,Size);
	if (n!=1)  copiaMatriz (M,N,n-1,Size,Size);
	N[n-1][m-1] = M[n-1][m-1];
}

int retornarMaiorElemento (matriz M, int n)
{	// Retorna o maior elemento de uma Matriz.
	static int maior, i = 0, j = 0, times = 0;
	if (times++ < n*n)   // Chama a si mesma n^2 vezes (uma vez para cada elemento).
		maior = retornarMaiorElemento (M,n);
	else return M[0][0]; // O primeiro retorno é o elemento M[0][0] da Matriz.
	if (++i>n)	 	// Percorre os elementos da coluna da matriz.
		if (++j<n)  // Se não tiver percorrido toda a matriz ainda,
			i=1;	// Começa a percorrer uma nova coluna.
	// Compara cada elemento da Matriz com o maior até então, retornando o maior.
	return (M[i-1][j] > maior) ? M[i-1][j] : maior;
}

void Transpor (matriz M, matriz N, int i, int j)
{	// Recursiva que transpõe uma Matriz.
	static int Size = i; // A recursão gera um Loop em i e j:
	if (j!=1) Transpor (M,N,i,j-1); // Acessando cada elemento de M
	else if (i!=1) Transpor (M,N,i-1,Size);
	N[i-1][j-1] = M[j-1][i-1];  // E transpondo-o para N.
}

matriz criarTransposta (matriz M, int n)
{	// Transpõe uma Matriz.
	matriz N = alocarMatriz(n); // Aloca Matriz N.
	Transpor (M,N,n,n); 	    // Transpões M para N.
	copiaMatriz (N,M,n,n,n);	// Copia N para M.
	desalocarMatriz(N,n);		// Desaloca N.
	return M;					// Retorna M.
}

int produtoLinhaColuna (matriz M1, matriz M2, int l, int c, int n)
{	// E finalmente, uma última recursão calcula cada elemento de M3.
	int soma = 0;
	if (n!=1) soma=produtoLinhaColuna (M1,M2,l,c,n-1); // Loop do somatório.
	soma+=M1[l][n-1]*M2[n-1][c]; // Cálculo de cada elemento do somatório.
	return soma;
}

vetor obterLinha (matriz M1, matriz M2, matriz M3, int l, int c, int n)
{	// Depois abre-se um Loop para cada elemento da linha.
	if (c!=1) M3[l]=obterLinha (M1,M2,M3,l,c-1,n);  // Percorre as Linhas.
	M3[l][c-1]=produtoLinhaColuna (M1,M2,l,c-1,n);	// Cada elemento recebe seu conteúdo.
	return M3[l];
}

matriz obterMatriz (matriz M1, matriz M2, matriz M3, int l, int n)
{	// Primeiramente, abre-se um Loop para as linhas da matriz M3.
	if (l!=1) M3 = obterMatriz (M1,M2,M3,l-1,n); // Percorre a Matriz.
	M3[l-1] = obterLinha (M1,M2,M3,l-1,n,n);     // Cada Linha recebe seu conteúdo.
	return M3;
}

matriz calcularProduto (matriz M1, matriz M2, int n)
{	// Calcula o produto de duas matrizes quadradas.
	matriz M3 = alocarMatriz (n);    // Aloca M3.
	M3 = obterMatriz (M1,M2,M3,n,n); // M3 recebe o produto
	copiaMatriz (M3,M1,n,n,n);		 // M3 é copiada para M1.
	desalocarMatriz (M3,n);			 // M3 é desalocada.
	return M1;						 // Retorna M1.
}

matriz MenorComplementar (matriz X, matriz M, int n, int coluna)
{	// Criação de uma Matriz menor complementar.
	for (int i=0; i<n-1; i++)
		for (int j=0; j<n-1; j++)
			if (j<coluna) X[i][j]=M[i+1][j];
			else X[i][j]=M[i+1][j+1];
	return X;
}

int calcularDeterminante (matriz M, int n)
{	// Calcula o determinante de uma Matriz.
	int sign, det=0;
	if (n==1) return M[0][0]; // Caso trivial do determinante.
	for (int f=0; f<n; f++)   // Aplicação de Laplace na matriz.
	{
		matriz X = alocarMatriz (n-1); 	 // Aloca a matriz X.
		X = MenorComplementar (X,M,n,f); // X é um menor complementar.
		sign = (f%2==0) ? 1: -1;		 // Cálculo do sinal no somatório.
		det+=sign*M[0][f]*calcularDeterminante(X,n-1); // Cálculo do det.
		desalocarMatriz(X,n);  // Cada matriz X é desalocada após o
	}						   // cálculo de seu determinante.
	return det;
}

int main ()
{
	matriz M, N;
	int Noperacoes, Operacao, n;
	FILE *entrada, *saida;
	entrada = fopen ("entrada.txt","r");
	saida = fopen ("felipetuyama1.txt","w");
	fscanf (entrada, "%d", &Noperacoes); // Ler o número de tarefas.
	for (int i=0; i<Noperacoes; i++) // Loop até realizar todas as tarefas.
	{
		fscanf (entrada, "%d %d", &Operacao, &n); // Ler a operação e ordem da matriz
		M = alocarMatriz (n); 		// Alocar matriz.
		lerMatriz (M, n, entrada); 	// Ler matriz.
		switch (Operacao)			// Realizar tarefa:
		{
		case 1: fprintf (saida, "%d\n\n", retornarMaiorElemento (M, n)); break;
		case 2: escreverMatriz (criarTransposta(M,n), n, saida); break;
		case 3:
			N = alocarMatriz (n);      // Alocar a matriz multiplicativa.
			lerMatriz (N, n, entrada); // Ler a matriz multiplicativa.
			escreverMatriz (calcularProduto(M,N,n), n, saida);
			desalocarMatriz (N, n);
			break;
		case 4: fprintf (saida, "%d\n\n", calcularDeterminante (M,n)); break;
		}
		desalocarMatriz (M, n);   // Desalocar a matriz após término da tarefa.
	}							// Continuação do Loop.
	fclose (entrada);
	fclose (saida);
	return 0;
}