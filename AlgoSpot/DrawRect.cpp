// https://algospot.com/judge/problem/read/DRAWRECT

/*
2
5 5
5 7
7 5
30 20
10 10
10 20
*/

#include "./function.h"

#ifdef __DRAWRECT__

#include <iostream>
#include <map>

using namespace std;

istream& in = cin;


// map에 있는 개수 중 홀수인 것을 찾아 반환함.
int getOddCountNum(const map<int, int>& cntMap)
{
	for (map<int, int>::const_iterator it = cntMap.begin(); it != cntMap.end(); ++it)
	{
		if ((it->second % 2) == 1)
			return it->first;
	}

	return 0;	// 이런 경우는 없을 것임.
}

int main(int argc, char* argv[])
{
	int caseCount = 0;

	in >> caseCount;

	while (caseCount--)
	{
		int x, y, n = 3;
		map<int, int> xNumCount, yNumCount;

		while (n--)
		{
			in >> x >> y;
			xNumCount[x] += 1;
			yNumCount[y] += 1;
		}

		cout << getOddCountNum(xNumCount) << " " << getOddCountNum(yNumCount) << "\n";
	}

	return 0;
}

#endif
