/*
Online Code Jam 2016 1차 #3 짝수 단어
*/

#include <fstream>
#include <iomanip>
#include <iostream>

#include <algorithm>
#include <string>
#include <cstring>

using namespace std;

// istream& in = cin;
ifstream in("V:\\Work\\Algorithm\\2016-01\\input\\problem_3_Set3.in"); // problem_3_Set1 problem_3_example
// ostream& out = cout;
ofstream out("V:\\Work\\Algorithm\\2016-01\\result\\problem_3_Set3.rst");


bool isEven(string& s, int start, int len)
{
	int count[30];

	memset(count, 0, sizeof(count));

	for (int i = 0; i < len; ++i)
	{
		count[s[start + i] - 'a'] += 1;
	}

	bool even = true;
	for (int i = 0; even && i < 26; ++i)
	{
		even = 0 == (count[i] % 2);
	}

	return even;
}

int main(int argc, char* argv[])
{
	std::ios::sync_with_stdio(false);

	int T = 0;

	in >> T;

	while (T--)
	{
		string s;

		in >> s;

		int count = 0;
		for (int start = 0; start < s.size() - 1; start += 1)
		{
			for(int len = 2; len + start <= s.size(); len += 2)
				if (isEven(s, start, len))
					count += 1;
		}

		out << count << "\n";
	}

	return 0;
}
