#include "Maze.h"
#include "Stack.h"
#include "Point.h"
#include <time.h>
#include <stdlib.h>
#include <fstream>

Maze::Maze()
{
	arr = NULL;
	size = 0;
}

Maze::Maze(int s)
{
	arr = new Array(s);
	size = s;
}

Maze::Maze(int s, double walls_part, int rnd_seed)
{
	arr = new Array(s);
	size = s;
	int dev = (int)(1 / walls_part);

	time_t tt = time(NULL);
	tm* cur_time = new tm;
	gmtime_s(cur_time, &tt);
	//cout << cur_time->tm_sec;

	if (rnd_seed == 0)
		srand(cur_time->tm_sec);
	else
		srand(rnd_seed);

	delete cur_time;

	bool is_corner_neig = false, is_wall_neig = false;

	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			if (i == 0 || j == 0 || i == size - 1 || j == size - 1)
			{
				arr->SetValue(0, i, j);
			}
			else
			{

				int r = rand() % dev;
				if (r != 0)
				{
					is_corner_neig = (arr->GetValue(i + 1, j + 1) == 1)
						|| (arr->GetValue(i - 1, j - 1) == 1)
						|| (arr->GetValue(i - 1, j + 1) == 1)
						|| (arr->GetValue(i + 1, j - 1) == 1);

					is_wall_neig = (arr->GetValue(i, j + 1) == 1)
						|| (arr->GetValue(i, j - 1) == 1)
						|| (arr->GetValue(i - 1, j) == 1)
						|| (arr->GetValue(i + 1, j) == 1);

					if (is_wall_neig || !is_corner_neig)
						r = 1;
				}
				arr->SetValue(r, i, j);
			}
		}
	}

	arr->SetValue(1, 1, 1);
	arr->SetValue(1, size - 2, size - 2);
}

Maze::~Maze()
{
	delete arr;
}

int Maze::GetValue(const int x, const int y) const
{
	return this->arr->GetValue(x, y);
}

void Maze::SetValue(const int val, const int x, const int y) const
{
	this->arr->SetValue(val, x, y);
}

int Maze::ReadMaze(istream& is)
{
	const int size_str_len = 4;
	char* size_str = new char[size_str_len];
	is.getline(size_str, size_str_len);
	this->size = atoi(size_str);
	delete[] size_str;

	if (arr)
	{
		delete arr;
	}

	arr = new Array(this->size);

	int x = 0;
	int y = 0;
	char c;

	while (x + y < 2 * this->size - 1)
	{
		c = is.get();
		if (is.eof())
		{
			cout << "File is to short. Size = " << this->size << ", x = " << x << ", y = " << y;
			return 1;
		}

		if (c == '\n')
		{
			x++;
			y = 0;
		}
		else
		{
			if (c == 'X')
			{
				this->SetValue(0, x, y);
				y++;
			}
			else if (c == ' ')
			{
				this->SetValue(1, x, y);
				y++;
			}
		}
	}

	return 0;
}

int Maze::WriteMaze(ostream& os) const
{
	for (int i = 0; i < this->size; ++i)
	{
		os << endl;
		for (int j = 0; j < this->size; ++j)
		{
			int val = this->GetValue(i, j);

			if (val == 0)
				os << "X";
			if (val == 1)
				os << " ";
			if (val == -1)
				os << "0";
			if (val == 2)
				os << ".";
		}
	}

	return 0;
}

int Maze::GetSize() const
{
	return size;
}

