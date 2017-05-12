/*
https://algospot.com/judge/problem/read/GALLERY
4
6 5
0 1
1 2
1 3
2 5
0 4
4 2
0 1
2 3
1000 1
0 1
6 5
5 4
4 3
4 2
3 0
5 1

3
2
999
3
// */

#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

istream& in = cin;
ostream& out = cout;

const int MAX_GALLERY = 1001;

int G[MAX_GALLERY][MAX_GALLERY];

int visited[MAX_GALLERY];

int N, cctvCnt;


/*
 * 지배 집합 찾기
 * 1. 잎노드는 선택하지 않는다.
 * 2. 잎노드가 아닌 경우, 자기 자손 중 지배당하지 않는 노드가 있는 경우만 선택
 */
enum state { UNWATCHED = 0, WATCHED = 1, WITHCCTV = 2 };

state checkState(int n)
{
    visited[n] = 1;

    int stateCnt[] = { 0, 0, 0 };

    // 모든 자식 노드의 상태 검사
    for(int i = 1; i <= G[n][0]; ++i)
    {
        int child = G[n][i];

        if( !visited[child] )
            stateCnt[checkState(child)] += 1;
    }

    // 감시되지(지배되지) 않은 자식이 있다면 카메라 설치
    if( stateCnt[UNWATCHED] > 0 )
    {
        cctvCnt += 1;
        return WITHCCTV;
    }

    // 카메라가 설치된 자식이 있다면
    if( stateCnt[WITHCCTV] > 0 )
        return WATCHED;

    return UNWATCHED;
}


int main(int argc, char* argv[])
{
    std::ios::sync_with_stdio(false);

    int T = 0;

    in >> T;
    while( T-- )
    {
        int H, v1, v2;

        in >> N >> H;

        memset(G, 0, sizeof(G)); // 그래프 초기화

        while( H-- )
        {
            in >> v1 >> v2;

            v1 += 1; v2 += 1; // 1-based

            // G[*][0]에 연결된 갤러리의 개수 (자식 노드의 수)
            G[v1][++G[v1][0]] = v2;
            G[v2][++G[v2][0]] = v1;
        }

        cctvCnt = 0;
        memset(visited, 0, sizeof(visited));

        for(int i = 1; i <= N; ++i)
        {
            if( !visited[i] && UNWATCHED == checkState(i) )
                cctvCnt += 1;
        }

        out << cctvCnt << "\n";
    }

    return 0;
}
