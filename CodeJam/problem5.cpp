/*
Online Code Jam 2016 1차 #4 뱀 발전기
*/

#include <fstream>
#include <iomanip>
#include <iostream>

#include <algorithm>
#include <vector>
#include <cstring>

using namespace std;

// istream& in = cin;
ifstream in("V:\\Work\\Algorithm\\2016-01\\input\\problem_5_Set1.in"); // problem_5_Set1 problem_5_example
// ostream& out = cout;
ofstream out("V:\\Work\\Algorithm\\2016-01\\result\\problem_5_Set1.rst");



int main(int argc, char* argv[])
{
	std::ios::sync_with_stdio(false);

	int T = 0, N;

	in >> T;

	while (T--)
	{
		in >> N;

		vector<int> power(N, 0);

		for (int i = 0; i < N; ++i)
			in >> power[i];

		int sex = 0;
		vector<int> female, male;

		for (int i = 0; i < N; ++i)
		{
			in >> sex;
			if (sex == 0)
				male.push_back(power[i]);
			else
				female.push_back(power[i]);
		}

		std::sort(male.begin(), male.end());
		std::sort(female.begin(), female.end());

		int i = female.size() - 1;
		int j = male.size() - 1;
		long long totalPower = 0;

		while(j >= 0 && i >= 0)
		{
			totalPower += female[i--] * male[j--];
		}

		out << totalPower << "\n";
	}

	return 0;
}
