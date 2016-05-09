/*
https://algospot.com/judge/problem/read/PICNIC
3
2 1
0 1
4 6
0 1 1 2 2 3 3 0 0 2 1 3
6 10
0 1 0 2 1 2 1 3 1 4 2 3 2 4 3 4 3 5 4 5

1
3
4
*/
#include <iostream>
#include <cstring>


using namespace std;

const int MAX_LIMIT = 11;

int N;

// 친구관계
int friendShip[MAX_LIMIT][MAX_LIMIT];
// Pair 계산 시 고려되었는 지 여부
int taken[MAX_LIMIT];

istream& in = cin;
ostream& out = cout;


int countPair()
{
	int start = -1;
	for (int i = 0; i < N; ++i)
	{
		if (!taken[i])
		{
			start = i;
			break;
		}
	}

	// 모두 매칭된 경우임. 따라서 가능한 경우 하나 추가
	if (start == -1) return 1;

	int pairCnt = 0;
	for (int i = 0; i < N; ++i)
	{
		if (!taken[i] && friendShip[start][i])
		{
			taken[start] = taken[i] = 1;

			// 다음 Pair 찾기
			pairCnt += countPair();

			taken[start] = taken[i] = 0;
		}
	}

	return pairCnt;
}

int main(int argc, char* argv[])
{
	int T = 0;

	in >> T;
	while (T--)
	{
		int M, i, j;

		in >> N >> M;

		memset(taken, 0, sizeof(taken));
		memset(friendShip, 0, sizeof(friendShip));

		while (M--)
		{
			in >> i >> j;
			friendShip[i][j] = friendShip[j][i] = 1;
		}

		out << countPair() << "\n";
	}

	return 0;
}
