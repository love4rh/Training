/*
https://algospot.com/judge/problem/read/DIAMONDPATH
3
4
1
2 3
4 5 6
7 8 9 10
11 12 13
14 15
16
5
6
1 2
6 7 4
9 4 1 7
6 7 5 9 4
4 4 3 2
1 2 3
6 1
7
5
39
43 16
74 94 24
25 76 98 62
79 58 71 67 98
43 55 27 44
10 96 56
73 31
95

64
48
664
*/

#include <algorithm>
#include <iostream>
#include <string.h>

using namespace std;

const int MAX_LIMIT = 204;

istream& in = cin;
ostream& out = cout;


int N;
int diaPath[MAX_LIMIT][MAX_LIMIT];


int main(int argc, char* argv[])
{
    int T = 0;

    in >> T;

    while (T--)
    {
        in >> N;

        memset(diaPath, -1, sizeof(diaPath));

        int R = 2 * N - 1;
        int C = (N + 1) / 2 + 3;

        for(int r = 0; r < R; ++r)
        {
            C += r < N ? -1 : 1;

            for(int i = 0; i <= (r < N ? r : R - r - 1); ++i)
            {
                int c = C + i * 2;
                in >> diaPath[r][c];

                if( r > 0 )
                {
                    diaPath[r][c] += max(diaPath[r - 1][c - 1], diaPath[r - 1][c + 1]);
                }
            }
        }

        out << diaPath[R - 1][C] << "\n";
    }

    return 0;
}
