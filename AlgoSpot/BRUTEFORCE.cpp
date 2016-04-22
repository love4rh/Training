/*
https://www.algospot.com/judge/problem/read/BRUTEFORCE
5
1 100000 1
4 4 10
4 8 36
4 9 3
3567404 46749457 21

100000
10000
712979373
29484
278986658
*/

#include <iostream>


using namespace std;

istream& in = cin;
ostream& out = cout;


const int MOD = 1000000007;


long long powEx(int n, int p)
{
	if (p == 0)
		return 1;

	long long halfPow = powEx(n, p / 2) % MOD;

	return halfPow * halfPow % MOD * ((p % 2) != 0 ? n : 1) % MOD;
}

long long sum(int n, int m)
{
	if (m == 0)
		return 1;

	long long ret = 0;

	if (m == 1)
		ret = 1 + n;
	else if (m == 2)
		ret = 1 + n + n * n;
	else if ((m % 2) == 1)
	{
		ret = (1 + powEx(n, (m + 1) / 2)) % MOD;
		ret = ret * (sum(n, m / 2) % MOD);
	}
	else // 짝수
	{
		ret = sum(n, m - 1) + powEx(n, m);

		//ret = (1 + powEx(n, m / 2)) % MOD;
		//ret = ret * (sum(n, (m - 1) / 2) % MOD) + powEx(n, m);
	}

	return ret % MOD;
}


int main()
{
	std::ios::sync_with_stdio(false);

	int T, A, B, N;

	in >> T;

	while(T--)
	{
		in >> A >> B >> N;

		out << ((powEx(N, A) * sum(N, B - A)) % MOD) << "\n";
	}

	return 0;
}
