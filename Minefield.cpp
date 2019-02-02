#include "stdafx.h"
#include <windows.h>
#include <iostream>
using namespace std;
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>  //cor da letra
#include <locale.h> //acentos
#include <ctime> 
#include <string>


#define CYAN 3
#define BLACK 0
#define LIGHTRED 12
#define LIGHTBLUE 9
#define LIGHTGREEN 10
#define WHITE 15

int i;
int o;

int x;//para desenhar
int y;//para desenhar

int x_escolhido;
int y_escolhido;

const int campo_x = 20;
const int campo_y = 20;

string localizacao_c;
int localizacao_i[5];

int campo[campo_x][campo_y];
int selecionados[campo_x][campo_y];

int num_bombas;
int bombas_x;
int bombas_y;

int total_do_campo;
int campos_limpos;

bool em_jogo = true;
bool bomba_explodida = false;


bool area_livre = false;

int contagem_periferica = 0;

void textcolor(int color)
{
	static int __BACKGROUND;

	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;


	GetConsoleScreenBufferInfo(h, &csbiInfo);

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
		color + (__BACKGROUND << 4));
}

void criar_bombas()
{
	num_bombas = rand() % 40 + 30;
	for (int i = 0; i<num_bombas; i++)
	{
		bombas_x = rand() % (campo_x - 1) + 0;
		bombas_y = rand() % (campo_y - 1) + 0;
		while (campo[bombas_x][bombas_y] == 9)
		{
			bombas_x = rand() % (campo_x - 1) + 0;
			bombas_y = rand() % (campo_y - 1) + 0;
		}
		if (campo[bombas_x][bombas_y] == 11)
		{
			campo[bombas_x][bombas_y] = 9;
		}
	}
}

void motrar_area()
{
	contagem_periferica = 0;
	for (i = 0; i<3; i++)//x
	{
		for (o = 0; o<3; o++)//y
		{
			if ((x + (i - 1) >= 0 && x + (i - 1) <campo_x) && (y + (o - 1) >= 0 && y + (o - 1) <campo_y))
			{
				if (campo[x + i - 1][y + o - 1] == 9)
				{
					contagem_periferica++;
				}
			}
		}
	}
	if (contagem_periferica != 0)
	{
		campo[x][y] = contagem_periferica;
	}
	else
	{
		campo[x][y] = contagem_periferica;

		for (i = 0; i<3; i++)//x
		{
			for (o = 0; o<3; o++)//y
			{
				if ((x + (i - 1) >= 0 && x + (i - 1) <campo_x) && (y + (o - 1) >= 0 && y + (o - 1) <campo_y))
				{
					if (campo[x + i - 1][y + o - 1] == 11)
					{
						campo[x + i - 1][y + o - 1] = -1;
					}
				}
			}
		}
	}

}


void atualizar_campo()
{
	textcolor(CYAN);

	printf("  ");
	for (o = 0; o<campo_x; o++)
	{
		if (o + 1<10)
		{
			textcolor(CYAN);
			printf(" 0%d", o + 1);
		}
		else
		{
			textcolor(CYAN);
			printf(" %d", o + 1);
		}
	}
	printf("\n");

	for (y = 0; y<campo_y; y++)
	{
		if (y + 1<10)
		{
			textcolor(CYAN);
			printf("0%d", y + 1);
		}
		else
		{
			textcolor(CYAN);
			printf("%d", y + 1);
		}
		for (x = 0; x<campo_x; x++)
		{
			if (selecionados[x][y] == 0)
			{
				textcolor(WHITE);
			}
			if (selecionados[x][y] == 1)
			{
				textcolor(LIGHTRED);
			}
			if (campo[x][y] == -1)
			{
				motrar_area();
			}
			if (campo[x][y] == 0)//boatwe hfdnkxkuykj
			{
				printf("   ");
			}
			if (campo[x][y] == 9)//bomba escondida
			{
				if (em_jogo == true)
				{
					printf("  -");
				}
				else
				{
					textcolor(LIGHTRED);
					printf("  *");
				}
			}
			if (campo[x][y] == 11)//livre escondido
			{
				printf("  -");
			}
			if (campo[x][y] >= 1 && campo[x][y] <= 8)
			{
				textcolor(LIGHTBLUE);
				printf("  %d", campo[x][y]);
			}
		}
		if (y + 1<10)
		{
			textcolor(CYAN);
			printf(" 0%d", y + 1);
		}
		else
		{
			textcolor(CYAN);
			printf(" %d", y + 1);
		}
		printf("\n");
	}
	textcolor(CYAN);
	printf("  ");
	for (o = 0; o<campo_x; o++)
	{
		if (o + 1<10)
		{
			textcolor(CYAN);
			printf(" 0%d", o + 1);
		}
		else
		{
			textcolor(CYAN);
			printf(" %d", o + 1);
		}
	}
	printf("\n");
	printf("\n");
}



