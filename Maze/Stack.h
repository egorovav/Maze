#pragma once
class Stack
{
	struct Element
	{
		void* Data;
		Element* next;
	};

	Element* top;

public:
	Stack();
	~Stack();

	void* pop();
	void push(void* data);
	void print_int();
};

