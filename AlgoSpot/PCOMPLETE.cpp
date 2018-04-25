/*
https://algospot.com/judge/problem/read/PCOMPLETE
4
6
b???bb
1 3
1
?
1 2
3
???
1 2
2
??
1 2

5
1
3
2
*/

#include <cmath>
#include <iostream>
#include <string>

using namespace std;

istream& in = cin;
ostream& out = cout;


int main()
{
    std::ios::sync_with_stdio(false);

    int T = 0, N = 0;
    int cost[2];

    string s;

    in >> T;
    while (T--)
    {
        in >> N >> s >> cost[0] >> cost[1];

        int time = 0;
        int minCost = min(cost[0], cost[1]);

        // 앞쪽 뒤쪽을 비교해 가면서,
        // 한쪽만 ?이면 다른 쪽의 문자를 추가하는 비용을 추가해야 하고,
        // 양쪽 모두 ?이면 작은 비용을 두번 더하면 됨. 양쪽이 같은 경우에는 한번만 더함.
        for(int i = 0; i < (N + 1) / 2; ++i)
        {
            if( '?' == s[i] )
            {
                if( '?' == s[N - i - 1] )
                {
                    time += minCost;
                    if( i != N - i - 1 )
                        time += minCost;
                }
                else
                    time += cost[s[N - i - 1] - 'a'];
            }
            else if( '?' == s[N - i - 1] )
                time += cost[s[i] - 'a'];
        }

        out << time << "\n";
    }

    return 0;
}
