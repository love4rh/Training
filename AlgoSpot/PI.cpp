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

int cached[10005];


// ������ ���� �� ���ڿ��� ���� ���̵� ���
int calcDifficulty(int start, int len)
{
	// ���� ���� --> 1
	// 1�� ���� ���� Ȥ�� ���� --> 2
	// �� ���� ���� �ݺ� --> 4
	// ��������(2�̻� ���� ���� Ȥ�� ����) --> 5
	// �̿� 10

	int d1, d2;
	int end = start + len - 1;
	
	d1 = d2 = digits[start] - digits[start + 1];

	bool isSame = true;		// ���̰� ���� �� ����
	bool isAlter = true;	// ������ ���� ��Ÿ���� �� ����

	for (int i = start + 1; (isSame || isAlter) && i < end; ++i)
	{
		int d = digits[i] - digits[i + 1];

		isSame &= d == d1;
		isAlter &= d == -d2;

		d1 = d2; d2 = d;
	}

	int level = isAlter ? 4 : 10;

	if (isSame)
	{
		if (d1 == 0)
			level = 1;
		else if (d1 == 1 || d1 == -1)
			level = 2;
		else
			level = 5;
	}

	return level;
}


int solve(int start)
{
	if (start >= digits.size())
		return 0;

	int& ret = cached[start];

	if (ret != -1)
		return ret;

	ret = 0x7ffffff;

	for (int i = 3; i <= 5; ++i)
	{
		if (start + i > digits.size())
			break;

		ret = min(ret, solve(start + i) + calcDifficulty(start, i));
	}

	return ret;
}

int main()
{
	std::ios::sync_with_stdio(false);

	int T;

	in >> T;
	while (T--)
	{
		in >> digits;

		memset(cached, -1, sizeof(cached));
		out << solve(0) << "\n";
	}

	return 0;
}

