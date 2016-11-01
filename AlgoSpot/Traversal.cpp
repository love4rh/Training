// https://algospot.com/judge/problem/read/TRAVERSAL

/*
1
7
27 16 9 12 54 36 72
9 12 16 27 36 54 72
*/

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

istream& in = cin;
ostream& out = cout;

// [s, e) of ar
class Slice
{
public:
	Slice(const vector<int>& ar, int s, int len)
		: _ar(ar), _start(s), _len(len)
	{
		//
	}

	Slice(const Slice& cp)
		: _ar(cp._ar), _start(cp._start), _len(cp._len)
	{
		//
	}

	Slice(const Slice& cp, int s, int len)
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


void postOrder(const Slice& preOrder, const Slice& inOrder, int level)
{
	if (preOrder.empty() || inOrder.empty())
		return;

	int root = preOrder[0];
	int rootPos = inOrder.find(root);

	postOrder( Slice(preOrder, 1, rootPos)
			 , Slice(inOrder, 0, rootPos), level + 1 );

	postOrder( Slice(preOrder, rootPos + 1, preOrder.size() - rootPos - 1)
			 , Slice(inOrder, rootPos + 1, inOrder.size() - rootPos - 1), level + 1 );

	out << root;
	if (level > 0 )
		out << " ";
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

		postOrder( Slice(preOrder, 0, preOrder.size()), Slice(inOrder, 0, inOrder.size()), 0 );
		out << "\n";
	}

	return 0;
}
