#ifndef IVEC2_H_
#define IVEC2_H_

struct IVec2
{
	IVec2()
	{
		m_X = 0;
		m_Y = 0;
	}

	IVec2(__int8 x_, __int8 y_)
	{
		m_X = x_;
		m_Y = y_;
	}

	IVec2(const IVec2& vec_)
	{
		this->m_X = vec_.m_X;
		this->m_Y = vec_.m_Y;
	}


	//! X値
	__int8 m_X;
	//! Y値
	__int8 m_Y;
};

#endif