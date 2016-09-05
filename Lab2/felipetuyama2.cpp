/*********************************************/
/*  Felipe Tuyama de Faria Barbosa - Turma 1 */
/*  Exerc�cio 2                          	 */
/*  Programa compilado com Borland C++ 5.02  */
/*********************************************/
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
typedef char string[50];
struct nodeSignificado 
{ 
	string significado; 
	nodeSignificado *prox; 
};
struct nodeExpressao 
{
	string expressao;	
	nodeSignificado *listaSignificado; 
	nodeExpressao *prox; 
};
struct dicionario 
{
	nodeExpressao **lista;
	int N;
};
/*-----------------------------------------------------------------------------------------------*/
// Fun��o de dispers�o associada a uma express�o.
int f (int N, string palavra)
{
	int sum = 0;
	for (int i = 0; palavra[i]!='\0'; i++)
		sum += palavra[i];
	return sum%N;
}
/*-----------------------------------------------------------------------------------------------*/
// Fun��o que consulta uma express�o (tarefa 2).
void ConsultarExpressao (FILE *saida, dicionario V, string expr)
{
	nodeExpressao *p;
	nodeSignificado *q;
	p = V.lista[f(V.N, expr)]; // Acessando lista de express�es.
	if (p!=NULL)			   // Se a lista � n�o vazia:
	{
		while (p->prox!=NULL && strcmp(expr,p->expressao)!=0) // Percorrer express�es checando
			p=p->prox;										  // se a express�o consultada existe.
		if (strcmp(expr,p->expressao)==0)					  // Se a express�o existir,
			for (q = p->listaSignificado; q!=NULL; q=q->prox) // percorrer a lista de significados
				fprintf (saida, "%s\n", q->significado);	  // escrevendo-os no arquivo de sa�da.
		else fprintf (saida, "nada consta\n");
	}
	else fprintf (saida, "nada consta\n");
	fprintf (saida, "\n");
}
/*-----------------------------------------------------------------------------------------------*/
// Fun��o usada para ler express�o/significado de uma string.
void LerQuebrado (FILE *arqEntrada, string *expr, string *signif)
{
	char *pch, aux[101];
	fgets(aux,101,arqEntrada); // "aux" recebe a linha lida.
	aux[strlen(aux)-1]='\0';
	pch = strtok(aux,"|");     // A string � quebrada em "|".
	strcpy(*expr,pch);         // "expr" recebe a primeira parte.
	pch = strtok(NULL,"|");
	strcpy(*signif,pch);	   // "signif" recebe a segunda.
}
/*-----------------------------------------------------------------------------------------------*/
// Fun��o que insere um novo significado (tarefa 3).
void InserirSignificado (dicionario *V, string expr, string signif)
{
	nodeExpressao *p, *NovaExpressao;
	nodeSignificado *q, *NovoSignificado;
	NovaExpressao = (nodeExpressao*)malloc(sizeof(nodeExpressao));
	NovoSignificado = (nodeSignificado*)malloc(sizeof(nodeSignificado));
	strcpy (NovaExpressao->expressao, expr);          // Registrando uma NovaExpressao.
	strcpy (NovoSignificado->significado, signif);    // Registrando um NovoSignificado.
	p = V->lista[f(V->N,expr)];                       // Acessando a lista de express�es.
	if (p!=NULL)				                      // Se a lista for n�o vazia:
	{
		while (strcmp(expr,p->expressao)!=0 && p->prox!=NULL) // Procurar a express�o na lista.
			p = p->prox;
		if (strcmp(expr,p->expressao)==0)	// Se a express�o for encontrada:
		{
			free (NovaExpressao);		// Se a express�o j� existir, liberar mem�ria.
			q = p->listaSignificado;    // Checar agora se o significado j� existe.
			while (strcmp(signif,q->significado)!=0 && q->prox!=NULL) // Percorrendo a lista de significados
				q = q->prox;										  // � procura do significado.
			if (strcmp(signif,q->significado)!=0) // Se o significado ainda n�o existir:
			{
				NovoSignificado->prox = p->listaSignificado; // Inseri-lo no in�cio da lista.
				p->listaSignificado = NovoSignificado;
			}
			else free (NovoSignificado); // Se o significado j� existir, liberar mem�ria.
		}
		else // Se a express�o ainda n�o existir:
		{
			NovaExpressao->listaSignificado = NovoSignificado; // Encaixar NovaExpress�o e NovoSignificado.
			NovaExpressao->prox = V->lista[f(V->N,expr)];	   // Colocar NovaExpress�o no in�cio da fila.
			V->lista[f(V->N,expr)] = NovaExpressao;            // Apontando para o ex-primeiro elemento da fila.
			NovoSignificado->prox = NULL;                      // O Significado � �nico, apontando para NULL.
		}
	}
	else // Se a lista de express�es estiver vazia:
	{
		NovaExpressao->listaSignificado = NovoSignificado; // Encaixar NovaExpress�o e NovoSignificado.
		V->lista[f(V->N,expr)] = NovaExpressao;            // Colocar NovaExpress�o no in�cio da fila.
		NovaExpressao->prox = NULL;                        // NovaExpress�o � �nica, apontando para NULL.
		NovoSignificado->prox = NULL;                      // O Significado � �nico, apontando para NULL.
	}
}
/*-----------------------------------------------------------------------------------------------*/
// Fun��o que elimina um significado (tarefa 4)
void EliminarSignificado (dicionario *V, string expr, string signif)
{
	nodeExpressao *p, *l;
	nodeSignificado *q, *k;
	l = p = V->lista[f(V->N, expr)];  // Acessando a lista de express�es.
	if (p!=NULL)                      // Se a lista de express�es n�o for vazia:
	{
		while (p->prox!=NULL && strcmp(expr,p->expressao)!=0) // Percorrer a lista de express�es,
		{
			l = p;      // procurando a express�o e guardando
			p=p->prox;  // a posi��o da express�o anterior a ela.
		}
		if (strcmp(expr,p->expressao)==0) // Se a express�o for encontrada,
		{
			k = q = p->listaSignificado;  // Percorrer a lista de significados,
			while (q!=NULL && strcmp(signif,q->significado)!=0)
			{
				k = q;        // procurando o significado e guardando
				q = q->prox;  // a posi��o do significado anterior a ele.
			}
			if (q!=NULL) // Se o significado for encontrado:
			{
				if (k!=q) k->prox = q->prox;        // Se o significado n�o for o primeiro da lista.
				else p->listaSignificado = q->prox; // Se ele for o primeiro.
				free (q);                           // Eliminar o significado.
				if (p->listaSignificado==NULL)      // Se n�o houver mais significados para a express�o:
				{
					if (l!=p) l->prox = p->prox;            // Se a express�o n�o for a primeira da lista.
					else V->lista[f(V->N, expr)] = p->prox; // Se ela for a primeira.
					free (p);                               // Eliminar a Express�o (sem significados).
				}
			}
		}
	}
}
/*-----------------------------------------------------------------------------------------------*/
// Fun��o que elimina uma express�o (tarefa 5).
void EliminarExpressao (dicionario *V, string expr)
{
	nodeExpressao *p, *l;
	nodeSignificado *q, *k;
	l = p = V->lista[f(V->N, expr)];  // Acessando a lista de express�es.
	if (p!=NULL)                      // Se a lista de express�es n�o for vazia:
	{
		while (p->prox!=NULL && strcmp(expr,p->expressao)!=0) // Percorrer a lista de express�es,
		{
			l = p;     // procurando a express�o e guardando
			p=p->prox; // a posi��o da express�o anterior a ela.
		}
		if (strcmp(expr,p->expressao)==0) // Se a express�o for encontrada,
		{
			q = p->listaSignificado;
			while (q!=NULL) // Percorrer a lista de significados.
			{
				k = q;
				q = q->prox;
				free (k); // Eliminando todos os significados da express�o.
			}
		}
		if (l!=p) l->prox = p->prox;            // Se a express�o n�o for a primeira da lista.
		else V->lista[f(V->N, expr)] = p->prox; // Se ela for a primeira.
		free (p);                               // Por fim, eliminar a Express�o (j� sem significados).
	}
}
/*-----------------------------------------------------------------------------------------------*/
// Fun��o que gera uma base de dados (tarefa 6).
void GerarBaseDados (dicionario V)
{
	FILE *arqSaida = fopen("DicionITA.txt", "w");
	nodeExpressao *p;
	nodeSignificado *q;
	for (int i=0; i<V.N; i++) // Percorrendo o vetor principal do dicion�rio.
		for (p = V.lista[i]; p!=NULL; p=p->prox) // Percorrendo as express�es.
			for (q = p->listaSignificado; q!=NULL; q=q->prox) // Percorrendo os significados.
				fprintf (arqSaida, "%s|%s\n", p->expressao, q->significado); // Escrevendo express�o/significado.
	fclose (arqSaida);
}
/*-----------------------------------------------------------------------------------------------*/
// Fun��o que carrega uma base de dados (tarefa 1).
void CarregarBaseDados (dicionario *V)
{
	string expr, signif;
	FILE *arqEntrada = fopen("DicionITA.txt", "r");
	V->lista = (nodeExpressao**)malloc(V->N*sizeof(nodeExpressao)); 
	for (int i=0; i<V->N; i++)  V->lista[i] = NULL; // Inicializando dicion�rio.
	while (!feof(arqEntrada))  // Enquanto n�o terminar a leitura do arquivo :
	{
		LerQuebrado (arqEntrada, &expr, &signif); // Ler express�o/significado.
		InserirSignificado (V, expr, signif); // Inserir novo significado no dicion�rio.
	}
	fclose (arqEntrada);
}
/*-----------------------------------------------------------------------------------------------*/
int main ()
{
	dicionario V;
	bool inicio = false;    // Booleana indicando a inicializa��o da base de dados.
	int Noperacoes, tarefa; // N�mero de opera��es a serem feitas e o n�mero da tarefa.
	string expr, signif;
	FILE *entrada = fopen ("entrada.txt","r"); 
	FILE *saida = fopen ("felipetuyama2.txt","w");
	fscanf (entrada, "%d %d", &V.N, &Noperacoes); // L� o tamanho do vetor e o n�mero de opera��es.
	for (int i=0; i<Noperacoes; i++)              // Loop para realizar as tarefas.
	{
		fscanf (entrada, "%d", &tarefa); fgets(expr,50,entrada); // L� o n�mero da tarefa e pula uma linha.
		if (tarefa == 2 || tarefa == 5) {fgets(expr,50,entrada); expr[strlen(expr)-1]='\0';}  // L� uma express�o (tarefas 2, 5).
		if (tarefa == 3 || tarefa == 4) LerQuebrado (entrada, &expr, &signif); // L� uma express�o e um significado (tarefas 3, 4).
		if (inicio || tarefa == 1) // Realiza as tarefas somente depois de inicializada a base de dados.
			switch (tarefa) // Switch para as diversas tarefas do programa.
			{
			case 1: CarregarBaseDados (&V); inicio = true; break;
			case 2: ConsultarExpressao (saida, V, expr); break;
			case 3: InserirSignificado (&V, expr, signif); break;
			case 4: EliminarSignificado (&V, expr, signif); break;
			case 5: EliminarExpressao (&V, expr); break;
			case 6: GerarBaseDados (V); break;
			}
	}
	fclose (entrada);
	fclose (saida);
	return 0;
}