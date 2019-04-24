// Kursach.cpp 

//#include "pch.h"
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <cstdlib>
#include <ctime>

using namespace std;

int scale = 30;

int N = 20;

int index[20][20];

int en_i = 8, en_j = 7, en1_i = 1, en1_j = 18, en2_i = 18, en2_j = 18, en3_i = 18, en3_j = 4;

bool gameover = false;

bool gamewin = false;

int help();

int about();

int game();

int display();

bool check_index(int, int);

bool check_apples(int, int);

bool check_enemy(int, int);

bool check(int, int);

void init_index();

void init_apples(int);

void move_enemy(); 

void move_enemy(int);

void move_enemy(float);

void move_enemy(char);

int menu();

void title();

void frame(HANDLE, COORD, COORD);

void clean(HANDLE, COORD, COORD);


int main()
{
	HWND hwnd = GetConsoleWindow();
	HDC hdc = GetDC(hwnd);
	RECT r;
	GetWindowRect(hwnd, &r);
	MoveWindow(hwnd, r.left, r.top, 1100, 800, TRUE);
	int result = 4;
	init_index();
	
	while (result != 1) {
		
		result = menu();

		if (result == 0) {
			result = game();
		}

		if (result == 1) {
			return 0;
		}

		if (result == 2) {
			result = help();
		}

		if (result == 3) {
			result = about();
		}

	}
	return 1;
}

int game() {

	int result;
	COORD s;
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	s.X = 300; s.Y = 300;
	SetConsoleCursorPosition(h, s);

	result = display();
	
	if (result == 0) {
		cout << "Congratulations! You're the winner!";
	}
	
	if (result == 1) {
		cout << "Unfortunetly, you lost";
	}

	Sleep(2000);
	system("cls");
	return 0;
}

