#pragma once

#include <string>

using std::string;

typedef struct straightlist {
	int value;
	struct straightlist* next;
} Node;

Node* InitEmptySet();//F1
bool  IsEmpty(Node* firstNode);//F2
bool  HasElement(Node* firstNode, int value);//F3
Node* AddElement(Node* firstNode, int value);//F4
Node* CreateNewSet(int size, int massive[]);//F5
int   Length(Node* firstNode);//F6
string PrintSet(Node* firstNode, char delimeter);//F7
Node* ClearSet(Node* firstNode);//F8

bool IsSub(Node* a, Node* b);//F9
bool IsEqu(Node* a, Node* b);//F10
Node* Unite(Node* a, Node* b);//F11
Node* CommonElements(Node* a, Node* b);//F12
Node* Substraction(Node* a, Node* b);//F13
Node* SimmetricalSub(Node* a, Node* b);//F14
