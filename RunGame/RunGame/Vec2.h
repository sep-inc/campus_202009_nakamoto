#ifndef VEC2_H_
#define VEC2_H_

struct Vec2
{
	Vec2()
	{
		m_X = 0.0f;
		m_Y = 0.0f;
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


	//! X値
	float m_X;
	//! Y値
	float m_Y;

};

#endif