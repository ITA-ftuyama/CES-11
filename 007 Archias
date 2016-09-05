# include <stdio.h>
# include <conio.h>
# include <time.h>
# include <stdlib.h>

int x, y, p, a;
int win, gift;
int life, score, grass, var;
float wi, dano;
bool morreu, fim;
char name[20];
char d, c;

struct person
{
	char name[20];
	int xo;
	int yo;
};

struct player
{
	char name[20];
	int HP, atk, def, lvl;
	int HP0, acc;
	int php, patk, pdef;
};

player P;
player wild;
person idiota;
person prof;

void menu()
{
	gotoxy(54, 1); printf("MENU");
	gotoxy(54, 3); printf("%s", P.name);
	gotoxy(54, 4); printf("LVL: %2d", P.lvl);
	gotoxy(54, 5); printf("HP:%3d", P.HP);
	gotoxy(54, 6); printf("   %3d", P.HP0);
	gotoxy(54, 7); printf("ATK: %2d", P.atk);
	gotoxy(54, 8); printf("DEF: %2d", P.def);

}

void wild0()
{
	if (P.lvl==1){
		wild.lvl = 1;
		wild.HP = rand() % 8 + 5;
		wild.atk = rand() % 3 + 3;
		wild.def = rand() % 3 + 3;
	}
	else {
		wild.lvl = P.lvl+ rand ()%5 - 2;
		wild.HP = 5 + 1.5*wild.lvl + rand ()% wild.lvl;
		wild.atk = rand() % wild.lvl + 1.25*wild.lvl;
		wild.def = rand() % wild.lvl + 1.25*wild.lvl;
	}
}

void wild1()
{
	wild.lvl = P.lvl +2;
	wild.HP = 5+2*P.HP- 0.025*P.HP*P.HP;
	if (P.HP>=20)
		wild.HP=35;
	wild.atk = 1.2*P.atk;
	wild.def = 1.2*P.def;
}


void menu0()
{
	gotoxy(54, 10);
	printf("Wild");
	gotoxy(54, 11);
	printf("LVL: %2d", wild.lvl);
	gotoxy(54, 12);
	printf("HP:%3d", wild.HP);
	gotoxy(54, 13);
	printf("ATK: %2d", wild.atk);
	gotoxy(54, 14);
	printf("DEF: %2d", wild.def);
}

void lvlup()
{
	if (score > P.lvl * P.lvl * 10)
	{
		P.lvl++;
		P.HP0 += 2 + rand() % 2 + P.php;;
		P.atk += 1 + rand() % 2 + P.patk;
		P.def += 1 + rand() % 2 + P.pdef;
		P.HP = P.HP0;
	}
}
void iniciar0()
{
	x=40;
	y=8;
	idiota.xo = 40;
	idiota.yo = 12;
	gotoxy(40, 8);
	printf("*");
	clrscr();
}

void mundo0()
{
	for (int i = 20; i < 32; i++)
	{
		for (int j = 2; j < 7; j++)
		{
			gotoxy(i, j);
			printf("^");
			if (x == i && y == j)
			{
				grass++;
			}
		}
	}
	for (int i = 0; i <= 52; i++)
	{
		gotoxy(i, 1);
		printf("#");
		gotoxy(i, 14);
		printf("#");
	}
	if (win == 1)
		{
			gotoxy (29,13);
			printf("*   *");
			gotoxy (30,14);
			printf("   ");
		}
	for (int i = 0; i <= 14; i++)
	{
		gotoxy(1, i);
		printf("#");
		gotoxy(52, i);
		printf("#");
	}
	for (int i = 3; i <= 8; i++)
	{
		gotoxy(45, i);
		printf("|");
		gotoxy(35, i);
		printf("|");
	}
	for (int i = 35; i <= 45; i++)
	{
		gotoxy(i, 3);
		printf("/");
	}

	gotoxy(36, 4);
	printf("Lab");
	gotoxy(42, 5);
	printf("[+]");
	gotoxy(36, 8);
	printf("___| |__");
	gotoxy(36, 9);
	printf("   / /");
	gotoxy(39, 7);
	printf("___");
}


