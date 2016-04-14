/*
https://www.algospot.com/judge/problem/read/LECTURE
4
abbaaccb
dddcccbbbaaa
geegeegeegeebabybabybaby
oh
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

istream& in = cin;
ostream& out = cout;


int main()
{
	std::ios::sync_with_stdio(false);

	int T;

	in >> T;

	while (T--)
	{
		string s;

		in >> s;

		vector<string> sub;

		for (int i = 0; i < s.size(); i += 2)
		{
			sub.push_back(s.substr(i, 2));
		}

		std::sort(sub.begin(), sub.end());

		for (vector<string>::iterator it = sub.begin(); it != sub.end(); ++it)
			out << *it;
		out << "\n";
	}

	return 0;
}