void filtrar_escolhido()
{
	textcolor(WHITE);

	printf("Write the coordinate: ");
	getline(cin, localizacao_c);
	system("cls");

	for (i = 0; i<5; i++)
	{
		if (localizacao_c[i]!=' ')
			localizacao_i[i] = localizacao_c[i] - '0';
	}

	x_escolhido = localizacao_i[0] * 10 + localizacao_i[1] - 1;
	y_escolhido = localizacao_i[3] * 10 + localizacao_i[4] - 1;
	if (localizacao_c.length() > 5){
		if (localizacao_c[6] == 'b')
		{
			selecionados[x_escolhido][y_escolhido] = 1;
			x_escolhido = -1;
			y_escolhido = -1;
		}
	}
}

void contagem_campo()
{
	for (y = 0; y<campo_y; y++)
	{
		for (x = 0; x<campo_x; x++)
		{
			if (campo[x][y] != 9 && campo[x][y] != 11)
			{
				campos_limpos++;
			}
		}
	}
	if (campos_limpos == total_do_campo)
	{
		em_jogo = false;
	}
	campos_limpos = 0;
}
//------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
	//textbackground(WHITE); 
	system("cls");

	textcolor(WHITE);
	setlocale(LC_ALL, "Portuguese");
	srand(time(NULL));
	total_do_campo = campo_x*campo_y - num_bombas;

	for (y = 0; y<campo_y; y++)//reseta o campo
	{
		for (x = 0; x<campo_x; x++)
		{
			campo[x][y] = 11;
			selecionados[x][y] = 0;
		}
	}

	criar_bombas();

	while (em_jogo == true)
	{
		for (i = 0; i<5; i++)
		{
			system("cls");
			atualizar_campo();
		}

		filtrar_escolhido();
		if (campo[x_escolhido][y_escolhido] == 11)
		{
			x = x_escolhido;
			y = y_escolhido;
			motrar_area();
		}
		if (campo[x_escolhido][y_escolhido] == 9)
		{
			em_jogo = false;
			bomba_explodida = true;
			atualizar_campo();
			system("cls");
			atualizar_campo();

		}
		contagem_campo();
	}
	if (bomba_explodida == true)
	{
		system("cls");
		atualizar_campo();
		textcolor(LIGHTRED);
		printf("\nYOU LOST... close and try again, I know you can do this");
		Sleep(10000);
	}
	if (bomba_explodida == false)
	{
		system("cls");
		atualizar_campo();
		textcolor(LIGHTGREEN);
		printf("\nYOU WIN!!! I'm so proud of you :)");
		Sleep(10000);
	}

	return 0;
}


//0=escondido_limpo
//1=limpo
//2=escondido_bomba
//3=bomba aparecendo


//-1=limpo_nao_verificado
//0=limpo_verificado
//1
//2
//3
//4
//5
//6
//7
//8
//9=bomba_escondida
//10=bomba
//11=escondido_limpo