int display() {
	
	bool gameover = false;
	int ch_i = 11, ch_j = 10, ch_i_try, ch_j_try, ch_i_temp, ch_j_temp;
	int score = 0;
	COORD ch_top, ch_bot, field, temp_top, temp_bot, try_top, try_bot, s;
	
	int marker1 = 1;
	float marker2 = 2;
	char marker3 = '3';

	ch_i_try = ch_i; ch_j_try = ch_j; ch_i_temp = ch_i; ch_j_temp = ch_j;
	ch_top.X = 390; ch_top.Y = 420; ch_bot.X = 420; ch_bot.Y = 450;
	try_top.X = ch_top.X; try_top.Y = ch_top.Y; try_bot.X = ch_bot.X; try_bot.Y = ch_bot.Y;
	temp_top.X = ch_top.X; temp_top.Y = ch_top.Y; temp_bot.X = ch_bot.X; temp_bot.Y = ch_bot.Y;
	field.X = 90; field.Y = 90;
	s.X = 0; s.Y = 0;
	index[en_i][en_j] = 3;
	
	HWND hwnd = GetConsoleWindow();
	HDC hdc = GetDC(hwnd);
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	HBRUSH hBrush = CreateSolidBrush(RGB(128, 128, 128)); //for walls
	HBRUSH hBrush1 = CreateSolidBrush(RGB(0, 255, 255)); //for character
	HBRUSH hBrush2 = CreateSolidBrush(RGB(0, 0, 0)); //for erasing
	HBRUSH hBrush3 = CreateSolidBrush(RGB(255, 30, 0)); //for apples	
	HBRUSH hBrush4 = CreateSolidBrush(RGB(173, 255, 40)); // for enemies

	while (!gameover && !gamewin) {

		SetConsoleCursorPosition(h, s);
		cout << "Score: " << score;

		//Drawing the game field

		SelectObject(hdc, hBrush);

		Rectangle(hdc, field.X, field.Y, field.X + N * scale, field.Y + scale);
		Rectangle(hdc, field.X, field.Y, field.X + scale, field.Y + N * scale);
		Rectangle(hdc, field.X, field.Y + (N - 1) * scale, field.X + N * scale, field.Y + N * scale);
		Rectangle(hdc, field.X + (N - 1) * scale, field.Y, field.X + N * scale, field.Y + N * scale);
		Rectangle(hdc, 150, 150, 180, 360);
		Rectangle(hdc, 150, 330, 240, 360);
		Rectangle(hdc, 210, 360, 240, 150);
		Rectangle(hdc, 210, 150, 300, 180);
		Rectangle(hdc, 270, 150, 300, 270);
		Rectangle(hdc, 270, 240, 360, 270);
		Rectangle(hdc, 330, 180, 360, 330);
		Rectangle(hdc, 330, 300, 420, 330);
		Rectangle(hdc, 390, 150, 420, 360);
		Rectangle(hdc, 390, 330, 450, 360);
		Rectangle(hdc, 450, 150, 480, 300);
		Rectangle(hdc, 450, 270, 630, 300);
		Rectangle(hdc, 600, 210, 630, 300);
		Rectangle(hdc, 510, 210, 630, 240);
		Rectangle(hdc, 510, 150, 540, 240);
		Rectangle(hdc, 510, 150, 660, 180);
		Rectangle(hdc, 150, 390, 300, 420);
		Rectangle(hdc, 270, 300, 300, 420);
		Rectangle(hdc, 300, 360, 330, 480);
		Rectangle(hdc, 150, 450, 330, 480);
		Rectangle(hdc, 150, 450, 180, 630);
		Rectangle(hdc, 240, 510, 270, 660);
		Rectangle(hdc, 240, 510, 330, 540);
		Rectangle(hdc, 300, 570, 330, 660);
		Rectangle(hdc, 300, 570, 390, 600);
		Rectangle(hdc, 360, 570, 390, 630);
		Rectangle(hdc, 360, 510, 450, 540);
		Rectangle(hdc, 420, 510, 450, 630);
		Rectangle(hdc, 420, 600, 630, 630);
		Rectangle(hdc, 600, 540, 630, 630);
		Rectangle(hdc, 480, 540, 630, 570);
		Rectangle(hdc, 480, 480, 510, 570);
		Rectangle(hdc, 480, 480, 600, 510);
		Rectangle(hdc, 570, 420, 600, 510);
		Rectangle(hdc, 480, 420, 600, 450);
		Rectangle(hdc, 480, 330, 510, 450);
		Rectangle(hdc, 480, 330, 630, 360);
		Rectangle(hdc, 360, 390, 390, 480);
		Rectangle(hdc, 360, 450, 450, 480);
		Rectangle(hdc, 420, 390, 450, 480);

		//Drawing apples

		SelectObject(hdc, hBrush3);

		if (score == 10) {
			init_apples(score);
			Rectangle(hdc, field.X + 1 * scale, field.Y + 1 * scale, field.X + 2 * scale, field.Y + 2 * scale);
		}
		if (score == 4) {
			init_apples(score);
			Rectangle(hdc, field.X + 1 * scale, field.Y + 18 * scale, field.X + 2 * scale, field.Y + 19 * scale);
		}
		if (score == 12) {
			init_apples(score);
			Rectangle(hdc, field.X + 3 * scale, field.Y + 7 * scale, field.X + 4 * scale, field.Y + 8 * scale);
		}
		if (score == 1) {
			init_apples(score);
			Rectangle(hdc, field.X + 3 * scale, field.Y + 13 * scale, field.X + 4 * scale, field.Y + 14 * scale);
		}
		if (score == 8) {
			init_apples(score);
			Rectangle(hdc, field.X + 7 * scale, field.Y + 4 * scale, field.X + 8 * scale, field.Y + 5 * scale);
		}
		if (score == 6) {
			init_apples(score);
			Rectangle(hdc, field.X + 6 * scale, field.Y + 11 * scale, field.X + 7 * scale, field.Y + 12 * scale);
		}
		if (score == 0) {
			init_apples(score);
			Rectangle(hdc, field.X + 8 * scale, field.Y + 17 * scale, field.X + 9 * scale, field.Y + 18 * scale);
		}
		if (score == 11) {
			init_apples(score);
			Rectangle(hdc, field.X + 9 * scale, field.Y + 6 * scale, field.X + 10 * scale, field.Y + 7 * scale);
		}
		if (score == 9) {
			init_apples(score);
			Rectangle(hdc, field.X + 10 * scale, field.Y + 11 * scale, field.X + 11 * scale, field.Y + 12 * scale);
		}
		if (score == 3) {
			init_apples(score);
			Rectangle(hdc, field.X + 14 * scale, field.Y + 9 * scale, field.X + 15 * scale, field.Y + 10 * scale);
		}
		if (score == 13) {
			init_apples(score);
			Rectangle(hdc, field.X + 14 * scale, field.Y + 14 * scale, field.X + 15 * scale, field.Y + 15 * scale);
		}
		if (score == 2) {
			init_apples(score);
			Rectangle(hdc, field.X + 15 * scale, field.Y + 3 * scale, field.X + 16 * scale, field.Y + 4 * scale);
		}
		if (score == 14) {
			init_apples(score);
			Rectangle(hdc, field.X + 16 * scale, field.Y + 5 * scale, field.X + 17 * scale, field.Y + 6 * scale);
		}
		if (score == 7) {
			init_apples(score);
			Rectangle(hdc, field.X + 16 * scale, field.Y + 16 * scale, field.X + 17 * scale, field.Y + 17 * scale);
		}
		if (score == 5) {
			init_apples(score);
			Rectangle(hdc, field.X + 18 * scale, field.Y + 1 * scale, field.X + 19 * scale, field.Y + 2 * scale);
		}
		

		// Erasing enemies

		SelectObject(hdc, hBrush2);
		Rectangle(hdc, field.X + en_j * scale, field.Y + en_i * scale, field.X + (en_j + 1) * scale, field.Y + (en_i + 1) * scale);
		Rectangle(hdc, field.X + en1_j * scale, field.Y + en1_i * scale, field.X + (en1_j + 1) * scale, field.Y + (en1_i + 1) * scale);
		Rectangle(hdc, field.X + en2_j * scale, field.Y + en2_i * scale, field.X + (en2_j + 1) * scale, field.Y + (en2_i + 1) * scale);
		Rectangle(hdc, field.X + en3_j * scale, field.Y + en3_i * scale, field.X + (en3_j + 1) * scale, field.Y + (en3_i + 1) * scale);
		
		if (_kbhit()) {

			int ch = _getch();

			try_top.X = temp_top.X; try_top.Y = temp_top.Y; try_bot.X = temp_bot.X; try_bot.Y = temp_bot.Y;
			ch_i_try = ch_i_temp; ch_j_try = ch_j_temp;

			switch (ch) {

				case 72: //UP
					
					try_top.Y -= 30;
					try_bot.Y -= 30;
					ch_i_try--;

					// Checking enemy's position

					if (check_enemy(ch_i_try, ch_j_try)) {
						gameover = true;
						system("cls");
						return 1;
					}

					// Movment of enemy
					move_enemy();
					move_enemy(marker1);
					move_enemy(marker2);
					move_enemy(marker3);
					break;

				case 77: //RIGHT

					try_top.X += 30;
					try_bot.X += 30;
					ch_j_try++;

					// Checking enemy's position

					if (check_enemy(ch_i_try, ch_j_try)) {
						gameover = true;
						system("cls");
						return 1;
					}
				
					// Movment of enemy
					move_enemy();
					move_enemy(marker1);
					move_enemy(marker2);
					move_enemy(marker3);
					break;


				case 80: //DOWN

					try_top.Y += 30;
					try_bot.Y += 30;
					ch_i_try++;

					// Checking enemy's position

					if (check_enemy(ch_i_try, ch_j_try)) {
						gameover = true;
						system("cls");
						return 1;
					}
				
					// Movment of enemy
					move_enemy();
					move_enemy(marker1);
					move_enemy(marker2);
					move_enemy(marker3);
					break;

				case 75: //LEFT

					try_top.X -= 30;
					try_bot.X -= 30;
					ch_j_try--;

					// Checking enemy's position

					if (check_enemy(ch_i_try, ch_j_try)) {
						gameover = true;
						system("cls");
						return 1;
					}
				
					// Movment of enemy
					move_enemy();
					move_enemy(marker1);
					move_enemy(marker2);
					move_enemy(marker3);
					break;

				case 27:
					gameover = true;
					system("cls");
					return 1;
			}

			// Checking coordinates of charecter 
			if (check_index(ch_i_try, ch_j_try)) { 
		
				ch_i_temp = ch_i_try; ch_j_temp = ch_j_try;
				temp_top.X = try_top.X; temp_top.Y = try_top.Y; temp_bot.X = try_bot.X; temp_bot.Y = try_bot.Y;
			}

			else continue;

			ch_i = ch_i_temp; ch_j = ch_j_temp;
			ch_top.X = temp_top.X; ch_top.Y = temp_top.Y; ch_bot.X = temp_bot.X; ch_bot.Y = temp_bot.Y;

			// Checking enemy's position

			if (check_enemy(ch_i, ch_j)) {
				gameover = true;
				system("cls");
				return 1;
			}

		}


		// Checking position of apples

		if (check_apples(ch_i, ch_j)) {
			score++;
		}
		
		// Checking game win

		if (score == 15) {
			system("cls");
			gamewin = true;
			return 0;
		}

		// Drawing enemies

		SelectObject(hdc, hBrush4);
		Rectangle(hdc, field.X + en_j * scale, field.Y + en_i * scale, field.X + (en_j + 1) * scale, field.Y + (en_i + 1) * scale);
		Rectangle(hdc, field.X + en1_j * scale, field.Y + en1_i * scale, field.X + (en1_j + 1) * scale, field.Y + (en1_i + 1) * scale);
		Rectangle(hdc, field.X + en2_j * scale, field.Y + en2_i * scale, field.X + (en2_j + 1) * scale, field.Y + (en2_i + 1) * scale);
		Rectangle(hdc, field.X + en3_j * scale, field.Y + en3_i * scale, field.X + (en3_j + 1) * scale, field.Y + (en3_i + 1) * scale);

		// Drawing charecter
		SelectObject(hdc, hBrush1);
		Rectangle(hdc, ch_top.X, ch_top.Y, ch_bot.X, ch_bot.Y);

		Sleep(40);

		// Erasing charecter
		SelectObject(hdc, hBrush2);
		Rectangle(hdc, ch_top.X, ch_top.Y, ch_bot.X, ch_bot.Y);

}

	DeleteObject(hBrush);
	DeleteObject(hBrush1);
	DeleteObject(hBrush2);

	ReleaseDC(NULL, hdc);
	system("cls");

}


