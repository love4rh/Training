/*
https://www.algospot.com/judge/problem/read/PROMISES
2
4 2 2
0 1 4
0 3 1
0 2 2
1 2 6
4 2 2
0 1 4
0 3 1
1 2 6
0 2 2

1
0
*/

#include <iostream>
#include <cstring>
#include <limits>
#include <algorithm>

using namespace std;

istream& in = cin;
ostream& out = cout;

const int MAX_NUM = 201;
const int INF = numeric_limits<int>::max() - 1;

int V, M, N;
int cost[MAX_NUM][MAX_NUM];


// a에서 b로 가는 최소 비용 (cost[a][b]) 계산.
// a에서 b로 가는 비용은 중간 k를 거처가는 경우의 비용과 비교해서 적은 쪽이 최소 비용임.
// 따라서, min(cost(a->b), cost(a->k) + cost(k->b)) 임.
// 갈수 없는 경로의 비용 INF로 함.
void calcDistance()
{
	// a -> a는 비용이 0임.
	for (int a = 0; a < V; ++a)
		cost[a][a] = 0;

	for(int a = 0; a < V; ++a)
		for (int b = 0; b < V; ++b)
			for (int k = 0; k < V; ++k)
			{
				if (cost[a][k] < INF && cost[k][b] < INF)
					cost[a][b] = min(cost[a][b], cost[a][k] + cost[k][b]);
			}
}

// a에서 b로 가는 비용이 w인 도로를 새로 추가함.
// 추가한 도로가 기존 대비 비용이 적은 도로라면 true 반환.
bool addRoad(int a, int b, int w)
{
	// 기존 경로 비용이 더 작다면 더 이상 계산할 필요 없음
	if (cost[a][b] <= w)
		return false;

	// 새로운 길의 비용 추가
	cost[a][b] = cost[b][a] = w;

	// 새로운 도로를 건설했을 때 다른 도시간 비용이 감소하는 경우가 있는 지 계산
	// a<->b에 따라 변경된 경로의 비용을 계산해서 업데이트 해야 함.
	// 경로의 비용은 x->y, x->a->b->y, x->b->a->y 중 작은 것으로 업데이트 하면 됨.
	for(int x = 0; x < V; ++x)
		for (int y = 0; y < V; ++y)
		{
			if (cost[x][a] < INF && cost[b][y] < INF)
				cost[x][y] = min(cost[x][y], cost[x][a] + w + cost[b][y]);

			if (cost[x][b] < INF && cost[a][y] < INF)
				cost[x][y] = min(cost[x][y], cost[x][b] + w + cost[a][y]);
		}

	// 기존 경로보다 작은 비용이라면 도로 건설이 유의미함
	return true;
}

int main()
{
	std::ios::sync_with_stdio(false);

	int T;

	in >> T;
	while(T--)
	{
		in >> V >> M >> N;

		for(int i = 0; i < V; ++i)
			for (int j = 0; j < V; ++j)
				cost[i][j] = INF;

		int from, to, weight;

		for (int i = 0; i < M; ++i)
		{
			in >> from >> to >> weight;
			cost[to][from] = cost[from][to] = weight;
		}

		// 도시 A에서 B로 갈 때의 비용 계산
		calcDistance();

		int usefulCount = 0;
		for (int i = 0; i < N; ++i)
		{
			in >> from >> to >> weight;
			
			// 새로운 도로를 추가 함.
			if (addRoad(from, to, weight))
				usefulCount += 1;
		}

		out << (N - usefulCount) << "\n";
	}

	return 0;
}
