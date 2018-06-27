/*
https://algospot.com/judge/problem/read/MAXSUM
4
4
1 2 3 4
3
-1 0 1
5
5 4 -6 7 8
10
-2 -1 0 1 2 3 4 -1 7 8

10
1
18
24
*/
#include <iomanip>
#include <iostream>
#include <cmath>


using namespace std;

istream& in = cin;
ostream& out = cout;


int main(int argc, char* argv[])
{
    std::ios::sync_with_stdio(false);

    int T = 0, N;

    in >> T;
    while( T-- )
    {
        in >> N;

        int a;
        int maxVal = -999999999;
        int pSum = 0;

        for(int i = 0; i < N; ++i)
        {
            in >> a;
            pSum += a;

            if( pSum < 0 )
            {
                pSum = 0;
                continue;
            }

            maxVal = max(maxVal, pSum);
        }

        out << maxVal << "\n";
    }

    return 0;
}
