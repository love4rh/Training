// https://algospot.com/judge/problem/read/BOGGLE

/*
1
URLPM
XPRET
GIAET
XTNZY
XOQRS
6
PRETTY
GIRL
REPEAT
KARA
PANDORA
GIAZAPX

PRETTY YES
GIRL YES
REPEAT YES
KARA NO
PANDORA NO
GIAZAPX YES
*/

#include <string>
#include <iomanip>
#include <iostream>
#include <vector>
#include <string.h>

using namespace std;

istream& in = cin;
ostream& out = cout;


string word;
string board[5];
int never[5][5][11];	// 안 되는 애들에 대한 정보 저장


int dir[][2] =
{
	{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}
};

const char b(int x, int y)
{
	if( x < 0 || y < 0 || x >= 5 || y >= 5 )
		return 0;

	return board[y][x];
}

bool traverse(int x, int y, int c)
{
	if( c == (int) word.size() )
		return true;

	// 안된다고 판단이 난 경우는 더 이상 돌 필요 없음
	if( never[y][x][c] != 0 )
		return false;

	for(int d = 0; d < 8; ++d)
	{
		int nx = x + dir[d][0];
		int ny = y + dir[d][1];

		if( b(nx, ny) == word[c] && traverse(nx, ny, c + 1) )
			return true;
	}

	// 돌아봐야 안 되는 경우임
	never[y][x][c] = 1;

	return false;
}

bool found()
{
	memset(never, 0, sizeof(never));

	for(int y = 0; y < 5; ++y)
		for(int x = 0; x < 5; ++x)
		{
			if( board[y][x] == word[0] && traverse(x, y, 1) )
				return true;
		}

	return false;
}


int main(int argc, char* argv[])
{
	std::ios::sync_with_stdio(false);

	int T, N;

	in >> T;

	while(T--)
	{
		for(int i = 0; i < 5; ++i)
			in >> board[i];

		in >> N;
		while(N--)
		{
			in >> word;

			out << word << " " << (found() ? "YES" : "NO") << "\n";
		}
	}

	return 0;
}
