#include "SetList.hpp"

#include <algorithm>
#include <exception>
#include <cstdlib>
#include <ctime>

using namespace std;

SetList::SetList() {
	container = list<int>();
}

bool SetList::isEmpty() {
	return container.empty();
}

bool SetList::has(int value) {
	if (isEmpty())
		return false;

	return find(container.begin(), container.end(), value) != container.end();
}

bool SetList::add(int value) {
	if (!has(value)) {
		container.push_front(value);
		return true;
	}
	else return false;
}

void SetList::fillRandom(int size, int massive[]) {
	if (size < 0)
		throw exception("Некорректный размер");

	for (int i{}; i < size; i++)
		add(massive[i]);
}

int SetList::length() {
	return container.size();
}

string SetList::print(char delimeter) {
	if (isEmpty())
		return "- ";

	string result = "";
	list<int>::iterator iter = container.begin();
	do {
		result += to_string(*(iter++));
		result += delimeter;
	} while (iter != container.end());
	return result.substr(0, result.length() - 1);
}

bool SetList::isSubset(SetList& b) {
	if (isEmpty())
		return true;

	if (this->length() > b.length())
		return false;

	list<int>::iterator iter = container.begin();
	do {
		if (!b.has(*(iter++)))
			return false;
	} while (iter != container.end());

	return true;
}

bool SetList::isEqual(SetList& b) {
	return this->isSubset(b) && b.isSubset(*this);
}

SetList* SetList::unite(SetList& a, SetList& b) {
	if (a.isEmpty())
		return new SetList(b);
	if (b.isEmpty())
		return new SetList(a);

	SetList* c = new SetList();

	if (!a.isEmpty()) {
		list<int>::iterator iter = a.begin();
		do c->add(*(iter++));
		while (iter != a.end());
	}

	if (!b.isEmpty()) {
		list<int>::iterator iter = b.begin();
		do c->add(*(iter++));
		while (iter != b.end());
	}

	return c;
}

SetList* SetList::cross(SetList& a, SetList& b) {
	if (a.isEmpty() || b.isEmpty())
		return new SetList();

	SetList* c = new SetList();

	list<int>::iterator iter = a.begin();
	do {
		if (b.has(*iter))
			c->add(*iter);
		iter++;
	} while (iter != a.end());

	return c;
}

SetList* SetList::substraction(SetList& a, SetList& b) {
	if (a.isEmpty())
		return new SetList();
	if (b.isEmpty())
		return new SetList(a);

	SetList* c = new SetList();

	list<int>::iterator iter = a.begin();
	do {
		if (!b.has(*iter))
			c->add(*iter);
		iter++;
	} while (iter != a.end());

	return c;
}

SetList* SetList::simmetricalSub(SetList& a, SetList& b) {
	SetList* _unite = unite(a, b);
	SetList* _cross = cross(a, b);
	SetList* _sub = substraction(*_unite, *_cross);

	delete _unite;
	delete _cross;
	return _sub;
}

SetList::SetList(SetList& const set) {
	container = list<int>(set.container);
}

list<int>::iterator SetList::begin() {
	return container.begin();
}

list<int>::iterator SetList::end() {
	return container.end();
}
