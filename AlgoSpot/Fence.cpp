/*
https://algospot.com/judge/problem/read/FENCE
3
7
7 1 5 9 6 7 3
7
1 4 4 4 4 1 1
4
1 8 2 2

20
16
8
*/
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <map>

#define MAX_LIMIT 20001

using namespace std;

istream& in = cin;
ostream& out = cout;

int height[MAX_LIMIT];


int main()
{
    std::ios::sync_with_stdio(false);

    int T = 0, N = 0;

    in >> T;

    while( T-- )
    {
        in >> N;

        int maxArea = 0;

        map<int, int> area;  // Height --> area

        for(int p = 0; p < N; ++p)
        {
            in >> height[p];

            map<int, int>::iterator it = area.find(height[p]);

            // 처음 나온 높이라면,
            if( area.end() == it )
            {
                area[height[p]] = 0;  // 아래 루틴에서 1이 더해지므로 여기서는 1이어야 함.

                it = area.find(height[p]);

                // pos 이전에 지금 높이보다 크거나 같은 것이 얼마나 있는 지 탐색
                int i = p;
                while( --i >= 0 && height[i] >= height[p] )
                    it->second += height[p];
            }

            // 기존에 있던 애들 중에서 높이가 지금 것보다 작거나 같은 애들은 하나씩 더해 줘야 함.
            for(it = area.begin(); it != area.end();)
            {
                if( it->first <= height[p] )
                {
                    it->second += it->first;
                    maxArea = max(maxArea, it->second);
                    ++it;
                }
                else
                {
                    maxArea = max(maxArea, it->second);

                    map<int, int>::iterator dit = it++;
                    area.erase(dit);
                }
            }
        }

        for(map<int, int>::iterator it = area.begin();
            it != area.end();
            ++it)
        {
            maxArea = max(maxArea, it->second);
        }

        out << maxArea << "\n";
    }

    return 0;
}
