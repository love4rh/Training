/*
https://algospot.com/judge/problem/read/REPEATLESS
25
10000
0

27
26057
*/

#include <iostream>
#include <vector>

using namespace std;

#define MAX_LIMIT 1000001

istream& in = cin;
ostream& out = cout;


// 같은 숫자가 위치에 상관없이 두번 이상 나오면 반복숫자임.
// 연속으로 반복된 경우가 있을 때만 반복 숫자인줄 알고 헤맸음...
bool isRepeated(int n)
{
    bool digits[10] = {false, };

    while( n )
    {
        int d = n % 10;

        if( digits[d] )
            return true;

        digits[d] = true;
        n /= 10;
    }

    return false;
}


int main(int argc, char* argv[])
{
    // 반복되지 않는 숫자의 개수 저장. 예) cached[25] = 27
    vector<int> cached(MAX_LIMIT, 0);

    int d = 1, i = 1;

    // 1. 순차적으로 반복숫자 여부를 체크
    // 2. 반복되는 숫자라면 다음으로 넘어감
    // 3. 반복되지 않는 숫자가 나오면 현재 위치에 반복 체크한 숫자를 넣음
    while( i < MAX_LIMIT )
    {
        if( !isRepeated(d) )
            cached[i++] = d;

        d += 1;
    }

    while( 1 )
    {
        int n = 0;

        in >> n;
        if( n == 0 )
            break;

        out << cached[n] << "\n";
    }

    return 0;
}
