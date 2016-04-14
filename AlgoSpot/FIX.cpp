/*
https://www.algospot.com/judge/problem/read/FIX
2
12
9 11 4 2 6 3 10 8 1 12 7 5
12
1 7 9 10 2 11 6 4 3 12 5 8
*/
#include <fstream>

#include <iomanip>
#include <iostream>

using namespace std;

istream& in = cin;
ostream& out = cout;


int main(int argc, char* argv[])
{
	int T = 0;

	in >> T;

	while (T--)
	{
		int N, degree, count = 0;

		in >> N;

		for (int i = 1; i <= N; ++i)
		{
			in >> degree;

			if (i == degree)
				count += 1;
		}

		out << count << endl;
	}

	return 0;
}
