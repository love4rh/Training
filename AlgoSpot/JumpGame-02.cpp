// https://algospot.com/judge/problem/read/JUMPGAME

#include <iostream>


using namespace std;

istream& in = cin;
ostream& out = cout;

int main(int argc, char* argv[])
{
	int T = 0;

	in >> T;

	while (T--)
	{
		int N, step;
		bool board[101][101] = { true, };

		in >> N;

		for (int y = 0; y < N; ++y)
			for (int x = 0; x < N; ++x)
			{
				in >> step;
				
				// 이 위치에 올 수 없다면 읽은 step 값은 의미 없으므로 스킵
				if (!board[y][x])
					continue;

				// 아래쪽으로 갈 수 있는 위치 마킹
				if (y + step < N)
					board[y + step][x] = true;
				// 오른쪽으로 갈 수 있는 위치 마킹
				if (x + step < N)
					board[y][x + step] = true;
			}

		// 끝점의 값이 1이면 올 수 있는 것임.
		out << (board[N - 1][N - 1] ? "YES" : "NO") << "\n";
	}

	return 0;
}
