// https://algospot.com/judge/problem/read/PALINDROMIZE

#include <fstream>

#include <iomanip>
#include <iostream>
#include <string>
#include <vector>


using namespace std;

//istream& in = cin;
ifstream in("V:\\Work\\Algorithm\\data\\PALINDROMIZE.txt");


int main(int argc, char* argv[])
{
	int T = 0;

	string word;
	word.reserve(100002);
	vector<int> pi(100002, -1);

	in >> T;

	while (T--)
	{
		in >> word;

		const char* s = word.data();
		int L = word.size();
		int begin = 2, matched = 0;

		while (begin <= L)
		{
			if (s[begin - 1] == s[L - 1 - matched])
				pi[begin++] = ++matched;
			else if (matched > 0)
				matched = pi[matched];
			else
				pi[begin++] = 0;
		}

		int i;
		for (i = 0; i < L / 2; ++i)
		{
			if (s[i] != s[L - 1 - i])
				break;
		}

		if (i == L / 2)
			printf("%d\n", L);
		else
			printf("%d\n", (L << 1) - pi[L]);
	}

	return 0;
}
