// https://algospot.com/judge/problem/read/HELLOWORLD

#include "./function.h"

#ifdef _HELLOWORLD_

#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

istream& in = cin;


int main(int argc, char* argv[])
{
	int caseCount = 0, depth = 0;

	in >> caseCount;

	while (caseCount--)
	{
		string name;

		in >> name;

		cout << "Hello, " << name << "!\n";
	}

	return 0;
}

#endif
