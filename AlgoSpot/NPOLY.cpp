/* https://algospot.com/judge/problem/read/NPOLY
3
2
4
92

0
14
10202127
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

const int MOD = 20090711;


// n개의 블록으로 폴리오미노를 만들 때 첫 줄에 f개의 블록이 있는 경우의 개수
int polyCount(int n, int f)
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
        count += (f + s - 1) * polyCount(n - f, s) % MOD;
        count %= MOD;
    }

    return count;
}

// n로 만들 수 있는 전체 폴리오미노 개수
int totalCount(int n)
{
    int total = 0;
    for(int f = 1; f <= n; ++f)
    {
        total += polyCount(n, f);
        total %= MOD;
    }

    return total;
}

// n로 만들 수 있는 폴리오미노 중 세로 대칭 것의 개수
// n가 짝수라면 절반의 개수가 되며,
// 2개씩 빼서 가운데 놓을 수 있으므로 이 경우는 n / 2 - 2의 개수에
// 첫 번째 블럭과 맞출 수 있는 개수를 곱해야 함.
// 위 경우들을 모두 더하면 됨.
// 홀수의 경우는 가운데 놓일 수 있는 블럭의 개수가 홀수개인 것만 다름.
int symetricCount(int n)
{
    int count = 0;
    int h = n / 2;
    int m = (n % 2) == 0 ? 0 : 1;

    while( h > 0 )
    {
        for(int f = 1; f <= h; ++f)
        {
            count += polyCount(h, f) * (m == 0 ? 1 : f + m - 1);
            count %= MOD;
        }

        m += 2;
        h -= 1;
    }

    return count + 1; // 가로로 쭉 있는 것이 고려 안되므로 1을 더해야 함.
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
        // 뺄셈의 나머지 연산 (손책임님 감사)
        // https://jhc.gitbooks.io/algorithm-study/content/c54c_ace0_b9ac_c998_c5d0_c11c_c4f0_c774_b294_c218_.html
        out << ((totalCount(N) - symetricCount(N) + MOD) % MOD) << "\n";
    }

    return 0;
}
