#include <stdio.h>
#include <iostream>
#include "Stack.h"

using namespace std;

Stack::Stack()
{
	top = NULL;
}

Stack::~Stack()
{
	while (top)
	{
		Stack::Element* temp = top;
		top = top->next;
		delete temp;
	}
}

void Stack::push(void* data)
{
	Stack::Element* _new = new Stack::Element;
	_new->Data = data;
	_new->next = top;
	top = _new;
}

void* Stack::pop()
{
	if (top)
	{
		Stack::Element* temp_top = top;
		void* temp_data = top->Data;
		top = top->next;
		delete temp_top;
		return temp_data;
	}
	else
		return NULL;
}

void Stack::print_int()
{
	Element* cur = top;
	while (cur)
	{
		cout << *(int*)(cur->Data) << " ";
		cur = cur->next;
	}
	cout << endl;
}

int main_stack()
{
	Stack stack;
	int user_input = 0;
	while (user_input != 3)
	{
		cout << "Select operation:" << endl;
		cout << "=================" << endl;
		cout << "1 - push" << endl;
		cout << "2 - pop" << endl;
		cout << "3 - exit" << endl;

		cin >> user_input;

		switch (user_input)
		{
		case 1:
		{
			int* num = new int;
			cout << "Input number ?- " << endl;
			cin >> *num;
			stack.push(num);
			stack.print_int();
			break;
		}
		case 2:
		{
			void* tp = stack.pop();
			if (tp)
			{
				int t = *(int*)tp;
				cout << t << endl;
				stack.print_int();
			}
			else
				cout << "Stack is empty." << endl;
			break;
		}
		case 3:
			break;
		default:
			cout << "Input number from 1 to 3." << endl;
			break;
		}
	}

	return 0;
}