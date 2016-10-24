/*
https://algospot.com/judge/problem/read/ORDERING
6
4 0
4 2
AB
CB
4 1
DC
4 4
DA
BD
CA
CD
6 3
AC
AD
BE
5 4
DA
ED
CA
CD

ABCD
ACBD
ABDC
BCDA
ABCDEF
BCEDA
*/

#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <queue>


using namespace std;

istream& in = cin;
ostream& out = cout;

int dependCount[26];
vector<set<int> > dependency;


int main()
{
	std::ios::sync_with_stdio(false);

	string ds;
	int T, N, M;

	in >> T;

	while (T--)
	{
		in >> N >> M;

		memset(dependCount, 0, sizeof(dependCount));
		dependency = vector<set<int> >(N, set<int>());

		while (M--)
		{
			in >> ds;

			// 나에게 종속된 작업 목록을 넣음.
			dependency[ds[0] - 'A'].insert(ds[1] - 'A');
			dependCount[ds[1] - 'A'] += 1;
		}

		// dependCount내 값이 0인 작업을 넣음.
		// 이 값이 0이라는 것은 종속된 것이 없으므로 알파벳 순으로 찍기만 하면 된다는 것임.
		// 알파벳 순으로 찍기 위하여 우선순위 큐를 이용하였음.
		priority_queue<int, vector<int>, greater<int> > indepenWork;

		for(int i = 0; i < N; ++i)
		{
			if( dependCount[i] == 0 )
				indepenWork.push(i);
		}

		while( !indepenWork.empty() )
		{
			int p = indepenWork.top();
			indepenWork.pop();

			out << char(p + 'A');

			// 작업 p가 수행되었으므로 p에 종속되어 있던 작업의 종속회수를 하나씩 빼야 함
			set<int>& d = dependency.at(p);
			for(set<int>::iterator it = d.begin(); it != d.end(); ++it)
			{
				// 더이상 종속된 값이 없을 경우에 작업을 수행해도 되는 경우이므로 큐에 추가함.
				if( --dependCount[*it] == 0 )
					indepenWork.push(*it);
			}
		}
		out << "\n";
	}

	return 0;
}
