/*
https://www.algospot.com/judge/problem/read/URI
2
Happy%20Joy%20Joy%21
http://algospot.com/%2a
*/
#include <iostream>
#include <string>

using namespace std;

istream& in = cin;
ostream& out = cout;

string decode(const string& uri)
{
	int pos = 0;
	string decoded = "";
	decoded.reserve(uri.size() + 1);

	while (pos < uri.size())
	{
		if ('%' == uri.at(pos))
		{
			int ascii = strtol(uri.substr(pos + 1, 2).data(), 0, 16);

			decoded += (char) ascii;
			pos += 2;
		}
		else
			decoded += uri.at(pos);

		pos += 1;
	}

	return decoded;
}

int main()
{
	int T = 0;

	in >> T;

	while (T--)
	{
		string uri;
		in >> uri;

		out << decode(uri) << endl;
	}

	return 0;
}
