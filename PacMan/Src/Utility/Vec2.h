#ifndef VEC2_H_
#define VEC2_H_


struct Vec2
{
	Vec2()
	{
		m_X = 0;
		m_Y = 0;
	}

	Vec2(__int8 x_, __int8 y_)
	{
		m_X = x_;
		m_Y = y_;
	}

	Vec2(const Vec2& vec_)
	{
		this->m_X = vec_.m_X;
		this->m_Y = vec_.m_Y;
	}

	bool operator == (const Vec2& vec_) const
	{
		return (m_X == vec_.m_X && m_Y == vec_.m_Y);
	}


	//! X’l
	__int8 m_X;
	//! Y’l
	__int8 m_Y;
};

#endif