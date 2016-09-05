/****************************/
/*       Maze Solver	    */
/*                          */
/*    By Tuyama             */
/****************************/
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace System;
#define Color Console::ForegroundColor = ConsoleColor::
#define gotoxy Console::SetCursorPosition
struct pto	
{
	int x, y;
};
struct quad
{
	int z, d, explr;
	pto ant;
};
class maze
{
public:
	quad Maze[100][100];
	int x, y;
	void imprime();
	void distancia();
	void ant();
	maze();
};
maze::maze()
{
	for (int i=0; i<100; i++)
		for (int j=0; j<100; j++)
		{
			this->Maze[i][j].z=0;
			this->Maze[i][j].d=-1;
			this->Maze[i][j].ant.x=0;
			this->Maze[i][j].ant.y=0;
			this->Maze[i][j].explr=0;
		}
}
void maze::imprime ()
{
	for (int i=1; i<=this->y; i++)
	{
		for (int j=1; j<=this->x; j++)
			if (this->Maze[j][i].z==1)
				printf ("X");
			else printf (" ");
		printf ("\n");
	}
}
void maze::ant ()
{
	for (int i=1; i<=this->y; i++)
	{
		for (int j=1; j<=this->x; j++)
			printf ("%d,%d ", Maze[j][i].ant.x, Maze[j][i].ant.y);
		printf ("\n");
	}
}
void maze::distancia ()
{
	printf ("\n\n\n::: Distancia:::\n\n");
	for (int i=1; i<=this->y; i++)
	{
		for (int j=1; j<=this->x; j++)
			if (this->Maze[j][i].d>0)
				printf ("%3d", Maze[j][i].d);
			else printf ("   ");
		printf ("\n");
	}
}
void Dijkstra (maze *H, int u, int v)
{
	pto min;
	for (int i=0; i<100; i++)
		for (int j=0; j<100; j++)
		{
			H->Maze[i][j].d=-1;
			H->Maze[i][j].ant.x=0;
			H->Maze[i][j].ant.y=0;
			H->Maze[i][j].explr=0;
		}
		H->Maze[u][v].d=0;
		for (int i=1; i<=H->x; i++)
			for (int j=1; j<=H->y; j++)
			{
				min.x = -1; min.y = -1;
				for (int a=1; a<=H->x; a++)
				{
					for (int b=1; b<=H->y; b++)
						if (H->Maze[a][b].z!=1 && H->Maze[a][b].explr==0 && H->Maze[a][b].d!=-1)
							if (min.x<0 || H->Maze[a][b].d < H->Maze[min.x][min.y].d)
							{
								min.x = a; min.y = b;
							}
				}
				if (min.x>0 && min.y >0)
				{
					H->Maze[min.x][min.y].explr=1;
					for (int c=-1; c<=1; c++)
						for (int d=-1; d<=1; d++)
							if (H->Maze[min.x+c][min.y+d].z!=1)
								if (H->Maze[min.x+c][min.y+d].d==-1 || H->Maze[min.x+c][min.y+d].d > 1+H->Maze[min.x][min.y].d)
								{
									H->Maze[min.x+c][min.y+d].d = 1+H->Maze[min.x][min.y].d;
									H->Maze[min.x+c][min.y+d].ant.x = min.x;
									H->Maze[min.x+c][min.y+d].ant.y = min.y;
								}
				}

			}
}
void path (maze *H, int u, int v, int x, int y)
{
	if (H->Maze[x][y].d<0)
		printf ("No way");
	else
	{
		if (H->Maze[x][y].ant.x==u && H->Maze[x][y].ant.y==v)
		{
			gotoxy (x, y); printf (".");
		}
		else
		{
			path (H, u, v, H->Maze[x][y].ant.x, H->Maze[x][y].ant.y);
			gotoxy (x, y); printf (".");
		}
	}
}
void showpath (maze *H, int u, int v, int x, int y)
{
	int a=x, b=y;
	system ("cls");
	H->imprime();
	Color Blue; gotoxy (u,v); printf ("X");
	Color Red; path (H, u, v, x, y);
	Color Blue; gotoxy (a,b); printf ("O");
	Color Magenta; gotoxy (0,H->y+2);
}
void main ()
{
	maze H;
	char c;
	int i=0, j=0, x, y;
	FILE* entrada = fopen ("C:\\Users\\Felipe\\Desktop\\maze.txt","r");
	/*------------  READ  -------------*/
	fscanf (entrada, "%d %d", &H.x, &H.y);
	while (fscanf (entrada, "%c", &c)>0)
		if (c=='\n') { j++; i=0; }
		else if (c=='X') H.Maze[++i][j].z=1;
		else H.Maze[++i][j].z=0;
	/*------------- MENU --------------*/
	while (c!='s')
	{
		fflush (stdin);
		system ("cls");
		printf ("\n :::::::::::::::::::::::::::::::::::::::::::");
		printf ("\n ::                                       ::");
		printf ("\n :: (i) imprimir  (d) dijkstra  (w) way   ::");
		printf ("\n :: (p) posic                             ::");
		printf ("\n :: (c) cls                     (s) sair  ::");
		printf ("\n ::                                       ::");
		printf ("\n :::::::::::::::::::::::::::::::::::::::::::\n");
		scanf ("%c", &c);
		switch (c)
		{
		case 'i': H.imprime(); break;
		case 'd':	
			printf ("Digite a origem (x,y): "); scanf ("%d %d", &i, &j);
			Dijkstra (&H, i, j);
			H.distancia();
			break;
		case 'w':
			printf ("Digite a origem (x,y): "); scanf ("%d %d", &x, &y);
			printf ("Digite o destino (u,v): "); scanf ("%d %d", &i, &j);
			Dijkstra (&H, x, y);
			showpath (&H, x, y, i, j);
			break;
		case 'p':
			printf ("Digite a origem (x,y): "); scanf ("%d %d", &x, &y);
			printf ("Digite o destino (u,v): "); scanf ("%d %d", &i, &j);
			while (c!='q')
			{
				Dijkstra (&H, x, y);
				showpath (&H, x, y, i, j);
				gotoxy (H.x, H.y+1);
				printf ("ASDW, Q(quit): ");
				fflush (stdin); scanf ("%c", &c);
				switch (c)
				{
				case 'a': i--; break;
				case 'd': i++; break;
				case 's': j++; break;
				case 'w': j--; break;
				}
			}
			break;
		}
		system ("pause");
	}
}
