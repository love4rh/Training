/*
https://algospot.com/judge/problem/read/STRJOIN
3
3
2 2 4
5
3 1 3 4 1
8
1 1 1 1 1 1 1 2

12
26
27
*/
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

istream& in = cin;
ostream& out = cout;


int main(int argc, char* argv[])
{
	int T = 0, N;

	in >> T;
	while (T--)
	{
		in >> N;

		vector<int> strLen(N, 0);

		for (int i = 0; i < N; ++i)
		{
			in >> strLen[i];
		}

		int costSum = 0;

		// 작은 길이의 것 2개를 계속 더해 나가는 것이 최소 비용임.
		while (strLen.size() > 1)
		{
			std::sort(strLen.begin(), strLen.end());

			int cost = 0;
			vector<int>::iterator it = strLen.begin();

			cost = *it + *(++it);
			costSum += cost;

			strLen.erase(strLen.begin());
			strLen.erase(strLen.begin());

			strLen.push_back(cost);
		}

		out << costSum << "\n";
	}

	return 0;
}
