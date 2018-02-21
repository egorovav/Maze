#include "Array.h"
#include <math.h>
#include <iostream>

using namespace std;

Array::Array(int size, int dn)
{
	demention_number = dn;
	dementions_size = new int[dn];
	for (int i = 0; i < dn; ++i)
	{
		dementions_size[i] = size;
	}

	int arr_size = (int)pow((float)size, dn);
	array = new int[arr_size];
}

Array::Array(int* ds, int dn)
{
	dementions_size = ds;
	demention_number = dn;
	int arr_size = 1;
	for (int i = 0; i < dn; ++i)
	{
		arr_size *= ds[i];
	}

	array = new int[arr_size];
}

Array::~Array()
{
	delete[] dementions_size;
	delete[] array;
}

int Array::GetIndex(const int* coords) const
{
	int index = 0;
	int m = 1;
	for (int i = 0; i < demention_number; ++i)
	{
		index += coords[i] * m;
		m *= dementions_size[i];
	}

	return index;
}

int Array::GetIndex(const int x0, ...) const
{
	return GetIndex(&x0);
}

int Array::GetValue(const int* coords) const
{
	//cout << coords[0] << ", " << coords[1] << endl;
	int index = GetIndex(coords);
	int val = array[index];

	return val;
}

int Array::GetValue(const int x0, ...) const
{
	return GetValue(&x0);
}

void Array::SetValue(const int value, const int* coords)
{
	int index = GetIndex(coords);
	array[index] = value;
}

void Array::SetValue(const int value, const int x0, ...)
{
	SetValue(value, &x0);
}