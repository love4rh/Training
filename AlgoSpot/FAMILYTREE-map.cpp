﻿// https://algospot.com/judge/problem/read/FAMILYTREE

/*
1
13 7
0 1 1 3 3 0 6 0 8 9 9 8
2 7
10 11
4 11
7 7
10 0
6 7
0 10

4
2
6
0
3
1
3
*/

#include <iomanip>
#include <iostream>
#include <map>

using namespace std;

istream& in = cin;
ostream& out = cout;

int A[100000];


int lca(const map<int, int>& otherFarthers, int p, int level)
{
    map<int, int>::const_iterator it = otherFarthers.find(p);

    if( it != otherFarthers.end() )
        return it->second + level;

    return lca(otherFarthers, A[p], level + 1);
}

int main(int argc, char* argv[])
{
    std::ios::sync_with_stdio(false);

    int T;

    in >> T;

    while(T--)
    {
        // N: No. of people, Q: No. of Questions
        int N, Q;

        in >> N >> Q;

        for(int i = 1; i < N; ++i)
            in >> A[i];

        int p1, p2;
        A[0] = 0;

        while(Q--)
        {
            in >> p1 >> p2;

            // find LCA between p1 and p2
            if( p1 == p2 )
                out << 0 << "\n";
            else
            {
            	int level = 0;
                map<int, int> farthers;

                farthers[p1] = level;
                while( p1 != 0 )
				{
					p1 = A[p1];
					farthers[p1] = ++level;
				}

                out << lca(farthers, p2, 0) << "\n";
            }
        }
    }

    return 0;
}

