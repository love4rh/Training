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

		// DP�� ���� �ʱ�ȭ
		memset(cached, 0, sizeof(cached));

		// ���� �ݾ� �� ����. ���� �ݾ׺��� ����� ������ ������
		std::sort(coins, coins + C);

		// coin �ݾ��� ���� ������ �����ϸ鼭 ������ �� �ݾ��� ������ ��Ÿ�� ������.
		for (int i = 0; i < C; ++i)
		{
			int coin = coins[i];

			// �� �̻� ����� �ʿ� ���� �����
			if (coin > M)
				break;

			// ���ο� coin�� �ϳ� �����ϴ� ���� ������ �ִ� ����� ���� �ٸ� �����
			cached[coin] += 1;
			cached[coin] %= MOD;

			// ������ �ݾ׺��� ����� ������
			for (int c = 1 + coin; c <= M; ++c)
			{
				// ������ ����� �������� ���� �� �ִ� �ݾ��� �ִ� ���
				if (cached[c - coin] > 0)
				{
					// ���� �ִ� ���� ������ ������ ��츦 ���ϸ� ����.
					// coin�� 50�ε� �ݾ� 10, 60�� ������ ���� 1�̿��ٸ�,
					// 10�� ������ ��찡 ������ ���⿡ 50�� ���ϸ� 60�� �ǹǷ�
					// 60�� �� �� �ִ� ���� ���� ����� ���� 
					// 10�� 50�� ���� ���� ����� ��(��, 10�� ����� ����)�� ���ϸ� ��.s
					cached[c] += cached[c - coin];
					cached[c] %= MOD;
				}
			}
		}

		out << cached[M] << "\n";
	}

	return 0;
}