int maze_test()
{
	const double walls_part = 0.3;

	int rnd_seed = 0;
	int prev_rnd_seed = 0;

	Point start_p(1, 1);
	Stack stack;

	Point cur_p(start_p.x, start_p.y);

	//int create_count = 0;
	//int delete_count = 0;


	while (true)
	{

		rnd_seed++;
		srand(rnd_seed);
		bool is_path_found = true;
		Maze maze(100, walls_part, rand());

		//Maze maze;
		//char* file_name = "Maze.txt";
		//ifstream fin(file_name, ios::_Nocreate || ios::in);
		//if (!fin)
		//{
		//	cout << "Open file error " << file_name;
		//	getchar();
		//	return 1;
		//}
		//maze.ReadMaze(fin);

		int size = maze.GetSize();

		//char* file_name = "Maze.txt";
		//ofstream fout(file_name, ios::_Nocreate || ios::out);
		//if (!fout)
		//{
		//	cout << "Open file error " << file_name;
		//	getchar();
		//	return 1;
		//}
		//maze.WriteMaze(fout);
		//fout.close();
		//maze.WriteMaze(std::cout);
		//getchar();

		int count = 0;
		do
		{
			//maze.WriteMaze(cout);

			Point* temp_p = new Point(cur_p.x, cur_p.y);
			//create_count++;

			int right_side = maze.GetValue(cur_p.x + 1, cur_p.y);
			int bottom_side = maze.GetValue(cur_p.x, cur_p.y + 1);

			if (right_side == 1 && bottom_side == 1)
			{
				if (cur_p.x <= cur_p.y)
					cur_p.x++;
				else
					cur_p.y++;
			}
			else if (right_side == 1)
				cur_p.x++;
			else if (bottom_side == 1)
				cur_p.y++;
			else if (maze.GetValue(cur_p.x - 1, cur_p.y) == 1)
				cur_p.x--;
			else if (maze.GetValue(cur_p.x, cur_p.y - 1) == 1)
				cur_p.y--;
			else
			{
				delete temp_p;
				//delete_count++;
				void* top = stack.pop();
				if (top)
				{
					cur_p = *(Point*)top;
					delete top;
					//delete_count++;
					//std::cout << " pop " << cur_p.x << ", " << cur_p.y << endl;
					continue;
				}
				else
				{
					//std::cout << " Path not found." << endl;
					is_path_found = false;
					break;
				}
			}

			maze.SetValue(2, cur_p.x, cur_p.y);
			stack.push(temp_p);

			//cur_p = *temp_p;

			//std::cout << "  push " << cur_p.x << ", " << cur_p.y << endl;

			count++;
			if (count > size * size)
				break;

		} while (cur_p.x != size - 2 || cur_p.y != size - 2);

		//maze.WriteMaze(std::cout);

		if (rnd_seed == prev_rnd_seed + 1000000)
		{
			//cout << "create - " << create_count << endl;
			//cout << "delete - " << delete_count << endl;
			cout << rnd_seed << endl;
			prev_rnd_seed = rnd_seed;
		}

		if (is_path_found || rnd_seed == 2000000000)
		{
			cout << "===========================" << endl;
			cout << rnd_seed << endl;
			Point* p;
			while (p = (Point*)stack.pop())
			{
				cout << p->x << ", " << p->y << endl;
				maze.SetValue(-1, p->x, p->y);
			}
			delete p;
			cout << "===========================" << endl;

			char* file_name = "Maze.txt";
			ofstream fout(file_name, ios::_Nocreate || ios::out);
			if (!fout)
			{
				cout << "Open file error " << file_name;
				getchar();
				return 1;
			}
			maze.WriteMaze(fout);
			fout.close();
			break;
		}
		//getchar();
		//break;
	}

	getchar();
}

#include <stack>
#include <time.h>

int maze_test_stl()
{
	const double walls_part = 0.33;

	time_t* t = new time_t();
	time(t);

	int rnd_seed = *t;
	int prev_rnd_seed = 0;

	Point start_p(1, 1);
	stack<Point> stack;

	Point cur_p(start_p.x, start_p.y);

	while (true)
	{

		rnd_seed++;
		srand(rnd_seed);
		bool is_path_found = true;
		Maze maze(50, walls_part, rand());

		int size = maze.GetSize();

		int count = 0;
		do
		{
			Point* temp_p = new Point(cur_p.x, cur_p.y);

			int right_side = maze.GetValue(cur_p.x + 1, cur_p.y);
			int bottom_side = maze.GetValue(cur_p.x, cur_p.y + 1);

			if (right_side == 1 && bottom_side == 1)
			{
				if (cur_p.x <= cur_p.y)
					cur_p.x++;
				else
					cur_p.y++;
			}
			else if (right_side == 1)
				cur_p.x++;
			else if (bottom_side == 1)
				cur_p.y++;
			else if (maze.GetValue(cur_p.x - 1, cur_p.y) == 1)
				cur_p.x--;
			else if (maze.GetValue(cur_p.x, cur_p.y - 1) == 1)
				cur_p.y--;
			else
			{
				delete temp_p;

				if (!stack.empty())
				{
					Point top = stack.top();
					cur_p = top;
					stack.pop();
					continue;
				}
				else
				{
					is_path_found = false;
					break;
				}
			}

			maze.SetValue(2, cur_p.x, cur_p.y);
			stack.push(*temp_p);

			count++;
			if (count > size * size)
				break;

		} while (cur_p.x != size - 2 || cur_p.y != size - 2);

		if (rnd_seed == prev_rnd_seed + 1000000)
		{
			cout << rnd_seed << endl;
			prev_rnd_seed = rnd_seed;
		}

		if (is_path_found || rnd_seed == 2000000000)
		{
			cout << "===========================" << endl;
			cout << rnd_seed << endl;
			Point p;
			while (!stack.empty())
			{
				p = stack.top();
				stack.pop();
				cout << p.x << ", " << p.y << endl;
				maze.SetValue(-1, p.x, p.y);
			}
			cout << "===========================" << endl;

			char* file_name = "Maze.txt";
			ofstream fout(file_name, ios::_Nocreate || ios::out);
			if (!fout)
			{
				cout << "Open file error " << file_name;
				getchar();
				return 1;
			}
			maze.WriteMaze(fout);
			fout.close();
			break;
		}
	}

	cout << "Press anykey for exit.";
	cin.get();
}
