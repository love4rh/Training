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
ostream& out = cout;

// 삼각형 경로 저장을 위한 전역변수
int triPath[MAX_LIMIT][MAX_LIMIT];


int main(int argc, char* argv[])
{
	int T = 0, depth = 0;

	in >> T;

	while (T--)
	{
		in >> depth;

		// (0, 0) 읽어서 설정
		in >> triPath[0][0];

		// 2단계부터 읽기
		for (int d = 1; d < depth; ++d)
		{
			// 바로 위에서만 올 수 있음
			in >> triPath[d][0];
			triPath[d][0] += triPath[d - 1][0];

			// 가운데 있는 애들
			for (int j = 1; j < d; ++j)
			{
				in >> triPath[d][j];

				triPath[d][j] += max(triPath[d - 1][j - 1], triPath[d - 1][j]);
			}

			// 대각선 위쪽에서만 올 수 있음
			in >> triPath[d][d];
			triPath[d][d] += triPath[d - 1][d - 1];
		}

		// 마지막 경로 합 비교하여 최대값 찾기
		int maxSum = triPath[depth - 1][0];

		for (int j = 1; j < depth; ++j)
			maxSum = max(maxSum, triPath[depth - 1][j]);

		out << maxSum << "\n";
	}

	return 0;
}
