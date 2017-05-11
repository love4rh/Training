#ifndef _ADJGRAPH_H_
#define _ADJGRAPH_H_

#include <algorithm>
#include <queue>
#include <vector>

using namespace std;


// 인접 리스트 형태로 표현한 그래프
class AdjGraph
{
public:
	// n개의 정점을 갖는 노드 표현.
	AdjGraph(int n) : _adj(n, vector<int>()) {}

private:
	vector<vector<int>> _adj;

private:
	void dfs(int here, vector<int>& order, vector<bool>& visited)
	{
		order.push_back(here);	// 방문 완료
		visited[here] = true;

		// 인접한 정점을 순회
		for (int i = 0; i < _adj[here].size(); ++i)
		{
			int there = _adj[here][i];

			if (!visited[there])
				dfs(there, order, visited);
		}
	}

	// 위상정렬을 위한 깊이 우선 탐색
	void dfs4ts(int here, vector<int>& order, vector<int>& seen)
	{
		seen[here] = 1;
		for (int there = 0; there < _adj[here].size(); ++there)
		{
			if (_adj[here][there] && !seen[there])
				dfs4ts(there, order, seen);
		}

		order.push_back(here);
	}

	// 최단 경로를 계산하는 너비 우선 탐색
	// start에서 시작해 그래프를 너무 우선 탐색하고
	// 시작점부터 각 정점까지의 최단 거리와 너비 우선 탐색 스패닝 트리를 계산한다.
	// distance[i] = start부터 i까지의 최단거리
	// parent[i] = 너비 우선 탐색 스패닝 트리에서 i의 부모의 번호. 루트인 경우 자신의 번호.
	void bfs2(int start, vector<int>& distance, vector<int>& parent)
	{
		distance = vector<int>(_adj.size(), -1);
		parent = vector<int>(_adj.size(), -1);

		// 방문할 정점 목록을 유지하는 큐
		queue<int> q;

		distance[start] = 0;
		parent[start] = start;
		q.push(start);

		while (!q.empty())
		{
			int here = q.front();
			q.pop();

			// here의 모든 인접한 정점을 검사
			for (int i = 0; i < _adj[here].size(); ++i)
			{
				int there = _adj[here][i];

				// 처음 보는 정점이면 방문 목록에 넣는다.
				if (distance[there] == -1)
				{
					q.push(there);
					distance[there] = distance[here] + 1;
					parent[there] = here;
				}
			}
		}
	}

public:
	// 정점 연결하여 그래프 구성
	// here --> there임
	void link(int here, int there)
	{
		_adj[here].push_back(there);
	}

	// 정점 연결하여 그래프 구성
	// here <--> there임
	void linkBoth(int here, int there)
	{
		link(here, there);
		link(there, here);
	}

	// 깊이 우선 탐색
	vector<int> dfsAll()
	{
		vector<int> order;
		order.reserve(_adj.size());

		vector<bool> visited = vector<bool>(_adj.size(), false);

		for (int i = 0; i < _adj.size(); ++i)
			if (!visited[i])
			{
				// 여기로 들어 오는 개수가 분리된 그래프의 개수임.
				dfs(i, order, visited);
			}

		return order;
	}

	// 위상정렬
	vector<int> topologiclaSort()
	{
		int n = _adj.size();

		vector<int> seen = vector<int>(n, 0);
		vector<int> order;
		order.reserve(n);

		for (int i = 0; i < n; ++i)
			if (!seen[i]) dfs4ts(i, order, seen);

		reverse(order.begin(), order.end());

		// 만약 그래프가 DAG가 아니라면 정렬 결과에 역발향 간선이 있음.
		for (int i = 0; i < n; ++i)
			for (int j = i + 1; j < n; ++j)
				if (_adj[order[j]][order[i]])
					return vector<int>();

		// 역방향이 없는 경우
		return order;
	}

	// 너비우선 탐색
	vector<int> bfs(int start)
	{
		vector<bool> discovered(_adj.size(), false);
		queue<int> q;
		vector<int> order;

		discovered[start] = true;
		q.push(start);

		while (!q.empty())
		{
			int here = q.front();
			q.pop();

			order.push_back(here);	// here를 방문

			// 인접한 정점 검사
			for (int i = 0; i < _adj[here].size(); ++i)
			{
				int there = _adj[here][i];

				if (!discovered[there])
				{
					q.push(there);
					discovered[there] = true;
				}
			}
		}

		return order;
	}

	// v로 부터 시작점까지의 최단 경로를 계산한다.
	vector<int> shortesPath(int v, int start)
	{
		vector<int> distance, parent;

		bfs2(start, distance, parent);

		vector<int> path(1, v);

		while (parent[v] != v)
		{
			v = parent[v];
			path.push_back(v);
		}

		reverse(path.begin(), path.end());

		return path;
	}
};


#endif
