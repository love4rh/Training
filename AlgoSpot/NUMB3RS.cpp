/*
https://algospot.com/judge/problem/read/NUMB3RS
2
5 2 0
0 1 1 1 0
1 0 0 0 1
1 0 0 0 0
1 0 0 0 0
0 1 0 0 0
3
0 2 4
8 2 3
0 1 1 1 0 0 0 0
1 0 0 1 0 0 0 0
1 0 0 1 0 0 0 0
1 1 1 0 1 1 0 0
0 0 0 1 0 0 1 1
0 0 0 1 0 0 0 1
0 0 0 0 1 0 0 0
0 0 0 0 1 1 0 0
4
3 1 2 6

0.83333333 0.00000000 0.16666667
0.43333333 0.06666667 0.06666667 0.06666667
// */

#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>


using namespace std;

istream& in = cin;
ostream& out = cout;

const int MAX_VILLAGE = 51;
const int MAX_DAY = 101;

int N, P, D;
int A[MAX_VILLAGE][MAX_VILLAGE];
double prob[MAX_DAY][MAX_VILLAGE];


/*
 * D일에 마을 V에 있을 확률을 P(D, V)라고 하고, 마을 V에 연결된 마을의 개수를 C(V)하고 하면,
 * P(D, V) = SUM( P(D-1, V') / C(V') ), where V' is the set of villages connected to V.
 * 그리고 0일째는 교도소가 있는 마을만 확률이 1.0임.
 */
void calculateProbability()
{
	memset(prob, 0, sizeof(prob));

	prob[0][P] = 1.0; // He is in the prison at 0-th day.

    // 다음 날 그가 V 마을에 있을 확률은,
    // V에 연결된 마을 중 이전 날 있었던 확률
	for(int d = 1; d <= D; ++d)
	{
		for(int i = 0, j = 0; i < N && j < N; ++j >= N ? ++i, j = 0 : j)
		{
			if( A[i][j] )
				prob[d][i] += prob[d - 1][j] / double(A[j][N]);
		}
	}
}

int main(int argc, char* argv[])
{
    std::ios::sync_with_stdio(false);

    int T = 0, t = 0, q = 0;

    in >> T;
    while( T-- )
    {
        in >> N >> D >> P;

        for(int i = 0, j = 0; i < N && j < N; ++j >= N ? ++i, j = 0 : j)
        {
            // 끝에 연결되 마을 수 저장
        	if( j == 0 )
        		A[i][N] = 0;

            in >> A[i][j];

            if( A[i][j] )
            	A[i][N] += 1;
        }

        // calculate
        calculateProbability();

        in >> t;
        for(int i = 0; i < t; ++i)
        {
        	in >> q;
        	if( i > 0 )
        		printf(" ");

        	printf("%.8f", prob[D][q]);
        }
        printf("\n");
    }

    return 0;
}
