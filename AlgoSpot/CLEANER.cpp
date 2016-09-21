#include <iostream>


using namespace std;

istream& in = cin;
ostream& out = cout;

int N, M;
int room[7][7];


int getOrder(int x, int y)
{
	if (x < 0 || x >= N || y < 0 || y >= M)
		return -2;

	return room[x][y];
}

int navigate(int x, int y, int order)
{
	// 한 경우가 완성된 것임
	if (x == N - 1 && y == M - 1 && order == N * M - 1)
		return 1;

	// 돌았음음 마킹
	if (-1 == room[x][y])
		room[x][y] = -2;

	int caseNum = 0;

	// (x, y)를 기준으로 갈 수 있는 곳은 상/하/좌/우 가 있을 수 있음.
	// 이 중 room[][]의 값이 order + 1라면 그쪽으로만 가야함.
	static int d[][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

	// 가야만 하는 위치가 있는 지 확인
	int direction = -1;
	for (int c = 0; c < 4; ++c)
	{
		if (order + 1 == getOrder(x + d[c][0], y + d[c][1]))
		{
			direction = c;
			break;
		}
	}

	// 가야만 하는 위치가 있는 경우임.
	if (direction != -1)
		caseNum += navigate(x + d[direction][0], y + d[direction][1], order + 1);
	else
	{
		// 없다면 가능한 경우를 뒤져봄
		for (int c = 0; c < 4; ++c)
		{
			if (-1 == getOrder(x + d[c][0], y + d[c][1]))
				caseNum += navigate(x + d[c][0], y + d[c][1], order + 1);
		}
	}

	// 다른 경우 계산을 위하여 원래 값으로 복원
	if (-2 == room[x][y])
		room[x][y] = -1;

	return caseNum % 1000000007;
}

int main()
{
	int T;

	in >> T;

	while (T--)
	{
		in >> N >> M;

		for (int x = 0; x < N; ++x)
			for (int y = 0; y < M; ++y)
				in >> room[x][y];

		out << navigate(0, 0, 0) << "\n";
	}

	return 0;
}