void init_index() {
	
	// 0 means walls and 1 means spaces

	for (int j = 0; j < 20; j++) index[0][j] = 0;

	index[1][0] = 0;
	for (int j = 1; j < 19; j++) index[1][j] = 1;
	index[1][19] = 0;

	index[2][0] = 0;
	index[2][1] = 1;
	index[2][2] = 0;
	index[2][3] = 1;
	for (int j = 4; j < 7; j++) index[2][j] = 0;
	for (int j = 7; j < 10; j++) index[2][j] = 1;
	index[2][10] = 0;
	index[2][11] = 1;
	index[2][12] = 0;
	index[2][13] = 1;
	for (int j = 14; j < 20; j++) index[2][j] = 0;

	index[3][0] = 0;
	index[3][1] = 1;
	index[3][2] = 0;
	index[3][3] = 1;
	index[3][4] = 0;
	index[3][5] = 1;
	index[3][6] = 0;
	index[3][7] = 1;
	index[3][8] = 0;
	index[3][9] = 1;
	index[3][10] = 0;
	index[3][11] = 1;
	index[3][12] = 0;
	index[3][13] = 1;
	index[3][14] = 0;
	for (int j = 15; j < 19; j++) index[3][j] = 1;
	index[3][19] = 0;

	index[4][0] = 0;
	index[4][1] = 1;
	index[4][2] = 0;
	index[4][3] = 1;
	index[4][4] = 0;
	index[4][5] = 1;
	index[4][6] = 0;
	index[4][7] = 1;
	index[4][8] = 0;
	index[4][9] = 1;
	index[4][10] = 0;
	index[4][11] = 1;
	index[4][12] = 0;
	index[4][13] = 1;
	for (int j = 14; j < 18; j++) index[4][j] = 0;
	index[4][18] = 1;
	index[4][19] = 0;

	index[5][0] = 0;
	index[5][1] = 1;
	index[5][2] = 0;
	index[5][3] = 1;
	index[5][4] = 0;
	index[5][5] = 1;
	for (int j = 6; j < 9; j++) index[5][j] = 0;
	index[5][9] = 1;
	index[5][10] = 0;
	index[5][11] = 1;
	index[5][12] = 0;
	for (int j = 13; j < 17; j++) index[5][j] = 1;
	index[5][17] = 0;
	index[5][18] = 1;
	index[5][19] = 0;

	index[6][0] = 0;
	index[6][1] = 1;
	index[6][2] = 0;
	index[6][3] = 1;
	index[6][4] = 0;
	for (int j = 5; j < 8; j++) index[6][j] = 1;
	index[6][8] = 0;
	index[6][9] = 1;
	index[6][10] = 0;
	index[6][11] = 1;
	for (int j = 12; j < 18; j++) index[6][j] = 0;
	index[6][18] = 1;
	index[6][19] = 0;

	index[7][0] = 0;
	index[7][1] = 1;
	index[7][2] = 0;
	index[7][3] = 1;
	index[7][4] = 0;
	index[7][5] = 1;
	index[7][6] = 0;
	index[7][7] = 1;
	for (int j = 8; j < 11; j++) index[7][j] = 0;
	for (int j = 11; j < 19; j++) index[7][j] = 1;
	index[7][19] = 0;

	index[8][0] = 0;
	index[8][1] = 1;
	for (int j = 2; j < 5; j++) index[8][j] = 0;
	index[8][5] = 1;
	index[8][6] = 0;
	for (int j = 7; j < 10; j++) index[8][j] = 1;
	index[8][10] = 0;
	index[8][11] = 0;
	index[8][12] = 1;
	for (int j = 13; j < 18; j++) index[8][j] = 0;
	index[8][18] = 1;
	index[8][19] = 0;

	index[9][0] = 0;
	for (int j = 1; j < 6; j++) index[9][j] = 1;
	index[9][6] = 0;
	index[9][7] = 0;
	for (int j = 8; j < 13; j++) index[9][j] = 1;
	index[9][13] = 0;
	for (int j = 14; j < 19; j++) index[9][j] = 1;
	index[9][19] = 0;

	index[10][0] = 0;
	index[10][1] = 1;
	for (int j = 2; j < 8; j++) index[10][j] = 0;
	index[10][8] = 1;
	index[10][9] = 0;
	index[10][10] = 1;
	index[10][11] = 0;
	index[10][12] = 1;
	index[10][13] = 0;
	for (int j = 14; j < 19; j++) index[10][j] = 1;

	index[11][0] = 0;
	for (int j = 1; j < 7; j++) index[11][j] = 1;
	index[11][7] = 0;
	index[11][8] = 1;
	index[11][9] = 0;
	index[11][10] = 1;
	index[11][11] = 0;
	index[11][12] = 1;
	for (int j = 13; j < 17; j++) index[11][j] = 0;
	index[11][17] = 1;
	index[11][18] = 1;
	index[11][19] = 0;

	index[12][0] = 0;
	index[12][1] = 1;
	for (int j = 2; j < 8; j++) index[12][j] = 0;
	index[12][8] = 1;
	for (int j = 9; j < 12; j++) index[12][j] = 0;
	for (int j = 12; j < 16; j++) index[12][j] = 1;
	index[12][16] = 0;
	index[12][17] = 1;
	index[12][18] = 1;
	index[12][19] = 0;

	index[13][0] = 0;
	index[13][1] = 1;
	index[13][2] = 0;
	for (int j = 3; j < 13; j++) index[13][j] = 1;
	for (int j = 13; j < 17; j++) index[13][j] = 0;
	index[13][17] = 1;
	index[13][18] = 1;
	index[13][19] = 0;

	index[14][0] = 0;
	index[14][1] = 1;
	index[14][2] = 0;
	index[14][3] = 1;
	index[14][4] = 1;
	for (int j = 5; j < 8; j++) index[14][j] = 0;
	index[14][8] = 1;
	for (int j = 9; j < 12; j++) index[14][j] = 0;
	index[14][12] = 1;
	index[14][13] = 0;
	for (int j = 14; j < 19; j++) index[14][j] = 1;
	index[14][19] = 0;

	index[15][0] = 0;
	index[15][1] = 1;
	index[15][2] = 0;
	index[15][3] = 1;
	index[15][4] = 1;
	index[15][5] = 0;
	for (int j = 6; j < 11; j++) index[15][j] = 1;
	index[15][11] = 0;
	index[15][12] = 1;
	for (int j = 13; j < 18; j++) index[15][j] = 0;
	index[15][18] = 1;
	index[15][19] = 0;

	index[16][0] = 0;
	index[16][1] = 1;
	index[16][2] = 0;
	index[16][3] = 1;
	index[16][4] = 1;
	index[16][5] = 0;
	index[16][6] = 1;
	for (int j = 7; j < 10; j++) index[16][j] = 0;
	index[16][10] = 1;
	index[16][11] = 0;
	for (int j = 12; j < 17; j++) index[16][j] = 1;
	index[16][17] = 0;
	index[16][18] = 1;
	index[16][19] = 0;

	index[17][0] = 0;
	index[17][1] = 1;
	index[17][2] = 0;
	index[17][3] = 1;
	index[17][4] = 1;
	index[17][5] = 0;
	index[17][6] = 1;
	index[17][7] = 0;
	index[17][8] = 1;
	index[17][9] = 0;
	index[17][10] = 1;
	for (int j = 11; j < 18; j++) index[17][j] = 0;
	index[17][18] = 1;
	index[17][19] = 0;

	index[18][0] = 0;
	for (int j = 1; j < 5; j++) index[18][j] = 1;
	index[18][5] = 0;
	index[18][6] = 1;
	index[18][7] = 0;
	for (int j = 8; j < 19; j++) index[18][j] = 1;
	index[18][19] = 0;

	for (int j = 0; j < 20; j++) index[19][j] = 0;

}


