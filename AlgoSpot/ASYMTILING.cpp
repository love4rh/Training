/*
https://www.algospot.com/judge/problem/read/ASYMTILING
3
2
4
92
*/

#include <iostream>


using namespace std;

istream& in = cin;
ostream& out = cout;

/*
A는 세로 한개, BB는 가로 두개
너비에 따라 가능한 모든 경우는 (대칭, 비대칭 포함)
1: A
2: AA, BB
3: AAA, ABB, BBA
4: AABB, BBBB, AAAA, ABBA, BBAA
5: AAABB, ABBBB, BBABB, AABBA, BBBBA, AAAAA, ABBAA, BBAAA
...
와 같이, n개의 너비를 채우는데 n - 2에 AA 혹은 BB를 넣거나 n - 1에 A를 채우는 방법이 있음.
즉, f(n)를 너비 n인 보드에 타일을 채우는 회수라고 가정하면, f(n) = f(n - 1) + f(n - 2)임.
그리고 f(1) = 1, f(2) = 2임.

비대칭인 것은 가운데를 기준으로 한쪽이 가능한 경우의 수를 빼면 되므로,
n이 짝수일 때는 가운데 BB가 오거나 아무 것도 없이 대칭인 경우가 있으므로,
  f(n) - f(n / 2 - 1) - f(n / 2)
홀수일 때는 가운 A가 오는 경우만 대칭이므로
  f(n) - f(n / 2)
*/

class ExpNumber
{
public:
	ExpNumber() : _d(0), _r(0) {}
	ExpNumber(int d, int r) : _d(d), _r(r) {}
	ExpNumber(const ExpNumber& cp) : _d(cp._d), _r(cp._r) {}

	ExpNumber& operator=(const ExpNumber& rhs)
	{
		if (this == &rhs)
			return *this;

		_d = rhs._d;
		_r = rhs._r;

		return *this;
	}

private:
	static const int _exp = 1000000007;

	// _exp로 나눈 몫
	int _d;

	// _exp로 나눈 나머지
	int _r;

public:
	int d() const { return _d;  }
	int r() const { return _r; }

	ExpNumber& operator-(const ExpNumber& rhs)
	{
		_d -= rhs._d;
		_r -= rhs._r;

		if (_r < 0)
		{
			_d -= 1;
			_r += _exp;
		}

		return *this;
	}

	ExpNumber& operator+(const ExpNumber& rhs)
	{
		_d += rhs._d;
		_r += rhs._r;

		if (_r >= _exp)
		{
			_d += 1;
			_r -= _exp;
		}

		return *this;
	}
};

const int MAX_NUM = 100;

ExpNumber tileNumber[MAX_NUM + 1];


// f(n) 구현
// 큰수를 처리하기 위해서 MOD로 나눈 몫은 d, 나머지는 r로 반환함.
ExpNumber f(int n)
{
	if (n <= 1)
		return ExpNumber(0, 1);
	else if (n <= 2)
		return ExpNumber(0, 2);

	ExpNumber& num = tileNumber[n];

	if (num.d() == -1)
		num = f(n - 2) + f(n - 1);

	return num;
}


int main()
{
	std::ios::sync_with_stdio(false);

	// 초기화
	for (int i = 0; i <= MAX_NUM; ++i)
		tileNumber[i] = ExpNumber(-1, 0);

	int C;

	in >> C;

	while (C--)
	{
		int N;

		in >> N;

		ExpNumber res = f(N) - f(N / 2);

		if ((N % 2) == 0)
			res = res - f(N / 2 - 1);

		out << res.r() << "\n";
	}

	return 0;
}
