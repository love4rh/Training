/*
https://algospot.com/judge/problem/read/RESTORE
3
3
abrac
cadabra
dabr
3
geo
oji
jing
2
world
hello

cadabrac
geojing
helloworld
// */

#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#include <string>


using namespace std;

istream& in = cin;
ostream& out = cout;

const int MAX_K = 16;
const int BIG_INT = 9999999;

int K = 0;
string word[MAX_K];

// overlap[i][j]: i 문자열 뒤에 j 문자열을 붙일 때 추가로 붙어야 하는 문자열의 길이
int overlap[MAX_K][MAX_K];

int cached[MAX_K][(1 << MAX_K)];


// front의 뒤쪽과 rear의 앞쪽을 겹쳐 놓을 때 추가되는 길이 계산
// 문자열 abcde, cdef가 입력되면 cde가 겹치므로 abcde에 f만 더하면 되므로 1을 반환.
// returns BIG_INT, if front includes rear.
int calcOverlapLength(const string& front, const string& rear)
{
    int overLen = 0;
    int flen = (int) front.size();
    int rlen = (int) rear.size();

    if( rlen <= flen && front.find(rear) != string::npos )
        return BIG_INT;

    for(int l = min(flen, rlen); l > 0; --l)
    {
        const char* f = front.data() + (flen - l);
        const char* r = rear.data();

        while( *f && *r && *f == *r )
        {
            overLen += 1;
            ++f; ++r;
        }

        if( overLen == l )
            break;
        else
            overLen = 0;
    }

    return rlen - overLen;
}

// 단어들 돌아다녀 보기
int traverse(int here, int traversed)
{
    // 모든 단어를 모두 살핀 경우임.
    if( traversed == (1 << K) - 1 )
        return 0;

    int& d = cached[here][traversed];

    if( d != -1 )
        return d;

    d = BIG_INT;

    // 다른 단어들 살펴보기
    for(int there = 0; there < K; ++there)
    {
        // 이미 연결해 본 단어는 패스
        if( traversed & (1 << there) )
            continue;

        d = min(d, overlap[here][there] + traverse(there, traversed | (1 << there)));
    }

    return d;
}

// 문자열 합치기.
// 최소 경로를 갖는 단어 순서대로 출력하기 위하여 traverse()와 비슷한 방식으로
// 단어를 찾아가며 같은 최소값을 갖는 경우가 최소 경로가 됨.
// 같은 값을 가지면 현재 단어 중 겹치지 않는 부분만 취하여 더해 나감.
string reconstruct(int here, int traversed)
{
    // 모든 단어를 모두 살핀 경우임.
    if( traversed == (1 << K) - 1 )
        return "";

    // 다른 단어들 살펴보기
    for(int there = 0; there < K; ++there)
    {
        // 이미 연결해 본 단어는 패스
        if( traversed & (1 << there) )
            continue;

        int d = overlap[here][there] + traverse(there, traversed | (1 << there));

        if( cached[here][traversed] == d )
        {
            return word[there].substr(word[there].size() - overlap[here][there])
                    + reconstruct(there, traversed | (1 << there));
        }
    }

    return "";
}

int main(int argc, char* argv[])
{
    std::ios::sync_with_stdio(false);

    int T = 0;

    in >> T;
    while( T-- )
    {
        in >> K;

        for(int i = 0; i < K; ++i)
            in >> word[i];

        // 고려할 필요가 없는 문자열 표시
        int unused = 0;

        memset(cached, -1, sizeof(cached));

        for(int i = 0; i < K; ++i)
        {
            if( (1 << i) & unused )
                continue;

            for(int j = 0; j < K; ++j)
            {
                if( (1 << j) & unused )
                    continue;

                if( i != j )
                {
                    int o = calcOverlapLength(word[i], word[j]);

                    if( o == BIG_INT )
                        unused |= (1 << j);
                    else
                        overlap[i][j] = o;
                }
                else
                    overlap[i][j] = 0;
            }
        }

        int ans = BIG_INT;
        int minStart = -1;
        for(int i = 0; i < K; ++i)
        {
            if( (1 << i) & unused )
                continue;

            int newAns = traverse(i, unused | (1 << i)) + (int) word[i].size();

            if( ans > newAns )
            {
                ans = newAns;
                minStart = i;
            }
        }

        out << word[minStart] << reconstruct(minStart, unused | (1 << minStart)) << "\n";
    }

    return 0;
}