void iniciar1()
{
	x = 26;
	y = 13;
	prof.xo = 26;
	prof.yo = 3;
	gotoxy (26,13);
	printf ("*");
	clrscr();
}


void mundo1()
{
	
	for (int i = 16; i <= 36; i++)
	{
		gotoxy(i, 1);
		printf("#");
		if (x == i && y == 1)
			iniciar1();
	}
	for (int i = 16; i <= 20; i++)
	{
		gotoxy(i, 6);
		printf("#");
	}
	for (int i = 32; i <= 36; i++)
	{
		gotoxy(i, 6);
		printf("#");
		if (x == i && y == 6)
			iniciar1();
	}
	for (int i = 1; i <= 6; i++)
	{
		gotoxy(16, i);
		printf("#");
		gotoxy(36, i);
		printf("#");
		if (x == 16 && y == i)
			iniciar1();
		if (x == 36 && y == i)
			iniciar1();
	}
	for (int i = 7; i <= 14; i++)
	{
		gotoxy(20, i);
		printf("#");
		gotoxy(32, i);
		printf("#");
		if (x == 20 && y == i)
			iniciar1();
		if (x == 32 && y == i)
			iniciar1();
	}
	for (int i = 20; i <= 32; i++)
	{

		gotoxy(i, 12);
		printf("#");
		gotoxy(i, 14);
		printf("#");
	}


}
void iniciar2()
{
	x=31;
	y=2;
    gotoxy (x,y);
	printf ("*");
	clrscr();
}

void mundo2()
{
	for (int i = 0; i <= 52; i++)
	{
		gotoxy(i, 1);
		printf("#");
		gotoxy(i, 14);
		printf("#");
		if (x>51||x<1)
			iniciar2();
	}
		for (int i = 0; i <= 14; i++)
	{
		gotoxy(1, i);
		printf("#");
		gotoxy(52, i);
		printf("#");
		if (y<1||y>13)
			iniciar2();
	}
	gotoxy (29,2);
	printf("*   *");
	gotoxy (30,1);
	printf("   ");
}

void battle()
{
	switch (a){
		case 0:
			wild0();
			break;
		case 1:
			wild1();
			break;
	}
	fflush(stdin);
	menu0();
	while (P.HP > 0 && wild.HP > 0)
	{
		c = 'v';
		wi = (rand() % 25) / 100 + 0.85;
		menu();
		menu0();
		gotoxy(16, 10);
		printf("TURNO 1");
		gotoxy(15, 5);
		printf("xxxxxxxxxxxxx");
		gotoxy(15, 6);
		printf("x   ATACAR  x");
		gotoxy(15, 7);
		printf("x   SPECIAL x");
		gotoxy(15, 8);
		printf("x   GIVEUP  x");
		gotoxy(15, 9);
		printf("xxxxxxxxxxxxx");
		gotoxy(9, 12);
		printf("                                    ");
		gotoxy(9, 12);
		printf("%s HP: ", P.name);
		var = (P.HP * 10) / (P.HP0);
		for (int i = 0; i <= var; i++)
		{
			printf("*");
		}
		printf(" %d", P.HP);
		gotoxy(9, 13);
		printf("                                     ");
		gotoxy(9, 13);
		printf("WILD HP: ");
		var = (wild.HP * 10) / (P.HP0);
		for (int i = 0; i <= var; i++)
		{
			printf("*");
		}
		printf(" %d", wild.HP);
		gotoxy(1, 1);
		while (c != 'a' && c != 'A' && c != '\n' && c != '[')
			c = getch();

		if (c == 'a' || c == 'A')
		{
			gotoxy(17, 6);
			printf("!");
			dano = ((P.lvl) / 2 + 2.4) * (wi) * (P.atk) / (wild.def);
			P.acc = rand() % 100;
			if (P.acc > 90)
				dano = 0;
			wild.HP -= dano;
			gotoxy(17, 11);
			printf("                                 ");
			gotoxy(17, 11);
			if (dano == 0)
			  printf("ERROU O GOLPE");
			else printf(" ACERTOU: %.1f", dano);
		}

		else if (c == '\n')
		{
			gotoxy(17, 7);
			printf(" ! ");
			dano = ((P.lvl) / 2 + 3.0) * (wi) * (P.atk) / (wild.def);
			P.acc=rand ()%100;
			if (P.acc>70)
				dano = 0;
			wild.HP -= dano;
			gotoxy(17, 11);
			printf("                                 ");
			gotoxy(17, 11);
			if (dano == 0)
				printf (" ERROU O GOLPE");
			else
				printf("ACERTOU: %.1f", dano);
		}

		else if (c == '[')
		{
			life++;
			P.HP = 0;
			break;
		}

		wi = (rand() % 25) / 100 + 0.85;
		menu();
		menu0();
		gotoxy(16, 10);
		printf("TURNO 2");
		dano = ((wild.lvl) / 2 + 2.4) * (wi) * (wild.atk) / (P.def);
		wild.acc = rand() % 100;
		if (wild.acc > 70)
			dano = 0;
		P.HP -= dano;
		gotoxy(17, 11);
			printf("                                 ");
		gotoxy(17, 11);
		if (dano == 0)
		  printf("ERROU O GOLPE");
		else printf(" DANO: %.1f", dano);
	}

	if (wild.HP <= 0)
	{
		gotoxy(9,13);
		printf ("                                 ");
		gotoxy(9,13);
		score += (wild.atk + wild.def + wild.lvl) / 3;
		lvlup();
		P.HP = P.HP0;
		gotoxy(16, 10);
		printf(" YOU WON + %d exp: ", (wild.atk + wild.def)/2 *(wild.lvl)/(P.lvl));
		if (a==1)
			 win ++;
		getch();
	}

	if (P.HP <= 0)
	{
		gotoxy(16, 11);
		printf("                                  ");
		gotoxy(16, 10);
		printf(" YOU LOST ");
		life--;
		P.HP = P.HP0;
		getch();
	}
	clrscr();
}

