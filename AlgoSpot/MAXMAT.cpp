/*
https://algospot.com/judge/problem/read/MAXMAT
2
4
0 -2 -7  0
9  2 -6  2
-4  1 -4  1
-1 8  0 -2
2
1 2
3 4

15
10
*/
#include <iomanip>
#include <iostream>
#include <cmath>
#include <string.h>

using namespace std;

istream& in = cin;
ostream& out = cout;

const int MAX_LIMIT = 201;

int R[MAX_LIMIT];
int S[MAX_LIMIT][MAX_LIMIT];


int main(int argc, char* argv[])
{
    std::ios::sync_with_stdio(false);

    int T = 0, N, a;

    in >> T;
    while( T-- )
    {
        in >> N;

        memset(S, 0, sizeof(S));

        for(int i = 0; i < N; ++i)
        {
            for(int j = 0; j < N; ++j)
            {
                in >> a;

                  // 열 방향으로 누적 합을 계산하여 저장
                S[i][j + 1] = S[i][j] + a;
            }
        }

        int maxVal = -999999999;

        for(int i = 0; i < N; ++i)
        {
            for(int j = i + 1; j <= N; ++j)
            {
            R[0] = 0;
                for(int k = 0; k < N; ++k)
                {
                    // k번째 행의 i열에서 (j - 1)열까지의 합의 누적 계산
                    R[k + 1] = R[k] + S[k][j] - S[k][i];
                }

                for(int f = 0; f < N; ++f)
                {
                    for(int t = f + 1; t <= N; ++t)
                    {
                        // R[t] - R[f]: f행에서 (t - 1)행까지의 합
                           // 부분행렬 (f, i) ~ (j-1, t-1) 원소의 합임.
                        maxVal = max(maxVal, R[t] - R[f]);
                    }
                }
            }
        }

        out << maxVal << "\n";
    }

    return 0;
}
