/*
https://www.algospot.com/judge/problem/read/DECUAL
3
C(O)^2KIE(RUN)^100000000
COOKIER(UNR)^99999999UN
C(O)^2KIE(RUN)^50
CO(OKIER)^1(UNR)^49UN
KR(I)^3(I)^4
K(RI)^4

YES
YES
NO
*/

#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

typedef long long int64;

const int64 seed = 33;

istream& in = cin;
ostream& out = cout;


// b ^ e
int64 powEx(int64 b, int64 e)
{
	int64 p = 1;

	while( e )
	{
		if( e & 0x01 ) p = p * b;

		b *= b;
		e >>= 1;
	}

	return p;
}

int64 powSum2(int64 b, int64 n)
{
	return (1 - powEx(b, n)) / (1 - b);
}

// b^0 + b^1 + b^2 + ... + b^(n-1)
int64 powSum(int64 b, int64 n)
{
	int64 s = 0, c = 1;

	while( n )
	{
		// lowest bit가 1이라면
		if( n & 0x01 )
		{
			// s에 들어 있는 값들은 비트가 1이 되기 전
			s = s * b + c;
		}

		c = c + c * b; // b^0  + b^1  + b^2 + ... 순차적으로 더해짐.
		b = b * b; // b^1 -> b^2 -> b^3 ....
		n >>= 1; // 2씩 나눠가면서,
	}

	return s;
}

// hash value: h = 33 * h + s[i]
int64 toHash(const string& s)
{
	int64 h = 0;

	for(size_t i = 0; i < s.size(); ++i)
	{
        if( s[i] == '(' )
        {
        	int64 sub = 0;

        	size_t j = i;
        	while( s[++j] != ')' )
        		sub = sub * seed + s[j];

        	int64 n = j - i - 1;
        	int64 r = atoll(s.data() + j + 2);

        	h *= powEx(seed, n * r);
        	h += powSum(powEx(seed, n), r) * sub;

        	i = j + 2;
        }
        else if( 'A' <= s[i] && s[i] <= 'Z' )
        {
        	h = seed * h + s[i];
        }
	}

	return h;
}


int main()
{
	std::ios::sync_with_stdio(false);

	int T = 0;

	in >> T;
	while (T--)
	{
		string s1, s2;

		in >> s1 >> s2;

		out << (toHash(s1) == toHash(s2) ? "YES" : "NO") << "\n";
	}

	return 0;
}
