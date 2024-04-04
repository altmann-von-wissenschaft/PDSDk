#pragma once
#include <set>
#include <string>

using std::set;
using std::string;

class Set {
	set<int> container;

public:
	Set();//F1
	bool isEmpty();//F2
	bool has(int value);//F3
	bool add(int value);//F4
	void fillRandom(int size, int minVal, int maxVal);//F5
	void fillRandom(int size, int minVal, int maxVal, char type);//F5*
	int length();//F6
	string print(char delimeter);//F7

	bool isSubset(Set& b);//F9
	bool isEqual(Set& b);//F10

	static Set* unite(Set& a, Set& b);//F11
	static Set* cross(Set& a, Set& b);//F12
	static Set* substraction(Set& a, Set& b);//F13
	static Set* simmetricalSub(Set& a, Set& b);//F14

	Set(Set& const set);
	set<int>::iterator begin() { return container.begin(); }
	set<int>::iterator end() { return container.end(); }
};
