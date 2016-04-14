// https://algospot.com/judge/problem/read/JLIS

#include <fstream>

#include <memory.h>
#include <algorithm>
#include <iomanip>
#include <iostream>

using namespace std;

//istream& in = cin;
ifstream in("V:\\Work\\Algorithm\\data\\jlis.txt");

int N, M;

int len[101][101];
long long A[101], B[101];


// A의 n, B의 m에서 시작할 때 최대로 얻을 수 있는 JLIS의 길이 반환
int jlis(int n, int m)
{
	int& count = len[n][m];

	if (count != 0)
		return count;

	count = 1;	// 둘 중에 하나는 꼭 포함되므로 1이어야 함.

	long long maxElem = max(A[n], B[m]);

	for (int i = n + 1; i <= N; ++i)
		if (maxElem < A[i])
			count = max(count, jlis(i, m) + 1);

	for (int i = m + 1; i <= M; ++i)
		if (maxElem < B[i])
			count = max(count, jlis(n, i) + 1);

	return count;
}

int main(int argc, char* argv[])
{
	int T = 0;

	in >> T;

	// 작은 값을 하나 넣이 위한 처리
	A[0] = 1;
	A[0] <<= 33;
	A[0] *= -1;
	B[0] = A[0];

	while (T--)
	{
		in >> N >> M;

		for (int i = 1; i <= N; ++i)
			in >> A[i];

		for (int i = 1; i <= M; ++i)
			in >> B[i];

		memset(len, 0, sizeof(len));

		// 포함되지 않는 경우를 계산하기 위하여 제일 앞에 작은 값을 넣을 것이
		// 하나 추가되므로 1을 빼줘야 함.
		cout << jlis(0, 0) - 1 << "\n";
	}

	return 0;
}
