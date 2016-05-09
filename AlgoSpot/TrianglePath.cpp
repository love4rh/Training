/*
https://algospot.com/judge/problem/read/TRIANGLEPATH
2
5
6
1  2
3  7  4
9  4  1  7
2  7  5  9  4
5
1
2 4
8 16 8
32 64 32 64
128 256 128 256 128

28
341
*/

#include <algorithm>
#include <iostream>

using namespace std;

const int MAX_LIMIT = 100;

istream& in = cin;

// 삼각형 경로 저장을 위한 전역변수
int trianglePath[MAX_LIMIT][MAX_LIMIT];



int main(int argc, char* argv[])
{
	int T = 0, depth = 0;

	in >> T;

	while (T--)
	{
		in >> depth;

		// (0, 0) 읽어서 설정
		in >> trianglePath[0][0];

		// 2단계부터 읽기
		for (int curDepth = 1; curDepth < depth; ++curDepth)
		{
			// 바로 위에서만 올 수 있음
			in >> trianglePath[curDepth][0];
			trianglePath[curDepth][0] += trianglePath[curDepth - 1][0];

			// 가운데 있는 애들
			for (int j = 1; j < curDepth; ++j)
			{
				in >> trianglePath[curDepth][j];

				trianglePath[curDepth][j] += max(trianglePath[curDepth - 1][j - 1], trianglePath[curDepth - 1][j]);
			}

			// 대각선 위쪽에서만 올 수 있음
			in >> trianglePath[curDepth][curDepth];
			trianglePath[curDepth][curDepth] += trianglePath[curDepth - 1][curDepth - 1];
		}

		// 마지막 경로 합 비교하여 최대값 찾기
		int maxSum = trianglePath[depth - 1][0];

		for (int j = 1; j < depth; ++j)
			maxSum = max(maxSum, trianglePath[depth - 1][j]);

		cout << maxSum << "\n";
	}

	return 0;
}
