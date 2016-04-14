// https://algospot.com/judge/problem/read/ENCRYPT

/*
2
A
HelloWorld
*/

#include "./function.h"

#ifdef __ENCRYPT__

#include <iostream>

using namespace std;

istream& in = cin;


int main(int argc, char* argv[])
{
	int caseCount = 0;

	in >> caseCount;

	while (caseCount--)
	{
		string str;

		in >> str;

		for (int i = 0; i < str.length(); i += 2)
			cout << str.at(i);

		for (int i = 1; i < str.length(); i += 2)
			cout << str.at(i);

		cout << "\n";
	}

	return 0;
}

#endif
