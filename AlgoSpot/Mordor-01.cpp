// https://algospot.com/judge/problem/read/MORDOR

#include <fstream>

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

//istream& in = cin;
ifstream in("V:\\Work\\Algorithm\\data\\mordor.txt");


int H[100001];

int main(int argc, char* argv[])
{
	std::ios::sync_with_stdio(false);

	int T = 0, N = 0, Q = 0;

	in >> T;

	while (T--)
	{
		in >> N >> Q;

		for (int i = 0; i < N; ++i)
			in >> H[i];

		int S, E;
		for (int i = 0; i < Q; ++i)
		{
			in >> S >> E;

			int minH = H[S], maxH = H[S];

			for (int j = S + 1; j <= E; ++j)
			{
				if (minH > H[j])
					minH = H[j];

				if (maxH < H[j])
					maxH = H[j];
			}

			cout << maxH - minH << "\n";
		}
	}

	return 0;
}
