/* https://algospot.com/judge/problem/read/POLY
3
2
4
92

2
19
4841817
*/

#include <iomanip>
#include <iostream>
#include <cstring>

using namespace std;

istream& in = cin;
ostream& out = cout;


#define MAX        101

// p(n, f) caching
int cached[MAX][MAX];

int MOD = 10000000;


// n개의 블록으로 폴리오미노를 만들 때 첫 줄에 f개의 블록이 있는 경우의 개수
int p(int n, int f)
{
    // 기저사례
    if( n == f || n == 1 ) return 1;

    int& count = cached[n][f];

    // 계산된 것 재활용
    if( count != -1 ) return count;

    // p(n, f) = sum of (f + s - 1) * p(n - f, s), where s is [1, n - f]
    count = 0;
    for(int s = 1; s <= n - f; ++s)
    {
        count += (f + s - 1) * p(n - f, s) % MOD;
        count %= MOD;
    }

    return count;
}

// n개의 블록으로 만들수 있는 폴리오미노 개수
// g(n) = sum of p(n, f), where f is [1, n]
int solve(int N)
{
    int ans = 0;
    for(int f = 1; f <= N; ++f)
    {
        ans += p(N, f);
        ans %= MOD;
    }

    return ans;
}

int main(int argc, char* argv[])
{
    std::ios::sync_with_stdio(false);

    memset(cached, -1, sizeof(cached));

    int T, N;

    in >> T;

    while(T--)
    {
        in >> N;
        out << solve(N) << "\n";
    }

    return 0;
}