void move()
{
	menu();
	gotoxy(1, 15);
	printf(" EXP: %d ", score);
	printf(" LIFE: ");
	for (int i = 0; i < life; i++)
		printf("o");
	printf(" MOVE: ");
	d = getch();
	gotoxy(x, y);
	printf(" ");
	switch (d)
	{
	case '1':
		y--;
		x--;
		break;
	case '2':
		y -= p;
		break;
	case '3':
		y--;
		x++;
		break;
	case '4':
		x -= p;
		break;
	case '5':
		P.HP=P.HP0;
		gotoxy(20, 15);
		printf(" Speed: ");
		scanf(" % d ", &p);
		break;
	case '6':
		x += p;
		break;
	case '7':
		y++;
		x--;
		break;
	case '8':
		y += p;
		break;
	case '9':
		y++;
		x++;
		break;
	case '[':
		fim = true;
		break;
	}
	if (x > 51 || x < 2)
		life--;
	if (y < 2 || y > 13)
		life--;
	if (life <= 0)
		morreu = true;


	if (grass >= 5)
	{
		grass = 0;
		battle();
	}

	switch (a)
	{
	case 0:
		mundo0();
		if (x == 15 && y == 8 && P.atk == 1)
			P.atk += 3;
		if (x == 19 && y == 11 && P.def == 1)
			P.def += 3;
		if (x == 3 && y == 3 && P.HP == 5)
		{
			P.HP += 5;
			P.HP0 += 5;
		}
		if (x == 32 && y == 8 && score == 0)
			score++;
		if (x == idiota.xo && y == idiota.yo)
		{
			gotoxy(4, 13);
			printf(" << O PROF TE AGUARDA. >> ");
			getch();
			clrscr();
		}
		idiota.xo += -1 + rand() % 3;
		gotoxy(idiota.xo - 5, idiota.yo);
		printf("         ");
		gotoxy(idiota.xo, idiota.yo);
		printf(":)");
		if (x == 40 && y == 8)
		{
			a = 1;
			iniciar1();
			mundo1();
		}
		if (win ==1){
			if (x>=30 && x<=32 && y==14){
				a = 2;
				life++;
				iniciar2();
				mundo2();
			}
		}
		break;

	case 1:
		mundo1();
		gotoxy(prof.xo, prof.yo);
		printf(";)");
		for (int i = 20; i <= 32; i++)
    	{
			if (x == i && y == 14){
				a=0;
				life ++;
				iniciar0();
				mundo0();
			}
    	}
	    if (x==prof.xo && y== prof.yo){
	    	if (win ==0){
	 	   	gotoxy(4, 13);
				printf(" << ESTIVE TE ESPERANDO, %s. >> ", P.name);
				getch();
				gotoxy(4, 13);
				printf("                                            "); 
	    		battle();
	    	}
	    	else {
	    		gotoxy(4, 13);
				printf("<< DESGRACADO. >>");
				if (gift==0){
					gotoxy(4,13);
					printf(" ESCOLHA UM: (ATK) A (DEF) ENTER (HP) START");
					fflush(stdin);
					c = getch ();
					if (c == 'a' || c == 'A')
						P.patk++;
					else if (c=='\n')
						P.pdef++;
					else if (c=='[')
						P.php=+2;
					else P.lvl++;
					gift++;
				}
				gotoxy(4, 13);
				life=3;
				printf("                                                             "); 
	    	}
	    }
		gotoxy(prof.xo, prof.yo);
		printf(":)");
		break;
		
		case2:
			mundo2();
			break;
	}
	gotoxy(x, y);
	printf("*");
}

