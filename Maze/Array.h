#pragma once
class Array
{
private:
	int demention_number;
	int* dementions_size;
	int* array;

	int GetIndex(const int*) const;
	int GetIndex(const int, ...) const;

public:
	Array(int size, int dn = 2);
	Array(int*, int);
	~Array();

	int GetValue(const int*) const;
	int GetValue(const int, ...) const;
	void SetValue(const int, const int*);
	void SetValue(const int, const int, ...);
};
