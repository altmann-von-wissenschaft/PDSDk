#include "SetMap.hpp"

#include <exception>
#include <cstdlib>
#include <ctime>

using namespace std;

SetMap::SetMap() {
	container = map<int, int*>();
}

bool SetMap::isEmpty() {
	return container.empty();
}

bool SetMap::has(int value) {
	return container.find(value) != container.end();
}

bool SetMap::add(int value) {
	int size = length();
	container.insert({ value, nullptr });
	return size != length();
}

void SetMap::fillRandom(int size, int massive[]) {
	if (size < 0)
		throw exception("Некорректный размер");

	for (int i{}; i < size; i++)
		add(massive[i]);
}

int SetMap::length() {
	return container.size();
}

string SetMap::print(char delimeter) {
	if (isEmpty())
		return "- ";

	string result = "";
	map<int, int*>::iterator iter = container.begin();
	do {
		result += to_string((iter++)->first);
		result += delimeter;
	} while (iter != container.end());
	return result.substr(0, result.length() - 1);
}

bool SetMap::isSubset(SetMap& b) {
	if (isEmpty())
		return true;

	if (this->length() > b.length())
		return false;

	map<int, int*>::iterator iter = container.begin();
	do {
		if (!b.has((iter++)->first))
			return false;
	} while (iter != container.end());

	return true;
}

bool SetMap::isEqual(SetMap& b) {
	return this->isSubset(b) && b.isSubset(*this);
}

SetMap* SetMap::unite(SetMap& a, SetMap& b) {
	if (a.isEmpty())
		return new SetMap(b);
	if (b.isEmpty())
		return new SetMap(a);

	SetMap* c = new SetMap();

	if (!a.isEmpty()) {
		map<int, int*>::iterator iter = a.begin();
		do c->add((iter++)->first);
		while (iter != a.end());
	}

	if (!b.isEmpty()) {
		map<int, int*>::iterator iter = b.begin();
		do c->add((iter++)->first);
		while (iter != b.end());
	}

	return c;
}

SetMap* SetMap::cross(SetMap& a, SetMap& b) {
	if (a.isEmpty() || b.isEmpty())
		return new SetMap();

	SetMap* c = new SetMap();

	map<int, int*>::iterator iter = a.begin();
	do {
		if (b.has(iter->first))
			c->add(iter->first);
		iter++;
	} while (iter != a.end());

	return c;
}

SetMap* SetMap::substraction(SetMap& a, SetMap& b) {
	if (a.isEmpty())
		return new SetMap();
	if (b.isEmpty())
		return new SetMap(a);

	SetMap* c = new SetMap();

	map<int, int*>::iterator iter = a.begin();
	do {
		if (!b.has(iter->first))
			c->add(iter->first);
		iter++;
	} while (iter != a.end());

	return c;
}

SetMap* SetMap::simmetricalSub(SetMap& a, SetMap& b) {
	SetMap* _unite = unite(a, b);
	SetMap* _cross = cross(a, b);
	SetMap* _sub = substraction(*_unite, *_cross);

	delete _unite;
	delete _cross;
	return _sub;
}

SetMap::SetMap(SetMap& const set) {
	container = map<int, int*>(set.container);
}
