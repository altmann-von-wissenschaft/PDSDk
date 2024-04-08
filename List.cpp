#include "List.hpp"

#include <exception>
#include <ctime>
#include <cstdlib>

using namespace std;

/* Инициализация пустого множества */
List::List() {
	head = nullptr;
}

/* Проверка на пустое множество */
bool List::isEmpty() {
	return head == nullptr;
}

/* Проверка наличия элемента в множестве */
bool List::has(int value) {
	if (isEmpty())
		return false;

	Node* tmp = head;
	do {
		if (tmp->value == value)
			return true;
		tmp = tmp->next;
	} while (tmp != nullptr);

	return false;
}

/* Добавление элемента спереди */
bool List::add(int value) {
	if (has(value))
		return false;

	Node* element = new Node{ 0 };
	element->value = value;
	element->next = head;
	head = element;

	return true;
}

/* Создание множества с заданным размером и границей значений */
void List::fillRandom(int size, int minVal, int maxVal) {
	/* Проверка размера */
	if (size <= 0)
		throw exception("Некорректный размер");

	/* Проверка границ значений */
	if (maxVal < minVal)
		throw exception("Некорректные границы");

	srand(time(nullptr)); // Сид случайной генерации
	int i = 0;
	while (i < size) {
		if (add(rand() % (maxVal - minVal + 1) + minVal));
		i++;
	}
}

/* Создание множества с заданным размером, границей значений и типом множества*/
void List::fillRandom(int size, int minVal, int maxVal, char type) {
	/* Проверка размера */
	if (size <= 0)
		throw exception("Некорректный размер");

	/* Проверка границ значений */
	if (maxVal < minVal)
		throw exception("Некорректные границы");

	srand(time(nullptr)); // Сид случайной генерации
	int i = 0;

	switch (type) {
	case 'A':
		while (i < size)
		{
			int generated = rand() % (maxVal - minVal + 1) + minVal;
			if (generated % 10 > 3)
				if (add(generated))
					i++;
		}
		break;
	case 'B':
		while (i < size)
		{
			int generated = rand() % (maxVal - minVal + 1) + minVal;
			if (generated % 10 < 8)
				if (add(generated))
					i++;
		}
		break;
	default:
		throw exception("Неверный тип массива");
	}
}

/* Множество в строку */
string List::print(char delimeter) {
	if (isEmpty())
		return "- ";

	Node* firstNode = head;
	string result = "";
	do {
		result += to_string(firstNode->value);
		result += delimeter;
		firstNode = firstNode->next;
	} while (firstNode != nullptr);

	return result.substr(0, result.length() - 1);
}

/* Возвращение мощности множества */
int List::length() {
	if (isEmpty())
		return 0;

	int length = 0;
	Node* firstNode = head;
	do {
		length++;
		firstNode = firstNode->next;
	} while (firstNode != nullptr);
	return length;
}

/* Очищение множества */
List::~List() {
	if (isEmpty())
		return;

	Node* firstNode = head;
	Node* next = firstNode->next;
	while (next != nullptr) {
		delete firstNode;
		firstNode = next;
		next = next->next;
	}
	delete firstNode;
	head = nullptr;
}

/* A подмножество B */
bool List::isSubset(List& b) {
	if (isEmpty())
		return true;

	if (this->length() > b.length())
		return false;

	Node* a = head;
	do {
		if (!b.has(a->value))
			return false;
		a = a->next;
	} while (a);

	return true;
}

/* Равенство множеств */
bool List::isEqual(List& b) {
	return this->isSubset(b) && b.isSubset(*this);
}

/* Объединение множеств A и B */
List* List::unite(List& a, List& b) {
	List* c = new List();

	Node* tmp = a.getHead();
	if (!a.isEmpty()) {
		do {
			c->add(tmp->value);
			tmp = tmp->next;
		} while (tmp);
	}

	tmp = b.getHead();
	if (!b.isEmpty()) {
		do {
			c->add(tmp->value);
			tmp = tmp->next;
		} while (tmp);
	}

	return c;
}

/* Пересечение множеств */
List* List::cross(List& a, List& b) {
	if (a.isEmpty() || b.isEmpty())
		return nullptr;

	List* c = new List();

	Node* tmp = a.getHead();
	do {
		if (b.has(tmp->value))
			c->add(tmp->value);
		tmp = tmp->next;
	} while (tmp);

	return c;
}

/* Разность множеств */
List* List::substraction(List& a, List& b) {
	if (a.isEmpty())
		return nullptr;
	if (b.isEmpty())
		return new List(a);

	List* c = new List();

	Node* tmp = a.getHead();
	do {
		if (!b.has(tmp->value))
			c->add(tmp->value);
		tmp = tmp->next;
	} while (tmp);

	return c;
}

/* Симметричная разность множеств */
List* List::simmetricalSub(List& a, List& b) {
	List* _unite = unite(a, b);
	List* _cross = cross(a, b);
	List* c = substraction(*_unite, *_cross);

	delete _unite;
	delete _cross;
	return c;
}

List::List(List& const set) {
	head = nullptr;
	if (!set.isEmpty()) {
		Node* a = set.head;
		do {
			add(a->value);
			a = a->next;
		} while (a);
	}
}



