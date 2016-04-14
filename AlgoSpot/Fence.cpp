// https://algospot.com/judge/problem/read/FENCE

/*
3
7
7 1 5 9 6 7 3
7
1 4 4 4 4 1 1
4
1 8 2 2
*/

#include "./function.h"

#ifdef _FENCE_

#include <fstream>

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <map>

#define MAX_LIMIT 20000

using namespace std;

istream& in = cin;
// ifstream in("E:\\Work\\Algorithm\\data\\fence.txt");

int fenceHeight[MAX_LIMIT];


int main(int argc, char* argv[])
{
	int caseCount = 0, num = 0;

	in >> caseCount;

	while (caseCount--)
	{	
		in >> num;

		int pos = 0;
		int maxArea = 0;

		map<int, int> area;

		while (num--)
		{
			in >> fenceHeight[pos];

			map<int, int>::iterator it = area.find(fenceHeight[pos]);

			if (area.end() == it)
			{
				area[fenceHeight[pos]] = 0;	// �Ʒ� ��ƾ���� 1�� �������Ƿ� ���⼭�� 1�̾�� ��.

				it = area.find(fenceHeight[pos]);

				// pos ������ ���� ���̺��� ũ�ų� ���� ���� �󸶳� �ִ� �� Ž��
				int i = pos;
				while (--i >= 0 && fenceHeight[i] >= fenceHeight[pos])
					it->second += it->first;
			}
			
			// ������ �ִ� �ֵ� �߿��� ���̰� ���� �� ���� �۰ų� ���� �ֵ��� �ϳ��� ���� ��� ��.
			for (it = area.begin(); it != area.end();)
			{
				if (it->first <= fenceHeight[pos])
				{
					it->second += it->first;
					maxArea = max(maxArea, it->second);

					++it;
				}
				else
				{
					maxArea = max(maxArea, it->second);

					map<int, int>::iterator dit = it++;
					area.erase(dit);
				}
			}

			pos += 1;
		}

		for (map<int, int>::iterator it = area.begin(); it != area.end(); ++it)
			maxArea = max(maxArea, it->second);

		cout << maxArea << "\n";
	}

	return 0;
}

#endif
