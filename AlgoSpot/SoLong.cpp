// https://algospot.com/judge/problem/read/SOLONG

#include "./function.h"

#ifdef __SOLONG__

#include <fstream>

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>
#include <memory.h>

using namespace std;

//istream& in = cin;
ifstream in("E:\\Work\\Algorithm\\data\\soLong.txt");


class Node
{
public:
	Node() : _typeCnt(0) { memset(_subNode, 0, sizeof(_subNode)); }

private:
	int		_typeCnt;
	Node*	_subNode[26];

public:
	void addString(const string& str, int pos, int typeCnt)
	{
		Node* &child = _subNode[str[pos] - 'A'];

		if (child == 0)
			child = new Node();
		else
			typeCnt += 1;

		if (++pos < (int)str.length())
			child->addString(str, pos, typeCnt);
		// ������ �Դٸ� Typing Count ����
		else
			child->_typeCnt = min(typeCnt + 1, (int)str.length());
	}

	int getTypingCnt(const string& str, int pos)
	{
		if (pos == str.length())
			return _typeCnt == 0 ? str.length() : _typeCnt;

		Node* child = _subNode[str[pos] - 'A'];

		if (child == 0)
			return str.length();

		return child->getTypingCnt(str, ++pos);
	}

	void deleteChild()
	{
		for (int i = 0; i < 26; ++i)
			if (_subNode[i] != 0)
			{
				_subNode[i]->deleteChild();
				delete _subNode[i];
				_subNode[i] = 0;
			}
	}
};


int main(int argc, char* argv[])
{
	int caseCount = 0, num = 0, dictNum = 0, wordNum = 0;

	in >> caseCount;

	while (caseCount--)
	{
		in >> dictNum >> wordNum;

		// ���� �б�
		int weight;
		string word;
		vector<pair<int, string>> dict;

		while (dictNum--)
		{
			in >> word >> weight;
			dict.push_back(pair<int, string>(-weight, word));
		}

		// Ÿ���� ȸ�� ����� ���� ����.
		std::sort(dict.begin(), dict.end());

		// �˻� Tree ����
		Node* rootNode = new Node();
		for (vector<pair<int, string>>::iterator it = dict.begin(); it != dict.end(); ++it)
		{
			rootNode->addString(it->second, 0, 1);
		}

		int totalPress = wordNum - 1;	//< �߰� ������ �̸� ���
		while (wordNum--)
		{
			in >> word;

			totalPress += rootNode->getTypingCnt(word, 0);
		}

		cout << totalPress << "\n";

		rootNode->deleteChild();
		delete rootNode;
	}

	return 0;
}

#endif
