/*
Online Code Jam 2016 1차 #1 가계도
3
6
3 5
1 2
4 1
3 4
4 6
7
3 5
1 2
4 1
3 4
4 6
6 7
10
5 1
4 5
4 6
6 2
5 8
6 3
7 10
5 9
4 7
*/

#include <fstream>
#include <iomanip>
#include <iostream>

#include <algorithm>
#include <vector>

using namespace std;

// istream& in = cin;
ifstream in("V:\\Work\\Algorithm\\2016-01\\input\\problem_1_Set3.in");
// ostream& out = cout;
ofstream out("V:\\Work\\Algorithm\\2016-01\\result\\problem_1_Set3.rst");


int maxStep = 0;

class Node
{
public:
	Node() : _parent(0), _level(1) {}
	Node(const Node& cp) : _parent(cp._parent), _level(cp._level) {}

	friend class Wall;

public:
	Node*			_parent;
	int				_level;

public:
	void init()
	{
		_parent = 0;
		_level = 1;
	}

	void addChild(Node* child)
	{
		child->_parent = this;

		if (this->_level < child->_level + 1)
		{
			this->_level = child->_level + 1;

			maxStep = max(maxStep, this->_level);

			int s = 1;
			Node* p = this->_parent;
			while (p != 0)
			{
				p->_level = max(p->_level, this->_level + s);

				maxStep = max(maxStep, p->_level);

				p = p->_parent;
				s += 1;
			}
		}
	}
};

Node P[50001];


int main(int argc, char* argv[])
{
	std::ios::sync_with_stdio(false);

	int T = 0, N = 0;
	int pNo, cNo;

	in >> T;

	while (T--)
	{
		in >> N;

		maxStep = 0;
		for (int i = 0; i <= N; ++i)
			P[i].init();

		for (int i = 1; i < N; ++i)
		{
			in >> pNo >> cNo;
			P[pNo].addChild(&P[cNo]);
		}

		out << maxStep << "\n";
	}

	return 0;
}
