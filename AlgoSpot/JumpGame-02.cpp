// https://algospot.com/judge/problem/read/JUMPGAME

#include <fstream>

#include <iomanip>
#include <iostream>


using namespace std;

//istream& in = cin;
ifstream in("V:\\Work\\Algorithm\\data\\jumpGame.txt");

int main(int argc, char* argv[])
{
	int T = 0;

	in >> T;

	while (T--)
	{
		int N, step;
		int board[101][101] = { 1, };

		in >> N;

		for (int y = 0; y < N; ++y)
			for (int x = 0; x < N; ++x)
			{
				in >> step;
				
				if (!board[y][x])
					continue;

				// �Ʒ������� �� �� �ִ� ��ġ ��ŷ
				if (y + step < N)
					board[y + step][x] = 1;
				// ���������� �� �� �ִ� ��ġ ��ŷ
				if (x + step < N)
					board[y][x + step] = 1;
			}

		// ������ ���� 1�̸� �� �� �ִ� ����.
		cout << (board[N - 1][N - 1] ? "YES" : "NO") << "\n";
	}

	return 0;
}
