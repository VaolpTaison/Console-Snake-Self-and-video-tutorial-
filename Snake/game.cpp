#include <iostream>
#include <conio.h> // для обработки нажатий
#include <Windows.h> // для замедление игры 
					//(без этой библиотеки и ф-ии Sleep змейка двигается очень быстро)

using namespace std;

bool gameOver;
const int width = 20; // длина поля
const int height = 20; // ширина поля
int x, y, fruitX, fruitY, score; // координаты змейки(x, y), фрукта(fruitX, fruitY), очки(score)
int tailX[100], tailY[100]; // координаты хвоста
int nTail; // количество съеденных фруктов
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;


void Setup() { // вызов функции в начале игры
	gameOver = false; // по умолчанию мы не проиграли
	dir = STOP; // в начале игры змейка стоит на месте...
	x = width / 2 - 1; // ...в середине карты
	y = height / 2 - 1; // ...в середине карты
	fruitX = rand() % width; // рандомное появление фрукта для змейки
	fruitY = rand() % height; // рандомное появление фрукта для змейки 
	score = 0;
}

void Draw() { // функция рисование
	system("cls"); // использование system в linux: system("clear")
	for (int i = 0; i < width + 1; i++) // прорисовка верхней границы
		cout << "#";
	cout << endl;

	for (int i = 0; i < height; i++) { // прорисовка боковых границ
		for (int j = 0; j < width; j++) {
			if (j == 0 || j == width - 1) // условие прорисовки границ
				cout << "#";
			if (i == y && j == x) // условие появление змейки
				cout << "0";
			else if (i == fruitY && j == fruitX)
				cout << "f";
			else {
				bool print = false;
				for (int k = 0; k < nTail; k++) {
					if (tailX[k] == j && tailY[k] == i) {
						print = true;
						cout << "o";
					}
				}
				if (!print)
					cout << " ";
			}
				
		}
		cout << endl;
	}

	for (int i = 0; i < width + 1; i++) // прорисовка нижней границы
		cout << "#";
	cout << endl;
	cout << "Score: " << score << endl;

}

void Input() { // отслеживание нажатий от ползователя (управление змейкой)
	if (_kbhit()) {
		switch (_getch()) // отслеживание нажатий
		{
		case 'a': // нажатие на "A" влево
			dir = LEFT;
			break;
		case 'd': // нажатие на "D" вправо
			dir = RIGHT;
			break;
		case 'w': // нажатие на "W" вверх
			dir = UP;
			break;
		case 's': // нажатие на "S" вниз
			dir = DOWN;
			break;
		case 'x': // нажатие на "X" завершает игру
			gameOver = true;
			break;
		}
	}
}

void Logic() { // вся логика игры
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1; i < nTail; i++) { // хвост змейки
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}
	switch (dir) // обработка движения змейки
	{
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	}

	// с границами
	//if (x > width || x < 0 || x > height || y < 0) // условие выхода змейки за границы карты
	//	gameOver = true; // игра окончена
	// --------

	// без границ
	if (x >= width)
		x = 0;
	else if (x < 0)
		x = width - 1;
	if (y >= height)
		y = 0;
	else if (y < 0)
		y = height - 1;
	// --------


	for (int i = 0; i < nTail; i++) {
		if (tailX[i] == x && tailY[i] == y) // условие удара змейки об свой хвост
			gameOver == true; // игра окончена
	}

	if (x == fruitX && y == fruitY) { // условие поедание змейкой фрукта
		score += 10;
		fruitX = rand() % width; // рандомное появление фрукта после поедание змейкой
		fruitY = rand() % height; // рандомное появление фрукта после поедания змейкой 
		nTail++;
	}
}

int main() {
	Setup();
	while (!gameOver) {
		Draw();
		Input();
		Logic();
		Sleep(230); //Задержка в мс
	}


	return 0;
}