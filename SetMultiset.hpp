#pragma once
#include <set>
#include <string>

using std::multiset;
using std::string;

class SetMultiset {
	multiset<int> container;

public:
	SetMultiset();//F1
	bool isEmpty();//F2
	bool has(int value);//F3
	bool add(int value);//F4
	void fillRandom(int size, int minVal, int maxVal);//F5
	void fillRandom(int size, int minVal, int maxVal, char type);//F5*
	int length();//F6
	string print(char delimeter);//F7

	bool isSubset(SetMultiset& b);//F9
	bool isEqual(SetMultiset& b);//F10

	static SetMultiset* unite(SetMultiset& a, SetMultiset& b);//F11
	static SetMultiset* cross(SetMultiset& a, SetMultiset& b);//F12
	static SetMultiset* substraction(SetMultiset& a, SetMultiset& b);//F13
	static SetMultiset* simmetricalSub(SetMultiset& a, SetMultiset& b);//F14

	SetMultiset(SetMultiset& const set);
	multiset<int>::iterator begin() { return container.begin(); }
	multiset<int>::iterator end() { return container.end(); }
};
