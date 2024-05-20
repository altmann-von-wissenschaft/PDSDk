#include <Windows.h>
#include <Shlwapi.h>
#include <iostream>
#include <iomanip>
#include <chrono>
#include <thread>
#include <algorithm>

#include "StraightList.hpp"
#include "List.hpp"
#include "SetList.hpp"
#include "Set.hpp"
#include "SetMultiset.hpp"
#include "SetMap.hpp"

#define ROWS          14
#define COLUMNS       7
#define ADDICTIVE_LEN 2
#define DEFAULT_SIZE  0
#define RATIO         2
#define MIN           0

using namespace std;
using namespace std::chrono;

typedef high_resolution_clock timer;

int* generateRandom(int, int, int);
string printLine(int length);
void printTable(string [][COLUMNS], int, int, int[], int);

int main() {
	setlocale(LC_ALL, "rus");
	int columnWidth[COLUMNS] = {25, 25, 20, 15, 15, 15, 15};
	int length = ADDICTIVE_LEN;
	for (int k : columnWidth)
		length += k;
	string data[ROWS][COLUMNS] = {
		{"", "Односвязный список", "Класс \"Список\"",  "List ", "Set", "Multiset ", "Map"},
		{"Создание множества A", "0", "0", "0", "0", "0", "0"},
		{"Создание множества B", "0", "0", "0", "0", "0", "0"},
		{"Мощность A", "0", "0", "0", "0", "0", "0"},
		{"Мощность B", "0", "0", "0", "0", "0", "0"},
		{"Подмножество A-A", "0", "0", "0", "0", "0", "0"},
		{"Подмножество B-A", "0", "0", "0", "0", "0", "0"},
		{"Равенство A-A", "0", "0", "0", "0", "0", "0"},
		{"Равенство B-A", "0", "0", "0", "0", "0", "0"},
		{"Объединение", "0", "0", "0", "0", "0", "0"},
		{"Пересечение", "0", "0", "0", "0", "0", "0"},
		{"Разность A-B", "0", "0", "0", "0", "0", "0"},
		{"Разность A-А", "0", "0", "0", "0", "0", "0"},
		{"Симметричная разность", "0", "0", "0", "0", "0", "0"},
	};
	
	int size_a = DEFAULT_SIZE;
	int size_b = DEFAULT_SIZE;
	std::cout << "Введите мощность множества А: ";
	cin >> size_a;
	std::cout << "Введите мощность множества B: ";
	cin >> size_b;
	std::cout << endl;

	try {
		/* Генерация случайного массива */
		int* A = generateRandom(MIN, RATIO * size_a, size_a);
		int* B = generateRandom(MIN, RATIO * size_b, size_b);
		
		/* Расчеты */
		thread thread1([&](){
			int i = 1, j = 1;
			// Список
			Node * c;
			auto t = timer::now();
			Node * a = InitEmptySet();
			a = CreateNewSet(size_a, A);
			data[i++][j] = to_string((duration_cast<milliseconds>(timer::now() - t)).count());

			t = timer::now();
			Node * b = InitEmptySet();
			b = CreateNewSet(size_b, B);
			data[i++][j] = to_string((duration_cast<milliseconds>(timer::now() - t)).count());

			t = timer::now();
			Length(a);
			data[i++][j] = to_string((duration_cast<microseconds>(timer::now() - t)).count());

			t = timer::now();
			Length(b);
			data[i++][j] = to_string((duration_cast<microseconds>(timer::now() - t)).count());

			t = timer::now();
			IsSub(a, a);
			data[i++][j] = to_string((duration_cast<milliseconds>(timer::now() - t)).count());

			t = timer::now();
			IsSub(b, a);
			data[i++][j] = to_string((duration_cast<milliseconds>(timer::now() - t)).count());

			t = timer::now();
			IsEqu(a, a);
			data[i++][j] = to_string((duration_cast<milliseconds>(timer::now() - t)).count());

			t = timer::now();
			IsEqu(b, a);
			data[i++][j] = to_string((duration_cast<milliseconds>(timer::now() - t)).count());

			t = timer::now();
			c = Unite(a, b);
			data[i++][j] = to_string((duration_cast<milliseconds>(timer::now() - t)).count());
			ClearSet(c);

			t = timer::now();
			c = CommonElements(a, b);
			data[i++][j] = to_string((duration_cast<milliseconds>(timer::now() - t)).count());
			ClearSet(c);

			t = timer::now();
			c = Substraction(a, b);
			data[i++][j] = to_string((duration_cast<milliseconds>(timer::now() - t)).count());
			ClearSet(c);

			t = timer::now();
			c = Substraction(a, a);
			data[i++][j] = to_string((duration_cast<milliseconds>(timer::now() - t)).count());
			ClearSet(c);

			t = timer::now();
			c = SimmetricalSub(a, b);
			data[i++][j] = to_string((duration_cast<milliseconds>(timer::now() - t)).count());
			ClearSet(c);
			});
		thread thread2([&]() {
			int i = 1, j = 2;
			// Класс "Список"
			auto t = timer::now();
			List a;
			a.fillRandom(size_a, A);
			data[i++][j] = to_string((duration_cast<milliseconds>(timer::now() - t)).count());

			t = timer::now();
			List b;
			b.fillRandom(size_b, B);
			data[i++][j] = to_string((duration_cast<milliseconds>(timer::now() - t)).count());

			t = timer::now();
			a.length();
			data[i++][j] = to_string((duration_cast<microseconds>(timer::now() - t)).count());

			t = timer::now();
			b.length();
			data[i++][j] = to_string((duration_cast<microseconds>(timer::now() - t)).count());

			t = timer::now();
			a.isSubset(a);
			data[i++][j] = to_string((duration_cast<milliseconds>(timer::now() - t)).count());

			t = timer::now();
			b.isSubset(a);
			data[i++][j] = to_string((duration_cast<milliseconds>(timer::now() - t)).count());

			t = timer::now();
			a.isEqual(a);
			data[i++][j] = to_string((duration_cast<milliseconds>(timer::now() - t)).count());

			t = timer::now();
			b.isEqual(a);
			data[i++][j] = to_string((duration_cast<milliseconds>(timer::now() - t)).count());

			t = timer::now();
			List::unite(a, b);
			data[i++][j] = to_string((duration_cast<milliseconds>(timer::now() - t)).count());

			t = timer::now();
			List::cross(a, b);
			data[i++][j] = to_string((duration_cast<milliseconds>(timer::now() - t)).count());

			t = timer::now();
			List::substraction(a, b);
			data[i++][j] = to_string((duration_cast<milliseconds>(timer::now() - t)).count());

			t = timer::now();
			List::substraction(a, a);
			data[i++][j] = to_string((duration_cast<milliseconds>(timer::now() - t)).count());

			t = timer::now();
			List::simmetricalSub(a, b);
			data[i++][j] = to_string((duration_cast<milliseconds>(timer::now() - t)).count());
		});

		SetList a;
		SetList b;
		
		thread thread31([&]() {
			int i = 1, j = 3;
			// List
			auto t = timer::now();
			a.fillRandom(size_a, A);
			data[i++][j] = to_string((duration_cast<milliseconds>(timer::now() - t)).count());
			});
		thread thread32([&]() {
			int i = 2, j = 3;
			// List
			auto t = timer::now();
			b.fillRandom(size_b, B);
			data[i++][j] = to_string((duration_cast<milliseconds>(timer::now() - t)).count());
			});
		thread thread3([&]() {
			thread31.join();
			thread32.join();
			
			int i = 3, j = 3;
			auto t = timer::now();
			a.length();
			data[i++][j] = to_string((duration_cast<microseconds>(timer::now() - t)).count());

			t = timer::now();
			b.length();
			data[i++][j] = to_string((duration_cast<microseconds>(timer::now() - t)).count());

			t = timer::now();
			a.isSubset(a);
			data[i++][j] = to_string((duration_cast<milliseconds>(timer::now() - t)).count());

			t = timer::now();
			b.isSubset(a);
			data[i++][j] = to_string((duration_cast<milliseconds>(timer::now() - t)).count());

			t = timer::now();
			a.isEqual(a);
			data[i++][j] = to_string((duration_cast<milliseconds>(timer::now() - t)).count());

			t = timer::now();
			b.isEqual(a);
			data[i++][j] = to_string((duration_cast<milliseconds>(timer::now() - t)).count());

			t = timer::now();
			SetList::unite(a, b);
			data[i++][j] = to_string((duration_cast<milliseconds>(timer::now() - t)).count());

			t = timer::now();
			SetList::cross(a, b);
			data[i++][j] = to_string((duration_cast<milliseconds>(timer::now() - t)).count());

			t = timer::now();
			SetList::substraction(a, b);
			data[i++][j] = to_string((duration_cast<milliseconds>(timer::now() - t)).count());

			t = timer::now();
			SetList::substraction(a, a);
			data[i++][j] = to_string((duration_cast<milliseconds>(timer::now() - t)).count());

			t = timer::now();
			SetList::simmetricalSub(a, b);
			data[i++][j] = to_string((duration_cast<milliseconds>(timer::now() - t)).count());
			});
		
		thread thread4([&]() {
			int i = 1, j = 4;
			// Set
			auto t = timer::now();
			Set a;
			a.fillRandom(size_a, A);
			data[i++][j] = to_string((duration_cast<milliseconds>(timer::now() - t)).count());

			t = timer::now();
			Set b;
			b.fillRandom(size_b, B);
			data[i++][j] = to_string((duration_cast<milliseconds>(timer::now() - t)).count());

			t = timer::now();
			a.length();
			data[i++][j] = to_string((duration_cast<microseconds>(timer::now() - t)).count());

			t = timer::now();
			b.length();
			data[i++][j] = to_string((duration_cast<microseconds>(timer::now() - t)).count());

			t = timer::now();
			a.isSubset(a);
			data[i++][j] = to_string((duration_cast<milliseconds>(timer::now() - t)).count());

			t = timer::now();
			b.isSubset(a);
			data[i++][j] = to_string((duration_cast<milliseconds>(timer::now() - t)).count());

			t = timer::now();
			a.isEqual(a);
			data[i++][j] = to_string((duration_cast<milliseconds>(timer::now() - t)).count());

			t = timer::now();
			b.isEqual(a);
			data[i++][j] = to_string((duration_cast<milliseconds>(timer::now() - t)).count());

			t = timer::now();
			Set::unite(a, b);
			data[i++][j] = to_string((duration_cast<milliseconds>(timer::now() - t)).count());

			t = timer::now();
			Set::cross(a, b);
			data[i++][j] = to_string((duration_cast<milliseconds>(timer::now() - t)).count());

			t = timer::now();
			Set::substraction(a, b);
			data[i++][j] = to_string((duration_cast<milliseconds>(timer::now() - t)).count());

			t = timer::now();
			Set::substraction(a, a);
			data[i++][j] = to_string((duration_cast<milliseconds>(timer::now() - t)).count());

			t = timer::now();
			Set::simmetricalSub(a, b);
			data[i++][j] = to_string((duration_cast<milliseconds>(timer::now() - t)).count());
		});
		thread thread5([&]() {
			int i = 1, j = 5;
			// Multiset
			auto t = timer::now();
			SetMultiset a;
			a.fillRandom(size_a, A);
			data[i++][j] = to_string((duration_cast<milliseconds>(timer::now() - t)).count());

			t = timer::now();
			SetMultiset b;
			b.fillRandom(size_b, B);
			data[i++][j] = to_string((duration_cast<milliseconds>(timer::now() - t)).count());

			t = timer::now();
			a.length();
			data[i++][j] = to_string((duration_cast<microseconds>(timer::now() - t)).count());

			t = timer::now();
			b.length();
			data[i++][j] = to_string((duration_cast<microseconds>(timer::now() - t)).count());

			t = timer::now();
			a.isSubset(a);
			data[i++][j] = to_string((duration_cast<milliseconds>(timer::now() - t)).count());

			t = timer::now();
			b.isSubset(a);
			data[i++][j] = to_string((duration_cast<milliseconds>(timer::now() - t)).count());

			t = timer::now();
			a.isEqual(a);
			data[i++][j] = to_string((duration_cast<milliseconds>(timer::now() - t)).count());

			t = timer::now();
			b.isEqual(a);
			data[i++][j] = to_string((duration_cast<milliseconds>(timer::now() - t)).count());

			t = timer::now();
			SetMultiset::unite(a, b);
			data[i++][j] = to_string((duration_cast<milliseconds>(timer::now() - t)).count());

			t = timer::now();
			SetMultiset::cross(a, b);
			data[i++][j] = to_string((duration_cast<milliseconds>(timer::now() - t)).count());

			t = timer::now();
			SetMultiset::substraction(a, b);
			data[i++][j] = to_string((duration_cast<milliseconds>(timer::now() - t)).count());

			t = timer::now();
			SetMultiset::substraction(a, a);
			data[i++][j] = to_string((duration_cast<milliseconds>(timer::now() - t)).count());

			t = timer::now();
			SetMultiset::simmetricalSub(a, b);
			data[i++][j] = to_string((duration_cast<milliseconds>(timer::now() - t)).count());
			});
		thread thread6([&]() {
			int i = 1, j = 6;
			// Map
			auto t = timer::now();
			SetMap a;
			a.fillRandom(size_a, A);
			data[i++][j] = to_string((duration_cast<milliseconds>(timer::now() - t)).count());

			t = timer::now();
			SetMap b;
			b.fillRandom(size_b, B);
			data[i++][j] = to_string((duration_cast<milliseconds>(timer::now() - t)).count());

			t = timer::now();
			a.length();
			data[i++][j] = to_string((duration_cast<microseconds>(timer::now() - t)).count());

			t = timer::now();
			b.length();
			data[i++][j] = to_string((duration_cast<microseconds>(timer::now() - t)).count());

			t = timer::now();
			a.isSubset(a);
			data[i++][j] = to_string((duration_cast<milliseconds>(timer::now() - t)).count());

			t = timer::now();
			b.isSubset(a);
			data[i++][j] = to_string((duration_cast<milliseconds>(timer::now() - t)).count());

			t = timer::now();
			a.isEqual(a);
			data[i++][j] = to_string((duration_cast<milliseconds>(timer::now() - t)).count());

			t = timer::now();
			b.isEqual(a);
			data[i++][j] = to_string((duration_cast<milliseconds>(timer::now() - t)).count());

			t = timer::now();
			SetMap::unite(a, b);
			data[i++][j] = to_string((duration_cast<milliseconds>(timer::now() - t)).count());

			t = timer::now();
			SetMap::cross(a, b);
			data[i++][j] = to_string((duration_cast<milliseconds>(timer::now() - t)).count());

			t = timer::now();
			SetMap::substraction(a, b);
			data[i++][j] = to_string((duration_cast<milliseconds>(timer::now() - t)).count());

			t = timer::now();
			SetMap::substraction(a, a);
			data[i++][j] = to_string((duration_cast<milliseconds>(timer::now() - t)).count());

			t = timer::now();
			SetMap::simmetricalSub(a, b);
			data[i++][j] = to_string((duration_cast<milliseconds>(timer::now() - t)).count());
		});

		thread1.join();
		thread2.join();
		thread3.join();
		thread4.join();
		thread5.join();
		thread6.join();

		/* Вывод */
		std::cout << printLine(length) << endl;
		printTable(data, ROWS, COLUMNS, columnWidth, length);

		delete A;
		delete B;
	}
	catch (exception exc) {
		MessageBoxA(nullptr, exc.what(), "Ошибка", MB_OK);
		return EXIT_FAILURE;
	}
	
	return EXIT_SUCCESS;
}


/* ---- Вспомогательные функции --- */

int* generateRandom(int min, int max, int size) {
	if (size < 0)
		throw exception("Некорректный размер");

	if (max < min)
		throw exception("Некорректные границы");

	srand(time(nullptr)); // Сид
	int* result = new int[size];
	int i = 0;
	while (i < size) {
		int generated = rand() % (max - min + 1) + min;
		if (find(result, result + size, generated) == result + size)
		{
			result[i] = generated;
			i++;
		}
	}
	return result;
}

string printLine(int length) {
	string line = "";
	for (int i{}; i < length; i++)
		line += '-';
	return line;
}

void printTable(string data[][COLUMNS], int dataRows, int dataColumns, int columnWidth[] , int lengthOfLine) {
	for (int i{}; i < dataRows; i++) {
		for (int j{}; j < dataColumns; j++) {
			std::cout << left << setw(columnWidth[j]) << "| " + data[i][j];
		}
		std::cout << " |" << endl;
		std::cout << printLine(lengthOfLine) << endl;
	}
}

/* ------------------------------- */
