// https://algospot.com/judge/problem/read/BOARDCOVER

#include <iomanip>
#include <iostream>
#include <string>


using namespace std;

istream& in = cin;


int H = 0, W = 0;
int board[21][21];
int possible[4][3][2] = { { { 0, 0 }, { 1, 0 }, { 1, 1 } }
						, { { 0, 0 }, { 0, 1 }, { 1, 1 } }
						, { { 0, 0 }, { 1, 0 }, { 1, -1 } }
						, { { 0, 0 }, { 1, 0 }, { 0, 1 } }
						};

int coverBoard(int sY, int sX)
{
	bool fillAll = true;
	int y = sY, x = sX;

	for (y; y < H; ++y)
	{
		for (x = sX; x < W; ++x)
		{
			if (board[y][x] == 0)
			{
				fillAll = false;
				break;
			}
		}

		if (!fillAll)
			break;

		sX = 0;
	}

	if (fillAll)
		return 1;

	int res = 0;
	for (int i = 0; i < 4; ++i)
	{
		if (!board[y + possible[i][0][0]][x + possible[i][0][1]]
			&& !board[y + possible[i][1][0]][x + possible[i][1][1]]
			&& !board[y + possible[i][2][0]][x + possible[i][2][1]])
		{
			board[y + possible[i][0][0]][x + possible[i][0][1]]
				= board[y + possible[i][1][0]][x + possible[i][1][1]]
				= board[y + possible[i][2][0]][x + possible[i][2][1]] = 1;

			res += coverBoard(y, x + 1);

			board[y + possible[i][0][0]][x + possible[i][0][1]]
				= board[y + possible[i][1][0]][x + possible[i][1][1]]
				= board[y + possible[i][2][0]][x + possible[i][2][1]] = 0;
		}
	}

	return res;
}

int main(int argc, char* argv[])
{
	int caseCount = 0;

	in >> caseCount;

	while (caseCount--)
	{
		in >> H >> W;

		string line;

		for (int h = 0; h < H; ++h)
		{
			in >> line;
			for (int w = 0; w < (int) line.length(); ++w)
			{
				board[h][w] = line[w] == '#' ? 2 : 0;
			}
			board[h][W] = 2;
		}

		for (int w = 0; w <= W; ++w)
			board[H][w] = 2;

		cout << coverBoard(0, 0) << "\n";
	}

	return 0;
}
