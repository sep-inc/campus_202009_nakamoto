#ifndef CALCULATION_H_
#define CALCULATION_H_

#define PI 3.14159265359

/* �v�Z�@�N���X */
class Calculation
{
public:
	/****************************
	�@�x�����W�A���ɕϊ�����֐�
	******************************/
	inline static float ToRadian(float degree_) { return degree_ * PI / 180.0f; }

	/****************************
	�@���W�A����x�ɕϊ�����֐�
    ******************************/
	inline static float ToDegree(float radian_) { return radian_ * 180.0f / PI; }

};

#endif