/*
https://www.algospot.com/judge/problem/read/XHAENEUNG
2
two + three = ivef
zero * zero = one
*/

#include <iostream>
#include <map>
#include <string>
#include <cstring>


using namespace std;

istream& in = cin;
ostream& out = cout;


class Number
{
public:
	Number(int n, const string& text)
		: _n(n), _text(text)
	{
		init();
	}

private:
	int		_n;
	string	_text;
	int		_count[26];

private:
	void init()
	{
		memset(_count, 0, sizeof(_count));

		for(int i = 0; i < _text.size(); ++i)
			_count[_text.at(i) - 'a'] += 1;
	}

public:
	int n() const { return _n; }
	const string& text() { return _text; }

	bool compare(const string& text)
	{
		if (_text.size() != text.size()) return false;

		int count[26];
		memset(count, 0, sizeof(count));

		for (int i = 0; i < text.size(); ++i)
			count[text.at(i) - 'a'] += 1;

		for (int i = 0; i < _text.size(); ++i)
		{
			int idx = _text.at(i) - 'a';
			if (_count[idx] != count[idx]) return false;
		}

		return true;
	}
};

map<string, int> strToNum;

Number numbers[11] = { Number(0, "zero"), Number(1, "one"), Number(2, "two"), Number(3, "three"), Number(4, "four")
					 , Number(5, "five"), Number(6, "six"), Number(7, "seven"), Number(8, "eight"), Number(9, "nine"), Number(10, "ten") };


int calc(const string& lhs, const string& opr, const string&rhs)
{
	int l = numbers[strToNum.find(lhs)->second].n();
	int r = numbers[strToNum.find(rhs)->second].n();

	switch (opr.at(0))
	{
	case '+':
		return l + r;
	case '-':
		return l - r;
	case '*':
		return l * r;
	}

	return -1;
}

int main()
{
	std::ios::sync_with_stdio(false);

	for (int i = 0; i < 11; ++i)
		strToNum[numbers[i].text()] = numbers[i].n();

	int T;
	in >> T;

	while (T--)
	{
		string lhs, opr, rhs, eqOpr, ans;

		in >> lhs >> opr >> rhs >> eqOpr >> ans;

		int ret = calc(lhs, opr, rhs);

		if (ret < 0 || ret > 10 || !numbers[ret].compare(ans))
			out << "No\n";
		else
			out << "Yes\n";
	}

	return 0;
}
