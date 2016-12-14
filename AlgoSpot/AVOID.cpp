/*
https://algospot.com/judge/problem/read/AVOID

2
8 10 4
1 2 1
2 4 1
1 3 1
3 4 1
1 4 2
4 5 2
5 7 1
5 8 3
4 6 1
6 8 4
2 4 5 7
4 4 2
1 2 1
1 3 1
2 4 1
3 4 1
2 4

1/3
1/1
1/2
0/1
1/2
1/1
*/

#include <iomanip>
#include <iostream>
#include <vector>
#include <map>
#include <queue>

using namespace std;

istream& in = cin;
ostream& out = cout;

typedef long long llong;
typedef pair<llong, llong> pint;


llong gcd(llong a, llong b)
{
    if( b == 0 ) return a;

    return gcd(b, a % b);
}


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

    int T;
    in >> T;

    while(T--)
    {
        int V, E, N;
        int v1, v2, w, p;

        in >> V >> E >> N;

        Graph G(V);
        while(E--)
        {
            in >> v1 >> v2 >> w;
            G.link(v1 - 1, v2 - 1, w);
        }

        vector<llong> pathCount1toV = vector<llong>(V, 0);
        vector<llong> pathCountVto1 = vector<llong>(V, 0);

        vector<llong> dist1toV = G.dijkstra(0, pathCount1toV);
        vector<llong> distVto1 = G.dijkstra(V - 1, pathCountVto1);

        while(N--)
        {
            in >> p;

            p -= 1; // 0-based

              // 1에서 V까지 가는 최소 경로 중 p 점을 지나는 경로의 개수
            llong pcount = 0;

            // p까지의 순방향 거리와 역방향 거리의 합이 1에서 V까지 가는데 소요된 거리와 같다면
              // 1에서 V까지 가는데 p점을 거쳐가게 됨. 다르라면 지나는 점이 아님
            if( dist1toV[p] + distVto1[p] == distVto1[0] )
            {
            	// (p점에서 정점 1까지 갈 수 있는 개수) x (p점에서 정점 V까지 갈 수 있는 개수) --> 1에서 p점을 거쳐 V까지 갈 수 있는 경우의 수
            	pcount = pathCount1toV[p] * pathCountVto1[p];
            }

            if( pcount == 0 )
            	out << "0/1\n";
            else
            {
            	llong d = gcd(pcount, pathCountVto1[0]);

            	out << (pcount / d) << "/" << (pathCountVto1[0] / d) << "\n";
            }
        }
    }

    return 0;
}
