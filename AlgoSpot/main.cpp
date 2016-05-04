/*
https://algospot.com/judge/problem/read/PI
5
12341234
11111222
12122222
22222222
12673939

4
2
5
2
14
*/

#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>
#include <cmath>


using namespace std;

istream& in = cin;
ostream& out = cout;


string digits;

// 지정된 구간 내 문자열에 대한 난이도 계산
int levelOfDifficulty(int start, int len)
{
	// 동일 숫자 --> 1
	// 1씩 단조 증가 혹은 감소 --> 2
	// 두 개의 숫자 반복 --> 4
	// 등차수열(2이상 단조 증가 혹은 감소) --> 5
	// 이외 10

	int end = start + len - 1;
	int d1 = digits[start] - digits[start + 1];
	int d2 = d1;

	bool sameDiff = true;
	for (int i = start + 1; sameDiff && i < end; ++i)
	{
		int d = digits[i] - digits[i + 1];

		sameDiff = abs(d2) == abs(d);

		d1 = d2;
		d2 = d;
	}

	int level = 10;

	if (sameDiff)
	{
		if (d1 == 0)
			level = 1;
		else if (d1 == -1 * d2)
			level = 4;
		else if (d1 == 1 || d1 == -1)
			level = 2;
		else if (d1 == 1 || d1 == -1)
			level = 5;
	}

	return level;
}

int calMinimum(int begin)
{

}

int main()
{
	std::ios::sync_with_stdio(false);

	int T;

	in >> T;
	while (T--)
	{
		in >> digits;

		out << calMinimum(0) << "\n";
	}

	return 0;
}
