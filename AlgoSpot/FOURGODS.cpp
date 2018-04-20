/*
https://algospot.com/judge/problem/read/FOURGODS
1
6 8
2 4
3 6
2 6
1 4
1 6
4 5
2 3
4 6

2
*/

#include <string.h>
#include <iostream>

using namespace std;

istream& in = cin;
ostream& out = cout;

typedef long long int64;

const int MOD = 20130728;

int N, M;

// Graph
int G[501][501];


int main(int argc, char* argv[])
{
    int T;

    in >> T;

    while( T-- )
    {
        int a, b;

        in >> N >> M;

        memset(G, 0, sizeof(G));

        for(int i = 0; i < M; ++i)
        {
            in >> a >> b;
            G[a][b] = G[b][a] = 1;
        }

        // 1-2-3-4-1와 같이 연결된 경우는 1-3-2, 1-4-2인 연결을 합치면 만들 수 있음.
        // 즉, i-k1-j, i-k2-j, ... i-kc-j로 앞, 뒤가 i, j로 연결된 k의 개수를 찾은 후
        // 이 중 순서 없이 2개를 선택하면(c Combination 2)
        // i-k1-j-k2-i와 같이 문제에서 원하는 경우를 찾을 계산할 수 있음.
        // k1, k2가 앞, 뒤 노드가 되는 경우가 한번 더 계산되므로 최종 2로 나누어야 함.
        int64 count = 0;
        for(int i = 1; i <= N; ++i)
        {
            for(int j = i + 1; j <= N; ++j)
            {
                int c = 0;
                for(int k = 1; k <= N; ++k)
                {
                    if( k == i || k == j )
                        continue;

                    if(G[i][k] == 1 && G[j][k] == 1)
                        c += 1;
                }
                count += c * (c - 1) / 2; // Combination(c, 2)
            }
        }
        out << (count / 2) % MOD << "\n";
    }

    return 0;
}
