/*
https://algospot.com/judge/problem/read/BRACKETS2
4
()()
({[}])
({}[(){}])
)

YES
NO
YES
NO
*/

#include <iostream>
#include <string>
#include <stack>


using namespace std;

istream& in = cin;
ostream& out = cout;


int main()
{
	std::ios::sync_with_stdio(false);

	int T;

	in >> T;
	while (T--)
	{
		string brackets;

		in >> brackets;

		stack<char> s;

		bool isOk = true;
		const char* ch = brackets.data();

		while (*ch && isOk)
		{
			if (*ch == '(' || *ch == '{' || *ch == '[')
			{
				s.push(*ch);
			}
			else
			{
				if (s.empty())
					isOk = false;
				else
				{
					char right = (*ch == ')' ? '(' : (*ch == '}' ? '{' : '['));

					if (s.top() != right)
						break;
					else
						s.pop();
				}
			}

			++ch;
		}

		out << (s.empty() && isOk ? "YES" : "NO") << "\n";
	}

	return 0;
}
