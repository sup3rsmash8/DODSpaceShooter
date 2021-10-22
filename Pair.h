#pragma once

template<class Left, class Right>
struct Pair
{
public:
	Pair(Left left, Right right)
	{
		m_leftValue = left;
		m_rightValue = right;
	}

	Left m_leftValue;
	Right m_rightValue;

	void SetBoth(Left left, Right right)
	{
		m_leftValue = left;
		m_rightValue = right;
	}
};

