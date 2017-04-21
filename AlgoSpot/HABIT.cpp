/* https://algospot.com/judge/problem/read/HABIT
4
2
uhmhellouhmmynameislibe
3
banana
1
thatsagoodquestion
3
hello

3
1
18
0
*/

#include <iomanip>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <cstring>

using namespace std;

istream& in = cin;
ostream& out = cout;


struct SuffixComp
{
    SuffixComp(const string& s) : _s(s) {}

    const string& _s;

    bool operator()(int a, int b)
    {
    	return strcmp(_s.data() + a, _s.data() + b) < 0;
    }
};


// Suffix Array: s의 모든 접미어를 알파벳 순으로 정렬하여 순서대로 넣은 배열
// 원소의 순서는 위와 같고 값은 각 접미어의 시작 위치를 가짐 --> 모든 접미어 표현 가능
// Suffix Array를 구하기 위한 더 좋은 알고리즘도 있음.
vector<int> getSuffixArray(const string& s)
{
    vector<int> ar(s.size());

    for(int i = 0; i < (int) s.size(); ++i)
        ar[i] = i;

    std::sort(ar.begin(), ar.end(), SuffixComp(s));

    return ar;
}


int solve(const string& s, int K)
{
    // Suffix Array
    vector<int> ar = getSuffixArray(s);

    int len = 0; // K회 이상 나오는 부분 문자열 중 가장 긴 문자열의 길이

    /*
    부분 문자열은 접미어의 모든 접두어로 표현할 수 있음.
    Suffix Array는 알파벳 순으로 정렬되어 있으므로 접두어가 반복되는 문자열이 나온다면 순서대로 몰려 있음.
    예를 들어, banana의 경우 Suffix Array는 다음과 같고
      1. a       5
      2. ana     3
      3. anana   1
      4. banana  0
      5. na      4
      6. nana    2
    ana의 경우 2번 나타나며 정렬되어 있기 때문에 2~3에 연속적으로 나타나며, a는 1~3에 연속적으로 나타남.
    즉, 문자열 x가 K회 이상 나타나는지 보려면, x가 있는 위치에 K-1(-1은 양쪽이 포함이기 때문에)를 더한 위치의 문자열을 비교하여
    같은 문자열까지가 K회 나타난 경우임.
    // */

    for(int i = 0; i <= (int) ar.size() - K; ++i)
    {
    	int a = ar[i], b = ar[i + K - 1], count = 0;

    	while( a < (int) s.size() && b < (int) s.size() && s[a] == s[b] )
    	{
    		a += 1;
    		b += 1;
    		count += 1;
    	}

    	len = max(len, count);
    }

    return len;
}


int main(int argc, char* argv[])
{
    std::ios::sync_with_stdio(false);

    int T;
    in >> T;

    while(T--)
    {
        int K;
        string s;

        in >> K >> s;

        // K가 1이면 전체 문자열의 길이가 답임(가장 긴 1회 이상 나오는 단어는 문장 자체이므로)
        if( K == 1 )
        	out << s.size() << "\n";
        else
        	out << solve(s, K) << "\n";
    }

    return 0;
}
