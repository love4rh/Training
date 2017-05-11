#ifndef _EXPNUMBER_
#define _EXPNUMBER_


// E^d + r 와 같이 큰 수를 표현하기 위한 클래스
class ExpNumber
{
public:
	ExpNumber() : _d(0), _r(0) {}
	ExpNumber(long long n) : _d(n / _exp), _r(n % _exp) {}
	ExpNumber(long long d, long long r) : _d(d), _r(r) {}
	ExpNumber(const ExpNumber& cp) : _d(cp._d), _r(cp._r) {}

	ExpNumber& operator=(const ExpNumber& rhs)
	{
		if (this == &rhs)
			return *this;

		_d = rhs._d;
		_r = rhs._r;

		return *this;
	}

	static const int _exp = 1000000007;

private:
	// _exp로 나눈 몫
	long long _d;

	// _exp로 나눈 나머지
	long long _r;

public:
	long long d() const { return _d; }
	long long r() const { return _r; }

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

	ExpNumber& operator*(const ExpNumber& rhs)
	{
		long long multipleR = _r * rhs._r;

		_d = _exp * _d * rhs._d + _d * rhs._r + _r * rhs._d + multipleR / _exp;
		_r = multipleR % _exp;

		return *this;
	}

	ExpNumber& operator*(int rhs)
	{
		long long multipleR = _r * rhs;

		_d *= rhs + multipleR / _exp;;
		_r = multipleR % _exp;

		return *this;
	}
};

#endif
