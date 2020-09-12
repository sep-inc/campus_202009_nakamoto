#ifndef CALCULATION_H_
#define CALCULATION_H_

#define PI 3.14159265359

/* 計算機クラス */
class Calculation
{
public:
	/****************************
	　度をラジアンに変換する関数
	******************************/
	inline static float ToRadian(float degree_) { return degree_ * PI / 180.0f; }

	/****************************
	　ラジアンを度に変換する関数
    ******************************/
	inline static float ToDegree(float radian_) { return radian_ * 180.0f / PI; }

};

#endif