/*
https://algospot.com/judge/problem/read/PREFIX
2
6 4
dark
date
dave
doc
doc
dock
7 3
ab
ab
ac
acc
bc
c
cba

d
da
doc
dark
a
ab
acc
// */

#include <cstring>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

#define MAX 201


istream& in = cin;
ostream& out = cout;

int N, M;
string words[3001];

int maxCount[MAX];
string maxPrefix[MAX];


/**
 * 최다 출연 m-Prefix를 계산하여 maxPrefix에 저장함.
 * probableList: m-prefix를 계산하기 위한 대상 단어 목록. words의 인덱스를 가짐.
 *
 * probableList에는 m까지 같은 문자열을 가지는 단어의 인덱스가 들어 오게됨(m가 0인 경우에도^^).
 * 따라서, 동일한 m-prefix의 출연 회수는 probableList의 크기가 되며,
 * 이 크기가 이전 것보다 크다면 더 좋은 경우가 나타난 것이므로 갱신한다.
 *
 * 같은 크기의 경우 알파벳 순으로 첫 번째 것을 뽑으려면 words가 정렬되어 있어야 함.
 */
void solve(int m, vector<int>& probableList)
{
    if( probableList.empty() || m >= M + 1 )
        return;

    int pn = (int) probableList.size();

    if( maxCount[m] < pn )
    {
        maxCount[m] = pn;
        maxPrefix[m] = words[probableList[0]].substr(0, m);
    }

    char prevCh = 0;
    vector<int> newList; // 다음 단계를 따져봐야 할 단어의 인덱스

    for(int i = 0; i < pn; ++i)
    {
        const string& s = words[probableList[i]];

        if( m >= (int) s.size() )
            continue;

        // prevCh == s[m]는 (m+1)-prefix까지 같다는 것을 의미함.
        // 다른 문자가 나온 경우, 이전까지는 같은 접두어이지만 더 이상은 아니므로,
        if( prevCh != s[m] )
        {
            // 현재까지 같은 (m+1)-prefix를 갖는 단어들이 newList에 들어 있음.
            solve(m + 1, newList);

            prevCh = s[m];
            newList.clear(); // 새로 따져봐야 함으로 정리
        }

        newList.push_back( probableList[i] );
    }

    // (m+1)-prefix를 계산 혹은 저장을 위하여 한번 더 호출해야 함.
    solve(m + 1, newList);
}


int main(int argc, char* argv[])
{
    std::ios::sync_with_stdio(false);

    int T;

    in >> T;
    while(T--)
    {
        in >> N >> M;

        // 같은 접미어를 가질 가능성이 있는 단어의 인덱스
        vector<int> probableList(N, 0);

        for(int n = 0; n < N; ++n)
        {
            in >> words[n];
            probableList[n] = n;
        }

        memset(maxCount, 0, sizeof(maxCount));
        solve(0, probableList);

        for(int i = 1; i <= M; ++i)
            out << maxPrefix[i] << "\n";
    }

    return 0;
}
