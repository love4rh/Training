/*
https://algospot.com/judge/problem/read/HOTSUMMER
3
90
10 10 10 10 10 10 10 10 10
1000
77 77 70 11 34 35 41 83 54
50
10 20 30 40 50 60 50 40 3012

YES
YES
NO
*/

#include <iostream>
#include <algorithm>


using namespace std;

istream& in = cin;
ostream& out = cout;


int main()
{
	std::ios::sync_with_stdio(false);

	int T;

	in >> T;
	while (T--)
	{
		int W;
		int sum = 0, P;
		
		in >> W;
		for (int i = 0; i < 9; ++i)
		{
			in >> P;
			sum += P;
		}

		out << (W >= sum ? "YES" : "NO") << "\n";
	}

	return 0;
}
