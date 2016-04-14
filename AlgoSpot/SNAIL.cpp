/*
https://www.algospot.com/judge/problem/read/SNAIL
4
5 4
5 3
4 2
3 2
*/
#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;


istream& in = cin;
ostream& out = cout;

// 비가 내릴 확률
const double p = 0.75;


// 이항계수를 동적 계획법을 이용하여 빠르게 계산하기 위한 클래스
class Binomial
{
public:
	// size: 원소 크기
	Binomial(int size)
	{
		_binomial.resize(size + 1, vector<double>(size + 1, 0));
	}

private:
	vector<vector<double> >	_binomial;

public:
	int size() const
	{
		return _binomial.size();
	}

	double get(int n, int k)
	{
		if (n == k || k == 0)
			return 1.0;

		if (_binomial[n][k] != 0)
			return _binomial[n][k];

		return _binomial[n][k] = get(n - 1, k - 1) + get(n - 1, k);
	}
};


int main()
{
	Binomial combination(1000);

	int T, N, M;

	in >> T;

	while (T--)
	{
		in >> N >> M;

		// 기본으로 M미터는 올라가게 되어 있으므로 (N - M) 만큼만 비가 오면 됨.
		// (N - M) 만큼 비가 오지 않을 확률을 계산하면 탈출할 수 없는 확률이니 이 것을 구해 1.0에서 빼자.
		// Sum of (1 - p) ^ x * p ^ (M - x) * Combination(M, x), for x in [M - (N - M), M]

		double r = 0.0;

		// 이 경우는 100% 탈출임
		if (M >= N)
			r = 1.0;
		// 이 경우는 100% 실패임
		else if( N > M * 2 )
			r = 0.0;
		else
		{
			for (int i = 0; i < N - M; i += 1)
			{
				double x = M - i;

				r += pow(1.0 - p, x) * pow(p, M - x) * combination.get(M, (int) x);
			}

			r = 1.0 - r;
		}

		printf("%.10f\n", r);
	}

	return 0;
}
