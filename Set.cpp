#include "Set.hpp"

#include <exception>
#include <cstdlib>
#include <ctime>

using namespace std;

Set::Set() {
	container = set<int>();
}

bool Set::isEmpty() {
	return container.empty();
}

bool Set::has(int value) {
	return container.find(value) != container.end();
}

bool Set::add(int value) {
	return container.insert(value).second;
}

void Set::fillRandom(int size, int minVal, int maxVal) {
	if (size <= 0)
		throw exception("Некорректный размер");

	if (maxVal < minVal)
		throw exception("Некорректные границы");

	srand(time(nullptr)); // Сид
	int i = 0;
	while (i < size)
		if (add(rand() % (maxVal - minVal + 1) + minVal))
			i++;
}

void Set::fillRandom(int size, int minVal, int maxVal, char type) {
	if (size <= 0)
		throw exception("Некорректный размер");

	if (maxVal < minVal)
		throw exception("Некорректные границы");

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

int Set::length() {
	return container.size();
}

string Set::print(char delimeter) {
	if (isEmpty())
		return "- ";

	string result = "";
	set<int>::iterator iter = container.begin();
	do {
		result += to_string(*(iter++));
		result += delimeter;
	} while (iter != container.end());
	return result.substr(0, result.length() - 1);
}

bool Set::isSubset(Set& b) {
	if (isEmpty())
		return true;

	if (this->length() > b.length())
		return false;

	set<int>::iterator iter = container.begin();
	do {
		if (!b.has(*(iter++)))
			return false;
	} while (iter != container.end());

	return true;
}

bool Set::isEqual(Set& b) {
	return this->isSubset(b) && b.isSubset(*this);
}

Set* Set::unite(Set& a, Set& b) {
	Set* c = new Set();

	if (!a.isEmpty()) {
		set<int>::iterator iter = a.begin();
		do c->add(*(iter++));
		while (iter != a.end());
	}

	if (!b.isEmpty()) {
		set<int>::iterator iter = b.begin();
		do c->add(*(iter++));
		while (iter != b.end());
	}

	return c;
}

Set* Set::cross(Set& a, Set& b) {
	if (a.isEmpty() || b.isEmpty())
		return nullptr;

	Set* c = new Set();

	set<int>::iterator iter = a.begin();
	do {
		if (b.has(*iter))
			c->add(*iter);
		iter++;
	} while (iter != a.end());

	return c;
}

Set* Set::substraction(Set& a, Set& b) {
	if (a.isEmpty())
		return nullptr;
	if (b.isEmpty())
		return new Set(a);

	Set* c = new Set();

	set<int>::iterator iter = a.begin();
	do {
		if (!b.has(*iter))
			c->add(*iter);
		iter++;
	} while (iter != a.end());

	return c;
}

Set* Set::simmetricalSub(Set& a, Set& b) {
	Set* _unite = unite(a, b);
	Set* _cross = cross(a, b);
	Set* _sub = substraction(*_unite, *_cross);

	delete _unite;
	delete _cross;
	return _sub;
}

Set::Set(Set& const _set) {
	container = set<int>(_set.container);
}
