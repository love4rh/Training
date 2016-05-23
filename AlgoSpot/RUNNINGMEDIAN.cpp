/*
https://algospot.com/judge/problem/read/RUNNINGMEDIAN
4
10 1 0
10 1 1
10000 1273 4936
200000 1273 4936

19830
19850
2448920
*/
#include <iostream>

using namespace std;

istream& in = cin;
ostream& out = cout;

const int MOD = 20090711;

int N = 0, a, b;

int prevVal = -1;

int next()
{
	if (prevVal == -1)
		return prevVal = 1983;

	long long nextVal = prevVal;

	nextVal *= a;
	nextVal += b;

	prevVal = nextVal % MOD;

	return prevVal;
}

int pos; // numbers 저장된 값 개수
int numbers[200002]; // = { 1, 1, 1, 3, 5, 5, 5, 7, 9, 11, 11, 11, 11, };

// [0, pos] 범위 중 v가 들어가야할 위치를 찾아 반환함.
int search(int v)
{
	int low = 0, high = pos + 1;

	while (low < high)
	{
		int mid = (low + high) >> 1;

		if (numbers[mid] < v)
			low = mid + 1;
		else
			high = mid;
	}

	return high;
}

int insert(int v)
{
	if (pos < 0)
	{
		numbers[0] = v;
	}
	else
	{
		int ins = search(v);

		// ins에 넣어야 함.
		if (ins <= pos)
			for (int i = pos + 1; i > ins; --i)
				numbers[i] = numbers[i - 1];

		numbers[ins] = v;
	}

	return numbers[++pos / 2];
}

int main(int argc, char* argv[])
{
	int T = 0;

	in >> T;
	while (T--)
	{
		in >> N >> a >> b;

		pos = prevVal = -1;

		int sum = 0;
		while (N--)
		{
			sum += insert(next());
			sum %= MOD;
		}

		out << sum << "\n";
	}

	return 0;
}
