/*
https://www.algospot.com/judge/problem/read/SUSHI
2
6 10000
2500 7
3000 9
4000 10
5000 12
10000 20
15000 1
6 543975612
2500 7
3000 9
4000 10
5000 12
10000 20
15000 1

28
1631925
*/

#include <iostream>
#include <algorithm>
#include <cstring>


using namespace std;

istream& in = cin;
ostream& out = cout;

const int mod = 201;

int N, M;
int price[20], prefer[20];

int cached[mod];


// 예산 범위 내 최대 선호도 반환
int solve()
{
	int preferMax = 0;

	for (int b = 1; b <= M; b += 1)
	{
		cached[b % mod] = 0;

		for (int i = 0; i < N; ++i)
		{
			if (b < price[i])
				continue;

			cached[b % mod] = max(cached[b % mod], cached[(b - price[i]) % mod] + prefer[i]);
		}

		preferMax = max(preferMax, cached[b % mod]);
	}

	return preferMax;
}


int main()
{
	std::ios::sync_with_stdio(false);

	int T;

	in >> T;
	while (T--)
	{
		in >> N >> M;

		M /= 100;	// price와 order를 맞춰야지. 100 이하의 값은 무시해도 됨.

		for (int i = 0; i < N; ++i)
		{
			in >> price[i] >> prefer[i];

			price[i] /= 100;	// 100의 배수이니 값을 낮춰서 처리하기 위해 나눔.
		}

		memset(cached, 0, sizeof(cached));

		out << solve() << "\n";
	}

	return 0;
}
