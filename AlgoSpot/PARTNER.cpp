/*
https://algospot.com/judge/problem/read/PARTNER
7
10 0.1
C
10 1
CCCCU
10 50
CCCCU
10 3.124
CCCUUUCCCUUCCCUCCCUCCCUCCUUUCCUUCC
10 3.124
CCCUUUCCCUUCCCCCCCUCCCUCCUUUCCUUCC
10 0.1
U
10 3.124
CCCUUUCCCUUCCCCCCCUCCCUCCUUUCCUUCU

100000.0
3940.4
93750.0
75317.4
77320.7
0.0
42234.7
// */

#include <cstdio>
#include <iostream>
#include <string>

using namespace std;


/*
 * 남은 소고기를 모두 나누어 가질 때까지 협상은 계속됨.
 * P의 길이가 협상을 지속한 날로 이 날들 동안의 협상으로 모든 소고기를 나누게 된 것임.
 *
 * 창규, 의종 모두 지극히 이성적(?)이므로 자신이 비율을 제시한 다음 날이 있다는 의미는
 * 상대방이 납득할 수 있는 수준(어짜피 없어질 정도)으로 제안하여 받아 들인 것으로
 * 생각할 수 있다. 따라서, 감각상각된 정도만 제안하여 자신의 이득을 취한 것임.
 * 그리고, 마지막에는 협상이 끝난 것으므로 모두 제안한 사람이 이득을 취한 것임.
 */
double solve(const string& P, double M, double D)
{
    int lastDay = (int) P.size() - 1;
    double pM, cM, profit = 0;
    double decay = 1.0 - D / 100.0;

    pM = cM = M;

    // 마지막 전 일까지만 계산
    for(int i = 0; i < lastDay; ++i)
    {
        cM *= decay;

        // 감각상된 양만 이득을 취한 것임
        if( P[i] == 'C' )
            profit += (pM - cM);

        pM = cM;
    }

    // 마직막이 창규일 경우만 남은 이익을 모두 더함
    if( P[lastDay] == 'C' )
        profit += pM;

    return profit * 10000.0;
}


int main(int argc, char* argv[])
{
    std::ios::sync_with_stdio(false);

    int T = 0;
    string P;
    double M, D;

    cin >> T;
    while( T-- )
    {
        cin >> M >> D >> P;
        printf("%.1f\n", solve(P, M, D));
    }

    return 0;
}
