// https://algospot.com/judge/problem/read/PALINDROMIZE

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

istream& in = cin;
//ifstream in("C:\\Workspace\\CodeJam\\CodeJam201403\\data\\palindrome.txt");

class rstring
{
public:
	rstring(const string& original) : _str(original) {}

private:
	const string& _str;

public:
	int length() const { return (int) _str.length(); }

	string::const_reference operator[](int pos) const
	{
		return _str.at(length() - pos - 1);
	}
};


// "알고리즘 문제해결 전략" p. 653 참고
vector<int> getPartialMatch(const rstring& N)
{
	int m = N.length();
	vector<int> pi(m, 0);

	int begin = 1, matched = 0;

	while (begin + matched < m)
	{
		if (N[begin + matched] == N[matched])
		{
			matched += 1;
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

int calcMaxMatched(const string& s)
{
	rstring r(s);	//< s를 뒤집은 문자열
	vector<int> pi = getPartialMatch(r);
	int n = s.length(); // r도 길이가 s와 같음.

	// s의 접미사가 r의 접두사와 일치하는 최대개수
	int begin = 0, matched = 0;
	while (begin < n)
	{
		if (matched < n && s[begin + matched] == r[matched])
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

int main(int argc, char* argv[])
{
	int T;

	in >> T;

	while (T--)
	{
		string s;

		in >> s;

		int m = calcMaxMatched(s);
		
		cout << (s.length() * 2 - m) << "\n";
	}

	return 0;
}
