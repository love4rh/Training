/*
https://algospot.com/judge/problem/read/CCRICKET
3
3 4 7 10
0000
0000
0000
3 4 5 8
0100
0101
0000
4 3 2 3
101
010
101
010

60
37
12

이분 그래프의 최대 부합(Matching)을 계산하는 문제임.
이분 그래프의 최대 부합(Matching) 계산하는 방법 아래 참고.
http://blog.sisobus.com/2013/10/bipartite-matching.html#.WROxLZNLs_t
// */

#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>


using namespace std;

istream& in = cin;
ostream& out = cout;

const int MAX_LIMIT = 101;

int N, M, P1, P2;

// count of broken tiles
int brokenCnt;

// node index of the odd partner
int evenPartner[MAX_LIMIT * MAX_LIMIT / 2];

int oddVisited[MAX_LIMIT * MAX_LIMIT / 2];

// Odd Part 기준으로 정렬된 Graph
vector<vector<int> > G;


bool dfs(int oddIdx)
{
    if( oddVisited[oddIdx] )
        return false;

    oddVisited[oddIdx] = true;

    for(int i = 0; i < (int) G[oddIdx].size(); ++i)
    {
        int evenPair = G[oddIdx][i];

        if( evenPartner[evenPair] == -1 || dfs(evenPartner[evenPair]) )
        {
            evenPartner[evenPair] = oddIdx;
            return true;
        }
    }

    return false;
}

int bipartiteMatching()
{
    memset(evenPartner, -1, sizeof(evenPartner));

    int matched = 0;

    for(int i = 0; i < (int) G.size(); ++i)
    {
        memset(oddVisited, 0, sizeof(oddVisited));
        if( dfs(i) )
            matched += 1;
    }

    return matched;
}

int main(int argc, char* argv[])
{
	std::ios::sync_with_stdio(false);

    int T = 0;

    in >> T;
    while( T-- )
    {
        in >> N >> M >> P1 >> P2;

        string tile, prevTile;

        // x와 y의 합이 홀수, 짝수인 것으로 이분되는 그래프로 표현할 수 있으며,
        // 이분한 노드의 각 파트별 인덱싱을 위한 변수.
        int idx[] = { -1, -1 };
        int* pIdx = evenPartner;
        int* cIdx = oddVisited;

        brokenCnt = 0;
        G.clear();

        for(int y = 0; y < N; ++y)
        {
            in >> tile;

            for(int x = 0; x < M; ++x)
            {
                if( '1' == tile[x] )
                {
                    cIdx[x] = -1;
                    continue;
                }

                brokenCnt += 1;

                int part = (x + y) & 0x01;

                cIdx[x] = ++idx[part];

                if( part == 1 )
                {
                    G.push_back(vector<int>());

                    if( x > 0 && cIdx[x - 1] != -1 )
                        G[idx[part]].push_back( cIdx[x - 1] );

                    if( y > 0 && pIdx[x] != -1 )
                        G[idx[part]].push_back( pIdx[x] );
                }
                else
                {
                    if( x > 0 && cIdx[x - 1] != -1 )
                        G[cIdx[x - 1]].push_back( cIdx[x] );

                    if( y > 0 && pIdx[x] != -1 )
                        G[pIdx[x]].push_back( cIdx[x] );
                }
            }

            swap(cIdx, pIdx);
        }

        // 그래프 상에 한 Part만 있거나, 타일 두개를 채우는데 P1가 P2보다 저렴하거나 같다면, P1 * brokenCnt
        if( P1 * 2 <= P2 || idx[0] == -1 || idx[1] == -1 )
            out << (P1 * brokenCnt);
        // 비싸다면, P2를 채울 수 있는 최대 회수(C)를 계산 후 P2 * C + (brokenCnt - C * 2) * P1
        else
        {
            int C = bipartiteMatching();
            out << (P2 * C + (brokenCnt - C * 2) * P1);
        }
        out << "\n";
    }

    return 0;
}
