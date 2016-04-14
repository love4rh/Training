// https://algospot.com/judge/problem/read/CSBASEBALL

#include <iostream>

using namespace std;

istream& in = cin;
ostream& out = cout;


int main(int argc, char* argv[])
{
	std::ios::sync_with_stdio(false);

	int T = 0, A, B;

	in >> T;

	while (T--)
	{
		in >> A >> B;

		out << (A > B ? 0 : (B - A + 4)) << "\n";
	}

	return 0;
}
