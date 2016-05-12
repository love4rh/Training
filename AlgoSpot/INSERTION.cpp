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

const int MAX_LIMIT = 50001;

int N;
int P[MAX_LIMIT];
int A[MAX_LIMIT];


int main(int argc, char* argv[])
{
	int T = 0;

	in >> T;
	while (T--)
	{
		in >> N;

		list<int> numbers;

		for (int i = 0; i < N; ++i)
		{
			in >> P[i];
			numbers.push_back(i + 1);
		}

		// 제일 뒤에 부터 계산하여
		// A[i] = 현재 가용한 정렬된 숫자들(numbers) 중 뒤에서 P[i]번째(0-based) 있는 수임.
		// 앞에서는 i - P[i] 번째임.
		list<int>::iterator it;

		for (int i = N - 1; i >= 0; --i)
		{
			if( P[i] > i - P[i])
				it = std::next(numbers.begin(), i - P[i]);
			else
				it = std::prev(--numbers.end(), P[i]);

			A[i] = *it;

			numbers.erase(it);
		}

		out << A[0];
		for (int i = 1; i < N; ++i)
			out << " " << A[i];

		out << "\n";
	}

	return 0;
}
