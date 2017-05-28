/*
https://algospot.com/judge/problem/read/AUTOPRODUCTION
3
2
3 6
1 3 3 4 4 4
3 6
2 3 4 7 8 10
1
5 3
20 18 13
2
1 10
1 1 1 1 1 1 1 1 1 1
1 1
100

6
10
9
*/

#include <iostream>
#include <algorithm>
#include <functional>
#include <cstring>
#include <queue>

using namespace std;

const int MAX = 11;
const int BIGINT = 99999999;

istream& in = cin;
ostream& out = cout;

int N;
int R[MAX];
int slot[MAX];

// amount of ingredient in the slots
int stuff[MAX][MAX];


int solve()
{
    priority_queue<pair<int, int> > pq;

    for(int i = 0; i < N; ++i)
    {
        // 칸을 j개 선택했을 때 만들 수 최대 생산물 개수 계산하여 stuff에 저장
        int sum = 0;
        for(int j = 0; j < slot[i]; ++j)
        {
            sum += stuff[i][j] / R[i];

            if( j == 0 )
                pq.push(make_pair(-sum, i));

            // 남은 거 다음 칸으로
            stuff[i][j + 1] += (stuff[i][j] % R[i]);
            stuff[i][j] = sum;
        }
    }

    int index[MAX];
    memset(index, 0, sizeof(index));

    // 적어도 한 재료씩은 있어야 하므로 N에서 시작.
    // 루틴을 돌면 하나가 더 선택되는 것으로 9까지만 실행해야 함(9에서 한번 돌면 10이 됨).
    for(int i = N; i <= 9; ++i)
    {
        pair<int, int> small = pq.top();

        // 한 재료를 모두 사용한 경우임
        if( ++index[small.second] >= slot[small.second] )
            break;

        pq.pop();
        pq.push(make_pair(-stuff[small.second][index[small.second]], small.second));
    }

    return -pq.top().first;
}


int main()
{
    std::ios::sync_with_stdio(false);

    int T = 0;

    in >> T;

    while (T--)
    {
        in >> N;

        for(int i = 0; i < N; ++i)
        {
            in >> R[i] >> slot[i];

            for(int j = 0; j < slot[i]; ++j)
                in >> stuff[i][j];

            // 재료의 개수 순으로 정렬
            sort(stuff[i], stuff[i] + slot[i], greater<int>());
        }

        out << solve() << "\n";
    }

    return 0;
}
