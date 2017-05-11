#ifndef _DISJOINT_SET_H_
#define _DISJOINT_SET_H_

#include <algorithm>
#include <vector>

using namespace std;


// 상호 배타적 집합 구현
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
	// 해당 위치의 노드의 부모 노드 정보
	vector<int>	_parent;

	// 트리의 깊이가 깊어지는 것을 방지하기 위한 비교 값.
	// 여기서는 노드의 깊이를 Rank로 이용함.
	vector<int>	_rank;

public:
	// u가 속한 트리의 루트 번호를 반환한다.
	// find(v) == find(v) --> u, v는 같은 그룹에 속한 원소임.
	int find(int u)
	{
		if (u == _parent[u]) return u;

		return _parent[u] = find(_parent[u]);
	}

	// u가 속한 트리와 v가 속한 트리를 합침 --> 같은 그룹으로 만듦
	void merge(int u, int v)
	{
		u = find(u); v = find(v);

		// 이미 같은 그룹이므로 리턴
		if (u == v) return;

		if (_rank[u] > _rank[v]) swap(u, v);

		_parent[u] = v;
		if (_rank[u] == _rank[v]) ++_rank[v];
	}
};

#endif // _DISJOINT_SET_H_
