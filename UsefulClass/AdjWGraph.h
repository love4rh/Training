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
	// ���� �����Ͽ� �׷��� ����
	// here --weight--> there��
	void link(int here, int there, int weight)
	{
		_adj[here].push_back(pair<int, int>(there, weight));
	}

	// ���ͽ�Ʈ���� �ִ� �Ÿ� �˰���
	// �������� s�������� �ٸ� ��������� �ִ� �Ÿ��� �����.
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

			// ���� ���� �ͺ�Ÿ �� ª�� ��θ� �˰� �ִٸ� ���� ���� ���� ����
			if (dist[here] < cost)
				continue;

			// ������ �������� �˻�
			for (int i = 0; i < _adj[here].size(); ++i)
			{
				int there = _adj[here][i].first;
				int nextDist = cost + _adj[here][i].second;

				// �� ª�� ��θ� �߰��ϸ�, dist[]�� �����ϰ� �켱���� ť�� �ִ´�.
				if (dist[there] > nextDist)
				{
					dist[there] = nextDist;
					pq.push(pair<int, int>(-nextDist, there));
				}
			}
		}

		return dist;
	}

	// �켱���� ť�� �̿����� �ʴ� ���ͽ�Ʈ�� �˰���
	vector<int> dijkstra2(int s)
	{
		vector<bool> visited(_adj.size(), false);
		vector<int> dist(_adj.size(), numeric_limits<int>::max());

		dist[s] = 0; visited[s] = true;

		while (1)
		{
			// ���� �湮���� ���� ���� �� ���� ����� ������ ã�´�.
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

			// ���� ����� ������ �湮�Ѵ�.
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

	// �������� s�������� �ٸ� ��������� �ִ� �Ÿ��� �����. ���� ����ġ�� �����
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
