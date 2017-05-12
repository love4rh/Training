/*
https://algospot.com/judge/problem/read/CLUBROOM
3
1 2
3 1
1 1
2 3
2 4
1 2
3 4
1 5
2 3
3 6
5 2
2 3
3 3
6 7
6 6
4 4
5 5

G G
G G B B
G G G
// */

#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>

using namespace std;

istream& in = cin;
ostream& out = cout;

const int MAX_FACIALITY= 101;
const int MAX_ROOM = 100001;

int N, M;

// 복지시설과 각 동방의 거리
int dist[MAX_ROOM][MAX_FACIALITY];

// 복지시설 위치
int facialityPos[MAX_FACIALITY][2];



int main(int argc, char* argv[])
{
    std::ios::sync_with_stdio(false);

    int T = 0;

    in >> T;
    while( T-- )
    {
        in >> M >> N;

        memset(dist, 0, sizeof(dist));

        for(int i = 0; i < M; ++i)
            in >> facialityPos[i][0] >> facialityPos[i][1];

        int x, y;
        for(int i = 0; i < N; ++i)
        {
            in >> x >> y;

            for(int j = 0; j < M; ++j)
                dist[i][j] = max(abs(facialityPos[j][0] - x), abs(facialityPos[j][1] - y));

            bool isGood = true;

            if( i > 0 )
            {
                for(int r = 0; isGood && r < i; ++r)
                {
                    int lessCnt = 0;
                    for(int j = 0; j < M; ++j)
                    {
                        if( dist[i][j] > dist[r][j] )
                            lessCnt += 1;
                    }

                    isGood = lessCnt < M;
                }
            }

            if( i > 0 )
                out << " ";

            out << (isGood ? "G" : "B");
        }

        out << "\n";
    }

    return 0;
}
