/*
https://www.algospot.com/judge/problem/read/NUMBERGAME
3
5
-1000 -1000 -3 -1000 -1000
6
100 -1000 -1000 100 -1000 -1000
10
7 -5 8 5 1 -4 -8 6 7 9

-1000
1100
7
*/

#include <iostream>
#include <cstring>
#include <algorithm>
#include <map>
#include <tuple>

using namespace std;

istream& in = cin;
ostream& out = cout;

const int MAX_NUM = 51;

int N;
int board[MAX_NUM];

map<tuple<int, int, bool>, int> cached;


// (현우점수 - 서하점수)을 반환하도록 정의하면,
// 현우 차례일 경우, 점수의 차이가 최대가 되도록 선택해야 하며,
// 서하 차례인 경우는 점수 차이가 최소가 되도록 선택해야 함.
int score(int left, int right, bool hyunwoo)
{
	if (left > right)
		return 0;

	tuple<int, int, bool> key(left, right, hyunwoo);

	if (cached.find(key) != cached.end())
	{
		return cached[key];
	}

	int diff = -999999999;

	// hyunwoo가 true이면 max, 아니면 min을 계산해야 함.
	// 왼쪽 혹은 오른쪽 한개를 가져와 점수에 포함시킴
	if (hyunwoo)
	{
		diff = max(board[left] + score(left + 1, right, !hyunwoo)
			, board[right] + score(left, right - 1, !hyunwoo));
	}
	else
	{
		diff = min(-board[left] + score(left + 1, right, !hyunwoo)
			, -board[right] + score(left, right - 1, !hyunwoo));
	}

	// 두개를 제거할 수 있는 경우
	if (right - left >= 1)
	{
		if (hyunwoo)
		{
			diff = max(diff, score(left + 2, right, !hyunwoo));
			diff = max(diff, score(left, right - 2, !hyunwoo));
		}
		else
		{
			diff = min(diff, score(left + 2, right, !hyunwoo));
			diff = min(diff, score(left, right - 2, !hyunwoo));
		}
	}

	cached[key] = diff;

	return diff;
}


int main()
{
	std::ios::sync_with_stdio(false);

	int T;

	in >> T;
	while(T--)
	{
		in >> N;

		for (int i = 0; i < N; ++i)
			in >> board[i];

		cached.clear();
		out << score(0, N - 1, true) << "\n";
	}

	return 0;
}
