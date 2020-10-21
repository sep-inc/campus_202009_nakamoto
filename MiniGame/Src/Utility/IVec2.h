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

	bool operator == (const IVec2& vec_) const
	{
		return (m_X == vec_.m_X && m_Y == vec_.m_Y);
	}

	IVec2 operator - (IVec2& vec_) {
		IVec2 vec2;
		vec2.m_X = this->m_X - vec_.m_X;
		vec2.m_Y = this->m_Y - vec_.m_Y;
		return vec2;
	}

	IVec2 operator + (IVec2& vec_) {
		IVec2 vec2;
		vec2.m_X = this->m_X + vec_.m_X;
		vec2.m_Y = this->m_Y + vec_.m_Y;
		return vec2;
	}

	// ゼロベクトルかどうかを返す関数
	bool Zero() const;


	//! X値
	__int8 m_X;
	//! Y値
	__int8 m_Y;
};

#endif