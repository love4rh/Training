/*
https://algospot.com/judge/problem/read/BRAVE

2
5 3
1 2
2 4
3 2
10 6
1 3
7 4
2 4
5 6
9 10
8 6

4
3
*/

#include <iomanip>
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

istream& in = cin;
ostream& out = cout;

class Graph
{
public:
	// n개의 정점을 갖는 노드 표현.
	Graph(int n) : _adj(n, vector<int>()) {}

private:
	vector<vector<int> > _adj;

private:
	int bfs(int start, vector<bool>& visited)
	{
		queue<int> q;

		visited[start] = true;
		q.push(start);

		int count = 1;
		while (!q.empty())
		{
			int here = q.front();
			q.pop();

			// here의 모든 인접한 정점을 검사
			for(size_t i = 0; i < _adj[here].size(); ++i)
			{
				int there = _adj[here][i];

				// 처음 보는 정점이면 방문 목록에 넣는다.
				if( !visited[there] )
				{
					q.push(there);
					visited[there] = true;
					count += 1;
				}
			}
		}

		return count;
	}

public:
	void link(int here, int there)
	{
		_adj[here].push_back(there);
		_adj[there].push_back(here);
	}

	int bfsAll()
	{
		int countMax = -1;
		vector<bool> visited(_adj.size(), false);

		for(size_t i = 0; i < _adj.size(); ++i)
		{
			if( !visited[i] )
			{
				// 여기로 들어 오는 개수가 분리된 그래프의 개수임.
				int count = bfs(i, visited);

				if( countMax < count )
				{
					countMax = count;
				}
			}
		}

		return countMax;
	}
};




int main(int argc, char* argv[])
{
    std::ios::sync_with_stdio(false);

    int T;

    in >> T;

    while(T--)
    {
        int N, M, v1, v2;

        in >> N >> M;

        Graph G(N);

        while(M--)
        {
        	in >> v1 >> v2;

        	G.link(v1 - 1, v2 - 1);
        }

        out << G.bfsAll() << "\n";
    }

    return 0;
}