void init_apples(int c) {

	// 2 means apples

	if(c ==10) index[1][1] = 2;
	if (c == 4) index[18][1] = 2;
	if (c == 12) index[7][3] = 2;
	if (c == 1) index[13][3] = 2;
	if (c == 6) index[11][6] = 2;
	if (c == 8) index[4][7] = 2;
	if (c == 0) index[17][8] = 2;
	if (c == 9) index[11][10] = 2;
	if (c == 3) index[9][14] = 2;
	if (c == 13) index[14][14] = 2;
	if (c == 2) index[3][15] = 2;
	if (c == 14) index[5][16] = 2;
	if (c == 7) index[16][16] = 2;
	if (c == 5) index[1][18] = 2;
	if (c == 11) index[6][9] = 2;

}


bool check_index(int i, int j) {

	bool result = false;

	if (index[i][j] != 0) result = true;

	return result;
}


bool check_apples(int i, int j) {

	bool result = false;

	if (index[i][j] == 2) {
		result = true;
		index[i][j] = 1;
	}

	return result;
}

bool check_enemy(int i, int j) {

	bool result = false;

	if (index[i][j] == 3) {
		result = true;
	}

	return result;
}

void move_enemy() {

	bool stop = false;

	int temp_i = en_i, temp_j = en_j, try_i, try_j, t_i = en_i, t_j = en_j;

	srand(time(NULL));

	while (!stop) {


		int dir = rand() % 4;

		try_i = temp_i; try_j = temp_j;

		if (dir == 0) { //UP

			try_i--;
			if (check( try_i, try_j)) {
				temp_i = try_i;
				temp_j = try_j;
				stop = true;
			}
		}

		if (dir == 1) { //LEFT
			
			try_j--;
			if (check(try_i, try_j)) {
				temp_i = try_i;
				temp_j = try_j;
				stop = true;
			}
		}

		if (dir == 2) { //DOWN
			
			try_i++;
			if (check(try_i, try_j)) {
				temp_i = try_i;
				temp_j = try_j;
				stop = true;
			}
		}

		if (dir == 3) { //RIGHT
			
			try_j++;
			if (check(try_i, try_j)) {
				temp_i = try_i;
				temp_j = try_j;
				stop = true;
			}
			
		}
		en_i = temp_i; en_j = temp_j;

	}
	
	index[t_i][t_j] = 1;
	index[en_i][en_j] = 3;
}


