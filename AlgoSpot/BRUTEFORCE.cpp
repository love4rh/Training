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

/*
# P(N, M) = N^M
  M이 짝수: N^(M/2) * N^(M/2)
  M이 홀수: N^(M/2) * N^(M/2) * N

  따라서, 아래와 같이 승수 연산을 빠르게 할 수 있음.
  P(N, M) = P(N, M/2) * P(N, M/2) * (M == 홀수 ? N : 1)


# S(N, M) = 1 + N + N^2 + N^3 + . . . + N ^M
- S(N, 0) = 1

- S(N, 1) = 1 + N

- S(N, 2) = 1 + N + N^2

- S(N, 3) = 1 + N + N^2 + N^3
          = (1 + N^2) * (1 + N)
          = (1 + N^2) * S(N, 1)

- S(N, 4) = 1 + N + N^2 + N^3 + N^4
          = (1 + N^2) * (1 + N) + N^4
          = (1 + N^2) * S(N, 1) + N^4

- S(N, 5) = 1 + N + N^2 + N^3 + N^4 + N^5
          = (1 + N^3) * (1 + N + N^2)
          = (1 + N^3) * S(N, 2)

- S(N, 6) = 1 + N + N^2 + N^3 + N^4 + N^5 + N^6
          = (1 + N^3) * (1 + N + N^2) + N^6

- S(N, 7) = 1 + N + N^2 + N^3 + N^4 + N^5 + N^6 + N^7
          = (1 + N^4) * (1 + N + N^2 + N^3)
          = (1 + N^4) * S(N, 3)

- S(N, 8) = 1 + N + N^2 + N^3 + N^4 + N^5 + N^6 + N^7
          = (1 + N^4) * (1 + N + N^2 + N^3) + N^8
          = (1 + N^4) * S(N, 3) + N^8

이상을 종합해 보면,
1. M이 홀수일 때: S(N, M) = (1 + N^[(M+1)/2]) * S(N, [M/2])
2. M이 짝수일 때: S(N, M) = S(N, M - 1) + P(N, M) 혹은 (1 + N^[M/2]) * S(N, [(M-1)/2]) + P(N, M)
*/

#include <iostream>


using namespace std;

typedef long long llong;

istream& in = cin;
ostream& out = cout;


const int MOD = 1000000007;


llong powEx(int n, int p)
{
    if( p == 0 )
        return 1;

    llong halfPow = powEx(n, p / 2) % MOD;

    return halfPow * halfPow % MOD * ((p % 2) != 0 ? n : 1) % MOD;
}

llong sum(int n, int m)
{
    if( m == 0 )
        return 1;

    llong ret = 0;

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
