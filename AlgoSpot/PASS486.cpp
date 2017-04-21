/* https://algospot.com/judge/problem/read/PASS486
3
2 2 10
12 486 486
200 1000000 2000000

4
1
19
*/

#include <iomanip>
#include <iostream>
#include <cstring>

using namespace std;

istream& in = cin;
ostream& out = cout;


#define MAX		10000001


// index에 해당하는 숫자의 약수의 개수 저장
int divCount[MAX];


void preCalc()
{
	memset(divCount, 0, sizeof(divCount));

	for(int i = 2; i < MAX; ++i)
	{
		for(int j = i; j < MAX; j += i)
			divCount[j] += 1;
	}
}


int main(int argc, char* argv[])
{
    std::ios::sync_with_stdio(false);

    preCalc();

    int T, N, L, H;

    in >> T;

    while(T--)
    {
        in >> N >> L >> H;

        int count = 0;

        N -= 1;	// 1은 모두 수의 약수 이며, divCount에 1은 카운팅되어 있지 않음.
        for(int i = L; i <= H; ++i)
        {
        	if( divCount[i] == N )
        		count += 1;
        }

        out << count << "\n";
    }

    return 0;
}
