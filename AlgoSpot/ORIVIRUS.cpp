/*
https://algospot.com/judge/problem/read/ORIVIRUS
2
8
0 1 0 0 0 1 0 0
1 0 1 0 0 1 1 0
0 1 0 1 0 0 0 0
0 0 1 0 1 0 1 1
0 0 0 1 0 0 0 1
1 1 0 0 0 0 0 0
0 1 0 1 0 0 0 0
0 0 0 1 1 0 0 0
3
1 3
1 8
5 8
3
0 1 1
1 0 1
1 1 0
2
1 2
2 3

4 2 3
3 3
// */

#include <iostream>
#include <cstring>


using namespace std;

istream& in = cin;
ostream& out = cout;

const int MAX_STUDENT = 101;


int N, M;
int friendShip[MAX_STUDENT][MAX_STUDENT];
int infected[MAX_STUDENT];

// returns following values
// 0: not infected
// 1: already infected
// 2: newly infected
int checkInfected(int n)
{
    if( infected[n] )
        return 1;

    int infectedFriend = 0;

    for(int i = 1; infectedFriend < 3 && i <= N; ++i)
    {
        if( i == n || friendShip[n][i] != 1 )
            continue;

        infectedFriend += infected[i];
    }

    if( infectedFriend >= 2)
    {
        infected[n] = 1;
        return 2;
    }

    return 0;
}


int main(int argc, char* argv[])
{
    std::ios::sync_with_stdio(false);

    int T = 0;

    in >> T;
    while( T-- )
    {
        in >> N;

        memset(friendShip, 0, sizeof(friendShip));

        for(int i = 1, j = 1; i <= N && j <= N; ++j > N ? ++i, j = 1 : j)
            in >> friendShip[i][j];

        in >> M;

        while( M-- )
        {
            memset(infected, 0, sizeof(infected));

            int a, b, count = 2;

            in >> a >> b; // first-infected friends
            infected[a] = infected[b] = 1;

            bool going = false;

            do
            {
                going = false;

                for(int n = 1; n <= N; ++n)
                {
                    if( 2 == checkInfected(n) )
                    {
                        going = true;
                        count += 1;
                    }
                }
            } while( going );

            out << count << " ";
        }

        out << "\n";
    }

    return 0;
}
