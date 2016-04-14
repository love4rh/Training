/*
https://www.algospot.com/judge/problem/read/TILING2
3
2
4
92
*/

#include <iostream>


using namespace std;

istream& in = cin;
ostream& out = cout;

/*
A는 세로 한개, BB는 가로 두개
너비에 따라 가능한 모든 경우는 (대칭, 비대칭 포함)
1: A
2: AA, BB
3: AAA, ABB, BBA
4: AABB, BBBB, AAAA, ABBA, BBAA
5: AAABB, ABBBB, BBABB, AABBA, BBBBA, AAAAA, ABBAA, BBAAA
...
와 같이, n개의 너비를 채우는데 n - 2에 AA 혹은 BB를 넣거나 n - 1에 A를 채우는 방법이 있음.
즉, f(n)를 너비 n인 보드에 타일을 채우는 회수라고 가정하면, f(n) = f(n - 1) + f(n - 2)임.
그리고 f(1) = 1, f(2) = 2임.
*/

const int MAX_NUM = 100;
const int MOD = 1000000007;

int tileNumber[MAX_NUM + 1];


int getTileNumber(int n)
{
	if (n <= 1)
		return 1;
	else if (n <= 2)
		return 2;

	int& tile = tileNumber[n];

	if (tile != 0)
		return tile;
	
	return tile = (getTileNumber(n - 2) + getTileNumber(n - 1)) % MOD;
}


int main()
{
	std::ios::sync_with_stdio(false);

	// 초기화
	for (int i = 0; i <= MAX_NUM; ++i)
		tileNumber[i] = 0;

	int C;

	in >> C;

	while (C--)
	{
		int N;

		in >> N;

		out << getTileNumber(N) << "\n";
	}

	return 0;
}
