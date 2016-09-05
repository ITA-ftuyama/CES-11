/****************************************************/
/*  Felipe Tuyama de Faria Barbosa - Turma 1        */
/*  Exercício 5 - Grafos de Redes Rodoviárias       */
/*  Compilado com Microsoft Visual C++ 2010 Express */
/****************************************************/
#include <stdio.h>
#include <stdlib.h>
/*------------------- Implementação do Grafo e suas funções  -----------------------*/
struct CelAdj {
	int vert, comprimento;
	bool corte;
	CelAdj *prox;
};
struct CelVert {
	int expl, d, pred;
	char cidade[30];
	CelAdj *listaAdj;
};
struct grafo {
	int nvert, nComp;
	CelVert *vertices;
};
void inicGrafo (grafo *G) // Aloca e inicializa as variáveis de um novo Grafo
{
	G->vertices=(CelVert*)malloc((G->nvert+1)*sizeof(CelVert));	// Alocar N+1 vértices (desconsiderando posição 0)
	for (int i=1; i<=G->nvert; i++)			// Para todos os vértices do grafo:
	{
		G->vertices[i].listaAdj = NULL;		// O grafo começa sem nenhuma conexão
		G->vertices[i].d = -1;				// Em que -1 representa distância infinita
		G->vertices[i].expl = 0;			// Número de explorações zerados
		G->vertices[i].pred = 1;			// O predecessor de cada vértice começa como "1"
	}
}
void addAdj (grafo *G, CelAdj *p, int orig) // Função que adiciona uma nova aresta
{
	CelAdj *q, *r;
	p->prox = NULL;

	if (G->vertices[orig].listaAdj == NULL) 				// Se a lista de adjacência for vazia,
		G->vertices[orig].listaAdj = p;						// Apenas adicionar a nova aresta à lista
	else if (p->vert < G->vertices[orig].listaAdj->vert)	// Se o elemento for inserido na primeira posição
	{
		p->prox = G->vertices[orig].listaAdj;				// Seu campo "prox" aponta para o próximo elemento
		G->vertices[orig].listaAdj = p;						// O ponteiro do início da lista aponta para o elemento
	}
	else 													// Caso contrário,
	{
		q = r = G->vertices[orig].listaAdj;					// Deve-se procurar a posição em que a aresta deve ser
		while (r!=NULL && p->vert > r->vert)				// inserida, sempre guardando a posição anterior à
		{													// posição atual de busca
			q = r;											// "q" guarda a posição anterior de busca
			r = r->prox;									// "r" percorre a lista de arestas
		}													// Depois de encontrado:
		q->prox = p;										// O "prox" da aresta anterior se torna a aresta a ser inserida
		p->prox = r;										// O "prox" da aresta a ser inserida aponta para a primeira
	}														// aresta cujo número de vértice é maior que o seu, conservando
}															// a ordem crescente da lista
/*-------------------------------- Mínima Distância  -------------------------------*/
void Dijkstra (grafo *G) // Calcula a menor distância e o menor percurso de todos os vértices ao vértice 1
{
	int min;														// Toma a menor distância de um vértice ainda não explorado
	G->vertices[1].d = 0;											// A distância do vértice 1 a ele mesmo é nula
	for (int i=1; i<=G->nvert; i++)									// Para cada um dos vértices,
	{
		min = -1;													// A menor distância começa como infinita
		for (int j=1; j<=G->nvert; j++)
			if (G->vertices[j].expl==0 && G->vertices[j].d!=-1)		// Tomemos um vértice ainda não explorado, cujo d seja finito.
				if (min<0 || G->vertices[j].d < G->vertices[min].d)	// Se a distância dele for menor que a menor distância
					min = j;										// A nova distância se torna essa distância.
		if (min>0)													// Se a menor distância tomada for finita, continuamos o processo.
		{
			G->vertices[min].expl=1;								// O vértice é marcado como explorado
			for (CelAdj *p = G->vertices[min].listaAdj; p!=NULL; p=p->prox)	// Percorremos a sua lista de adjacência
				if (G->vertices[p->vert].d == -1 || G->vertices[p->vert].d > G->vertices[min].d+p->comprimento)
				{	// Se a distância desse vértice a um de seus vétices adjacentes for menor que a distância atual dele,
					G->vertices[p->vert].d = G->vertices[min].d+p->comprimento;	// Atualiza-se a sua nova distância mínima
					G->vertices[p->vert].pred = min;	// E esse vértice se torna o predecessor do seu vértice adjacente
				}
		}
	}
}
void imprimePercurso (grafo G, int pred, FILE* saida) // Imprime os percursos obtidos de Dijkstra
{
	if (pred==1) fprintf (saida, "1");							// Todos os percursos acabam em "1"
	else														// Enquanto não tiver acabado de percorrer,
	{
		imprimePercurso (G, G.vertices[pred].pred, saida);		// Chamar recursivamente os vértices predecessores
		fprintf (saida, "-%d", pred);							// Imprimindo, assim, a trajetória do percurso mínimo
	}
}
/*------------------------------- Arestas de Corte  --------------------------------*/
void DFSAC (grafo *G, int p, int *Nexplr) // Checa se determinada aresta é de corte
{
	G->vertices[p].expl = ++ (*Nexplr);							// Cada elemento recebe seu número de exploração
	G->vertices[p].d = G->vertices[p].expl;						// É calculado d[v] = mín{ expl[v], expl[x] }, 
	//onde x é um vértice que v (ou um de seus descendentes) atinge em T através de uma única aresta de retorno. 
	if (G->vertices[p].listaAdj != NULL)						// Analisemos as arestas desse elemento
		for (CelAdj *q = G->vertices[p].listaAdj; q!=NULL; q=q->prox)
			if (G->vertices[q->vert].expl==0)					// Se algum elemento de suas arestas não tiver sido explorado ainda
			{
				G->vertices[q->vert].pred = p;					// p se torna o seu pai
				DFSAC (G, q->vert, Nexplr);						// E então explora-se esse vértice
				if (G->vertices[p].d>G->vertices[q->vert].d)	// Depois de explorado, d assume o valor mínimo
					G->vertices[p].d=G->vertices[q->vert].d;	// dentre o d do filho e o do pai
				if (G->vertices[q->vert].d==G->vertices[q->vert].expl)
					q->corte = true;							// A aresta entre p e q->vert é de corte
			}
			else if (q->vert != G->vertices[p].pred)			// Se p não é o pai de q->vert
				if (G->vertices[p].d>G->vertices[q->vert].expl)	// d de p assume o mínimo entre
					G->vertices[p].d=G->vertices[q->vert].expl;	// o d do filho e o do pai
}
void Corte (grafo *G) // Verifica as arestas de cortes do Grafo
{
	int Nexplr = 0;					// O número de exploração começa no 0
	for (int i=1; i<=G->nvert; i++)	// Prepara o grafo para uma busca em profundidade
	{
		G->vertices[i].expl = 0;
		G->vertices[i].d = 0;
		G->vertices[i].pred = 0;
		for (CelAdj *q = G->vertices[i].listaAdj; q!=NULL; q=q->prox) // Inicia todas as arestas como não sendo de corte
			q->corte = false;
	}
	for (int i=1; i<=G->nvert; i++)	// Busca em profundidade procurando arestas de corte
		if (G->vertices[i].expl==0)
			DFSAC (G, i, &Nexplr);
}
/*----------------------------- Componentes Conexos  -------------------------------*/
void DFS (grafo *G, CelVert *celula)	// Exploração do grafo em profundidade
{										// Executa um DFS sem grandes mistérios
	celula->expl=1;
	celula->d = G->nComp;				// G->nComp guarda o número de componentes conexos do gráfico
	for (CelAdj *p = celula->listaAdj; p!=NULL; p=p->prox)
		if (G->vertices[p->vert].expl==0)
			DFS (G, &G->vertices[p->vert]);
}
void Conexos (grafo *G) // Encontra os componentes conexos do grafo
{
	G->nComp = 0;									// O número de componentes conexos começa como 0
	for (int i=1; i<=G->nvert; i++)					// Resetemos o número de exploração dos vértices
		G->vertices[i].d = G->vertices[i].expl = 0;
	for (int i=1; i<=G->nvert; i++)					// Início de uma busca em profundidade
	{
		if (G->vertices[i].expl==0)					// A cada vez que é aplicada uma exploração DFS
		{											// o número de componentes conexos é incrementado,
			G->nComp++;								// iniciando a busca em um novo componente conexo
			DFS(G, &G->vertices[i]);
		}
	}
}
/*----------------------------------------------------------------------------------*/
void main ()
{
	int m, orig,  aux;									// Declarando variáveis auxiliares
	FILE * entrada = fopen ("entrada.txt", "r");		// Arquivo de entrada
	if (!entrada) exit(1);								// Se o arquivo de entrada não existir, fechar o programa.
	FILE * saida = fopen ("saida.txt", "w");			// Arquivo de saida
	/*----------------------------   Leitura do Grafo  ---------------------------------*/
	grafo G;
	fscanf (entrada, "%d", &G.nvert);					// Leitura do número de vértices do grafo
	inicGrafo (&G);										// Alocando e inicializando o grafo
	fgets (G.vertices[0].cidade, 101, entrada);			// Pulando a leitura para a próxima linha
	for (int i=1; i<=G.nvert; i++)						// Ler o nome da cidade relacionada
		fgets (G.vertices[i].cidade, 101, entrada);		// a cada um dos vértices do grafo
	fscanf (entrada, "%d", &m);							// Lendo o número total de arestas do grafo
	for (int i=1; i<=m; i++)							// Realizando a leitura de cada uma das arestas
	{
		CelAdj *p =(CelAdj*)malloc(sizeof(CelAdj));		// Alocando duas células de arestas (simétricas)
		CelAdj *q =(CelAdj*)malloc(sizeof(CelAdj));		// (Uma aresta deve ser representada nas duas listas de adjacência)
		fscanf (entrada, "%d %d %d", &orig, &(p->vert), &(p->comprimento));  // Lendo as informações de uma dada aresta
		addAdj (&G, p, orig);							// Adicionando a primeira aresta
		q->vert = orig;									// A "origem" se torna o novo "destino"
		q->comprimento = p->comprimento;				// O comprimento da aresta é o mesmo
		addAdj (&G, q, p->vert);						// Adicionando a aresta simétrica
	}
	/*-------------------------------- Mínima Distância  -------------------------------*/
	fprintf (saida, "percursos");						// Determinemos os percursos mínimos ao vértice 1
	Dijkstra (&G);										// Usemos para isso a função Dijkstra
	for (int i=2; i<=G.nvert; i++)						// Para cada vértice do grafo (exceto o primeiro)
	{
		fprintf (saida, "\n1-%d", i);					// Imprimir origem e destino a ser analisado
		if (G.vertices[i].d==-1)						// Se a distância for negativa (=-1)
			fprintf (saida, "(inf)");					// É porque a distância entre os vértices é infinita
		else											// Caso a distância não seja infinita,
		{
			fprintf (saida, "(%d):", G.vertices[i].d);	// Imprimir a distância entre os vértices
			imprimePercurso (G, i, saida);				// Imprimir o percurso mínimo entre eles
		}
	}
	/*------------------------------- Arestas de Corte  --------------------------------*/
	fprintf (saida, "\narestas\n");						// Determinemos então as arestas de corte do grafo
	Corte (&G);											// Usemos para isso a função Corte
	for (int i=1; i<=G.nvert; i++)						// Percorrer então todas as arestas do grafo
		for (CelAdj *q = G.vertices[i].listaAdj; q!=NULL; q=q->prox)
			if (q->corte == true)						// Se uma dada aresta for de corte,
				fprintf (saida, "%d-%d\n", i, q->vert);	// Imprimí-la no arquivo de saída
	/*----------------------------- Componentes Conexos  -------------------------------*/
	fprintf (saida, "componentes\n");					// Determinemos agora os componentes conexos
	Conexos (&G);										// Usemos para tanto a função Conexos
	for (int i=1; i<=G.nComp; i++)						// Imprimamos componente a componente conexo do grafo
	{		
		m = 1;											
		while (m<=G.nvert && G.vertices[m].d!=i) m++;	// Procuremos pelo primeiro componente do conexo
		if (m<=G.nvert) fprintf (saida, "%d", m);		// Se encontrar, imprimir o primeiro componente
		if (m+1<=G.nvert)								// Se ainda for preciso checar mais vértices,
			for (m=m+1; m<=G.nvert; m++)				// Entrar em um Loop procurando os demais vértices
				if (G.vertices[m].d==i)					// que também pertencem ao conexo atual
					fprintf (saida, "-%d", m);			// Imprimindo os elementos de cada conexo na mesma linha
		fprintf (saida, "\n");							// Finalizada a busca de dado conexo, pular uma linha
	}
	fclose (entrada);	// Fechar arquivo de entrada
	fclose (saida);		// Fechar arquivo de saída
}