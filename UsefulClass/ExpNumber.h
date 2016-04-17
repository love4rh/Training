#ifndef _EXPNUMBER_
#define _EXPNUMBER_


// E^d + r �� ���� ū ���� ǥ���ϱ� ���� Ŭ����
class ExpNumber
{
public:
	ExpNumber() : _d(0), _r(0) {}
	ExpNumber(int d, int r) : _d(d), _r(r) {}
	ExpNumber(const ExpNumber& cp) : _d(cp._d), _r(cp._r) {}

	ExpNumber& operator=(const ExpNumber& rhs)
	{
		if (this == &rhs)
			return *this;

		_d = rhs._d;
		_r = rhs._r;

		return *this;
	}

private:
	static const int _exp = 1000000007;

	// _exp�� ���� ��
	int _d;

	// _exp�� ���� ������
	int _r;

public:
	int d() const { return _d; }
	int r() const { return _r; }

	ExpNumber& operator-(const ExpNumber& rhs)
	{
		_d -= rhs._d;
		_r -= rhs._r;

		if (_r < 0)
		{
			_d -= 1;
			_r += _exp;
		}

		return *this;
	}

	ExpNumber& operator+(const ExpNumber& rhs)
	{
		_d += rhs._d;
		_r += rhs._r;

		if (_r >= _exp)
		{
			_d += 1;
			_r -= _exp;
		}

		return *this;
	}
};

#endif
