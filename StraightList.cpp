#include "StraightList.hpp"

#include <exception>
#include <ctime>
#include <cstdlib>

using namespace std;

Node* Copy(Node* list);

/* ������������� ������� ��������� */
Node* InitEmptySet() {
	return nullptr;
}

/* �������� �� ������ ��������� */
bool IsEmpty(Node* firstNode) {
	return firstNode == nullptr;
}

/* �������� ������� �������� � ��������� */
bool HasElement(Node* firstNode, int value) {
	if (IsEmpty(firstNode))
		return false;

	do {
		if (firstNode->value == value)
			return true;
		firstNode = firstNode->next;
	} while (firstNode != nullptr);

	return false;
}

/* ���������� �������� ������� */
Node* AddElement(Node* firstNode, int value) {
	if (HasElement(firstNode, value))
		return firstNode;

	Node* element = new Node{ 0 };
	element->value = value;
	element->next = firstNode;

	return element;
}

/* �������� ��������� � �������� �������� � �������� �������� */
Node* CreateNewSet(int size, int massive[]) {
	/* �������� ������� */
	if (size < 0)
		throw exception("������������ ������");

	Node* first = nullptr;
	for (int i{}; i < size; i++)
		first = AddElement(first, massive[i]);

	return first;
}

/* ��������� � ������ */
string PrintSet(Node* firstNode, char delimeter) {
	if (IsEmpty(firstNode))
		return "- ";

	string result = "";
	do {
		result += to_string(firstNode->value);
		result += delimeter;
		firstNode = firstNode->next;
	} while (firstNode != nullptr);

	result = result.substr(0, result.length() - 1);

	return result;
}

/* ����������� �������� ��������� */
int Length(Node* firstNode) {
	if (IsEmpty(firstNode))
		return 0;

	int length = 0;
	do {
		length++;
		firstNode = firstNode->next;
	} while (firstNode != nullptr);
	return length;
}

/* �������� ��������� */
Node* ClearSet(Node* firstNode) {
	if (IsEmpty(firstNode))
		return nullptr;

	Node* next = firstNode->next;
	while (next != nullptr) {
		delete firstNode;
		firstNode = next;
		next = next->next;
	}
	delete firstNode;

	return nullptr;
}

/* A ������������ B */
bool IsSub(Node* a, Node* b) {
	if (IsEmpty(a))
		return true;

	if (Length(a) > Length(b))
		return false;

	do {
		if (!HasElement(b, a->value))
			return false;
		a = a->next;
	} while (a);

	return true;
}

/* ��������� �������� */
bool IsEqu(Node* a, Node* b) {
	return IsSub(a, b) && IsSub(b, a);
}

/* ����������� �������� A � B */
Node* Unite(Node* a, Node* b) {
	if (IsEmpty(a))
		return Copy(b);
	if (IsEmpty(b))
		return Copy(a);

	Node* c = InitEmptySet();

	if (!IsEmpty(a)) {
		do {
			c = AddElement(c, a->value);
			a = a->next;
		} while (a);
	}

	if (!IsEmpty(b)) {
		do {
			c = AddElement(c, b->value);
			b = b->next;
		} while (b);
	}

	return c;
}

/* ����������� �������� */
Node* CommonElements(Node* a, Node* b) {
	if (IsEmpty(a) || IsEmpty(b))
		return nullptr;

	Node* c = InitEmptySet();

	do {
		if (HasElement(b, a->value))
			c = AddElement(c, a->value);
		a = a->next;
	} while (a);

	return c;
}

/* �������� �������� */
Node* Substraction(Node* a, Node* b) {
	if (IsEmpty(a))
		return nullptr;
	if (IsEmpty(b))
		return Copy(a);

	Node* c = InitEmptySet();

	do {
		if (!HasElement(b, a->value))
			c = AddElement(c, a->value);
		a = a->next;
	} while (a);

	return c;
}

/* ������������ �������� �������� */
Node* SimmetricalSub(Node* a, Node* b) {
	Node* unite = Unite(a, b);
	Node* common = CommonElements(a, b);
	Node* c = Substraction(unite, common);

	ClearSet(unite);
	ClearSet(common);

	return c;
}

Node* Copy(Node* list) {
	Node* c = InitEmptySet();

	if (!IsEmpty(list)) {
		do {
			c = AddElement(c, list->value);
			list = list->next;
		} while (list);
	}

	return c;
}
