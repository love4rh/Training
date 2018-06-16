/*
https://algospot.com/judge/problem/read/DECODE
4
4 4 0000110100101100
5 2 0110000010
2 6 010000001001
5 5 0100001000011010110000010

1 ACM
2 HI
3 HI
4 HI HO
*/
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

typedef long long int64;

istream& in = cin;
ostream& out = cout;

int R, C;
string code;

// direction - 0: left, 1: down, 2: right, 3: up
const int direction[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};


string goSpiral()
{
    int x = 0, y = 0, d = 0;
    int count = 0, sum = 0;

    int sR = 0, sC = 0;
    int eR = R, eC = C;

    string result;

    while( sR < eR && sC < eC )
    {
        // out << " (" << x << "," << y << ") ";
        sum += code[y * C + x] == '1' ? 1 << (4 - count) : 0;

        if( ++count >= 5 )
        {
            result += (sum == 0 ? ' ' : char('A' + sum - 1));
            sum = count = 0;
        }

        x += direction[d][0];
        y += direction[d][1];

        if( d == 0 && x >= eC )
        {
            sR += 1;
            x -= direction[d][0];
            y -= direction[d][1];
            d = 1;
            x += direction[d][0];
            y += direction[d][1];
        }
        else if( d == 1 && y >= eR )
        {
            eC -= 1;
            x -= direction[d][0];
            y -= direction[d][1];
            d = 2;
            x += direction[d][0];
            y += direction[d][1];
        }
        else if( d == 2 && x < sC )
        {
            eR -= 1;
            x -= direction[d][0];
            y -= direction[d][1];
            d = 3;
            x += direction[d][0];
            y += direction[d][1];
        }
        else if( d == 3 && y < sR )
        {
            sC += 1;
            x -= direction[d][0];
            y -= direction[d][1];
            d = 0;
            x += direction[d][0];
            y += direction[d][1];
        }
    }

    return result.erase(result.find_last_not_of(" ") + 1);
}


int main(int argc, char* argv[])
{
    std::ios::sync_with_stdio(false);

    int T = 0;

    in >> T;
    for(int i = 1; i <= T; ++i)
    {
        in >> R >> C >> code;

        out << i << " " << goSpiral() << "\n";
    }

    return 0;
}
