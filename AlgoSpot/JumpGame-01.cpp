// https://algospot.com/judge/problem/read/JUMPGAME

#include <fstream>

#include <iomanip>
#include <iostream>


using namespace std;

//istream& in = cin;
ifstream in("V:\\Work\\Algorithm\\data\\jumpGame.txt");

int board[101][101];


bool nav(int y, int x)
{
	if (y == 0 && x == 0)
		return true;

	bool ret = false;

	// left
	for (int i = 0; !ret && i < x; ++i)
	{
		if (i + 1 == board[y][x - i - 1])
			ret = nav(y, x - i - 1);
	}

	// top
	for (int i = 0; !ret && i < y; ++i)
	{
		if (i + 1 == board[y - i - 1][x])
			ret = nav(y - i - 1, x);
	}

	return ret;
}

int main(int argc, char* argv[])
{
	int T = 0;

	in >> T;

	while (T--)
	{
		int n, x, y;

		in >> n;

		for (y = 0; y < n; ++y)
			for (x = 0; x < n; ++x)
				in >> board[y][x];

		// 끝점에서
		cout << (nav(n - 1, n - 1) ? "YES" : "NO") << "\n";
	}

	return 0;
}
