/*
 * Написать игру «Крестики-нолики».
 * */
#include <iostream>
using namespace std;
void moveX(char f[3][3]);
void move0(char f[3][3]);

void printField(char f[3][3]) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (!f[i][j]) {
				cout << ". ";
			} else {
				cout << f[i][j] << " ";
			}
		}
		cout << endl;
	}
}

bool fieldFull(char f[3][3]) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (!f[i][j])
				return false;
		}
	}
	return true;
}

bool winX(char f[3][3]) {
	char t { 'X' };
	return ((f[0][0] == t && f[0][1] == t && f[0][2] == t)
			|| (f[1][0] == t && f[1][1] == t && f[1][2] == t)
			|| (f[2][0] == t && f[2][1] == t && f[2][2] == t)
			|| (f[0][0] == t && f[1][0] == t && f[2][0] == t)
			|| (f[0][1] == t && f[1][1] == t && f[2][1] == t)
			|| (f[0][2] == t && f[1][2] == t && f[2][2] == t)
			|| (f[0][0] == t && f[1][1] == t && f[2][2] == t)
			|| (f[0][2] == t && f[1][1] == t && f[2][0] == t));
}

bool win0(char f[3][3]) {
	char t { '0' };
	return ((f[0][0] == t && f[0][1] == t && f[0][2] == t)
			|| (f[1][0] == t && f[1][1] == t && f[1][2] == t)
			|| (f[2][0] == t && f[2][1] == t && f[2][2] == t)
			|| (f[0][0] == t && f[1][0] == t && f[2][0] == t)
			|| (f[0][1] == t && f[1][1] == t && f[2][1] == t)
			|| (f[0][2] == t && f[1][2] == t && f[2][2] == t)
			|| (f[0][0] == t && f[1][1] == t && f[2][2] == t)
			|| (f[0][2] == t && f[1][1] == t && f[2][0] == t));
}

bool isLegal(char f[3][3], int i, int j) {
	return (!f[i][j] && i >= 0 && i < 3 && j >= 0 && j < 3);
}

void putX(char f[3][3], int i, int j) {
	f[i][j] = 'X';
}

void put0(char f[3][3], int i, int j) {
	f[i][j] = '0';
}

void moveX(char f[3][3]) {
	if (fieldFull(f)) {
		cout << "Field is full! A draw!" << endl;
		return;
	}
	printField(f);
	int y { }, x { };
	cout << "Enter coordinates where you want to put X (y,x, 0 to 2): ";
	cin >> y >> x;
	if (isLegal(f, y, x)) {
		putX(f, y, x);
		if (winX(f)) {
			printField(f);
			cout << "Xs won!" << endl;
			return;
		}
		move0(f);
	} else {
		cout << "Illegal move!" << endl;
		moveX(f);
	}
}

void move0(char f[3][3]) {
	if (fieldFull(f)) {
		cout << "Field is full! A draw!" << endl;
		return;
	}
	printField(f);
	int y { }, x { };
	cout << "Enter coordinates where you want to put 0 (y,x, 0 to 2): ";
	cin >> y >> x;
	if (isLegal(f, y, x)) {
		put0(f, y, x);
		if (win0(f)) {
			printField(f);
			cout << "0s won!" << endl;
			return;
		}
		moveX(f);
	} else {
		cout << "Illegal move!" << endl;
		move0(f);
	}
}

int main() {
	char field[3][3] { };
	moveX(field);
	return 0;
}
