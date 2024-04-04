#include "StraightList.hpp"

#include <exception>
#include <ctime>
#include <cstdlib>

using namespace std;

/* Инициализация пустого множества */
Node* InitEmptySet() {
	return nullptr;
}

/* Проверка на пустое множество */
bool IsEmpty(Node* firstNode) {
	return firstNode == nullptr;
}

/* Проверка наличия элемента в множестве */
bool HasElement(Node* firstNode, int value) {
	if (IsEmpty(firstNode))
		return false;

	do {
		if (firstNode->value == value)
			return true;
		firstNode = firstNode->next;
	} while (firstNode != nullptr);

	return false;
}

/* Добавление элемента спереди */
Node* AddElement(Node* firstNode, int value) {
	if (HasElement(firstNode, value))
		return firstNode;

	Node* element = new Node{ 0 };
	element->value = value;
	element->next = firstNode;

	return element;
}

/* Создание множества с заданным размером и границей значений */
Node* CreateNewSet(int size, int minVal, int maxVal) {
	/* Проверка размера */
	if (size <= 0)
		throw exception("Некорректный размер");

	/* Проверка границ значений */
	if (maxVal < minVal)
		throw exception("Некорректные границы");

	srand(time(nullptr)); // Сид случайной генерации
	int i = 0;
	Node* first = nullptr;
	Node* prev = nullptr;
	while (i < size) {
		first = AddElement(first, rand() % (maxVal - minVal + 1) + minVal);
		if (first != prev) {
			i++;
			prev = first;
		}
	}

	return first;
}

/* Создание множества с заданным размером, границей значений и типом множества*/
Node* CreateNewSet(int size, int minVal, int maxVal, char type) {
	/* Проверка размера */
	if (size <= 0)
		throw exception("Некорректный размер");

	/* Проверка границ значений */
	if (maxVal < minVal)
		throw exception("Некорректные границы");

	srand(time(nullptr)); // Сид случайной генерации
	int i = 0;
	Node* first = nullptr;
	Node* prev = nullptr;

	switch (type) {
	case 'A': {
		while (i < size) {
			int generated = rand() % (maxVal - minVal + 1) + minVal;
			if (generated % 10 > 3) {
				first = AddElement(first, generated);
				if (first != prev) {
					i++;
					prev = first;
				}
			}
		}
		break;
	}
	case 'B': {
		while (i < size) {
			int generated = rand() % (maxVal - minVal + 1) + minVal;
			if (generated % 10 < 8) {
				first = AddElement(first, generated);
				if (first != prev) {
					i++;
					prev = first;
				}
			}
		}
		break;
	}
	default:
		throw exception("Неверный тип массива");
	}

	return first;
}

/* Множество в строку */
string PrintSet(Node* firstNode, char delimeter) {
	if (IsEmpty(firstNode))
		return "- ";

	string result = "";
	do {
		result += to_string(firstNode->value);
		result += delimeter;
		firstNode = firstNode->next;
	} while (firstNode != nullptr);

	result = result.substr(0, result.length() - 1);

	return result;
}

/* Возвращение мощности множества */
int Length(Node* firstNode) {
	if (IsEmpty(firstNode))
		return 0;

	int length = 0;
	do {
		length++;
		firstNode = firstNode->next;
	} while (firstNode != nullptr);
	return length;
}

/* Очищение множества */
Node* ClearSet(Node* firstNode) {
	if (IsEmpty(firstNode))
		return nullptr;

	Node* next = firstNode->next;
	while (next != nullptr) {
		delete firstNode;
		firstNode = next;
		next = next->next;
	}
	delete firstNode;

	return nullptr;
}

/* A подмножество B */
bool IsSub(Node* a, Node* b) {
	if (IsEmpty(a))
		return true;

	if (Length(a) > Length(b))
		return false;

	do {
		if (!HasElement(b, a->value))
			return false;
		a = a->next;
	} while (a);

	return true;
}

/* Равенство множеств */
bool IsEqu(Node* a, Node* b) {
	return IsSub(a, b) && IsSub(b, a);
}

/* Объединение множеств A и B */
Node* Unite(Node* a, Node* b) {
	Node* c = InitEmptySet();

	if (!IsEmpty(a)) {
		do {
			c = AddElement(c, a->value);
			a = a->next;
		} while (a);
	}

	if (!IsEmpty(b)) {
		do {
			c = AddElement(c, b->value);
			b = b->next;
		} while (b);
	}

	return c;
}

/* Пересечение множеств */
Node* CommonElements(Node* a, Node* b) {
	if (IsEmpty(a) || IsEmpty(b))
		return nullptr;

	Node* c = InitEmptySet();

	do {
		if (HasElement(b, a->value))
			c = AddElement(c, a->value);
		a = a->next;
	} while (a);

	return c;
}

/* Разность множеств */
Node* Substraction(Node* a, Node* b) {
	if (IsEmpty(a))
		return nullptr;
	if (IsEmpty(b))
		return a;

	Node* c = InitEmptySet();

	do {
		if (!HasElement(b, a->value))
			c = AddElement(c, a->value);
		a = a->next;
	} while (a);

	return c;
}

/* Симметричная разность множеств */
Node* SimmetricalSub(Node* a, Node* b) {
	Node* unite = Unite(a, b);
	Node* common = CommonElements(a, b);
	Node* c = Substraction(unite, common);

	ClearSet(unite);
	ClearSet(common);

	return c;
}
