/*
https://algospot.com/judge/problem/read/NEWBUS
2
3 1 3
1 2 50
1 3
2 3
2 1
5 5 5
1 2 5
2 3 4
3 4 2
1 4 10
2 4 5
1 4
2 4
3 4
3 1
2 5

no
no
only
many
only
only
only
no

It's similar to AVOID.
// */

#include <iostream>
#include <algorithm>
#include <map>
#include <queue>

using namespace std;

istream& in = cin;
ostream& out = cout;

typedef long long llong;
typedef pair<llong, llong> pint;


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
    // pathCount: start에서 각 정점까지 최소 거리로 갈 수 있는 방법의 개수
    vector<llong> dijkstra(int start, vector<llong>& pathCount)
    {
        // start에서 각 정점에 도착할 최소 거리
        vector<llong> dist = vector<llong>(_adj.size(), 0x7fffffff);

        dist[start] = 0;
        pathCount[start] = 1;

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
                    // pq에 거리가 작은 것 부터 뽑기 위하여 음수로 처리하여
                    // 트래버스해 봐야 할 정점으로 추가
                    pq.push( pint(-distThere, there) );

                    dist[there] = distThere;
                    pathCount[there] = pathCount[here];
                }
                // 현재 거리와 같다면 새로운 경로가 있는 것이므로 추가함.
                else if( dist[there] == distThere )
                {
                    pathCount[there] += pathCount[here];
                }
                // 현재 거리보다 큰 경우는 고려할 필요 없음
            }
        }

        return dist;
    }
};


int main(int argc, char* argv[])
{
	std::ios::sync_with_stdio(false);

    int T = 0, N, M, Q;

    in >> T;
    while( T-- )
    {
        in >> N >> M >> Q;

        Graph G(N);
        int v1, v2, w;

        for(int i = 0; i < M; ++i)
        {
            in >> v1 >> v2 >> w;
            G.link(v1 - 1, v2 - 1, w); // 0-based
        }

        for(int i = 0; i < Q; ++i)
        {
            in >> v1 >> v2;

            vector<llong> pathCount = vector<llong>(N, 0);
            vector<llong> distance = G.dijkstra(v1 - 1, pathCount);

            switch( pathCount[v2 - 1] )
            {
            case 0:
                out << "no\n";
                break;
            case 1:
                out << "only\n";
                break;
            default:
                out << "many\n";
                break;
            }
        }
    }

    return 0;
}
