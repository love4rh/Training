// https://algospot.com/judge/problem/read/NAMING

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using namespace std;


// "알고리즘 문제해결 전략" p. 653 참고
vector<int> getPartialMatch(const string& N)
{
	int m = N.size();
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

int main(int argc, char* argv[])
{
	string name, tmp;

	cin >> name >> tmp;

	name += tmp;

	vector<int> ret;
	vector<int> pi = getPartialMatch(name);
	int k = name.size();

	while (k > 0)
	{
		ret.push_back(k);
		k = pi[k - 1];
	}

	for (int i = ret.size() - 1; i >= 0; --i)
		cout << ret[i] << (i == 0 ? "\n" : " ");

	return 0;
}
