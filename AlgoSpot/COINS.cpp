/*
https://www.algospot.com/judge/problem/read/COINS
4
110 4
10 50 100 500
850 4
10 50 100 500
3600 5
100 300 500 900 2000
1278 8
1 2 4 8 16 32 64 128

4
110
130
873794561
*/

#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>


using namespace std;

istream& in = cin;
ostream& out = cout;


const int MOD = 1000000007;

int M, C;
int coins[100];
int cached[5001];


int main()
{
	std::ios::sync_with_stdio(false);

	int T;

	in >> T;
	while (T--)
	{
		in >> M >> C;

		for (int i = 0; i < C; ++i)
			in >> coins[i];

		// DP를 위한 초기화
		memset(cached, 0, sizeof(cached));

		// 코인 금액 순 정렬. 적은 금액부터 계산해 나가기 위함임
		std::sort(coins, coins + C);

		// coin 금액을 작은 순으로 선택하면서 가능해 진 금액의 개수를 나타씩 증가함.
		for (int i = 0; i < C; ++i)
		{
			int coin = coins[i];

			// 더 이상 계산할 필요 없는 경우임
			if (coin > M)
				break;

			// 새로운 coin을 하나 선택하는 경우로 기존에 있던 경우의 수와 다른 경우임
			cached[coin] += 1;
			cached[coin] %= MOD;

			// 가능한 금액별로 계산해 가보자
			for (int c = 1 + coin; c <= M; ++c)
			{
				// 이전에 사용한 동전으로 만들 수 있는 금액이 있는 경우
				if (cached[c - coin] > 0)
				{
					// 현재 있는 값에 이전에 가능한 경우를 더하면 계산됨.
					// coin이 50인데 금액 10, 60에 가능한 수가 1이였다면,
					// 10이 가능한 경우가 있으며 여기에 50을 더하면 60이 되므로
					// 60이 될 수 있는 경우는 현재 경우의 수에 
					// 10에 50을 더할 때의 경우의 수(즉, 10의 경우의 수임)를 더하면 됨.s
					cached[c] += cached[c - coin];
					cached[c] %= MOD;
				}
			}
		}

		out << cached[M] << "\n";
	}

	return 0;
}

