// https://algospot.com/judge/problem/read/SENTENCE

/*
3 4
I will not buy this record, it is scratched.
My hovercraft is full of eels.
Do you want to come back to my place? Bouncy, bouncy.
I will not buy this rec
My helicopter is
Do you want to come back
I will not buy this cat.

2
*/

#include <string>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

istream& in = cin;
ostream& out = cout;


bool isMatch(const vector<string>& book, const string& memo)
{
	for(vector<string>::const_iterator it = book.begin();
		it != book.end();
		++it)
	{
		bool same = true;
		const char* b = it->data();
		const char* m = memo.data();

		while( *b && *m && (same = (*b++ == *m++)) );

		if( *m == 0 && same ) return true;
	}

	return false;
}


int main(int argc, char* argv[])
{
	std::ios::sync_with_stdio(false);

	int M, N;

	in >> M >> N;

	string temp;
	std::getline(in, temp);

	vector<string> book(M);

	for(int i = 0; i < M; ++i)
		std::getline(in, book[i]);

	string memo;
	int count = 0;

	for(int i = 0; i < N; ++i)
	{
		std::getline(in, memo);

		if( isMatch(book, memo) )
			count += 1;
	}

	out << count << "\n";

	return 0;
}
