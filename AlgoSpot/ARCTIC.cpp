/*
https://www.algospot.com/judge/problem/read/ARCTIC
2
5
0 0
1 0
1 1
1 2
0 2
6
1.0 1.0
30.91 8
4.0 7.64
21.12 6.0
11.39 3.0
5.31 11.0

1.00
10.18
*/

#include <iostream>
#include <algorithm>
#include <cmath>
#include <set>
#include <cstring>


using namespace std;

istream& in = cin;
ostream& out = cout;

int N;

double P[101][2];	// 기지의 위치
double D[101][101];	// 기지간 거리

set<double> uniqueDist;


double euclidean(double x1, double y1, double x2, double y2)
{
	return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

int visited[101];

// a 번째 기지로 부터 최대 d거리만큼씩 이동하여 갈 수 있는 기지의 수.
// 이 반환 값이 N이면 모든 기지를 순회할 수 있는 것임.
int traverse(int a, double d)
{
	int count = 1; // a는 방문하니 초기값은 1

	visited[a] = 1;

	for (int i = 0; i < N; ++i)
	{
		// 이미 방문한 기지임
		if (visited[i] == 1)
			continue;

		if (D[a][i] <= d)
			count += traverse(i, d);
	}

	return count;
}

int main()
{
	std::ios::sync_with_stdio(false);

	int T;

	in >> T;
	while (T--)
	{
		in >> N;

		uniqueDist.clear();
		for (int i = 0; i < N; ++i)
		{
			in >> P[i][0] >> P[i][1];

			D[i][i] = 0;
			for (int j = 0; j < i; ++j)
			{
				D[i][j] = D[j][i] = euclidean(P[i][0], P[i][1], P[j][0], P[j][1]);

				uniqueDist.insert(D[i][j]);
			}
		}

		// 아래를 이분법으로 나눠서 계산해 나가면 더 빠르게 할 수 있음.
		for (set<double>::iterator it = uniqueDist.begin(); it != uniqueDist.end(); ++it)
		{
			memset(visited, 0, sizeof(visited));

			if (traverse(0, *it) >= N)
			{
				printf("%.2f\n", *it);
				break;
			}

		}
	}

	return 0;
}
