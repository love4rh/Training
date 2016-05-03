/*
https://www.algospot.com/judge/problem/read/MEASURETIME
2
5
5 1 4 3 2
10
7 8 6 6 1 9 4 4 3 10

7
25
*/

#include <iostream>
#include <vector>

using namespace std;

istream& in = cin;
ostream& out = cout;


class Fenwick
{
public:
	Fenwick(int n) : _tree(n + 1) {}

private:
	vector<int>		_tree;

public:
	// [0, pos] 구간의 합을 반환
	int sum(int pos)
	{
		pos += 1;

		int ret = int();
		while (pos > 0)
		{
			ret += _tree[pos];
			pos &= (pos - 1);
		}

		return ret;
	}

	// pos 위치를 포함하는 영역에 값을 더함.
	void add(int pos, int val)
	{
		pos += 1;
		while (pos < _tree.size())
		{
			_tree[pos] += val;
			pos += (pos & -pos);
		}
	}
};


int main()
{
	std::ios::sync_with_stdio(false);

	int T, N;

	in >> T;

	while (T--)
	{
		in >> N;

		Fenwick tree(1000000);

		int val, count = 0, maxVal = -1;
		while (N--)
		{
			in >> val;

			tree.add(val, 1);
			count += (tree.sum(999999) - tree.sum(val));
		}

		out << count << endl;
	}

	return 0;
}
