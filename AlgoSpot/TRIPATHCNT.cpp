/*
https://algospot.com/judge/problem/read/TRIPATHCNT

2
4
9
5 7
1 3 2
3 5 5 6
4
1
1 1
1 1 1
1 1 1 1

3
8
*/

#include <iomanip>
#include <iostream>
#include <cstring>

using namespace std;

istream& in = cin;
ostream& out = cout;


int N;

// 삼각형내 원소값
int triangle[101][101];

// (아래서 위로) 경로상 원소값 합의 최대값. (0, 0)에 가질 수 있는 최대값이 들어감
int maxSum[101][101];

// 최대값을 갖는 경우 (row, column) 위치를 지나는 회수의
int counter[101][101];


// 삼각형의 각 위치에서 제일 아래까지 내려갔을 때 가질 수 있는 최대값 계산.
//
// (r, c)에서 가질 수 있는 최대값은,
// (r, c)의 원소값 + max[아래 위치 (r + 1, c)의 최대값, 아래 오른쪽 위치 (r + 1, c + 1)의 최대값]
int calcMaxSum(int r, int c)
{
    if( r >= N || c >= N )
        return 0;

    int& sum = maxSum[r][c];

    if( sum != -1 )
        return sum;

    sum = triangle[r][c] + max(calcMaxSum(r + 1, c + 1), calcMaxSum(r + 1, c));

    return sum;
}


// 최대값을 갖기 위해 maxSum의 각 위치를 지날 수 있는 경우의 수 계산.
//
// (r, c)의 최대값은 다음과 같이 계산된다.
//     (r, c)의 원소값 + max[(r + 1, c)의 최대값, (r + 1, c + 1)의 최대값]
// 즉, (r, c)에 최대값을 갖도록 한 경우는 (r + 1, c)와 (r + 1, c + 1) 중에서
// 더 큰 값을 갖는 경우에서 온 것이다. 따라서 (r, c)가 최대값을 갖도록 할 수 있는 경우는
// (r + 1, c)와 (r + 1, c + 1) 중 더 큰 값을 갖는 경우의 수와 일치한다.
// 그리고 (r + 1, c)와 (r + 1, c + 1)의 최대값이 같을 경우는 양쪽 모두 가능한 경우이므로
// 두 경우의 수를 모두 더하면 된다.
int calcCounter(int r, int c)
{
    if( r == N - 1 ) return 1;

    int& count = counter[r][c];

    if( count != -1 )
        return count;

    count = 0;

    if( maxSum[r + 1][c] <= maxSum[r + 1][c + 1] )
        count += calcCounter(r + 1, c + 1);

    if( maxSum[r + 1][c] >= maxSum[r + 1][c + 1] )
        count += calcCounter(r + 1, c);

    return count;
}


int solve()
{
    memset(maxSum, -1, sizeof(maxSum));
    memset(counter, -1, sizeof(counter));

    calcMaxSum(0, 0);

    return calcCounter(0, 0);
}


int main(int argc, char* argv[])
{
    std::ios::sync_with_stdio(false);

    memset(triangle, 0, sizeof(triangle));

    int T;
    in >> T;

    while( T-- )
    {
        in >> N;

        for(int i = 0; i < N; ++i)
            for(int j = 0; j <= i; ++j)
                in >> triangle[i][j];

        out << solve() << "\n";
    }

    return 0;
}
