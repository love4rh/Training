// https://algospot.com/judge/problem/read/ITES

#include <fstream>

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <queue>

using namespace std;

//istream& in = cin;
ifstream in("E:\\Work\\Algorithm\\data\\ites.txt");


int main(int argc, char* argv[])
{
	int T = 0, K = 0, N = 0;
	const long long M = (long long)1 << 32;

	in >> T;

	while (T--)
	{
		in >> K >> N;

		queue<int> q;
		int a, n = 0, count = 0;
		long long A = 1983, sum = 0;

		while (n < N || !q.empty())
		{
			if (n < N)
			{
				a = (int)(A % 10000) + 1;
				q.push(a);
				sum += a;
			}
			// 더 이상 더할 것도 없는 합이 작다면 끝내도 됨.
			else if (sum < K)
				break;

			// Queue에서 빼기
			while (sum >= K && !q.empty())
			{
				if (sum == K)
					count += 1;

				sum -= q.front();
				q.pop();
			}
			n += 1;

			A = (A * 214013L + 2531011L) % M;
		}

		cout << count << "\n";
	}

	return 0;
}
