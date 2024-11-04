#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <thread>
#include <chrono>
using namespace std;

void setConsoleColor(int color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

bool is_in_place(int* field, int index) {
	int raw = index / 9;
	int column = index % 9;
	int num = field[index];
	int temp = 0;
	for (int i = 0; i < 9; i++) {
		if (field[raw * 9 + i] == num and column != i) {
			temp++;
			
		}
	}
	for (int j = 0; j < 9; j++) {
		if (field[j * 9 + column] == num and raw != j){
			temp++;
		}
	}
	int temp_raw = (raw / 3) * 3 + 1;
	int temp_column = (column / 3) * 3 + 1;
	for (int a = temp_raw - 1; a < temp_raw + 2; a++) {
		for (int b = temp_column - 1; b < temp_column + 2; b++) {
			int temp_index = a * 9 + b;
			if (field[temp_index] == num and (raw != a and column != b)){
				temp++;
			}
		}
	}
	if (temp == 0) {
		return true;
	}
	return false;
}

void colorize(int* field, int* colors) {
	for (int i = 0; i < 81; i++) {
		if (field[i] == 0) {
			colors[i] = 2;
		}
		else {
			colors[i] = 15;
		}
	}
}

void print(int* input, int* colors){
	cout << "+-------+-------+-------+" << endl << "| ";
	for (int i = 0; i < 81; i++) {
		if (input[i] != 0) {
			setConsoleColor(colors[i]);
			cout << input[i] << " ";
			setConsoleColor(15);
		}
		else {
			cout << "  ";
		}
		if ((i + 1) % 27 == 0) {
			cout << "|" << endl << "+-------+-------+-------+";
			if (i != 80) {
				cout << endl << "| ";
			}
		} else if ((i + 1) % 9 == 0) {
			cout << "|" << endl << "| ";
		}else if ((i + 1) % 3 == 0) {
			cout << "| ";
		}
	}
}

void updateConsoleContent(int* field, int* colors) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD cursorPosition = { 0, 0 };
	SetConsoleCursorPosition(hConsole, cursorPosition);
	print(field, colors);
}

/*
					      { 0, 0, 0, 0, 0, 0, 0, 0, 0,
						0, 0, 0, 0, 0, 0, 0, 0, 0,
						0, 0, 0, 0, 0, 0, 0, 0, 0,
						0, 0, 0, 0, 0, 0, 0, 0, 0,
						0, 0, 0, 0, 0, 0, 0, 0, 0,
						0, 0, 0, 0, 0, 0, 0, 0, 0,
						0, 0, 0, 0, 0, 0, 0, 0, 0,
						0, 0, 0, 0, 0, 0, 0, 0, 0,
						0, 0, 0, 0, 0, 0, 0, 0, 0 }
*/

int main() {
	const int size = 81;
	int field[size] = { 0, 0, 9, 0, 0, 0, 6, 1, 3,
						0, 0, 0, 0, 0, 0, 2, 0, 0,
						0, 7, 2, 5, 3, 1, 0, 8, 0,
						3, 0, 6, 0, 0, 0, 0, 0, 0,
						1, 5, 7, 0, 0, 6, 8, 0, 2,
						2, 8, 0, 7, 0, 0, 1, 0, 0,
						0, 1, 5, 9, 6, 0, 0, 0, 0,
						0, 6, 0, 1, 0, 5, 4, 2, 0,
						9, 2, 0, 3, 0, 0, 5, 6, 1 };
	int colors[size];
	colorize(field, colors);
	int cursor = 0;
	string tmp = "w";
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(hConsole, &cursorInfo);
	cursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(hConsole, &cursorInfo);
	while (true) {
		updateConsoleContent(field, colors);
		this_thread::sleep_for(std::chrono::nanoseconds(1));
		if (cursor == 81) {
			cout << endl;
			break;
		}
		if (colors[cursor] == 2) {
			if (field[cursor] == 9) {
				field[cursor] = 0;
				cursor--;
				tmp = "s";
				continue;
			} else {
				field[cursor]++;
				if (is_in_place(field, cursor)) {
					cursor++;
					tmp = "w";
					continue;
				}
			}
		}
		else {
			if (tmp == "w") {
				cursor++;
			}
			else if (tmp == "s"){
				if (cursor == 0) {
					cout << "Incorrect Sudoku" << endl;
					break;
				}
				cursor--;
			}
		}
	}
}
