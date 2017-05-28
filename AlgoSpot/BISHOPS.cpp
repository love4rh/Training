/* https://algospot.com/judge/problem/read/BISHOPS
3
5
.....
.....
.....
.....
.....
8
..**.*.*
**.***.*
*.**...*
.*.**.**
*.**.*.*
..**.*.*
...*.*.*
**.*.*.*
8
*.*.*.*.
.*.*.*.*
*.*.*.*.
.*.*.*.*
*.*.*.*.
.*.*.*.*
*.*.*.*.
.*.*.*.*

8
18
7
*/

/*
이분 그래프의 최대 부합(Matching)을 계산하는 문제임.
이분 그래프의 최대 부합(Matching) 계산하는 방법 아래 참고.
http://blog.sisobus.com/2013/10/bipartite-matching.html#.WROxLZNLs_t
*/

#include <iomanip>
#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <set>

using namespace std;

istream& in = cin;
ostream& out = cout;

int N;
int board[10][10][2];

// 좌하 대각선 그룹의 노드가 연결된 우하 그룹의 번호
vector<set<int> > LG;

// 우하 대각선 그룹의 노드가 연결된 좌하 그룹의 번호
vector<set<int> > RG;

// 최대 부합 계산시 사용할 변수들
int rightPartner[64]; // 우하 그룹의 좌하 그룹 중 짝 번호
int leftVisited[64]; // 좌하 그룹 방문 여부


void addNode(int idx, int x, int y, bool left)
{
    int d = -1, a = 0, b = 1;
    vector<set<int> >* G1 = &LG;
    vector<set<int> >* G2 = &RG;

    if( !left )
    {
        d = 1;
        a = 1; b = 0;
        G1 = &RG;
        G2 = &LG;
    }

    G1->push_back(set<int>());

    while( x >= 0 && y < N && board[y][x][a] == -1 )
    {
        board[y][x][a] = idx;

        if( board[y][x][b] != -1 )
        {
            (*G1)[idx].insert(board[y][x][b]);
            (*G2)[board[y][x][b]].insert(idx);
        }

        y += 1;
        x += d;
    }
}

// 비숍은 대각선 방향으로 움직일 수 있으므로,
// 특정 위치에 놓았을 때 대각선 방향을 그룹지을 수 있는 셀들의 집합을 노드라고 하고
// 최대 2개(좌하, 우하)의 노드가 나올 수 있으며, 이 두 노드를 연결짓는 형태로 그래프 생성.
void makeGraph()
{
    LG.clear();
    RG.clear();

    int idxLeft = -1, idxRight = -1;

    for(int i = 0; i < N; ++i)
    {
        for(int j = 0; j < N; ++j)
        {
            // left-bottom
            if( board[i][j][0] == -1 )
                addNode(++idxLeft, j, i, true);

            // right-bottom
            if( board[i][j][1] == -1 )
                addNode(++idxRight, j, i, false);
        }
    }
}

bool dfs(int idx)
{
    if( leftVisited[idx] )
        return false;

    leftVisited[idx] = true;

    for(set<int>::iterator it = LG[idx].begin(); it != LG[idx].end(); ++it)
    {
        int rightPair = *it;

        if( rightPartner[rightPair] == -1 || dfs(rightPartner[rightPair]) )
        {
            rightPartner[rightPair] = idx;
            return true;
        }
    }

    return false;
}

int bipartiteMatching()
{
    memset(rightPartner, -1, sizeof(rightPartner));

    int matched = 0;

    for(int i = 0; i < (int) LG.size(); ++i)
    {
        memset(leftVisited, 0, sizeof(leftVisited));

        if( dfs(i) )
            matched += 1;
    }

    return matched;
}

int main(int argc, char* argv[])
{
    std::ios::sync_with_stdio(false);

    int T;
    string row;

    in >> T;

    while( T-- )
    {
        in >> N;

        for(int i = 0; i < N; ++i)
        {
            in >> row;

            for(int j = 0; j < N; ++j)
                  board[i][j][0] = board[i][j][1] = row[j] == '.' ? -1 : -2;
        }

        makeGraph();

        out << bipartiteMatching() << "\n";
    }

    return 0;
}
