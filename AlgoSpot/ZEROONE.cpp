/*
https://algospot.com/judge/problem/read/ZEROONE
0000011111
0001110001100
6
0 5
4 2
5 9
9 10
10 11
11 12

No
Yes
Yes
*/

#include <stdio.h>
#include <iostream>
#include <algorithm>
// #include <fstream>


using namespace std;

istream& in = cin;
// ifstream in("/home/ibs/data/work/cppSpace/AlgoSpot/data/ZEROONE.txt");
ostream& out = cout;
// ofstream out("/home/ibs/data/work/cppSpace/AlgoSpot/data/ZEROONE.txt");

string digits;
int digitSum[1000004];


int main()
{
	std::ios::sync_with_stdio(false);

	int T;

	digits.reserve(1000003);
	in >> digits;

	// 0000011111 인 경우 digitSum에는 다음과 같이 값이 들어감
	// --> 0000012345

	int sum = 0;
	digitSum[0] = 0;

	const char* s = digits.data();
	int* d = digitSum + 1;
	do
	{
		sum += (*s - '0');

		*d = sum;
		s++; d++;
	} while (*s);

	in >> T;
	while (T--)
	{
		int i, j;

		in >> i >> j;

		if (i > j)
		{
			int t = j;
			j = i;
			i = t;
		}

		int diff = digitSum[j + 1] - digitSum[i];

		printf("%s\n", ((diff == 0 || diff == (j - i + 1)) ? "Yes" : "No"));
	}

	return 0;
}