void move_enemy(int) {

	bool stop = false;

	int temp_i = en1_i, temp_j = en1_j, try_i, try_j, t_i = en1_i, t_j = en1_j;

	srand(time(NULL));

	while (!stop) {

		int dir = rand() % 4;

		try_i = temp_i; try_j = temp_j;

		if (dir == 0) { //UP

			try_i--;
			if (check(try_i, try_j)) {
				temp_i = try_i;
				temp_j = try_j;
				stop = true;
			}
		}

		if (dir == 1) { //LEFT

			try_j--;
			if (check(try_i, try_j)) {
				temp_i = try_i;
				temp_j = try_j;
				stop = true;
			}
		}

		if (dir == 2) { //DOWN

			try_i++;
			if (check(try_i, try_j)) {
				temp_i = try_i;
				temp_j = try_j;
				stop = true;
			}
		}

		if (dir == 3) { //RIGHT

			try_j++;
			if (check(try_i, try_j)) {
				temp_i = try_i;
				temp_j = try_j;
				stop = true;
			}

		}

		en1_i = temp_i; en1_j = temp_j;

	}

	index[t_i][t_j] = 1;
	index[en1_i][en1_j] = 3;
}

void move_enemy(float) {

	bool stop = false;

	int temp_i = en2_i, temp_j = en2_j, try_i, try_j, t_i = en2_i, t_j = en2_j;

	srand(time(NULL));

	while (!stop) {

		int dir = rand() % 4;

		try_i = temp_i; try_j = temp_j;

		if (dir == 0) { //UP

			try_i--;
			if (check(try_i, try_j)) {
				temp_i = try_i;
				temp_j = try_j;
				stop = true;
			}
		}

		if (dir == 1) { //LEFT

			try_j--;
			if (check(try_i, try_j)) {
				temp_i = try_i;
				temp_j = try_j;
				stop = true;
			}
		}

		if (dir == 2) { //DOWN

			try_i++;
			if (check(try_i, try_j)) {
				temp_i = try_i;
				temp_j = try_j;
				stop = true;
			}
		}

		if (dir == 3) { //RIGHT

			try_j++;
			if (check(try_i, try_j)) {
				temp_i = try_i;
				temp_j = try_j;
				stop = true;
			}

		}

		en2_i = temp_i; en2_j = temp_j;

	}

	index[t_i][t_j] = 1;
	index[en2_i][en2_j] = 3;
}


