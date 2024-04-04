#pragma once
#include <list>
#include <string>

using std::list;
using std::string;

class SetList {
	list<int> container;

public:
	SetList();//F1
	bool isEmpty();//F2
	bool has(int value);//F3
	bool add(int value);//F4
	void fillRandom(int size, int minVal, int maxVal);//F5
	void fillRandom(int size, int minVal, int maxVal, char type);//F5*
	int length();//F6
	string print(char delimeter);//F7

	bool isSubset(SetList& b);//F9
	bool isEqual(SetList& b);//F10

	static SetList* unite(SetList& a, SetList& b);//F11
	static SetList* cross(SetList& a, SetList& b);//F12
	static SetList* substraction(SetList& a, SetList& b);//F13
	static SetList* simmetricalSub(SetList& a, SetList& b);//F14

	SetList(SetList& const set);
	list<int>::iterator begin();
	list<int>::iterator end();
};
