﻿/*
https://algospot.com/judge/problem/read/TSP2
2
3
0.0000000000  611.6157225201  648.7500617289
611.6157225201  0.0000000000  743.8557967501
648.7500617289  743.8557967501  0.0000000000
4
0.0000000000  326.0008994586  503.1066076077  290.0250922998
326.0008994586  0.0000000000  225.1785728436  395.4019367384
503.1066076077  225.1785728436  0.0000000000  620.3945520632
290.0250922998  395.4019367384  620.3945520632  0.0000000000

1260.3657842490
841.2045646020
// */

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <limits>
#include <cmath>
#include <cstring>
#include <bitset>

using namespace std;

istream& in = cin;
ostream& out = cout;

const int MAX_LIMIT = 15;

typedef bitset<MAX_LIMIT>    VisitType;

int N = 0;
double dist[MAX_LIMIT][MAX_LIMIT];

// 계산된 값 재사용을 위한 캐시 변수
// (방문할 도시번호, 현재까지 방문한 도시 정보)를 키로 하여 해당 경우의 돌아다닌 최소 거리 저장
// 방문한 도시 정보는 bitset를 이용하여 방문여부를 저장하고 각 비트번호는 도시 번호와 같음
double cached[MAX_LIMIT][1 << MAX_LIMIT];


// 도시 돌아다녀 보기
double traverse(int here, VisitType traversed)
{
    double& d = cached[here][traversed.to_ulong()];

    if( d >= 0 )
        return d;

    traversed.set(here, true);

    // 모든 도시를 다 돌아다닌 경우임.
    if( (int) traversed.to_ulong() == (1 << N) - 1 )
        return 0; // 거리는 이미 다 계산되었기에 0을 반환해야 함.

    d = numeric_limits<double>::max();

    // 아직 안 간 다른 도시들을 가보자.
    for(int there = 0; there < N; ++there)
    {
        // 이미 가본 도시는 패스
        if( traversed[there] )
        	continue;

        d = min(d, dist[here][there] + traverse(there, traversed));
    }

    return d;
}

// 캐시 초기화
void clearCache()
{
    int p = 1 << N;
    for(int i = 0; i < MAX_LIMIT; ++i)
        for(int j = 0; j < p; ++j)
            cached[i][j] = -1;
}

int main(int argc, char* argv[])
{
	std::ios::sync_with_stdio(false);

    int T = 0;

    in >> T;
    while (T--)
    {
        in >> N;

        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
            {
                in >> dist[i][j];
                dist[j][i] = dist[i][j];
            }

        VisitType traversed;
        double ans = numeric_limits<double>::max();

        clearCache();
        for (int i = 0; i < N; ++i)
            ans = min(ans, traverse(i, traversed));

        printf("%.10f\n", ans);
    }

    return 0;
}