void move_enemy(char) {

	bool stop = false;

	int temp_i = en3_i, temp_j = en3_j, try_i, try_j, t_i = en3_i, t_j = en3_j;

	srand(time(NULL));

	while (!stop) {


		int dir = rand() % 4;

		try_i = temp_i; try_j = temp_j;

		if (dir == 0) { //UP

			try_i--;
			if (check(try_i, try_j)) {
				temp_i = try_i;
				temp_j = try_j;
				stop = true;
			}
		}

		if (dir == 1) { //LEFT

			try_j--;
			if (check(try_i, try_j)) {
				temp_i = try_i;
				temp_j = try_j;
				stop = true;
			}
		}

		if (dir == 2) { //DOWN

			try_i++;
			if (check(try_i, try_j)) {
				temp_i = try_i;
				temp_j = try_j;
				stop = true;
			}
		}

		if (dir == 3) { //RIGHT

			try_j++;
			if (check(try_i, try_j)) {
				temp_i = try_i;
				temp_j = try_j;
				stop = true;
			}

		}

		en3_i = temp_i; en3_j = temp_j;

	}

	index[t_i][t_j] = 1;
	index[en3_i][en3_j] = 3;
}


bool check(int i, int j) {

	if (index[i][j] == 1) {
		if (i < 20 && i >= 0  && j < 20 && j >= 0) {
			return true;
		}
	}
	
	else return false;
}


