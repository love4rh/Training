#ifndef _DISJOINT_SET_H_
#define _DISJOINT_SET_H_

#include <algorithm>
#include <vector>

using namespace std;


// ��ȣ ��Ÿ�� ���� ����
class DisjointSet
{
public:
	DisjointSet(int n)
		: _parent(n), _rank(n)
	{
		for (int i = 0; i < n; ++i)
		{
			_parent[i] = i;
			_rank[i] = 0;
		}
	}

private:
	// �ش� ��ġ�� ����� �θ� ��� ����
	vector<int>	_parent;

	// Ʈ���� ���̰� ������� ���� �����ϱ� ���� �� ��.
	// ���⼭�� ����� ���̸� Rank�� �̿���.
	vector<int>	_rank;

public:
	// u�� ���� Ʈ���� ��Ʈ ��ȣ�� ��ȯ�Ѵ�.
	// find(v) == find(v) --> u, v�� ���� �׷쿡 ���� ������.
	int find(int u)
	{
		if (u == _parent[u]) return u;

		return _parent[u] = find(_parent[u]);
	}

	// u�� ���� Ʈ���� v�� ���� Ʈ���� ��ħ --> ���� �׷����� ����
	void merge(int u, int v)
	{
		u = find(u); v = find(v);

		// �̹� ���� �׷��̹Ƿ� ����
		if (u == v) return;

		if (_rank[u] > _rank[v]) swap(u, v);

		_parent[u] = v;
		if (_rank[u] == _rank[v]) ++_rank[v];
	}
};

#endif // _DISJOINT_SET_H_
