#ifndef _TOOL_H_
#define _TOOL_H_

#include <algorithm>
#include <string>
#include <vector>
#include <cmath>

using namespace std;


// Greatest Common Devider (최대공약수 구하기)
int gcd(int a, int b);

// 최대공배수 구하기
int lcm(int a, int b);

// 소인수 분해
vector<int> factor(int n);

// 소수인지 여부 반환
bool isPrime(long number);

// KMP 알고리즘을 이용한 부분 일치 테이블 생성
// pi[] 값을 계산하여 반환함.
vector<int> getPartialMatch(const string& N);

// 접미사 배열을 계산
vector<int> getSuffixArray(const string& s);

// KMP 알고리즘을 이용한 검색
vector<int> kmpSearch(const string& H, const string& N);

// 약수 구하기
vector<int> getDivisors(int n, bool includeSelf);

#endif
