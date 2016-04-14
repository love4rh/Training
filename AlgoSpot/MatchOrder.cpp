// https://algospot.com/judge/problem/read/MATCHORDER

#include <fstream>

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

//istream& in = cin;
ifstream in("E:\\Work\\Algorithm\\data\\matchOrder.txt");


int main(int argc, char* argv[])
{
	int T = 0, N = 0;

	in >> T;

	while (T--)
	{
		in >> N;

		vector<int> kr(N, 0), ru(N, 0);

		// 러시아 선수 능력치 읽기
		for (int n = 0; n < N; ++n)
			in >> ru[n];

		// 한국 선수 능력치 읽기
		for (int n = 0; n < N; ++n)
			in >> kr[n];

		// 각 국 선수 능력치 비교
		std::sort(ru.begin(), ru.end());
		std::sort(kr.begin(), kr.end());

		int winCount = 0;
		vector<int>::iterator itRu = ru.begin();
		vector<int>::iterator itKr = kr.begin();

		while (itRu != ru.end() && itKr != kr.end())
		{
			if (*itRu <= *itKr)
			{
				winCount += 1;

				++itRu;
			}

			++itKr;
		}

		cout << winCount << "\n";
	}

	return 0;
}
