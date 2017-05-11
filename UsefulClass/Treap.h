#ifndef _TREAP_H_
#define _TREAP_H_

#include <map>
#include <iostream>

using namespace std;


// Treap에서 사용할 노드 객체 정의
template<typename KeyType> class TNode
{
public:
	TNode(const KeyType& key)
		: _key(key), _priority(rand()), _size(1), _left(NULL), _right(NULL)
	{
	}

	~TNode()
	{
		if (_left != NULL)
			delete _left;
		if (_right != NULL)
			delete _right;
	}

	typedef TNode<KeyType>		Node;

private:
	KeyType		_key;
	int			_priority, _size;

	Node		*_left, *_right;

private:
	void calcSize()
	{
		_size = 1;
		if (_left) _size += _left->_size;
		if (_right) _size += _right->_size;
	}

public:
	void setLeft(Node* newLeft)
	{
		_left = newLeft; calcSize();
	}

	void setRight(Node* newRight)
	{
		_right = newRight; calcSize();
	}

	const KeyType& key() const { return _key; }

	int priority() const { return _priority; }

	int size() const { return _size; }

	Node* left() const { return _left; }
	Node* right() const { return _right; }

	void print(int level)
	{
		int i = level;
		while (i--)
			cout << "  ";

		cout << _key << "\n";

		if (_left != NULL)
			_left->print(level + 1);
		if (_right != NULL)
			_right->print(level + 1);
	}
};


// 트립
template<typename KeyType> class Treap
{
public:
	typedef typename TNode<KeyType>::Node	TreapNode;
	typedef pair<TreapNode*, TreapNode*>	NodePair;

	Treap() : _root(NULL) {}
	Treap(const Treap<KeyType>& cp) : _root(cp._root) {}

	~Treap() { clear(); }

private:
	TreapNode*		_root;

private:
	// key 미만의 값과 이상의 값을 갖는 두 개의 트립으로 분리
	NodePair split(TreapNode* root, KeyType key)
	{
		if (root == NULL)
			return NodePair(NULL, NULL);

		if (root->key() < key)
		{
			NodePair rs = split(root->right(), key);
			root->setRight(rs.first);

			return NodePair(root, rs.second);
		}

		NodePair ls = split(root->left(), key);
		root->setLeft(ls.second);

		return NodePair(ls.first, root);
	}

	TreapNode* insert(TreapNode *root, TreapNode* node)
	{
		if (root == NULL)
		{
			return node;
		}

		if (root->priority() < node->priority())
		{
			NodePair splitted = split(root, node->key());

			node->setLeft(splitted.first);
			node->setRight(splitted.second);

			return node;
		}
		else if (node->key() < root->key())
			root->setLeft(insert(root->left(), node));
		else
			root->setRight(insert(root->right(), node));

		return root;
	}

	static TreapNode* merge(TreapNode *a, TreapNode* b)
	{
		if (a == NULL)
			return b;

		if (b == NULL)
			return a;

		if (a->priority() < b->priority())
		{
			b->setLeft(merge(a, b->left()));
			return b;
		}

		a->setRight(merge(a->right(), b));

		return a;
	}

	TreapNode* erase(TreapNode* root, KeyType key)
	{
		if (root == NULL)
			return root;

		if (root->key() == key)
		{
			TreapNode* ret = merge(root->left(), root->right());

			root->setLeft(NULL);
			root->setRight(NULL);

			delete root;
			return ret;
		}

		if (key < root->key())
			root->setLeft(erase(root->left(), key));
		else
			root->setRight(erase(root->right(), key));

		return root;
	}

	TreapNode* kth(TreapNode* root, int k)
	{
		int leftSize = 0;

		if (root->left() != NULL)
			leftSize = root->left()->size();

		if (k <= leftSize)
			return kth(root->left(), k);

		if (k == leftSize + 1)
			return root;

		return kth(root->right(), k - leftSize - 1);
	}

	int countLessThan(TreapNode* root, KeyType key)
	{
		if (root == NULL) return 0;

		if (root->key() >= key)
			return countLessThan(root->left(), key);

		int ls = (root->left() ? root->left()->size() : 0);

		return ls + 1 + countLessThan(root->right(), key);
	}

public:
	void clear()
	{
		if (_root != NULL)
		{
			delete _root;
			_root = NULL;
		}
	}

	// 노드 개수 반환
	int size() const
	{
		return _root == NULL ? 0 : _root->size();
	};

	// key 미만의 값과 이상의 값을 갖는 두 개의 트립으로 분리
	NodePair split(KeyType key)
	{
		return split(_root, key);
	}

	Treap<KeyType>& insert(KeyType key)
	{
		_root = insert(_root, new TreapNode(key));

		return *this;
	}

	// 두 트리를 하나로 합치기. 머지 후 a와 b의 root는 초기화됨.
	static Treap<KeyType> merge(Treap<KeyType>& a, Treap<KeyType>& b)
	{
		TreapNode* r = merge(a._root, b._root);

		a._root = b._root = NULL;

		return Treap<KeyType>(r);
	}

	Treap<KeyType>& erase(KeyType key)
	{
		_root = erase(_root, key);

		return *this;
	}

	// K번째 위치의 값 반환. 1-based
	KeyType kth(int k)
	{
		if (_root == NULL )
			throw "Empty Tree.";
		if (k < 1 || k > _root->size())
			throw "Invalid Index.";

		TreapNode* n = kth(_root, k);

		return n->key();
	}

	// key 보다 작은 값을 갖는 노드 개수 반환.
	int countLessThan(KeyType key)
	{
		return countLessThan(_root, key);
	}

	void print()
	{
		if (_root == NULL)
			cout << "not set\n";
		else
			_root->print(0);
	}
};

#endif
