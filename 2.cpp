/*
 * Написать игру «Пятнашки».
 *
 */
#include <iostream>
#include <cstdio>
#include <ctime>
using namespace std;

const int sorted[4][4] { { 1, 2, 3, 4 }, { 5, 6, 7, 8 }, { 9, 10, 11, 12 }, {
		13, 14, 15, 0 } };

bool isOnField(int n, int f[4][4]) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (f[i][j] == n)
				return true;
		}
	}
	return false;
}

void generateField(int f[4][4]) {
	srand(time(NULL));
	int n { };
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			do {
				n = rand() % 16 + 1;
			} while (isOnField(n, f));
			f[i][j] = n;
		}
	}
}

void find16(int f[4][4], int &y, int &x) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (f[i][j] == 16) {
				y = i;
				x = j;
				f[i][j] = 0;
				return;
			}
		}
	}
}

void printField(int f[4][4]) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (f[i][j] / 10 == 0) {
				cout << " " << f[i][j];
			} else {
				cout << f[i][j];
			}
			cout << " ";
		}
		cout << endl;
	}
}

void swap(int f[4][4], int i1, int j1, int i2, int j2) {
	int t { };
	t = f[i1][j1];
	f[i1][j1] = f[i2][j2];
	f[i2][j2] = t;
}

bool isSorted(int f[4][4]) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (f[i][j] != sorted[i][j])
				return false;
		}
	}
	return true;
}

void nextMove(int f[4][4], int y, int x) {
	printField(f);
	if (isSorted(f)) {
		cout << "Congratulations, the puzzle is sorted!" << endl;
		return;
	}
	char command { };

	cout << "Enter next move" << endl;
	cout << "Move the zero with wasd, q to quit: ";
	cin >> command;
	switch (command) {
	case 'q':
		return;
	case 'w':
		if (y > 0) {
			swap(f, y, x, y - 1, x);
			y--;
		} else {
			cout << "Illegal move!" << endl;
		}
		break;
	case 'a':
		if (x > 0) {
			swap(f, y, x, y, x - 1);
			x--;
		} else {
			cout << "Illegal move!" << endl;
		}
		break;
	case 's':
		if (y < 3) {
			swap(f, y, x, y + 1, x);
			y++;
		} else {
			cout << "Illegal move!" << endl;
		}

		break;
	case 'd':
		if (x < 3) {
			swap(f, y, x, y, x + 1);
			x++;
		} else {
			cout << "Illegal move!" << endl;
		}

		break;
	default:
		cout << "Wrong command!" << endl;
		break;
	}
	nextMove(f, y, x);
}

int main() {
	int field[4][4] { };
	int y { }, x { };

	generateField(field);
	find16(field, y, x);
	nextMove(field, y, x);
	//printField(field);

	return 0;
}
