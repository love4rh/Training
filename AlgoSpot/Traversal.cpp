// https://algospot.com/judge/problem/read/TRAVERSAL

/*
1
7
27 16 9 12 54 36 72
9 12 16 27 36 54 72
*/

#include <fstream>

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

istream& in = cin;
//ifstream in("V:\\Work\\Algorithm\\data\\MEASURETIME.txt");

// [s, e) of ar
class SliceVector
{
public:
	SliceVector(const vector<int>& ar, int s, int len)
		: _ar(ar), _start(s), _len(len)
	{
		//
	}

	SliceVector(const SliceVector& cp)
		: _ar(cp._ar), _start(cp._start), _len(cp._len)
	{
		//
	}

	SliceVector(const SliceVector& cp, int s, int len)
		: _ar(cp._ar), _start(cp._start + s), _len(len)
	{
		//
	}

private:
	const vector<int>& _ar;
	int _start, _len;

public:
	int size() const
	{
		return _len;
	}

	int operator[](int i) const
	{
		return _ar[_start + i];
	}

	bool empty() const
	{
		return _len <= 0;
	}

	int find(int num) const
	{
		vector<int>::const_iterator start = _ar.begin() + _start;
		vector<int>::const_iterator end = start + _len;
		vector<int>::const_iterator it = std::find(start, end, num);

		if (it == end)
			return -1;

		return it - start;
	}
};


void postOrder(const SliceVector& preOrder, const SliceVector& inOrder, int& level)
{
	if (preOrder.empty() || inOrder.empty())
		return;

	int root = preOrder[0];
	int rootPos = inOrder.find(root);

	level += 1;
	postOrder( SliceVector(preOrder, 1, rootPos), SliceVector(inOrder, 0, rootPos), level );
	postOrder( SliceVector(preOrder, rootPos + 1, preOrder.size() - rootPos - 1)
			 , SliceVector(inOrder, rootPos + 1, inOrder.size() - rootPos - 1), level );
	level -= 1;

	cout << root;
	if (level > 0 )
		cout << " ";
}


int main(int argc, char* argv[])
{
	std::ios::sync_with_stdio(false);

	int T = 0, N = 0;

	in >> T;

	while (T--)
	{
		in >> N;

		vector<int> preOrder(N, 0), inOrder(N, 0);

		for (int i = 0; i < N; ++i)
			in >> preOrder[i];

		for (int i = 0; i < N; ++i)
			in >> inOrder[i];

		int level = 0;
		postOrder( SliceVector(preOrder, 0, preOrder.size()), SliceVector(inOrder, 0, inOrder.size()), level );
		cout << "\n";
	}

	return 0;
}
