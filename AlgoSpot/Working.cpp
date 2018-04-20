/*
https://algospot.com/judge/problem/read/FOSSIL
2
5 5
35.74 35.85 69.64 50.00 73.52 82.55 43.50 92.22 17.67 76.18
16.47 8.02 60.98 14.62 66.80 37.74 45.89 67.22 13.04 55.19
4 3
73.84 11.41 71.61 32.72 39.87 38.84 22.41 17.87
75.13 51.64 47.72 87.34 15.97 64.56

27.6529680365
0.000000
*/

#include <string.h>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

const int MAX_LIMIT = 101;

istream& in = cin;
ostream& out = cout;


class Point
{
public:
	Point() : x(0), y(0) {}
	Point(const Point& pt) : x(pt.x), y(pt.y) {}

public:
	double x, y;
};

Point& operator>>(istream& in, Point& pt) { in >> pt.x >> pt.y; return pt; }


typedef vector<Point> PointList;
typedef vector<pair<Point, Point> > LineList;


LineList upper, lower;


// 시계 반대 방향으로 값이 주어지므로,
// X축의 값이 커지는 경우이면 아래 쪽, 작아지는 쪽이면 위쪽에 있음.
void separateUpperLower(PointList& point)
{
	// 마지막 점과 첫 번째 점 연결선을 처리하기 위해 넣음.
	point[point.size() - 1] = point[0];

	for(int i = 0; i < (int) point.size() - 1; ++i)
	{
		if( point[i].x < point[i + 1].x )
			lower.push_back(make_pair(point[i], point[i + 1]));
		else
			upper.push_back(make_pair(point[i], point[i + 1]));
	}
}

int main(int argc, char* argv[])
{
    int T;

    in >> T;

    while( T-- )
    {
    	int n, m;

    	upper.clear();
    	lower.clear();

        in >> n >> m;

        PointList point1(n + 1), point2(m + 1);

        // first
        for(int i = 0; i < n; ++i)
        	in >> point1[i];

        separateUpperLower(point1);

        // second
        for(int i = 0; i < m; ++i)
        	in >> point2[i];

        separateUpperLower(point2);
    }

    return 0;
}
