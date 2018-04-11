/*
https://algospot.com/judge/problem/read/LASER
1
7
6 6
1 1
3 3
4 4
10 10
5 5
1 10

1
*/

#include <iostream>
#include <algorithm>
#include <map>
#include <vector>

using namespace std;

typedef pair<int, pair<double, double> >	Line;

istream& in = cin;
ostream& out = cout;

int X[1001], Y[1001];


Line makeLine(int type, double a, double b)
{
	return make_pair(type, make_pair(a, b));
}

int main(int argc, char* argv[])
{
	int T, N;

	in >> T;
	while( T-- )
	{
		in >> N;

		for(int i = 0; i < N; ++i)
			in >> X[i] >> Y[i];

		vector<Line> lines;

		// 두점 (X[i], Y[i]), (X[j], Y[j])을 지나는 직선의 방정식 계산.
		// 기울기와 Y절편을 계산함.
		for(int i = 0; i < N - 1; ++i)
		{
			for(int j = i + 1; j < N; ++j)
			{
				int type = 0;
				double a, b;

				if( X[j] == X[i] )
				{
					type = 1;
					a = b = X[j];
				}
				else
				{
					a = double(Y[j] - Y[i]) / double(X[j] - X[i]);
					b = double(X[j] * Y[i] - X[i] * Y[j]) / double(X[j] - X[i]);
				}

				lines.push_back(makeLine(type, a, b));
			}
		}

		// 기울기 절편 순으로 정렬 후
		std::sort(lines.begin(), lines.end());

		int sameCount = 1, count = 0;
		Line& prevLine = lines.at(0);

		for(int i = 1; i < (int) lines.size(); ++i)
		{
			Line& line = lines.at(i);

			// 직선의 방정식이 같으면 같은 선상에 있는 점임.
			if( prevLine == line )
				sameCount += 1;
			else
			{
				// 5개 점 이상이 같은 직선 상에 있으려면 같은 직선의 방정식이 10개 이상이어야 함.
				if( sameCount >= 10 )
					count += 1;

				prevLine = line;
				sameCount = 1;
			}
		}

		if( sameCount >= 10 )
			count += 1;

		out << count << "\n";
	}

    return 0;
}
