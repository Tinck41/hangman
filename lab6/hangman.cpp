#include <iostream>
#include <fstream>
#include <clocale>
#include <time.h>
#include <string>
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
using namespace std;

bool check(char* word, char ch, char* displayWord, bool& win, int& suc) {
	int right = 0, len = strlen(word);
	for (int i = 0; i < len; i++) {
		if (ch == word[i]) {
			right = 1;
			displayWord[i] = ch;
		}
	}

	int lenMinus = 0;
	for (int i = 0; i < len; i++) {
		if (displayWord[i] == '-') {
			lenMinus++;
		}
	}

	if (lenMinus == 0) {
		win = true;
	}

	if (right)
		return true;
	else
		return false;
}


char UpCase(char c) {
	if (c >= 'А' && c <= 'Я')
		c += 32;
	return c;
}

void print(string partOfHank, int k) {
	for (int i = 0; i < k; i++)
		partOfHank = " " + partOfHank;
	cout << partOfHank.c_str() << "\n";
}

void PrintHank(int k) {
	if (k == 0) {
		for (int i = 0; i < 7; i++)
			print("", 4);
	}
	if (k >= 1) {
		print("|", 4);
		if (k == 1)
			for (int i = 0; i < 6; i++)
				print("", 4);
	}
	if (k >= 2) {
		print("|", 4);
		if (k == 2)
			for (int i = 0; i < 5; i++)
				print("", 4);
	}
	if (k >= 3) {
		print("|", 4);
		if (k == 3)
			for (int i = 0; i < 4; i++)
				print("", 4);
	}
	if (k >= 4) {
		print("0", 4);
		if (k == 4)
			for (int i = 0; i < 3; i++)
				print("", 4);
	}
	if (k == 5) {
		print("/", 3);
		if (k == 5)
			for (int i = 0; i < 2; i++)
				print("", 4);
	}
	if (k == 6) {
		print("/|", 3);
		if (k == 6)
			for (int i = 0; i < 2; i++)
				print("", 4);
	}
	if (k >= 7) {
		print("/|\\", 3);
		if (k == 7)
			for (int i = 0; i < 2; i++)
				print("", 4);
	}
	if (k == 8) {
		print("/", 3);
		if (k == 8)
			for (int i = 0; i < 1; i++)
				print("", 4);
	}
	if (k >= 9) {
		print("/ \\", 3);
		if (k == 9)
			for (int i = 0; i < 1; i++)
				print("", 4);
	}
}

void chooseWord(char* buffer, char* displayWord) {

	int n = rand() % 1000 + 1;
	ifstream file("dictionary.txt");
	
	for (int i = 0; i < n; i++) 
		file >> buffer;
	file.close();

	int len = strlen(buffer);

	for (int i = 0; i < len; i++) {
		displayWord[i] = '-';
	}

	displayWord[len] = 0;
}

int main() {
	PlaySound(TEXT("1.wav"), NULL, SND_FILENAME | SND_ASYNC|SND_LOOP);
	system("pause");
	system("cls");
	HANDLE hwnd = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hwnd, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	srand(time(0));
	int attempts = 9;
	char word[50], displayWord[50];
	bool win = false;
	char ch;
	int wrong = 0, suc=0;
	chooseWord(word, displayWord);
	setlocale(LC_ALL, "Ru");
	while (!win) {
		PrintHank(wrong);
		cout << "Угадайте слово:\n";
		cout << displayWord << "\n";
		cout << "У вас " << attempts << " попыток\n";
		cin >> ch;
		ch = UpCase(ch);
		if (check(word, ch, displayWord, win, suc) == false) {
			wrong++;
			attempts--;
		}
		if (attempts == 0) {
			PlaySound(TEXT("lose.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
			cout << "YOU LOSE\n";
			system("pause");
			return 0;
		}
		if (!win)
			system("cls");
	}
	cout << displayWord << "\n";
	PlaySound(TEXT("win.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	cout << "YOU WIN\n";
	system("pause");
	return 0;
}
