/*
https://algospot.com/judge/problem/read/TWONQR
7
1
2
3
4
5
6
7

0
20
432
28860
2710048
19597490
12701197
*/
#include <iomanip>
#include <iostream>
#include <cmath>
#include <cstring>


using namespace std;

istream& in = cin;
ostream& out = cout;

const int MAX_NUM = 9 * 2;
const int MOD = 20130203;

int N = 0;

// 배열의 인덱스는 열을 의미하고 값은 행의 위치를 의미.
// 같은 열에 Queen, Rook은 하나 밖에 올 수 없으므로 1차원 배열로 표현 가능
// 0을 아무것도 안 둔 것으로 처리하기 위해 인덱스는 1-based.
int queenPos[MAX_NUM];
int rookPos[MAX_NUM];
int rowPlaced[MAX_NUM];


// (col, row)에 Queen, Rook을 놓을 수 있는 지 여부 체크.
// 가능한 경우는 다음 조건을 만족해야 함.
// 0. 같은 col 값이 있으면 안됨 --> 이미 만족하고 있음.
// 1. queenPos와 rookPos에 row와 같은 값이 있으면 안됨.
// 2. queenPos에서 col의 차이 절대값과 row의 차이 절대값이 달라야 함. (대각선 위치)
bool isPossible(int col, int row)
{
	if( queenPos[col] || rookPos[col] || rowPlaced[row] )
		return false;

	for(int c = 1; c <= 2 * N; ++c)
	{
		if( queenPos[c] == row || rookPos[c] == row
				|| (queenPos[c] != 0 && abs(c - col) == abs(queenPos[c] - row)) )
			return false;
	}

	return true;
}

int placeRook(int c, int placed)
{
	if( placed == N )
		return 1;

	int count = 0;

	for(int col = c; col <= 2 * N; ++col)
	{
		if( queenPos[col] || rookPos[col] )
			continue;

		// 지정된 열 위치 (col) 내 row번째 행에 말을 넣어봄
		for(int row = 1; row <= 2 * N; ++row)
		{
			if( rowPlaced[row] )
				continue;

			// 다음 열 위치(col)의 row 번째 행에 말을 넣을 수 있는지 체크
			if( isPossible(col, row) )
			{
				// 가능하면 해당 위치에 말을 놓고
				rookPos[col] = row;
				rowPlaced[row] = 1;

				// 다음 열에 시도
				count += placeRook(col + 1, placed + 1);
				count %= MOD;

				rowPlaced[row] = rookPos[col] = 0;
			}
		}
	}

	return count;
}

// placed: 호출될 때까지 놓아진 말의 개수
int placeQueen(int c, int placed)
{
	if( placed == N )
		return placeRook(1, 0); // Rook 놓기

	int count = 0;

	for(int col = c; col <= 2 * N; ++col)
	{
		if( queenPos[col] || rookPos[col] )
			continue;

		// 지정된 열 위치 (col) 내 row번째 행에 말을 넣어봄
		for(int row = 1; row <= 2 * N; ++row)
		{
			if( rowPlaced[row] )
				continue;

			// 다음 열 위치(col)의 row 번째 행에 말을 넣을 수 있는지 체크
			if( isPossible(col, row) )
			{
				// 가능하면 해당 위치에 말을 놓고
				queenPos[col] = row;
				rowPlaced[row] = 1;

				// 다음 열에 시도
				count += placeQueen(col + 1, placed + 1);
				count %= MOD;

				rowPlaced[row] = queenPos[col] = 0;
			}
		}
	}

	return count;
}

int solve()
{
	memset(queenPos, 0, sizeof(queenPos));
	memset(rookPos, 0, sizeof(rookPos));
	memset(rowPlaced, 0, sizeof(rowPlaced));

	return placeQueen(1, 0);
}

int main(int argc, char* argv[])
{
	std::ios::sync_with_stdio(false);

	int T = 0;

	in >> T;

	while (T--)
	{
		in >> N;
		out << solve() << "\n";
	}

	return 0;
}
