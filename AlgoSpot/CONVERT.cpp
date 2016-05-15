/*
https://algospot.com/judge/problem/read/CONVERT
5
1 kg
2 l
7 lb
3.5 g
0 l

1 2.2046 lb
2 0.5284 g
3 3.1752 kg
4 13.2489 l
5 0.0000 g
*/
#include <iostream>
#include <map>
#include <string>

using namespace std;

istream& in = cin;
ostream& out = cout;


int main(int argc, char* argv[])
{
	map<string, pair<double, string>> conversion;

	conversion["kg"] = pair<double, string>(2.2046, "lb");
	conversion["lb"] = pair<double, string>(0.4536, "kg");
	conversion["l"] = pair<double, string>(0.2642, "g");
	conversion["g"] = pair<double, string>(3.7854, "l");

	int T = 0;

	double value;
	string unit;

	in >> T;
	for(int i = 1; i <= T; ++i)
	{
		in >> value >> unit;

		printf("%d %.4f %s\n", i, value * conversion[unit].first, conversion[unit].second.data());
	}

	return 0;
}
