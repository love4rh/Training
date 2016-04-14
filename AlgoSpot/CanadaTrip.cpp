// https://algospot.com/judge/problem/read/CANADATRIP

#include <fstream>

#include <algorithm>
#include <iomanip>
#include <iostream>

using namespace std;

//istream& in = cin;
ifstream in("V:\\Work\\Algorithm\\data\\CANADATRIP.txt");

int N = 0;
int L[5001], M[5001], G[5001];


// x 위치까지 갔을 때 만날 수 있는 표지판 개수
int calcSignNum(int x)
{
	int count = 0;
	int distGap = 0;

	for (int i = 0; i < N; ++i)
	{
		if( 0 < (distGap = std::min(x, L[i]) - (L[i] - M[i])) )
			count += distGap / G[i] + 1;
	}

	return count;
}

int solve(int K)
{
	int l = 0, h = 8030000;

	while (l < h)
	{
		int mid = (l + h) >> 1;

		if (calcSignNum(mid) >= K)
			h = mid;
		else if (l == mid)
			break;
		else
			l = mid;
	}

	return h;
}

int main(int argc, char* argv[])
{
	std::ios::sync_with_stdio(false);

	int T = 0, K = 0;

	in >> T;

	while (T--)
	{
		in >> N >> K;

		for (int i = 0; i < N; ++i)
			in >> L[i] >> M[i] >> G[i];

		cout << solve(K) << "\n";
	}

	return 0;
}
