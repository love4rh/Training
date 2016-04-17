#ifndef _ADJWGRAPH_H_H
#define _ADJWGRAPH_H_H

#include <algorithm>
#include <queue>
#include <vector>

using namespace std;


class AdjWeightGraph
{
public:
	AdjWeightGraph(int n) : _adj(n) {}

private:
	vector<vector<pair<int, int>>> _adj;

public:
	// 정점 연결하여 그래프 구성
	// here --weight--> there임
	void link(int here, int there, int weight)
	{
		_adj[here].push_back(pair<int, int>(there, weight));
	}

	// 다익스트라의 최단 거리 알고리즘
	// 시작정점 s에서부터 다른 정점들까의 최단 거리를 계산함.
	vector<int> dijkstra(int s)
	{
		vector<int> dist(_adj.size(), numeric_limits<int>::max());
		dist[s] = 0;

		priority_queue<pair<int, int> > pq;
		pq.push(pair<int, int>(0, s));

		while (!pq.empty())
		{
			int cost = -pq.top().first;
			int here = pq.top().second;

			pq.pop();

			// 지금 꺼낸 것보타 더 짧은 경로를 알고 있다면 지금 꺼낸 것을 무시
			if (dist[here] < cost)
				continue;

			// 인전한 정점들을 검사
			for (int i = 0; i < _adj[here].size(); ++i)
			{
				int there = _adj[here][i].first;
				int nextDist = cost + _adj[here][i].second;

				// 더 짧은 경로를 발견하면, dist[]를 갱신하고 우선순위 큐에 넣는다.
				if (dist[there] > nextDist)
				{
					dist[there] = nextDist;
					pq.push(pair<int, int>(-nextDist, there));
				}
			}
		}

		return dist;
	}

	// 우선순위 큐를 이용하지 않는 다익스트라 알고리즘
	vector<int> dijkstra2(int s)
	{
		vector<bool> visited(_adj.size(), false);
		vector<int> dist(_adj.size(), numeric_limits<int>::max());

		dist[s] = 0; visited[s] = true;

		while (1)
		{
			// 아직 방문하지 않은 정점 중 가장 가까운 정점을 찾는다.
			int here, closest = numeric_limits<int>::max();
			for (int i = 0; i < _adj.size(); ++i)
			{
				if (dist[i] < closest && !visited[i])
				{
					here = i;
					closest = dist[i];
				}
			}

			if (closest == numeric_limits<int>::max())
				break;

			// 가장 가까운 정점을 방문한다.
			visited[here] = true;
			for (int i = 0; i < _adj[here].size(); ++i)
			{
				int there = _adj[here][i].first;
				if (visited[there])
					continue;

				int nextDist = dist[here] + _adj[here][i].second;
				dist[there] = min(dist[there], nextDist);
			}
		}

		return dist;
	}

	// 시작정점 s에서부터 다른 정점들까의 최단 거리를 계산함. 음수 가중치를 고려함
	vector<int> bellmanFord(int s)
	{
		vector<int> upper(_adj.size(), numeric_limits<int>::max());
		upper[s] = 0;

		bool updated;

		for (int iter = 0; iter < _adj.size(); ++iter)
		{
			updated = false;
			for (int here = 0; here < _adj.size(); ++here)
			{
				for (int i = 0; i < _adj[here].size(); ++i)
				{
					int there = _adj[here][i].first;
					int cost = _adj[here][i].second;

					if (upper[there] > upper[here] + cost)
					{
						upper[there] = upper[here] + cost;
						updated = true;
					}
				}
			}
			if (!updated) break;
		}

		if (updated) upper.clear();

		return upper;
	}
};

#endif
