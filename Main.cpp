#include <iostream>
#include <iomanip>
#include <chrono>

#include "StraightList.hpp"
#include "List.hpp"
#include "SetList.hpp"
#include "Set.hpp"
#include "SetMultiset.hpp"
#include "SetMap.hpp"

#define ROWS          11
#define COLUMNS       7
#define ADDICTIVE_LEN 2
#define DEFAULT_SIZE  0
#define MIN           0

using namespace std;
using namespace std::chrono;

typedef high_resolution_clock timer;

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
		{"Создание множества", "0", "0", "0", "0", "0", "0"},
		{"Мощность", "0", "0", "0", "0", "0", "0"},
		{"Подмножество A-A", "0", "0", "0", "0", "0", "0"},
		{"Подмножество B-A", "0", "0", "0", "0", "0", "0"},
		{"Равенство A-A", "0", "0", "0", "0", "0", "0"},
		{"Равенство B-A", "0", "0", "0", "0", "0", "0"},
		{"Объединение", "0", "0", "0", "0", "0", "0"},
		{"Пересечение", "0", "0", "0", "0", "0", "0"},
		{"Разность A-B", "0", "0", "0", "0", "0", "0"},
		{"Симметричная разность", "0", "0", "0", "0", "0", "0"},
	};
	
	int size = DEFAULT_SIZE;
	cout << "Введите мощность множеств: ";
	cin >> size;
	cout << endl;

	/* Расчеты */
	{
		// Список
		Node* c;
		auto t = timer::now();
		Node* a = InitEmptySet();
		a = CreateNewSet(size, MIN, 10 * size);
		data[1][1] = to_string((duration_cast<milliseconds>(timer::now() - t)).count());

		Node* b = InitEmptySet();
		b = CreateNewSet(size, MIN, 10 * size);

		t = timer::now();
		Length(a);
		data[2][1] = to_string((duration_cast<milliseconds>(timer::now() - t)).count());

		t = timer::now();
		IsSub(a, a);
		data[3][1] = to_string((duration_cast<milliseconds>(timer::now() - t)).count());

		t = timer::now();
		IsSub(b, a);
		data[4][1] = to_string((duration_cast<milliseconds>(timer::now() - t)).count());

		t = timer::now();
		IsEqu(a, a);
		data[5][1] = to_string((duration_cast<milliseconds>(timer::now() - t)).count());

		t = timer::now();
		IsEqu(b, a);
		data[6][1] = to_string((duration_cast<milliseconds>(timer::now() - t)).count());

		t = timer::now();
		c = Unite(a, b);
		data[7][1] = to_string((duration_cast<milliseconds>(timer::now() - t)).count());
		ClearSet(c);

		t = timer::now();
		c = CommonElements(a, b);
		data[8][1] = to_string((duration_cast<milliseconds>(timer::now() - t)).count());
		ClearSet(c);

		t = timer::now();
		c = Substraction(a, b);
		data[9][1] = to_string((duration_cast<milliseconds>(timer::now() - t)).count());
		ClearSet(c);

		t = timer::now();
		c = SimmetricalSub(a, b);
		data[10][1] = to_string((duration_cast<milliseconds>(timer::now() - t)).count());
		ClearSet(c);
	}
	{
		// Класс "Список"
		auto t = timer::now();
		List a;
		a.fillRandom(size, MIN, 10 * size);
		data[1][2] = to_string((duration_cast<milliseconds>(timer::now() - t)).count());

		List b;
		b.fillRandom(size, MIN, 10 * size);

		t = timer::now();
		a.length();
		data[2][2] = to_string((duration_cast<milliseconds>(timer::now() - t)).count());

		t = timer::now();
		a.isSubset(a);
		data[3][2] = to_string((duration_cast<milliseconds>(timer::now() - t)).count());

		t = timer::now();
		b.isSubset(a);
		data[4][2] = to_string((duration_cast<milliseconds>(timer::now() - t)).count());

		t = timer::now();
		a.isEqual(a);
		data[5][2] = to_string((duration_cast<milliseconds>(timer::now() - t)).count());

		t = timer::now();
		b.isEqual(a);
		data[6][2] = to_string((duration_cast<milliseconds>(timer::now() - t)).count());

		t = timer::now();
		List::unite(a, b);
		data[7][2] = to_string((duration_cast<milliseconds>(timer::now() - t)).count());

		t = timer::now();
		List::cross(a, b);
		data[8][2] = to_string((duration_cast<milliseconds>(timer::now() - t)).count());

		t = timer::now();
		List::substraction(a, b);
		data[9][2] = to_string((duration_cast<milliseconds>(timer::now() - t)).count());

		t = timer::now();
		List::simmetricalSub(a, b);
		data[10][2] = to_string((duration_cast<milliseconds>(timer::now() - t)).count());
	}
	{
		// List
		auto t = timer::now();
		SetList a;
		a.fillRandom(size, MIN, 10 * size);
		data[1][3] = to_string((duration_cast<milliseconds>(timer::now() - t)).count());

		SetList b;
		b.fillRandom(size, MIN, 10 * size);

		t = timer::now();
		a.length();
		data[2][3] = to_string((duration_cast<milliseconds>(timer::now() - t)).count());

		t = timer::now();
		a.isSubset(a);
		data[3][3] = to_string((duration_cast<milliseconds>(timer::now() - t)).count());

		t = timer::now();
		b.isSubset(a);
		data[4][3] = to_string((duration_cast<milliseconds>(timer::now() - t)).count());

		t = timer::now();
		a.isEqual(a);
		data[5][3] = to_string((duration_cast<milliseconds>(timer::now() - t)).count());

		t = timer::now();
		b.isEqual(a);
		data[6][3] = to_string((duration_cast<milliseconds>(timer::now() - t)).count());

		t = timer::now();
		SetList::unite(a, b);
		data[7][3] = to_string((duration_cast<milliseconds>(timer::now() - t)).count());

		t = timer::now();
		SetList::cross(a, b);
		data[8][3] = to_string((duration_cast<milliseconds>(timer::now() - t)).count());

		t = timer::now();
		SetList::substraction(a, b);
		data[9][3] = to_string((duration_cast<milliseconds>(timer::now() - t)).count());

		t = timer::now();
		SetList::simmetricalSub(a, b);
		data[10][3] = to_string((duration_cast<milliseconds>(timer::now() - t)).count());
	}
	{
		// Set
		auto t = timer::now();
		Set a;
		a.fillRandom(size, MIN, 10 * size);
		data[1][4] = to_string((duration_cast<milliseconds>(timer::now() - t)).count());

		Set b;
		b.fillRandom(size, MIN, 10 * size);

		t = timer::now();
		a.length();
		data[2][4] = to_string((duration_cast<milliseconds>(timer::now() - t)).count());

		t = timer::now();
		a.isSubset(a);
		data[3][4] = to_string((duration_cast<milliseconds>(timer::now() - t)).count());

		t = timer::now();
		b.isSubset(a);
		data[4][4] = to_string((duration_cast<milliseconds>(timer::now() - t)).count());

		t = timer::now();
		a.isEqual(a);
		data[5][4] = to_string((duration_cast<milliseconds>(timer::now() - t)).count());

		t = timer::now();
		b.isEqual(a);
		data[6][4] = to_string((duration_cast<milliseconds>(timer::now() - t)).count());

		t = timer::now();
		Set::unite(a, b);
		data[7][4] = to_string((duration_cast<milliseconds>(timer::now() - t)).count());

		t = timer::now();
		Set::cross(a, b);
		data[8][4] = to_string((duration_cast<milliseconds>(timer::now() - t)).count());

		t = timer::now();
		Set::substraction(a, b);
		data[9][4] = to_string((duration_cast<milliseconds>(timer::now() - t)).count());

		t = timer::now();
		Set::simmetricalSub(a, b);
		data[10][4] = to_string((duration_cast<milliseconds>(timer::now() - t)).count());
	}
	{
		// Multiset
		auto t = timer::now();
		SetMultiset a;
		a.fillRandom(size, MIN, 10 * size);
		data[1][5] = to_string((duration_cast<milliseconds>(timer::now() - t)).count());

		SetMultiset b;
		b.fillRandom(size, MIN, 10 * size);

		t = timer::now();
		a.length();
		data[2][5] = to_string((duration_cast<milliseconds>(timer::now() - t)).count());

		t = timer::now();
		a.isSubset(a);
		data[3][5] = to_string((duration_cast<milliseconds>(timer::now() - t)).count());

		t = timer::now();
		b.isSubset(a);
		data[4][5] = to_string((duration_cast<milliseconds>(timer::now() - t)).count());

		t = timer::now();
		a.isEqual(a);
		data[5][5] = to_string((duration_cast<milliseconds>(timer::now() - t)).count());

		t = timer::now();
		b.isEqual(a);
		data[6][5] = to_string((duration_cast<milliseconds>(timer::now() - t)).count());

		t = timer::now();
		SetMultiset::unite(a, b);
		data[7][5] = to_string((duration_cast<milliseconds>(timer::now() - t)).count());

		t = timer::now();
		SetMultiset::cross(a, b);
		data[8][5] = to_string((duration_cast<milliseconds>(timer::now() - t)).count());

		t = timer::now();
		SetMultiset::substraction(a, b);
		data[9][5] = to_string((duration_cast<milliseconds>(timer::now() - t)).count());

		t = timer::now();
		SetMultiset::simmetricalSub(a, b);
		data[10][5] = to_string((duration_cast<milliseconds>(timer::now() - t)).count());
	}
	{
		// Map
		auto t = timer::now();
		SetMap a;
		a.fillRandom(size, MIN, 10 * size);
		data[1][6] = to_string((duration_cast<milliseconds>(timer::now() - t)).count());

		SetMap b;
		b.fillRandom(size, MIN, 10 * size);

		t = timer::now();
		a.length();
		data[2][6] = to_string((duration_cast<milliseconds>(timer::now() - t)).count());

		t = timer::now();
		a.isSubset(a);
		data[3][6] = to_string((duration_cast<milliseconds>(timer::now() - t)).count());

		t = timer::now();
		b.isSubset(a);
		data[4][6] = to_string((duration_cast<milliseconds>(timer::now() - t)).count());

		t = timer::now();
		a.isEqual(a);
		data[5][6] = to_string((duration_cast<milliseconds>(timer::now() - t)).count());

		t = timer::now();
		b.isEqual(a);
		data[6][6] = to_string((duration_cast<milliseconds>(timer::now() - t)).count());

		t = timer::now();
		SetMap::unite(a, b);
		data[7][6] = to_string((duration_cast<milliseconds>(timer::now() - t)).count());

		t = timer::now();
		SetMap::cross(a, b);
		data[8][6] = to_string((duration_cast<milliseconds>(timer::now() - t)).count());

		t = timer::now();
		SetMap::substraction(a, b);
		data[9][6] = to_string((duration_cast<milliseconds>(timer::now() - t)).count());

		t = timer::now();
		SetMap::simmetricalSub(a, b);
		data[10][6] = to_string((duration_cast<milliseconds>(timer::now() - t)).count());
	}

	cout << printLine(length) << endl;
	printTable(data, ROWS, COLUMNS, columnWidth, length);

	return EXIT_SUCCESS;
}


/* ---- Вспомогательные функции --- */

string printLine(int length) {
	string line = "";
	for (int i{}; i < length; i++)
		line += '-';
	return line;
}

void printTable(string data[][COLUMNS], int dataRows, int dataColumns, int columnWidth[] , int lengthOfLine) {
	for (int i{}; i < dataRows; i++) {
		for (int j{}; j < dataColumns; j++) {
			cout << left << setw(columnWidth[j]) << "| " + data[i][j];
		}
		cout << " |" << endl;
		cout << printLine(lengthOfLine) << endl;
	}
}

/* ------------------------------- */
