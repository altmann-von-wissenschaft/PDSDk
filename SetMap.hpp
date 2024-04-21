#pragma once
#include <map>
#include <string>

using std::map;
using std::string;

class SetMap {
	map<int, int*> container;

public:
	SetMap();//F1
	bool isEmpty();//F2
	bool has(int value);//F3
	bool add(int value);//F4
	void fillRandom(int size, int massive[]);//F5
	int length();//F6
	string print(char delimeter);//F7

	bool isSubset(SetMap& b);//F9
	bool isEqual(SetMap& b);//F10

	static SetMap* unite(SetMap& a, SetMap& b);//F11
	static SetMap* cross(SetMap& a, SetMap& b);//F12
	static SetMap* substraction(SetMap& a, SetMap& b);//F13
	static SetMap* simmetricalSub(SetMap& a, SetMap& b);//F14

	SetMap(SetMap& const set);
	map<int, int*>::iterator begin() { return container.begin(); }
	map<int, int*>::iterator end() { return container.end(); }
};
