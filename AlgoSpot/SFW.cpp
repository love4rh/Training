/*
https://algospot.com/judge/problem/read/SFW
3
9 9 0 1 8 8 4 3
9 9 8 8 0 1 4 3
9 9 1 1 1 1 3 4

5
5
0
*/

#include <cstdlib>
#include <iostream>
#include <cstring>


using namespace std;

istream& in = cin;
ostream& out = cout;


int main()
{
    std::ios::sync_with_stdio(false);

    int T, N, M, r0, c0, r, c, A, B;

    in >> T;

    while (T--)
    {
        in >> N >> M >> r0 >> c0 >> r >> c >> A >> B;
        out << (((long long) abs(r - r0) + A - 1) / A + ((long long) abs(c - c0) + B - 1) / B) << "\n";
    }

    return 0;
}
