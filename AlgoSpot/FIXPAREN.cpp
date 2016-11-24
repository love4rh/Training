// https://algospot.com/judge/problem/read/FIXPAREN

/*
2
(} {(<[
()([)> <({[

{}
()<()>
*/

#include <stack>
#include <string>
#include <iomanip>
#include <iostream>

using namespace std;

istream& in = cin;
ostream& out = cout;


bool isLeft(const char ch)
{
	return ch == '(' || ch == '{' || ch == '[' || ch == '<';
}

char rightPair(const char ch)
{
	if( ch == '(' )
		return ')';
	else if( ch == '{' )
		return '}';
	else if( ch == '[' )
		return ']';
	else
		return '>';
}

char leftPair(const char ch)
{
	if( ch == ')' )
		return '(';
	else if( ch == '}' )
		return '{';
	else if( ch == ']' )
		return '[';
	else
		return '<';
}

int order(const string& prior, char ch, bool right = true)
{
	if( right ) ch = leftPair(ch);

	for(int i = 0; i < (int) prior.size(); ++i)
	{
		if( ch == prior.at(i) )
			return i;
	}
	return 4;
}

int main(int argc, char* argv[])
{
	std::ios::sync_with_stdio(false);

	int T = 0;

	in >> T;

	while (T--)
	{
		stack<int> st;
		string mis, prior;

		in >> mis >> prior;

		for(int i = 0; i < (int) mis.size(); ++i)
		{
			char ch = mis.at(i);

			if( isLeft(ch) )
				st.push(i);
			else
			{
				int p = st.top();
				char l = mis.at(p);
				char r = rightPair(l);

				if( r != ch )
				{
					if( order(prior, l, false) < order(prior, ch, true) )
						mis.at(i) = r;
					else
						mis.at(p) = leftPair(ch);
				}
				st.pop();
			}
		}

		out << mis << "\n";
	}

	return 0;
}
