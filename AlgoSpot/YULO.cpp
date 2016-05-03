/*
https://www.algospot.com/judge/problem/read/YULO
3
3
48 96 73
4
0 0 98 99
5
35 85 94 76 40

73.0
49.5
76.0
*/

#include <iostream>
#include <algorithm>
#include <vector>


using namespace std;

istream& in = cin;
ostream& out = cout;


int main()
{
	std::ios::sync_with_stdio(false);

	int T, N;

	in >> T;

	while (T--)
	{
		in >> N;

		vector<int> score(N, 0);

		for (int i = 0; i < N; ++i)
			in >> score[i];

		std::sort(score.begin(), score.end());

		double maxAvg = 0.0;

		for (int i = 0; i < (N + 1) / 2; ++i)
		{
			double avg = score[i] + score[N - i - 1];
			avg /= 2.0;

			if (maxAvg < avg)
				maxAvg = avg;
		}

		printf("%.1f\n", maxAvg);
	}

	return 0;
}