int menu() {
	
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD c1, c2, t;
	bool fl = true;
	int result = 0;

	c1.X = 37;
	c1.Y = 8;
	c2.X = 70;
	c2.Y = 13;
	t.X = 48;
	t.Y = 10;
	system("cls");
	title();
	SetConsoleCursorPosition(h, t);
	cout << "Start game";
	t.X += 3;
	t.Y += 4;
	SetConsoleCursorPosition(h, t);
	cout << "Exit";
	t.Y += 4;
	SetConsoleCursorPosition(h, t);
	cout << "Help";
	t.Y += 4;
	SetConsoleCursorPosition(h, t);
	cout << "About";

	frame(h, c1, c2);
	while (fl) {
		
		if ( _kbhit() ) {
			
			int ch = _getch();

			switch (ch) {
					case 72: //UP
						clean(h, c1, c2);
						c1.Y -= 4;
						c2.Y -= 4;
						result--;
						if ((c1.Y < 8) && (c2.Y < 13)) {
							c1.Y = 20; c2.Y = 25;
							result = 3;
						}
						frame(h, c1, c2);
						break;
					case 80: //DOWN
						clean(h, c1, c2);
						c1.Y += 4;
						c2.Y += 4;
						result++;
						if ((c1.Y > 20) && (c2.Y > 25)) {
							c1.Y = 8; c2.Y = 13;
							result = 0;
						}
						frame(h, c1, c2);
						break;
					case 13:
						fl = false;
						break;
				}
		
		}
	}

	SetConsoleTextAttribute(h, 11);
	system("cls");
	return result;
}


