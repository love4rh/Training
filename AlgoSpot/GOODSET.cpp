// https://algospot.com/judge/problem/read/GOODSET

/*
2
3 4
2 3 4
3 1 2 3
1 1
3 3
3 3 2 1
2 2 1
1 1

YES
NO
*/

#include <iomanip>
#include <iostream>
#include <string.h>

using namespace std;

istream& in = cin;
ostream& out = cout;

int S[501];


int main(int argc, char* argv[])
{
	std::ios::sync_with_stdio(false);

	int T;

	in >> T;

	while(T--)
	{
		// N: participant, M: problem
		int N, M, C, P, A;

		in >> N >> M;

		memset(S, 0, sizeof(S));

		bool goodSet = true;
		for(int p = 0; p < N; ++p)
		{
			in >> C;
			A = C;

			while(A--)
			{
				in >> P;
				S[P] += 1;
			}

			if( goodSet && (C == 0 || C == M) ) goodSet = false;
		}

		if( goodSet ) {
			goodSet = false;
			for(int i = 1; i <= M; ++i)
				if( S[i] > 0 )
				{
					goodSet = true;
					break;
				}
		}

		out << (goodSet ? "YES" : "NO") << "\n";
	}

	return 0;
}
