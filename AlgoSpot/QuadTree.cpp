// https://algospot.com/judge/problem/read/QUADTREE

#include <iomanip>
#include <iostream>
#include <string>


using namespace std;


string reverse(string::iterator& it)
{
	char ch = *it;

	// 'x'가 아니라면 단일 색으로 이루어진 Block임. 따라서 그대로 리턴함.
	if (ch != 'x')
		return string(1, ch);

	// 'x'가 아니라면 위치를 하나 이동시키고 뒤집기
	string r[4];
	for (int i = 0; i < 4; ++i)
		r[i] = reverse(++it);

	return string(1, 'x') + r[2] + r[3] + r[0] + r[1];
}

int main(int argc, char* argv[])
{
	int caseCount = 0;

	cin >> caseCount;

	while( caseCount-- )
	{
		string quadTree;

		cin >> quadTree;

		string::iterator it = quadTree.begin();
		cout << reverse(it) << "\n";
	}

	return 0;
}
