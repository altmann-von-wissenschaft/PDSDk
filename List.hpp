#pragma once
#include <string>

using std::string;

class List {
	struct Node {
		int value;
		Node* next;
	};
	Node* head;

public:
	List();//F1
	bool isEmpty();//F2
	bool has(int value);//F3
	bool add(int value);//F4
	void fillRandom(int size, int massive[]);//F5
	int length();//F6
	string print(char delimeter);//F7
	~List();//F8

	bool isSubset(List& b);//F9
	bool isEqual(List& b);//F10

	static List* unite(List& a, List& b);//F11
	static List* cross(List& a, List& b);//F12
	static List* substraction(List& a, List& b);//F13
	static List* simmetricalSub(List& a, List& b);//F14

	List(List& const set);
	Node* const getHead() { return head; }
};