void iniciar()
{
	srand(time(0));
	gotoxy(15, 1);
	printf(" ** ARCHIAS ** ");
	gotoxy(17, 4);
	printf("    xx ");
	gotoxy(17, 5);
	printf("    xx ");
	gotoxy(17, 6);
	printf(" xxxxxxxx ");
	gotoxy(17, 7);
	printf(" x  xx  x ");
	gotoxy(17, 8);
	printf("    xx ");
	gotoxy(17, 9);
	printf("    xx ");
	gotoxy(17, 10);
	printf("    xx ");
	gotoxy(17, 11);
	printf("    xx ");
	gotoxy(17, 12);
	printf("    xx ");
	gotoxy(17, 13);
	printf("    xx ");
	gotoxy(17, 14);
	printf("    x ");
	gotoxy(15, 2);
	printf(" SEU NOME: ");
	scanf("%s", &P.name);
	gotoxy(12, 3);
	printf(" NEWGAME  CONTINUE ");
	scanf(" %c", &c);
	clrscr();
	x = 5;
	y = 5;
	p = 1;
	a = 0;
	win =0;
	gift =0;
	life = 3;
	score = 0;
	P.php=0;
	P.patk=0;
	P.pdef=0;
	P.lvl = 1;
	P.HP = 5;
	P.HP0 = 5;
	P.atk = 1;
	P.def = 1;
	mundo0();
	idiota.xo = 40;
	idiota.yo = 12;
	gotoxy(5, 5);
	printf("*");
	fim = false;
	morreu = false;
	gotoxy(15, 8);
	printf("!");
	gotoxy(19, 11);
	printf("!");
	gotoxy(3, 3);
	printf("!");
	gotoxy(32, 8);
	printf("$");
	gotoxy(40, 12);
	printf(":)");
}


void morrer()
{
	gotoxy(18, 6);
	printf(" GAME OVER ");
	gotoxy(18, 8);
	printf(" SCORE:  %d", score);
	getch();
}

int main()
{
	FILE *entrada;
	entrada = fopen("save.txt", "r");
	iniciar();
	if (c == 'a' || c == 'A')
	{
		fscanf(entrada, "%s %d %d %d %d %d %d %d %d %d %d %d %d %d", P.name, &score, &life, &P.lvl, &P.HP0, &P.atk, &P.def, &x, &y, &a, &win, &P.php, &P.patk, &P.def);
		P.HP=P.HP0;
	}
	while (!morreu)
	{
		while (!fim && !morreu)
		{
			move();
		}
		FILE *saida;
		saida = fopen("save.txt", "w");
		fprintf(saida, "%s %d %d %d %d %d %d %d %d %d %d %d %d %d", P.name, score, life,P.lvl, P.HP0, P.atk, P.def, x, y, a, win, P.php, P.patk, P.def);
		fclose(saida);
		gotoxy(18, 3);
		printf(" JOGO SALVO ");
		fim = false;
	}
	morrer();
	fclose(entrada);
	return 0;
}