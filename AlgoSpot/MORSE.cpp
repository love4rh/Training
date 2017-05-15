/*
https://algospot.com/judge/problem/read/MORSE
3
2 2 4
4 8 13
6 4 1

o--o
--o-ooo-oooo
------oooo
// */

#include <iostream>
#include <cstring>
#include <algorithm>
#include <string>


using namespace std;

istream& in = cin;
ostream& out = cout;

const int MAX_LIMIT = 201;


// 이항계수 계산
int comb[MAX_LIMIT][MAX_LIMIT];

void calcCombination()
{
    memset(comb, 0, sizeof(comb));

    comb[0][0] = 1;

    for(int i = 1; i < MAX_LIMIT; ++i)
    {
        comb[i][0] = 1;

        for(int j = 1; j <= i; ++j)
        {
            comb[i][j] = comb[i - 1][j - 1] + comb[i - 1][j];

            // 1000000000를 넘어가는 경우는 계산할 필요가 없음.
            // 오버플로 방지를 위하여 제한함.
            if( comb[i][j] > 1000000000 )
                comb[i][j] = 1000000000;
        }
    }
}


int main(int argc, char* argv[])
{
    std::ios::sync_with_stdio(false);

    calcCombination();

    int T = 0, N, M, K;

    in >> T;
    while( T-- )
    {
        in >> N >> M >> K;

        int L = N + M;

       string kth;
       kth.reserve(L + 1);

		for(; L; --L)
		{
			int c = comb[L - 1][N - 1];

			if( c < K)
			{
				kth.push_back('o');
				K -= c;
			}
			else
			{
				kth.push_back('-');
				N -= 1;
			}
		}

		out << kth << "\n";
    }

    return 0;
}
