/*
 *  Дана шахматная доска размером 8×8 и шахмат-
 ный конь. Программа должна запросить у пользователя
 координаты клетки поля и поставить туда коня. Задача
 программы найти и вывести путь коня, при котором он
 обойдет все клетки доски, становясь в каждую клетку
 только один раз. (Так как процесс отыскания пути для
 разных начальных клеток может затянуться, то реко-
 мендуется сначала опробовать задачу на поле размером
 6×6). В программе необходимо использовать рекурсию.
 *
 *Мои комментарии:
 Несмотря на то, в задаче речь о шахматных фигурах, задача о пути коня
 не относится к шахматам. Это задача из теории графов, её суть в том,
 чтобы найти Гамильтонов путь по связному графу из произвольной его вершины.
 В качестве вершин здесь выступают клетки поля, а в качестве рёбер —
 легальные ходы коня из каждой клетки.

 Для решения этой задачи я использовал так называемый алгоритм Варнсдорфа
 нахождения Гамильтонова пути. Суть его в том, чтобы каждый раз для следующего
 хода выбирать из связанных вершин вершину с наименьшей доступностью, то
 есть с наименьшим числом связанных вершин, которые мы ещё не посетили.
 Немного об использовании алгоритма Варнсдорфа для решения задачи о пути
 коня можно почитать здесь:
 https://www.geeksforgeeks.org/warnsdorffs-algorithm-knights-tour-problem/

 Моя программа принимает координаты начальной клетки и выводит путь в
 виде поля, в каждую клетку которого записан номер хода, на котором
 её посетил конь, или же сообщает что решения нет (для поля 6х6 или 8х8
 решение находится всегда).
 */
#include <iostream>
using namespace std;
#define SIZE 8
const int knightMoves[8][2] { { 2, 1 }, { 1, 2 }, { -1, 2 }, { 2, -1 },
		{ 1, -2 }, { -2, 1 }, { -1, -2 }, { -2, -1 } };

template<typename T>
void printMatrix(T m[SIZE][SIZE]) {
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++)
			cout << m[j][i] << " ";
		cout << endl;
	}
}

template<typename T>
bool isValid(T m[SIZE][SIZE], int i, int j) {
	return (i >= 0 && i < SIZE && j >= 0 && j < SIZE && !m[i][j]);
}

template<typename T>
int acessibility(T m[SIZE][SIZE], int i, int j) {
	int r { };
	for (int move = 0; move < 8; move++)
		r += isValid(m, i + knightMoves[move][0], j + knightMoves[move][1]);
	return r;
}

template<typename T>
int nextMove(T m[SIZE][SIZE], int i, int j, int n = 1) {
	if (n == SIZE * SIZE) {
		m[i][j] = n;
		return 0;
	}
	m[i][j] = n;
	int nexti { -1 }, nextj { -1 }, minacc { 9 };
	for (int move = 0; move < 8; move++) {
		if (isValid(m, i + knightMoves[move][0], j + knightMoves[move][1])
				&& acessibility(m, i + knightMoves[move][0],
						j + knightMoves[move][1]) < minacc) {
			minacc = acessibility(m, i + knightMoves[move][0],
					j + knightMoves[move][1]);
			nexti = i + knightMoves[move][0];
			nextj = j + knightMoves[move][1];
		}
	}
	if (nexti == -1 || nextj == -1) {
		return 1;
	}
	return nextMove(m, nexti, nextj, n + 1);
}

int main() {
	int field[SIZE][SIZE] { };
	int x { }, y { }, result { };
	do {
		cout
				<< "Enter initial position of the knight on the board (x,y from 0 to "
				<< SIZE - 1 << ")" << endl;
		cin >> x;
		cin >> y;
		if (!isValid(field, x, y))
			cout << "Invalid initial position!" << endl;
	} while (!isValid(field, x, y));
	result = nextMove(field, x, y, 1);

	if (result == 0) {
		printMatrix(field);
	} else {
		cout << "There's no solution";
	}

	return 0;
}
