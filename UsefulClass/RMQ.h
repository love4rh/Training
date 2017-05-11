#ifndef _RMQ_H_
#define _RMQ_H_

#include <algorithm>
#include <vector>

using namespace std;


// 배열의 구간 최소 쿼리를 해결하기 위한 구간 트리
template<typename ResultType, typename DataType, typename Calculator> class RMQ
{
public:
	RMQ(const vector<DataType>& array)
	{
		_n = array.size();
		_rangeMin.resize(_n * 4);

		init(array, 0, _n - 1, 1);
	}

private:
	// 배열의 길이
	int _n;

	// 각 구간의 결과
	vector<ResultType> _rangeMin;

	// Calculator는 ResultType operator()(ResultType, ResultType) 연산자가 구현되어 있어야 함.
	Calculator _calc;

private:
	ResultType init(const vector<DataType>& array, int left, int right, int node)
	{
		if (left == right)
			return _rangeMin[node] = ResultType(array[left]);

		int mid = (left + right) / 2;
		ResultType leftMin = init(array, left, mid, node * 2);
		ResultType rightMin = init(array, mid + 1, right, node * 2 + 1);

		return _rangeMin[node] = _calc(leftMin, rightMin);
	}

	ResultType query(int left, int right, int node, int nodeLeft, int nodeRight)
	{
		if (right < nodeLeft || nodeRight < left)
			return ResultType(numeric_limits<DataType>::max());	// TODO 값의 형태에 따라 바뀌어야 함.

		if (left <= nodeLeft && nodeRight <= right)
			return _rangeMin[node];

		int mid = (nodeLeft + nodeRight) / 2;
		return _calc( query(left, right, node * 2, nodeLeft, mid)
				    , query(left, right, node * 2 + 1, mid + 1, nodeRight) );
	}

	ResultType update(int index, int newValue, int node, int nodeLeft, int nodeRight)
	{
		if (index < nodeLeft || nodeRight < index)
			return _rangeMin[node];

		if (nodeLeft == nodeRight)
			return _rangeMin[node] = newValue;

		int mid = (nodeLeft + nodeRight) / 2;

		return _rangeMin[node] = _calc( update(index, newValue, node * 2, nodeLeft, mid)
									  , update(index, newValue, node * 2 + 1, mid + 1, nodeRight) );
	}

public:
	ResultType query(int left, int right)
	{
		return query(left, right, 1, 0, _n - 1);
	}

	ResultType update(int index, int newValue)
	{
		return update(index, newValue, 1, 0, _n - 1);
	}
};


#endif
