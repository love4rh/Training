/*
https://algospot.com/judge/problem/read/MMRECT1
https://algospot.com/judge/problem/read/MMRECT2
2
10
0 0
2 2
2 0
0 2
-10 -10
7 7
10 10
-10 10
10 -10
5 8
4
0 0
2 2
2 0
0 2

2 20
2 2
*/

#include <algorithm>
#include <iostream>
#include <vector>
#include <map>

using namespace std;


const int MAX_NUM = 20001;	// MMRECT1이면 50, MMRECT2이면 20000

istream& in = cin;
ostream& out = cout;

struct Point
{
	int x, y;

	Point() : x(0), y(0) {}
	Point(int tx, int ty) : x(tx), y(ty) {}

	bool operator<(const Point& rhs)
	{
		return this->x < rhs.x || (this->x == rhs.x && this->y < rhs.y);
	}

	bool operator==(const Point& rhs)
	{
		if (this == &rhs)
			return true;

		return this->x == rhs.x && this->y == rhs.y;
	}
};


int N, minVal, maxVal;
Point points[MAX_NUM];

int search(Point pt, int low, int high)
{
	int mid = 0;

	while (low < high)
	{
		mid = (low + high) >> 1;

		if (points[mid] < pt)
		{
			low = mid + 1;
		}
		else
		{
			high = mid;
		}
	}

	return points[high] == pt ? high : -1;
}


int main(int argc, char* argv[])
{
	int T = 0, depth = 0;

	in >> T;

	while (T--)
	{
		in >> N;

		for (int i = 0; i < N; ++i)
			in >> points[i].x >> points[i].y;

		std::sort(points, points + N);

		/* // search() 테스트
		out << "c: " << search(Point(-10, -10), 0, N - 1) << "\n";
		out << "c: " << search(Point(-10, -9), 0, N - 1) << "\n";
		out << "c: " << search(Point(0, 0), 0, N - 1) << "\n";
		out << "c: " << search(Point(10, 10), 0, N - 1) << "\n";
		out << "c: " << search(Point(11, 0), 0, N - 1) << "\n";
		*/

		minVal = 0x7fffffff;
		maxVal = -1;

		// 정사각형이 되는 경우 찾기
		for (int i = 0; i < N - 3; ++i)
		{
			for (int j = i + 1; j < N; ++j)
			{
				// x축에 평행한 경우만 고려
				if (points[i].x != points[j].x)
					break;

				// x가 같은 경우 정렬되어 있으므로 points[j].y 가 더 큼.
				// 따라서 한 변의 길이는 다음과 같음
				int width = points[j].y - points[i].y;

				// points[i], points[j] 두 점이 정해졌으므로 다른 두점은 다음과 같아야 함.
				Point pt3(points[i].x + width, points[i].y);
				Point pt4(points[i].x + width, points[j].y);

				// 두 점이 있다면 정사각형을 만들 수 있는 경우임
				if (-1 != search(pt3, j + 1, N) && -1 != search(pt4, j + 1, N))
				{
					if (minVal > width)
						minVal = width;

					if (maxVal < width)
						maxVal = width;
				}
			}
		}

		out << minVal << " " << maxVal << "\n";
	}

	return 0;
}
