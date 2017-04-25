/*
https://algospot.com/judge/problem/read/DOMINO
// */

#include <iostream>

using namespace std;

istream& in = cin;
ostream& out = cout;


int main(int argc, char* argv[])
{
    int N = 0;

    in >> N;

    int spot = 0;
    for(int i = 0; i <= N; ++i)
    {
        for(int j = i; j <= N; ++j)
            spot += (i + j);
    }

    out << spot << "\n";

    return 0;
}
