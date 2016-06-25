/*
Online Code Jam 2016 1차 #2 직각다각형
*/

#include <fstream>
#include <iomanip>
#include <iostream>

#include <algorithm>
#include <cmath>

using namespace std;

// istream& in = cin;
ifstream in("V:\\Work\\Algorithm\\2016-01\\input\\problem_2_Set1.in"); // problem_2_Set1 problem_2_example
// ostream& out = cout;
ofstream out("V:\\Work\\Algorithm\\2016-01\\result\\problem_2_Set1.rst");

int P1[100001];
int P2[100001];
int P3[100001];

bool isMatched(int R1[], int R2[], int N, bool forward)
{
	bool matched = false;

	for (int i = 0; !matched && i < N; ++i)
	{
		if (R2[0] == R1[i])
		{
			int a = 1, b = forward ? (i == N - 1 ? 0 : i + 1) : (i == 0 ? N - 1 : i - 1);
			while (a < N && R2[a] == R1[b])
			{
				a += 1;

				if (forward)
				{
					b += 1;
					if (b >= N) b = 0;
				}
				else
				{
					b -= 1;
					if (b < 0) b = N - 1;
				}
			}

			matched = a == N;
		}
	}

	return matched;
}

int main(int argc, char* argv[])
{
	std::ios::sync_with_stdio(false);

	int T = 0, N = 0;

	in >> T;

	while (T--)
	{
		in >> N;

		for (int i = 0; i < N; ++i)
		{
			in >> P1[i];

			// i - 1의 반대 방향
			if (i > 0)
				P3[i] = abs(P1[i]) * (P1[i - 1] < 0 ? 1 : -1);
		}
		P3[0] = abs(P1[0]) * (P1[N - 1] < 0 ? 1 : -1);

		for (int i = 0; i < N; ++i)
			in >> P2[i];

		bool matched = isMatched(P3, P2, N, false);

		if (!matched)
			matched = isMatched(P1, P2, N, true);

		out << (matched ? 1 : 0) << "\n";
	}

	return 0;
}
