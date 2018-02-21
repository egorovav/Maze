#pragma once
#include "Array.h"
#include <iostream>

using namespace std;

class Maze
{
private:
	Array* arr;
	int size;

public:
	Maze();
	Maze(int);
	Maze(int, double, const int rnd_seed = 0);
	~Maze();

	int ReadMaze(istream&);
	int WriteMaze(ostream&) const;
	int GetValue(const int, const int) const;
	void SetValue(const int, const int, const int) const;
	int GetSize() const;
};

int maze_test();
int maze_test_stl();