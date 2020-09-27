﻿#ifndef WALL_H_
#define WALL_H_

/****************************************************
	header
*****************************************************/
#include "ObjectType.h"

/****************************************************
	class
*****************************************************/

/*
	壁クラス
*/
class Wall
{
	// 壁の更新ステップ
	enum class WallStep
	{
		InitStep,		// 初期化ステップ
		DrawStep,		// 描画ステップ
		ReleaseStep,	// 解放ステップ
	};

public:
	/***************************************************************
		コンストラクター
	****************************************************************/
	Wall();

	/***************************************************************
		コンストラクター
	****************************************************************/
	~Wall()
	{}

	/***************************************************************
		ステップを更新する関数
	****************************************************************/
	void StepUpdate();

	/***************************************************************
		描画関数
	****************************************************************/
	void Draw();

	/***************************************************************
		ゲッター関数
	****************************************************************/
	inline const __int8 GetMinX()  const { return m_MinX;   }
	inline const __int8 GetMaxX()  const { return m_MaxX;   }
	inline const __int8 GetMinY()  const { return m_MinY;   }
	inline const __int8 GetMaxY()  const { return m_MaxY;   }
	inline const __int8 GetWidth() const { return m_Width;  }
	inline const __int8 GetHeight()const { return m_Height; }

private:
	/***************************************************************
		初期化関数
	****************************************************************/
	void Initializ();

private:
	// 左端の壁
	const __int8 m_MinX;

	// 右端の壁
	const __int8 m_MaxX;

	// 上の壁
	const __int8 m_MinY;

	// 下の壁
	const __int8 m_MaxY;

	// 横幅
	const __int8 m_Width;

	// 縦幅
	const __int8 m_Height;

	// オブジェクトタイプ
	const __int8 m_Type;

	// 現在のSTEP
	WallStep m_CurrentStep;

};


#endif