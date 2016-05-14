/*
https://www.algospot.com/judge/problem/read/ENDIANS
4
2018915346
1
100000
4294967295

305419896
16777216
2693136640
4294967295
*/

#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>


using namespace std;

istream& in = cin;
ostream& out = cout;

char digits[10];
char converted[10];

int convertTable[] = { 6, 7, 4, 5, 2, 3, 0, 1 };


int main()
{
	std::ios::sync_with_stdio(false);

	int T;
	unsigned int N;

	in >> T;
	while (T--)
	{
		in >> N;

		sprintf(digits, "%08x", N);

		for (int i = 0; i < 8; ++i)
			converted[i] = digits[convertTable[i]];

		converted[8] = 0;

		out << std::stoul(string(converted), nullptr, 16) << "\n";
	}

	return 0;
}

