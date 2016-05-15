#ifndef _TOOL_H_
#define _TOOL_H_

#include <algorithm>
#include <string>
#include <vector>
#include <cmath>

using namespace std;


// Greatest Common Devider (�ִ����� ���ϱ�)
int gcd(int a, int b);

// �ִ����� ���ϱ�
int lcm(int a, int b);

// ���μ� ����
vector<int> factor(int n);

// �Ҽ����� ���� ��ȯ
bool isPrime(long number);

// KMP �˰����� �̿��� �κ� ��ġ ���̺� ����
// pi[] ���� ����Ͽ� ��ȯ��.
vector<int> getPartialMatch(const string& N);

// ���̻� �迭�� ���
vector<int> getSuffixArray(const string& s);

// KMP �˰����� �̿��� �˻�
vector<int> kmpSearch(const string& H, const string& N);

// ��� ���ϱ�
vector<int> getDivisors(int n, bool includeSelf);

#endif
