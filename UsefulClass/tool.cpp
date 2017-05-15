#include "tool.h"


// Greatest Common Devider (최대공약수 구하기)
int gcd(int a, int b)
{
	if (a == b) return a;

	return b ? gcd(b, a % b) : a;
}

long smallestPrimeFactor(long number)
{
	if (number == 1)
		return 0;

	if (number % 2 == 0)
		return 2;

	long divisorLimit = (long) sqrt((double)number);

	for (long divisor = 3; divisor <= divisorLimit; divisor += 2)
	{
		if (number % divisor == 0)
			return divisor;
	}

	return number;
}

// 소수인지 여부 반환
bool isPrime(long number)
{
	return smallestPrimeFactor(number) == number;
}

// 최대공배수 구하기
int lcm(int a, int b)
{
	return a * (b / gcd(a, b));
}

// 소인수 분해
vector<int> factor(int n)
{
	if (n == 1) return vector<int>(1, 1);

	vector<int> ret;

	for (int div = 2; n > 1; ++div)
	{
		while (n % div == 0)
		{
			n /= div;
			ret.push_back(div);
		}
	}

	return ret;
}

// KMP 알고리즘을 이용한 부분 일치 테이블 생성
// pi[] 값을 계산하여 반환함.
vector<int> getPartialMatch(const string& N)
{
	int m = N.size();

	vector<int> pi(m, 0);

	int begin = 1, matched = 0;

	while (begin + matched < m)
	{
		if (N[begin + matched] == N[matched])
		{
			++matched;
			pi[begin + matched - 1] = matched;
		}
		else
		{
			if (matched == 0)
				begin += 1;
			else
			{
				begin += matched - pi[matched - 1];
				matched = pi[matched - 1];
			}
		}
	}

	return pi;
}

struct Comparator
{
	const vector<int>& _group;
	int _t;

	Comparator(const vector<int>& group, int t) : _group(group), _t(t) {}

	bool operator() (int a, int b) const
	{
		if (_group[a] != _group[b])
			return _group[a] < _group[b];

		return _group[a + _t] < _group[b + _t];
	}
};

// 접미사 배열을 계산
vector<int> getSuffixArray(const string& s)
{
	int n = s.size();

	vector<int> perm(n);
	vector<int> group(n + 1);

	for (int i = 0; i < n; ++i)
	{
		group[i] = s[i];
		perm[i] = i;
	}

	group[n] = -1;

	int t = 1;

	while (t < n)
	{
		Comparator compareUsing2T(group, t);

		sort(perm.begin(), perm.end(), compareUsing2T);

		t *= 2;

		if (t >= n) break;

		vector<int> newGroup(n + 1);
		newGroup[n] = -1;
		newGroup[perm[0]] = 0;

		for (int i = 1; i < n; ++i)
		{
			if (compareUsing2T(perm[i - 1], perm[i]))
				newGroup[perm[i]] = newGroup[perm[i - 1]] + 1;
			else
				newGroup[perm[i]] = newGroup[perm[i - 1]];
		}

		group = newGroup;
	}

	return perm;
}

// KMP 알고리즘을 이용한 문자열 검색
vector<int> kmpSearch(const string& H, const string& N)
{
	int n = H.size(), m = N.size();

	vector<int> ret;
	vector<int> pi = getPartialMatch(N);

	int begin = 0, matched = 0;

	while (begin <= n - m)
	{
		if (matched < m && H[begin + matched] == N[matched])
		{
			matched += 1;

			if (matched == m)
				ret.push_back(begin);
		}
		else
		{
			if (matched == 0)
				begin += 1;
			else
			{
				begin += matched - pi[matched - 1];
				matched = pi[matched - 1];
			}
		}
	}

	return ret;
}

// a의 접미사이면서 b의 접두사인 문자열의 최대 길이 구하기
int maxOverlap(const string& a, const string& b)
{
	int n = a.size(), m = b.size();
	vector<int> pi = getPartialMatch(b);

	int begin = 0, matched = 0;
	while (begin < n)
	{
		if (matched < m && a[begin + matched] == b[matched])
		{
			matched += 1;
			if (begin + matched == n)
				return matched;
		}
		else
		{
			if (matched == 0)
				begin += 1;
			else
			{
				begin += matched - pi[matched - 1];
				matched = pi[matched - 1];
			}
		}
	}

	return 0;
}


// 이진탐색 기본코드
int binarySearch(const vector<int>& A, int x)
{
	int n = A.size();
	int lo = -1, hi = n;

	while (lo + 1 < hi)
	{
		int mid = (lo + hi) / 2;

		if (A[mid] < x)
			lo = mid;
		else
			hi = mid;
	}

	return hi;
}


// n개의 원소 중 m개를 고르는 모든 조합을 찾는 알고리즘
// n: 전체 원소의 수
// picked: 지금까지 고른 원소들의 번호
// toPick: 더 고를 원소의 수
void pick(int n, vector<int>& picked, int toPick)
{
	if (toPick == 0)
	{
		// printPicked(picked);
		return;
	}

	// 고를 수 있는 가장 작은 번호를 계산
	int smallest = picked.empty() ? 0 : picked.back() + 1;

	// 이 단계에서 원소 하나를 고른다.
	for (int next = smallest; next < n; ++next)
	{
		picked.push_back(next);
		pick(n, picked, toPick - 1);
		picked.pop_back();
	}
}


// 동적계획법 기본 틀
/*
// -1로 초기화해야 함: memset(cache, -1, sizeof(cache));
int cache[####][####];

int someObscureFunction(int a, int b)
{
	// 기저사례 계산
	// if (...) return ....;

	// (a, b)에 대한 답을 구한 적이 있으면 곧장 반환
	int& ret = cache[a][b];

	if (ret != -1)
		return ret;

	// 여기에서 답을 계산하여 ret에 할당
	// ....

	return ret;
}
// */


// 이항계수 계산
int binoCached[30][30];

int bino(int n, int r)
{
	if (r == 0 || n == r) return 1;

	if (binoCached[n][r] != -1)
		return binoCached[n][r];

	return binoCached[n][r] = bino(n - 1, r - 1) + bino(n - 1, r);
}


int comb[30][30];

void calcCombination()
{
    memset(comb, 0, sizeof(comb));

    comb[0][0] = 1;

    for(int i = 1; i < 30; ++i)
    {
        comb[i][0] = 1;

        for(int j = 1; j <= i; ++j)
        {
            comb[i][j] = comb[i - 1][j - 1] + comb[i - 1][j];
        }
    }
}

// 약수 구하기
vector<int> getDivisors(int n, bool includeSelf)
{
	int to = (int)sqrt(n);

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

