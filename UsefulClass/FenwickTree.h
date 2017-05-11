#ifndef _FENWICK_TREE_H_
#define _FENWICK_TREE_H_

#include <vector>

using namespace std;


template<typename _VT> class FenwickTree
{
public:
	FenwickTree(int n) : _tree(n + 1) {}

private:
	vector<_VT>		_tree;

public:
	// [0, pos] 구간의 합을 반환
	_VT sum(int pos)
	{
		pos += 1;

		_VT ret = _VT();
		while(pos > 0)
		{
			ret += _tree[pos];
			pos &= (pos - 1);
		}

		return ret;
	}

	// pos 위치를 포함하는 영역에 값을 더함.
	void add(int pos, _VT val)
	{
		pos += 1;
		while (pos < _tree.size())
		{
			_tree[pos] += val;
			pos += (pos & -pos);
		}
	}
};

#endif
