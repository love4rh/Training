/*
https://www.algospot.com/judge/problem/read/MISPELL
4
4 MISSPELL
1 PROGRAMMING
7 CONTEST
3 BALLOON
*/

#include <iostream>
#include <string>


using namespace std;

istream& in = cin;
ostream& out = cout;


int main()
{
	std::ios::sync_with_stdio(false);

	int T;

	in >> T;

	for(int i = 1; i <= T; ++i)
	{
		int M;
		string word;

		in >> M >> word;

		out << i << " ";

		if (M > 1)
			out << word.substr(0, M - 1);

		if (M < word.size())
			out << word.substr(M);

		out << "\n";
	}

	return 0;
}
