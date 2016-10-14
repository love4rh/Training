/*
https://algospot.com/judge/problem/read/MOON
2
3 4 6
4 5 6

25.864
36.466
*/

#include <stdio.h>
#include <iostream>
#include <cmath>


using namespace std;

istream& in = cin;
ostream& out = cout;


int main()
{
	std::ios::sync_with_stdio(false);

	double pi = acos(-1.0);

	int T;

	in >> T;

	while (T--)
	{
		int r1, r2, d;

		in >> r1 >> r2 >> d;

		double cx = (d * d + r1 * r1 - r2 * r2) / 2.0 / d;
		double cy = sqrt(r1 * r1 - cx * cx);

		double th1 = acos(cx / r1);
		double th2 = acos((d - cx) / r2);

		double join = (r1 * r1 * th1 - cx * cy) + (r2 * r2 * th2 - (d - cx) * cy);

		printf("%.3f\n", (r1 * r1 * pi - join));
	}

	return 0;
}

