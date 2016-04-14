// https://algospot.com/judge/problem/read/CLOCKSYNC

#include <fstream>

#include <iomanip>
#include <iostream>

using namespace std;

//istream& in = cin;
ifstream in("E:\\Work\\Algorithm\\data\\clockSync.txt");

// 각 시계별 바늘 위치(12, 3, 6, 9)
int clockPos[16];

// 스위치별 연결된 시계정보
int clockSwitch[10][6] =
{ { 0, 1, 2, -1 }
, { 3, 7, 9, 11, -1 }
, { 4, 10, 14, 15, -1 }
, { 0, 4, 5, 6, 7, -1 }
, { 6, 7, 8, 10, 12, -1 }
, { 0, 2, 14, 15, -1 }
, { 3, 14, 15, -1 }
, { 4, 5, 7, 14, 15, -1 }
, { 1, 2, 3, 4, 5, -1 }
, { 3, 4, 5, 9, 13, -1 }
};

int pressCnt[10];
int totalPress = 0;


bool isAllAt12()
{
	for (int i = 0; i < 16; ++i)
		if (clockPos[i] != 12)
			return false;

	return true;
}

// 스위치 s를 눌렀을 때 바늘 위치 변경.
// 4번 눌러서 원래대로 돌아온 경우라면 false 반환
bool pressSwitch(int s)
{
	for (int i = 0; clockSwitch[s][i] != -1 && i < 6; ++i)
	{
		clockPos[clockSwitch[s][i]] += 3;

		if (clockPos[clockSwitch[s][i]] > 12)
			clockPos[clockSwitch[s][i]] = 3;
		else if (clockPos[clockSwitch[s][i]] == 0)
			clockPos[clockSwitch[s][i]] = 12;
	}

	totalPress += 1;
	if (++pressCnt[s] == 4)
	{
		pressCnt[s] = 0;
		totalPress -= 4;
		return false;
	}

	return true;
}


int main(int argc, char* argv[])
{
	int caseCount = 0;

	in >> caseCount;

	while (caseCount--)
	{
		for(int i = 0; i < 16; ++i)
			in >> clockPos[i];

		// 스위치당 최대 0 ~ 3번까지 누를 수 있음. 4^10 가지 경우의 수 존재.
		for (int i = 0; i < 10; ++i)
			pressCnt[i] = 0;

		int s = 0;
		int minNum = 999999999;

		while (s < 10)
		{
			if (totalPress < minNum && isAllAt12())
				minNum = totalPress;

			s = 0;
			while (s < 10 && !pressSwitch(s))
				++s;
		}

		cout << (minNum == 999999999 ? -1 : minNum) << "\n";
	}

	return 0;
}
