/*
https://algospot.com/judge/problem/read/FOSSIL
3
3 3
10 25 30 15 50 20
5 10 35 5 11 20
5 5
69.64 50.00 73.52 82.55 43.50 92.22 17.67 76.18 35.74 35.85
16.47 8.02 60.98 14.62 66.80 37.74 45.89 67.22 13.04 55.19
4 3
73.84 11.41 71.61 32.72 39.87 38.84 22.41 17.87
75.13 51.64 47.72 87.34 15.97 64.56

27.6529680365
0.000000
*/

#include <stdio.h>
#include <iostream>
#include <cmath>
#include <map>
#include <vector>

using namespace std;

istream& in = cin;
ostream& out = cout;


class Point
{
public:
    Point() : x(0), y(0) {}
    Point(const Point& pt) : x(pt.x), y(pt.y) {}

    Point& operator=(const Point& rhs)
    {
        if( this == &rhs )
            return *this;

        this->x = rhs.x;
        this->y = rhs.y;

        return *this;
    }

public:
    double x, y;
};

Point& operator>>(istream& in, Point& pt) { in >> pt.x >> pt.y; return pt; }


typedef vector<Point> PointList;
typedef vector<pair<Point, Point> > LineList;


LineList upper, lower;


// 시계 반대 방향으로 값이 주어지므로,
// X축의 값이 커지는 경우이면 아래 쪽, 작아지는 쪽이면 위쪽에 있음.
void assignUpDown(const Point& pt1, const Point& pt2)
{
    if( pt1.x < pt2.x )
        lower.push_back(make_pair(pt1, pt2));
    else
        upper.push_back(make_pair(pt1, pt2));
}

// 두점 pt1, pt2을 지나는 직선 상에서 X축의 값이 x일 경우의 Y값 계산
double clacY(const Point& pt1, const Point& pt2, double x)
{
    return (pt2.y - pt1.y) / (pt2.x - pt1.x) * (x - pt1.x) + pt1.y;
}

bool isIn(const Point& pt1, const Point& pt2, double x)
{
    return min(pt1.x, pt2.x) <= x && x <= max(pt1.x, pt2.x);
}

// x 위치에서 곂치는 영역의 높이는
// X축의 범위가 x를 포함하는 upper 라인들의 Y축 최소값과
// X축의 범위가 x를 포함하는 lower 라인들의 Y축 최대값의 차이임.
double calcHeight(double x)
{
    double upperMin = 1e24;
    double lowerMax = -1e24;

    // upper 라인들의 Y축 최소값
    for(int i = 0; i < (int) upper.size(); ++i)
    {
        if( isIn(upper[i].first, upper[i].second, x) )
        	upperMin = min(upperMin, clacY(upper[i].first, upper[i].second, x));
    }

    // lower 라인들의 Y축 최대값
    for(int i = 0; i < (int) lower.size(); ++i)
    {
        if( isIn(lower[i].first, lower[i].second, x) )
        	lowerMax = max(lowerMax, clacY(lower[i].first, lower[i].second, x));
    }

    return upperMin - lowerMax;
}

// [low, high]: 곂치는 X축의 범위
double solve(double low, double high)
{
	if( low > high )
		return 0;

    double l, h, g;

    // [low, high]을 삼등분하여 바이너리 검색 비슷하게 가장 큰 값을 찾아 나감.
    while( high - low > 1e-12 )
    {
        g = (high - low) / 3.0;
        l = g + low;
        h = l + g;

        if( calcHeight(l) < calcHeight(h) )
            low = l;
        else
            high = h;
    }

    return max(0.0, calcHeight(high));
}

int main(int argc, char* argv[])
{
	std::ios::sync_with_stdio(false);

    int T;

    in >> T;

    while( T-- )
    {
        int n, m;

        upper.clear();
        lower.clear();

        in >> n >> m;

        int flower = -1;
        Point p0, p1, p2;
        double minX[2], maxX[2];

        // 위쪽, 아래쪽 선분을 찾아 계산할 때 영역을 구분할 필요가 없음.
        for(int i = 0; i < n + m; ++i)
        {
            in >> p2;

            // 새로운 꽃가루 영역이 시작되면,
            if( i == 0 || i == n )
            {
                flower += 1;
                // 두 번째 꽃가루라면 첫 번째 것의 마지막과 첫 번째를 연결하는 선을 처리해야 함.
                if( i == n )
                    assignUpDown(p1, p0);

                p0 = p1 = p2;
                minX[flower] = maxX[flower] = p2.x;
                continue;
            }

            minX[flower] = min(minX[flower], p2.x);
            maxX[flower] = max(maxX[flower], p2.x);

            assignUpDown(p1, p2);
            p1 = p2;
        }
        assignUpDown(p1, p0);

        // 한 영역의 최대값이 다른 영역의 최소값 보다 작거나 같으면 곂치는 영역이 없는 것임.
        // 즉, 두영역의 최대값의 최소값이 최소값의 최대값 보다 작거나 같으면 곂치지 않음
        printf("%.10f\n", solve(max(minX[0], minX[1]), min(maxX[0], maxX[1])) );
    }

    return 0;
}
