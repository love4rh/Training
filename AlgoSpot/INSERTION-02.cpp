/*
https://algospot.com/judge/problem/read/INSERTION
2
5
0 1 1 2 3
4
0 1 2 3

5 1 4 3 2
4 3 2 1
*/
#include <iostream>
#include <cstring>
#include <list>
#include <functional>

using namespace std;

istream& in = cin;
ostream& out = cout;

/*
M에 0 ~ N - 1까지 순차적으로 할당
[i - P[i], i)번째 것을 오른쪽으로 한 칸씩 이동하고 M[i - P[i]] = i 할당. i가 [0, N)까지 반복.
M의 i번째 원소에 값 i의 위치가 저장됨.
따라서, 최종 결과 R은, R[M[i]] = i + 1 할당 (1-based)

P: 0 1 1 2 3 인 경우,
M: 0 1 2 3 4 로 초기 할당

i = 0, P[0]=0 이므로 이동할 필요 없음.
  --> M: 0 1 2 3 4
i = 1일 때 [1 - 1, 1) 이동, M[0] = 1
  --> M: 1 0 2 3 4
i = 2일 때 [2 - 1, 2) 이동, M[1] = 2
  --> M: 1 2 0 3 4
i = 3일 때 [3 - 2, 3) 이동, M[1] = 3
  --> M: 1 3 2 0 4
i = 4일 때 [4 - 3, 4) 이동, M[1] = 4
  --> M: 1 4 3 2 0
따라서, R: 5 1 4 3 2
*/

const int MAX_LIMIT = 50001;

int N;
int P[MAX_LIMIT];
int M[MAX_LIMIT];
int A[MAX_LIMIT];


int main(int argc, char* argv[])
{
	int T = 0;

	in >> T;
	while (T--)
	{
		in >> N;

		for (int i = 0; i < N; ++i)
		{
			in >> P[i];
			M[i] = i;
		}

		// P[i]에 정의된 수 만큼 반대로(오른쪽으로) 이동시키자
		// P[0]는 항상 0이기 때문에 할 필요 없음
		for (int i = 1; i < N; ++i)
		{
			for (int j = i; j > i - P[i]; --j)
			{
				M[j] = M[j - 1];
			}

			M[i - P[i]] = i;
		}

		for (int i = 0; i < N; ++i)
		{
			A[M[i]] = i + 1;
		}

		out << A[0];
		for (int i = 1; i < N; ++i)
			out << " " << A[i];

		out << "\n";
	}

	return 0;
}
