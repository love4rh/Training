/*
https://algospot.com/judge/problem/read/PARTNER
5
10 0.1
C
10 1
CCCCU
10 50
CCCCU
10 3.124
CCCUUUCCCUUCCCUCCCUCCCUCCUUUCCUUCC
10 3.124
CCCUUUCCCUUCCCCCCCUCCCUCCUUUCCUUCC

100000.0
3940.4
93750.0
75317.4
77320.7
// */

#include <cstdio>
#include <iostream>
#include <string>

using namespace std;


double solve(const string& P, double M, double D)
{
	int N = P.size();
	double pM, cM, cost = 0;
	double decay = 1.0 - D / 100.0;

	pM = cM = M;

	for(int i = 0; i < N - 1; ++i)
	{
		cM *= decay;

		if( P[i] == 'C' )
			cost += (pM - cM);

		pM = cM;
	}

	if( P[N - 1] == 'C' )
		cost += pM;

	return cost * 10000.0;
}


int main(int argc, char* argv[])
{
    std::ios::sync_with_stdio(false);

    int T = 0;

    cin >> T;
    while( T-- )
    {
    	string P;
    	double M, D;

		cin >> M >> D >> P;

		printf("%.1f\n", solve(P, M, D));
    }

    return 0;
}
