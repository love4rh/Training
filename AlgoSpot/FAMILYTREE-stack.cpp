// https://algospot.com/judge/problem/read/FAMILYTREE

/*
1
13 7
0 1 1 3 3 0 6 0 8 9 9 8
2 7
10 11
4 11
7 7
10 0
6 7
0 10

4
2
6
0
3
1
3
*/

#include <iomanip>
#include <iostream>
#include <string.h>
#include <stack>

using namespace std;

istream& in = cin;
ostream& out = cout;

int A[100000];	// Ancestor #


int main(int argc, char* argv[])
{
	std::ios::sync_with_stdio(false);

	int T;

	in >> T;

	while(T--)
	{
		// N: No. of people, Q: No. of Questions
		int N, Q;

		in >> N >> Q;

		for(int i = 1; i < N; ++i)
			in >> A[i];

		int p1, p2;

		while(Q--)
		{
			in >> p1 >> p2;

			// find LCA between p1 and p2
			if( p1 == p2 )
				out << 0 << "\n";
			else
			{
				stack<int> f1, f2;

				f1.push(p1);
				while( p1 != 0 )
				{
					p1 = A[p1];
					f1.push(p1);
				}

				f2.push(p2);
				while( p2 != 0 )
				{
					p2 = A[p2];
					f2.push(p2);
				}

				while( !f1.empty() && !f2.empty() && f1.top() == f2.top() )
				{
					f1.pop();
					f2.pop();
				}

				out << (f1.size() + f2.size()) << "\n";
			}
		}
	}

	return 0;
}
