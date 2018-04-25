/*
https://algospot.com/judge/problem/read/KWPATTERN
4
7
2
20
99

2000-11-11 11:00:02
2000-01-22 10:00:02
2001-12-22 21:10:02
2013-12-11 21:31:02
*/

#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

istream& in = cin;
ostream& out = cout;


// 가능한 년도의 앞 두자리
const int highYear[] = {
  20, 21, 22, 23, 24, 25, 30, 31, 32, 33
, 34, 35, 40, 41, 42, 43, 44, 45, 50, 51
, 52, 53, 54, 55, 60, 61, 62, 63, 64, 65
, 70, 71, 72, 73, 74, 75, 80, 81, 82, 83
, 84, 85, 90, 91, 92, 93, 94, 95
};

// 가능한 년도의 위 두자리
const int lowYear[] = {
   0,  1,  2,  3,  4,  5, 10, 11, 12, 13
, 14, 15, 20, 21, 22, 23, 24, 25, 30, 31
, 32, 33, 34, 35, 40, 41, 42, 43, 44, 45
, 50, 51, 52, 53, 54, 55, 60, 61, 62, 63
, 64, 65, 70, 71, 72, 73, 74, 75, 80, 81
, 82, 83, 84, 85, 90, 91, 92, 93, 94, 95
};

// 가능한 월
const int month[] = { 1,  2, 10, 11, 12 };

// 가능한 일자
const int day[] = { 11,  22 };

// 일의 자리 수
int fd(int n)
{
    return n % 10;
}

// 십의 자리 수
int sd(int n)
{
    return n / 10;
}

int main()
{
    std::ios::sync_with_stdio(false);

    char buffer[100];
    vector<string> cached;

    // 28800개 계산
    for(int h = 0; h < int(sizeof(highYear)/sizeof(int)); ++h)
    {
        for(int l = 0; l < int(sizeof(lowYear)/sizeof(int)); ++l)
        {
            for(int m = 0; m < int(sizeof(month)/sizeof(int)); ++m)
            {
                for(int d = 0; d < int(sizeof(day)/sizeof(int)); ++d)
                {
                    sprintf(buffer, "%02d%02d-%02d-%02d %d%d:%d%d:%d%d"
                        , highYear[h], lowYear[l], month[m], day[d]
                        , fd(month[m]), sd(month[m])
                        , fd(lowYear[l]), sd(lowYear[l])
                        , fd(highYear[h]), sd(highYear[h]));

                    cached.push_back(string(buffer));
                }
            }
        }
    }

    int T = 0, N = 0;

    in >> T;
    while (T--)
    {
        in >> N;
        out << cached[N-1] << "\n";
    }

    return 0;
}
