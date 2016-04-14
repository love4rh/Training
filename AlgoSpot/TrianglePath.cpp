// https://algospot.com/judge/problem/read/TRIANGLEPATH

#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

#define MAX_LIMIT 100

// 삼각형 경로 저장을 위한 전역변수
int trianglePath[MAX_LIMIT][MAX_LIMIT];

//istream& in = cin;
ifstream in;


int main(int argc, char* argv[])
{
	int caseCount = 0, depth = 0;

	in.open("E:\\Work\\Algorithm\\data\\trianglePath.txt");

	in >> caseCount;

	while (caseCount--)
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
