/*********************************************/
/*  Felipe Tuyama de Faria Barbosa - Turma 1 */
/*  Exercício 2                          	 */
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
// Função de dispersão associada a uma expressão.
int f (int N, string palavra)
{
	int sum = 0;
	for (int i = 0; palavra[i]!='\0'; i++)
		sum += palavra[i];
	return sum%N;
}
/*-----------------------------------------------------------------------------------------------*/
// Função que consulta uma expressão (tarefa 2).
void ConsultarExpressao (FILE *saida, dicionario V, string expr)
{
	nodeExpressao *p;
	nodeSignificado *q;
	p = V.lista[f(V.N, expr)]; // Acessando lista de expressões.
	if (p!=NULL)			   // Se a lista é não vazia:
	{
		while (p->prox!=NULL && strcmp(expr,p->expressao)!=0) // Percorrer expressões checando
			p=p->prox;										  // se a expressão consultada existe.
		if (strcmp(expr,p->expressao)==0)					  // Se a expressão existir,
			for (q = p->listaSignificado; q!=NULL; q=q->prox) // percorrer a lista de significados
				fprintf (saida, "%s\n", q->significado);	  // escrevendo-os no arquivo de saída.
		else fprintf (saida, "nada consta\n");
	}
	else fprintf (saida, "nada consta\n");
	fprintf (saida, "\n");
}
/*-----------------------------------------------------------------------------------------------*/
// Função usada para ler expressão/significado de uma string.
void LerQuebrado (FILE *arqEntrada, string *expr, string *signif)
{
	char *pch, aux[101];
	fgets(aux,101,arqEntrada); // "aux" recebe a linha lida.
	aux[strlen(aux)-1]='\0';
	pch = strtok(aux,"|");     // A string é quebrada em "|".
	strcpy(*expr,pch);         // "expr" recebe a primeira parte.
	pch = strtok(NULL,"|");
	strcpy(*signif,pch);	   // "signif" recebe a segunda.
}
/*-----------------------------------------------------------------------------------------------*/
// Função que insere um novo significado (tarefa 3).
void InserirSignificado (dicionario *V, string expr, string signif)
{
	nodeExpressao *p, *NovaExpressao;
	nodeSignificado *q, *NovoSignificado;
	NovaExpressao = (nodeExpressao*)malloc(sizeof(nodeExpressao));
	NovoSignificado = (nodeSignificado*)malloc(sizeof(nodeSignificado));
	strcpy (NovaExpressao->expressao, expr);          // Registrando uma NovaExpressao.
	strcpy (NovoSignificado->significado, signif);    // Registrando um NovoSignificado.
	p = V->lista[f(V->N,expr)];                       // Acessando a lista de expressões.
	if (p!=NULL)				                      // Se a lista for não vazia:
	{
		while (strcmp(expr,p->expressao)!=0 && p->prox!=NULL) // Procurar a expressão na lista.
			p = p->prox;
		if (strcmp(expr,p->expressao)==0)	// Se a expressão for encontrada:
		{
			free (NovaExpressao);		// Se a expressão já existir, liberar memória.
			q = p->listaSignificado;    // Checar agora se o significado já existe.
			while (strcmp(signif,q->significado)!=0 && q->prox!=NULL) // Percorrendo a lista de significados
				q = q->prox;										  // à procura do significado.
			if (strcmp(signif,q->significado)!=0) // Se o significado ainda não existir:
			{
				NovoSignificado->prox = p->listaSignificado; // Inseri-lo no início da lista.
				p->listaSignificado = NovoSignificado;
			}
			else free (NovoSignificado); // Se o significado já existir, liberar memória.
		}
		else // Se a expressão ainda não existir:
		{
			NovaExpressao->listaSignificado = NovoSignificado; // Encaixar NovaExpressão e NovoSignificado.
			NovaExpressao->prox = V->lista[f(V->N,expr)];	   // Colocar NovaExpressão no início da fila.
			V->lista[f(V->N,expr)] = NovaExpressao;            // Apontando para o ex-primeiro elemento da fila.
			NovoSignificado->prox = NULL;                      // O Significado é único, apontando para NULL.
		}
	}
	else // Se a lista de expressões estiver vazia:
	{
		NovaExpressao->listaSignificado = NovoSignificado; // Encaixar NovaExpressão e NovoSignificado.
		V->lista[f(V->N,expr)] = NovaExpressao;            // Colocar NovaExpressão no início da fila.
		NovaExpressao->prox = NULL;                        // NovaExpressão é única, apontando para NULL.
		NovoSignificado->prox = NULL;                      // O Significado é único, apontando para NULL.
	}
}
/*-----------------------------------------------------------------------------------------------*/
// Função que elimina um significado (tarefa 4)
void EliminarSignificado (dicionario *V, string expr, string signif)
{
	nodeExpressao *p, *l;
	nodeSignificado *q, *k;
	l = p = V->lista[f(V->N, expr)];  // Acessando a lista de expressões.
	if (p!=NULL)                      // Se a lista de expressões não for vazia:
	{
		while (p->prox!=NULL && strcmp(expr,p->expressao)!=0) // Percorrer a lista de expressões,
		{
			l = p;      // procurando a expressão e guardando
			p=p->prox;  // a posição da expressão anterior a ela.
		}
		if (strcmp(expr,p->expressao)==0) // Se a expressão for encontrada,
		{
			k = q = p->listaSignificado;  // Percorrer a lista de significados,
			while (q!=NULL && strcmp(signif,q->significado)!=0)
			{
				k = q;        // procurando o significado e guardando
				q = q->prox;  // a posição do significado anterior a ele.
			}
			if (q!=NULL) // Se o significado for encontrado:
			{
				if (k!=q) k->prox = q->prox;        // Se o significado não for o primeiro da lista.
				else p->listaSignificado = q->prox; // Se ele for o primeiro.
				free (q);                           // Eliminar o significado.
				if (p->listaSignificado==NULL)      // Se não houver mais significados para a expressão:
				{
					if (l!=p) l->prox = p->prox;            // Se a expressão não for a primeira da lista.
					else V->lista[f(V->N, expr)] = p->prox; // Se ela for a primeira.
					free (p);                               // Eliminar a Expressão (sem significados).
				}
			}
		}
	}
}
/*-----------------------------------------------------------------------------------------------*/
// Função que elimina uma expressão (tarefa 5).
void EliminarExpressao (dicionario *V, string expr)
{
	nodeExpressao *p, *l;
	nodeSignificado *q, *k;
	l = p = V->lista[f(V->N, expr)];  // Acessando a lista de expressões.
	if (p!=NULL)                      // Se a lista de expressões não for vazia:
	{
		while (p->prox!=NULL && strcmp(expr,p->expressao)!=0) // Percorrer a lista de expressões,
		{
			l = p;     // procurando a expressão e guardando
			p=p->prox; // a posição da expressão anterior a ela.
		}
		if (strcmp(expr,p->expressao)==0) // Se a expressão for encontrada,
		{
			q = p->listaSignificado;
			while (q!=NULL) // Percorrer a lista de significados.
			{
				k = q;
				q = q->prox;
				free (k); // Eliminando todos os significados da expressão.
			}
		}
		if (l!=p) l->prox = p->prox;            // Se a expressão não for a primeira da lista.
		else V->lista[f(V->N, expr)] = p->prox; // Se ela for a primeira.
		free (p);                               // Por fim, eliminar a Expressão (já sem significados).
	}
}
/*-----------------------------------------------------------------------------------------------*/
// Função que gera uma base de dados (tarefa 6).
void GerarBaseDados (dicionario V)
{
	FILE *arqSaida = fopen("DicionITA.txt", "w");
	nodeExpressao *p;
	nodeSignificado *q;
	for (int i=0; i<V.N; i++) // Percorrendo o vetor principal do dicionário.
		for (p = V.lista[i]; p!=NULL; p=p->prox) // Percorrendo as expressões.
			for (q = p->listaSignificado; q!=NULL; q=q->prox) // Percorrendo os significados.
				fprintf (arqSaida, "%s|%s\n", p->expressao, q->significado); // Escrevendo expressão/significado.
	fclose (arqSaida);
}
/*-----------------------------------------------------------------------------------------------*/
// Função que carrega uma base de dados (tarefa 1).
void CarregarBaseDados (dicionario *V)
{
	string expr, signif;
	FILE *arqEntrada = fopen("DicionITA.txt", "r");
	V->lista = (nodeExpressao**)malloc(V->N*sizeof(nodeExpressao)); 
	for (int i=0; i<V->N; i++)  V->lista[i] = NULL; // Inicializando dicionário.
	while (!feof(arqEntrada))  // Enquanto não terminar a leitura do arquivo :
	{
		LerQuebrado (arqEntrada, &expr, &signif); // Ler expressão/significado.
		InserirSignificado (V, expr, signif); // Inserir novo significado no dicionário.
	}
	fclose (arqEntrada);
}
/*-----------------------------------------------------------------------------------------------*/
int main ()
{
	dicionario V;
	bool inicio = false;    // Booleana indicando a inicialização da base de dados.
	int Noperacoes, tarefa; // Número de operações a serem feitas e o número da tarefa.
	string expr, signif;
	FILE *entrada = fopen ("entrada.txt","r"); 
	FILE *saida = fopen ("felipetuyama2.txt","w");
	fscanf (entrada, "%d %d", &V.N, &Noperacoes); // Lê o tamanho do vetor e o número de operações.
	for (int i=0; i<Noperacoes; i++)              // Loop para realizar as tarefas.
	{
		fscanf (entrada, "%d", &tarefa); fgets(expr,50,entrada); // Lê o número da tarefa e pula uma linha.
		if (tarefa == 2 || tarefa == 5) {fgets(expr,50,entrada); expr[strlen(expr)-1]='\0';}  // Lê uma expressão (tarefas 2, 5).
		if (tarefa == 3 || tarefa == 4) LerQuebrado (entrada, &expr, &signif); // Lê uma expressão e um significado (tarefas 3, 4).
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