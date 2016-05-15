/*
https://algospot.com/judge/problem/read/WEIRD
22
12
70
836
4030
5830
7192
7912
9272
10430
10570
10792
10990
11410
11690
12110
12530
12670
13370
13510
13790
13930
14770

not weird
weird
weird
...

WEIRD Number:
1. N의 약수 총합(N은 제외)이 N보다 크고,
2. 약수의 서브셋의 합이 N이 되는 경우가 없어야 함.
*/
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

istream& in = cin;
ostream& out = cout;

int N = 0;

// 약수 구하기
vector<int> getDivisors(int n, bool includeSelf)
{
	int to = (int) sqrt(n);

	vector<int> divisors;

	divisors.push_back(1);

	for (int i = 2; i <= to; ++i)
	{
		if ((n % i) == 0)
			divisors.push_back(i);
	}

	for (int i = divisors.size() - 1; i > 0; --i)
	{
		int d = n / divisors[i];

		if (d != divisors[i])
			divisors.push_back(d);
	}

	if (includeSelf)
		divisors.push_back(n);

	return divisors;
}


/*
divisors: 자신을 제외한 약수의 집합
sum: 약수의 서브셋을 합한 값. main에서 호출될 때는 전체 서브셋의 합이 들어 옴
start: 빼기 시작할 약수의 첫번째 원소
약수를 하나씩 빼나가는 식으로 traverse 함.
약수가 a, b, c, d 라고 할 때, 다음과 같은 트리형태로 계산해 나감
s -+- (s - a) -+- (s - a - b) --- (s - a - b - c) --- (s - a - b - c - d)
   |           |               +- (s - a - b - d)
   |           +- (s - a - c) --- (s - a - c - d)
   |           +- (s - a - d)
   +- (s - b) --- (s - b - c) --- (s - b - c - d)
   |           +- (s - b - d)
   +- (s - c) --- (s - c - d)
   +- (s - d)
*/
bool hasSubset(const vector<int>& divisors, int sum, int start)
{
	// 서브셋의 합이 N인 경우를 찾았음
	if (sum == N)
		return true;
	
	// 더 이상 실행할 필요가 없는 경우임.
	if (sum < N)
		return false;

	for (int i = start; i < divisors.size(); ++i)
	{
		if (hasSubset(divisors, sum - divisors[i], i + 1))
			return true;
	}

	return false;
}

int main(int argc, char* argv[])
{
	int T = 0;

	in >> T;
	while (T--)
	{
		in >> N;

		vector<int> divisors = getDivisors(N, false);
		
		int sum = 0;
		for (int i = 0; i < divisors.size(); ++i)
		{
			sum += divisors[i];
		}

		if (sum <= N || hasSubset(divisors, sum, 0))
			out << "not weird" << "\n";
		else
			out << "weird" << "\n";
	}

	return 0;
}
