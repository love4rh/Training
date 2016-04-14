/*
https://www.algospot.com/judge/problem/read/MEETING
2
4
1 2 3 4
8 6 7 5
3
-1 0 1
-1 -1 -1
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

		vector<int> M(N, 0);
		vector<int> W(N, 0);

		for (int i = 0; i < N; ++i)
			in >> M[i];

		for (int i = 0; i < N; ++i)
			in >> W[i];

		std::sort(M.begin(), M.end());
		std::sort(W.begin(), W.end());

		int sum = 0;
		for (int i = 0; i < N; ++i)
			sum += abs(M[i] - W[i]);

		out << sum << endl;
	}

	return 0;
}
