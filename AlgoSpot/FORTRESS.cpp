/*
https://algospot.com/judge/problem/read/FORTRESS
4
3
5 5 15
5 5 10
5 5 5
8
21 15 20
15 15 10
13 12 5
12 12 3
19 19 2
30 24 5
32 10 7
32 9 4
1
5 5 15
11
21 15 100
60 60 5
21 15 20
15 15 10
13 12 5
12 12 3
19 19 2
30 24 5
30 24 2
32 10 7
32 9 4

2
5
0
5
*/

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

istream& in = cin;
ostream& out = cout;


// 성벽의 포함관계를 트리로 표현하기 위한 클래스
class Node
{
public:
	Node() : _parent(0), _level(1) {}
	Node(const Node& cp) : _parent(cp._parent), _children(cp._children), _level(cp._level) {}

	friend class Wall;

public:
	Node*			_parent;
	vector<Node*>	_children;
	int				_level;

public:
	void addChild(Node* child)
	{
		child->_parent = this;
		_children.push_back(child);

		// 넓이 순서대로 추가하므로 자식 노드가 모두 추가된 상태가 됨.
		// 따라서 Parent를 다 뒤져볼 필요 없음
		if (_level < child->_level + 1)
			_level = child->_level + 1;
	}

	// 나를 지나가거나 나까지 올때까지 중 가증 많은 단계 수 반환
	int getMaxStep() const
	{
		// 가장 먼 말단 노드에서 나까지 올 때의 단계 수
		int h = _level - 1;

		// 나를 거쳐가는 애 중 가장 많은 단계 수를 계산
		if (_children.size() >= 2)
		{
			int h1 = max(_children[0]->_level, _children[1]->_level);
			int h2 = min(_children[0]->_level, _children[1]->_level);

			for (int i = 2; i < (int)_children.size(); ++i)
			{
				if (h1 <= _children[i]->_level)
				{
					h2 = h1;
					h1 = _children[i]->_level;
				}
			}

			h = max(h, h1 + h2);
		}

		return h;
	}

	// 전체 노드 중 가장 단계 수가 긴 경우
	int getGloablMaxStep() const
	{
		int h = getMaxStep();

		for (int i = 0; i < (int)_children.size(); ++i)
			h = max(h, _children[i]->getGloablMaxStep());

		return h;
	}
};

// 성벽을 표현하기 위한 노드
class Wall
{
public:
	Wall() : _x(0), _y(0), _radius(0), _node() {}
	Wall(const Wall& cp) : _x(cp._x), _y(cp._y), _radius(cp._radius), _node(cp._node) {}

	friend istream& operator >> (istream& in, Wall& wall);

private:
	// 중심 위치, 반지름
	int		_x, _y, _radius;

	// 포함 관계를 트리로 표현하기 위한 멤버
	Node	_node;

public:
	bool operator<(const Wall& rhs) { return this->getRadius() < rhs.getRadius(); }

	int getX() const { return _x; }

	int getY() const { return _y; }

	int getRadius() const { return _radius; }

	// 내가 w에 포함되는지 여부 반환.
	// 포함 조건: "중심 사이의 거리 + this의 반지름 < w의 반지름"
	bool isIn(const Wall& w)
	{
		return sqrt(pow(_x - w._x, 2) + pow(_y - w._y, 2)) + _radius < w._radius;
	}

	Node* node() { return &_node; }
};

istream& operator >> (istream& in, Wall& wall)
{
	in >> wall._x >> wall._y >> wall._radius;

	return in;
}

int main(int argc, char* argv[])
{
	std::ios::sync_with_stdio(false);

	int T = 0, N = 0;

	in >> T;

	while (T--)
	{
		in >> N;

		vector<Wall> W(N, Wall());

		// 원형 벽 정보 읽기
		for (int i = 0; i < N; ++i)
			in >> W[i];

		// 포함 관계를 쉽게 찾기 위하여 넓이 순으로 정렬 (오름차순)
		std::sort(W.begin(), W.end());

		// 트리 형태로 구성
		for (int i = 0; i < N - 1; ++i)
		{
			Wall& childWall = W[i];

			for (int j = i + 1; j < N; ++j)
			{
				if (childWall.isIn(W[j]))
				{
					W[j].node()->addChild(childWall.node());
					break;
				}
			}
		}

		// 최상위 노드부터 최대 단계수를 계산해 나감
		out << W.back().node()->getGloablMaxStep() << "\n";
	}

	return 0;
}
