/*
https://algospot.com/judge/problem/read/TSP1
2
3
0.0000000000  611.6157225201  648.7500617289
611.6157225201  0.0000000000  743.8557967501
648.7500617289  743.8557967501  0.0000000000
4
0.0000000000  326.0008994586  503.1066076077  290.0250922998
326.0008994586  0.0000000000  225.1785728436  395.4019367384
503.1066076077  225.1785728436  0.0000000000  620.3945520632
290.0250922998  395.4019367384  620.3945520632  0.0000000000

1260.3657842490
841.2045646020
*/
#include <iostream>
#include <algorithm>
#include <limits>
#include <cmath>
#include <cstring>

using namespace std;

istream& in = cin;
ostream& out = cout;

const int MAX_LIMIT = 10;

int N = 0;

double dist[MAX_LIMIT][MAX_LIMIT];

int traversed[MAX_LIMIT];

double minSum = 0;


void solve(int start, int count, double sum)
{
	if (count >= N - 1)
	{
		minSum = min(sum, minSum);
		return;
	}

	traversed[start] = 1;

	for (int i = 0; i < N; ++i)
	{
		if (traversed[i])
			continue;

		sum += dist[start][i];
		solve(i, count + 1, sum);
		sum -= dist[start][i];
	}

	traversed[start] = 0;
}

int main(int argc, char* argv[])
{
	int T = 0;

	in >> T;
	while (T--)
	{
		in >> N;
		
		for (int i = 0; i < N; ++i)
			for (int j = 0; j < N; ++j)
			{
				in >> dist[i][j];
				dist[j][i] = dist[i][j];
			}
		
		memset(traversed, 0, sizeof(traversed));
		minSum = numeric_limits<double>::max();

		for (int i = 0; i < N; ++i)
			solve(i, 0, 0);

		printf("%.10f\n", minSum);
	}

	return 0;
}
