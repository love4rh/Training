#ifndef _RSTRING_H_
#define _RSTRING_H_

#include <string>

using namespace std;


class rstring
{
public:
	rstring(const string& original) : _str(original) {}

private:
	const string& _str;

public:
	int length() const { return (int)_str.length(); }

	string::const_reference operator[](int pos) const
	{
		return _str.at(length() - pos - 1);
	}
};


#endif
