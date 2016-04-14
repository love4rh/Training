/*
https://www.algospot.com/judge/problem/read/NQUEEN
3
1
2
8
*/
#include <iomanip>
#include <iostream>
#include <cmath>


using namespace std;

istream& in = cin;
ostream& out = cout;

const int MAX_NUM = 12;

// 배열의 인덱스는 열을 의미함.
// 같은 열에 하나의 Queen 밖에 올 수 없으므로 이 정도만 사용하면 됨.
int queenPos[MAX_NUM];


// (col, row)에 Queen을 놓을 수 있는 지 여부 체크.
// 만족해야 할 조건은
// 0. 같은 col 값이 있으면 안됨 --> 이미 만족하고 있음.
// 1. row의 값이 이전 것과 같으면 안 됨.
// 2. col의 차이 절대값과 row의 차이 절대값이 달라야 함. (대각선 위치)
bool isPossible(int col, int row)
{
	for (int c = 0; c < col; ++c)
	{
		if (queenPos[c] == row || abs(c - col) == abs(queenPos[c] - row))
			return false;
	}

	return true;
}

int placeQueen(int col, int N)
{
	if (col == N)
	{
		return 1;
	}

	int possibleCount = 0;

	// 지정된 열 위치 (col) 내 row번째 행에 Queen을 위치시켜봄
	for (int row = 0; row < N; ++row)
	{
		// 다음 열 위치(col)의 row 번째 행에 Queen을 위치시킬 수 있는 지 체크
		if (isPossible(col, row))
		{
			// 가능하면 해당 위치에 Queen을 놓고
			queenPos[col] = row;

			// 다음 열에 Queen을 놓는 시도를 함
			possibleCount += placeQueen(col + 1, N);
		}
	}

	return possibleCount;
}

int main(int argc, char* argv[])
{
	int T = 0, N = 0;

	in >> T;

	while (T--)
	{
		in >> N;
		out << placeQueen(0, N) << endl;
	}

	return 0;
}
