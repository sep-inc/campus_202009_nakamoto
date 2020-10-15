#ifndef VEC2_H_
#define VEC2_H_


struct Vec2
{
	Vec2()
	{
		m_X = 0.f;
		m_Y = 0.f;
	}

	Vec2(float x_, float y_)
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
	float m_X;
	//! Y’l
	float m_Y;
};

#endif