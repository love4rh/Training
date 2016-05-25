/*
https://www.algospot.com/judge/problem/read/ANAGRAM
3
weird wired
apple angle
apple elppa

Yes
No.
Yes
*/

#include <algorithm>
#include <iostream>
#include <string>

using namespace std;


istream& in = cin;
ostream& out = cout;


int main(int argc, char* argv[])
{
	int T = 0;

	in >> T;
	while (T--)
	{
		string s1, s2;

		in >> s1 >> s2;

		bool isOk = s1.compare(s2) != 0;

		if (isOk)
		{
			std::sort(s1.begin(), s1.end());
			std::sort(s2.begin(), s2.end());

			isOk = s1.compare(s2) == 0;
		}

		out << (isOk ? "Yes" : "No.") << "\n";
	}

	return 0;
}
