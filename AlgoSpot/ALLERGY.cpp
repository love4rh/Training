/*
https://algospot.com/judge/problem/read/ALLERGY
2
4 6
cl bom dara minzy
2 dara minzy
2 cl minzy
2 cl dara
1 cl
2 bom dara
2 bom minzy
10 7
a b c d e f g h i j
6 a c d h i j
3 a d i
7 a c f g h i j
3 b d g
5 b c f h i
4 b e g j
5 b c g h i

2
3
*/
#include <iomanip>
#include <iostream>
#include <cmath>
#include <cstring>
#include <map>
#include <string>

using namespace std;

typedef long long int64;

istream& in = cin;
ostream& out = cout;

const int MAX = 51;
const int64 one = 1;

int N, M, result;

// 친구들별 먹을 수 있는 음식을 bit 단위로 표시
int64 eatable[MAX];


// who: 먹을 음식이 있는 친구 정보. 비트별로 친구를 나타냄.
// foods: 요리해야 하는 음식. 비트별로 음식을 나타냄.
// count: foods 내 set된 비트의 개수
void solve(int64 who, int64 foods, int count)
{
    if( count >= result )
        return;

    for(int i = 0; i < N; ++i)
    {
        if( foods & eatable[i] )
            who |= (one << i);
    }

    // 모두 먹을 음식이 있는 경우임.
    if( who == (one << N) - 1 )
    {
        result = min(result, count);
        return;
    }

    // 아직 먹을 음식이 없는 친구 찾기
    int notyet = -1;
    for(int i = 0; i < N; ++i)
    {
        if( (who & (one << i)) == 0 )
        {
            notyet = i;
            break;
        }
    }

    // 음식을 하나씩 요리함
    int i = 0;
    // notyet이 먹을 수 있는 음식 중 만들지 않은 것
    int64 p = eatable[notyet] & ~foods;

    while( p )
    {
        if( p & one )
            solve(who | (one << notyet), foods | (one << i), count + 1);

        i += 1;
        p >>= 1;
    }
}

int main(int argc, char* argv[])
{
    std::ios::sync_with_stdio(false);

    int T = 0;
    string name;

    in >> T;

    while (T--)
    {
        in >> N >> M;

        map<string, int> friends;

        for(int i = 0; i < N; ++i)
        {
            in >> name;
            friends[name] = i;
            eatable[i] = 0;
        }

        int cnt;
        for(int i = 0; i < M; ++i)
        {
            in >> cnt;
            while( cnt-- )
            {
                in >> name;
                eatable[friends[name]] |= (one << i);
            }
        }

        result = 999;  // assign a big number to find minimum count
        solve(0, 0, 0);

        out << result << "\n";
    }

    return 0;
}