void frame(HANDLE h, COORD frame_begin, COORD frame_end) {
	COORD t = frame_begin;
	int len_x = frame_end.X - t.X -2;
	int len_y = frame_end.Y - t.Y -2;
	SetConsoleTextAttribute(h, 10);
	SetConsoleCursorPosition(h, frame_begin);
	cout << char(457);
	
	for (int i = 0; i < len_x; i++) {
		cout << char(461);
	}
	
	cout << char(443);
	frame_begin.Y++;
	
	for (int i = 0; i < len_y; i++, frame_begin.Y++) {
		SetConsoleCursorPosition(h, frame_begin);
		cout << char(442);
	}
	
	SetConsoleCursorPosition(h, frame_begin);
	cout << char(456);
	
	for (int i = 0; i < len_x; i++, frame_begin.X++) {
		cout << char(461);
	}
	
	cout << char(444);
	frame_begin.X++;
	frame_begin.Y--;
	SetConsoleCursorPosition(h, frame_begin);
	
	
	for (int i = 0; i < len_y; i++, frame_begin.Y--) {
		SetConsoleCursorPosition(h, frame_begin);
		cout << char(442);
	}
}

void clean(HANDLE h, COORD frame_begin, COORD frame_end) {
	COORD t = frame_begin;
	int len_x = frame_end.X - t.X - 2;
	int len_y = frame_end.Y - t.Y - 2;
	SetConsoleCursorPosition(h, frame_begin);
	cout << " ";

	for (int i = 0; i < len_x; i++) {
		cout << " ";
	}

	cout << " ";
	frame_begin.Y++;

	for (int i = 0; i < len_y; i++, frame_begin.Y++) {
		SetConsoleCursorPosition(h, frame_begin);
		cout << " ";
	}

	SetConsoleCursorPosition(h, frame_begin);
	cout << " ";

	for (int i = 0; i < len_x; i++, frame_begin.X++) {
		cout << " ";
	}

	cout << " ";
	frame_begin.X++;
	frame_begin.Y--;
	SetConsoleCursorPosition(h, frame_begin);


	for (int i = 0; i < len_y; i++, frame_begin.Y--) {
		SetConsoleCursorPosition(h, frame_begin);
		cout << " ";
	}

}

void title() {
	
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD c;
	c.X = 35;
	c.Y = 0;
	SetConsoleCursorPosition(h, c);
	SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	cout << "X     X   X X X X   X     X   X     X" << endl;
	c.Y++;
	SetConsoleCursorPosition(h, c);
	cout << "XX   XX   X         XX    X   X     X" << endl;
	c.Y++;
	SetConsoleCursorPosition(h, c);
	cout << "X X X X   X X X     X X   X   X     X" << endl;
	c.Y++;
	SetConsoleCursorPosition(h, c);
	cout << "X  X  X   X         X  X  X   X     X" << endl;
	c.Y++;
	SetConsoleCursorPosition(h, c);
	cout << "X     X   X         X   X X   X     X" << endl;
	c.Y++;
	SetConsoleCursorPosition(h, c);
	cout << "X     X   X X X X   X    XX    X X X  " << endl;

}

int help() {
	cout << "Use keyboard arrows to move your character" << endl;
	cout << "Press Enter to continue" << endl;
	while (!_kbhit()) {
		if (_getch() == 13) {
			return 4;
		}
	}
}

int about() {
	
	cout << "This programme was created by Frolkin Volodymir from group KA-81" << endl;
	cout << "Press Enter to continue" << endl;
	while (!_kbhit()) {
		if (_getch() == 13) {
			return 4;
		}
	}
}
