#include "SetMultiset.hpp"

#include <exception>
#include <cstdlib>
#include <ctime>

using namespace std;

SetMultiset::SetMultiset() {
	container = multiset<int>();
}

bool SetMultiset::isEmpty() {
	return container.empty();
}

bool SetMultiset::has(int value) {
	return container.find(value) != container.end();
}

bool SetMultiset::add(int value) {
	if (!has(value)) {
		container.insert(value);
		return true;
	}
	else return false;
}

void SetMultiset::fillRandom(int size, int minVal, int maxVal) {
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

void SetMultiset::fillRandom(int size, int minVal, int maxVal, char type) {
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

int SetMultiset::length() {
	return container.size();
}

string SetMultiset::print(char delimeter) {
	if (isEmpty())
		return "- ";

	string result = "";
	multiset<int>::iterator iter = container.begin();
	do {
		result += to_string(*(iter++));
		result += delimeter;
	} while (iter != container.end());
	return result.substr(0, result.length() - 1);
}

bool SetMultiset::isSubset(SetMultiset& b) {
	if (isEmpty())
		return true;

	if (this->length() > b.length())
		return false;

	multiset<int>::iterator iter = container.begin();
	do {
		if (!b.has(*(iter++)))
			return false;
	} while (iter != container.end());

	return true;
}

bool SetMultiset::isEqual(SetMultiset& b) {
	return this->isSubset(b) && b.isSubset(*this);
}

SetMultiset* SetMultiset::unite(SetMultiset& a, SetMultiset& b) {
	SetMultiset* c = new SetMultiset();

	if (!a.isEmpty()) {
		multiset<int>::iterator iter = a.begin();
		do c->add(*(iter++));
		while (iter != a.end());
	}

	if (!b.isEmpty()) {
		multiset<int>::iterator iter = b.begin();
		do c->add(*(iter++));
		while (iter != b.end());
	}

	return c;
}

SetMultiset* SetMultiset::cross(SetMultiset& a, SetMultiset& b) {
	if (a.isEmpty() || b.isEmpty())
		return nullptr;

	SetMultiset* c = new SetMultiset();

	multiset<int>::iterator iter = a.begin();
	do {
		if (b.has(*iter))
			c->add(*iter);
		iter++;
	} while (iter != a.end());

	return c;
}

SetMultiset* SetMultiset::substraction(SetMultiset& a, SetMultiset& b) {
	if (a.isEmpty())
		return nullptr;
	if (b.isEmpty())
		return new SetMultiset(a);

	SetMultiset* c = new SetMultiset();

	multiset<int>::iterator iter = a.begin();
	do {
		if (!b.has(*iter))
			c->add(*iter);
		iter++;
	} while (iter != a.end());

	return c;
}

SetMultiset* SetMultiset::simmetricalSub(SetMultiset& a, SetMultiset& b) {
	SetMultiset* _unite = unite(a, b);
	SetMultiset* _cross = cross(a, b);
	SetMultiset* _sub = substraction(*_unite, *_cross);

	delete _unite;
	delete _cross;
	return _sub;
}

SetMultiset::SetMultiset(SetMultiset& const set) {
	container = multiset<int>(set.container);
}
