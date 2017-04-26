/*
https://algospot.com/judge/problem/read/FIRETRUCKS
2
8 12 3 2
1 2 3
1 6 9
2 3 6
3 4 4
3 5 2
4 5 7
6 5 5
8 6 5
6 7 3
8 7 3
7 5 1
2 8 3
2 3 5
4 6

16
// */

#include <iomanip>
#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <limits>

using namespace std;

typedef pair<int, int> pint;


istream& in = cin;
ostream& out = cout;


class Graph
{
public:
    Graph(int n) : _adj(n, vector<pint>()) {}

private:
    vector<vector<pint> > _adj;

public:
    void link(int here, int there, int weight)
    {
        _adj[here].push_back(pint(there, weight));
        _adj[there].push_back(pint(here, weight));
    }

    // start: 시작점
    vector<int> dijkstra(int start)
    {
        // start에서 각 정점에 도착할 최소 거리
        vector<int> dist = vector<int>(_adj.size(), numeric_limits<int>::max());

        dist[start] = 0;

        priority_queue<pint> pq;
        pq.push(pint(0, start));

        while( !pq.empty() )
        {
            int cost = -pq.top().first;
            int here = pq.top().second;

            pq.pop();

            // 비용이 현재 것 보다 크다면 더 이상 할 필요 없음
            if( dist[here] < cost ) continue;

            for(int i = 0; i < int(_adj[here].size()); ++i)
            {
            	pint& v2 = _adj[here][i];

                int there = v2.first;
                int distThere = cost + v2.second;

                // 현재 거리보다 작다면 더 작은 경로가 있는 것이므로
                // 큐에 넣고 경로 회수를 초기화 해야 함.
                if( dist[there] > distThere )
                {
                    // pq에 거리가 작은 것부터 뽑기 위하여 음수로 처리하여
                    // 트래버스해 봐야 할 정점으로 추가
                    pq.push( pint(-distThere, there) );

                    dist[there] = distThere;
                }
            }
        }

        return dist;
    }
};


int main(int argc, char* argv[])
{
    std::ios::sync_with_stdio(false);

    int T;
    in >> T;

    while(T--)
    {
        int V, E, n, m;
        int v1, v2, w, tmp;

        in >> V >> E >> n >> m;

        Graph G(V);
        while(E--)
        {
            in >> v1 >> v2 >> w;
            G.link(v1 - 1, v2 - 1, w);
        }

        // read the numbers of fire places
        vector<int> firePlace(n, 0);
        for(int i = 0; i < n; ++i)
        {
        	in >> tmp;
        	firePlace[i] = tmp -1;
        }

        // read the numbers of fire stations
        vector<int> fireStation(m, 0);
        for(int j = 0; j < m; ++j)
        {
        	in >> tmp;
        	fireStation[j] = tmp -1;
        }

        int distSum = 0;
        for(int i = 0; i < n; ++i)
        {
        	vector<int> distance = G.dijkstra(firePlace[i]);

        	int minVal = numeric_limits<int>::max();
        	for(int j = 0; j < m; ++j)
        		minVal = min(minVal, distance[fireStation[j]]);

        	distSum += minVal;
        }

        out << distSum << "\n";
    }

    return 0;
}
