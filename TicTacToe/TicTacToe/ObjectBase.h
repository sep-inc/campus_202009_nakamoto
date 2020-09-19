﻿#ifndef OBJECTBASE_H_
#define OBJECTBASE_H_

#include "ObjectType.h"

/*
	オブジェクト基底クラス
	共通関数や変数をまとめている
*/
class ObjectBase
{
public:
	// コンストラクタ
	ObjectBase(ObjectType type_):
		m_ObjectType(type_),
		m_Selected(false),
		m_SelectX(0),
		m_SelectY(0)
	{}

	// デストラクタ
	virtual ~ObjectBase(){}

	// 初期化関数
	virtual void Init() = 0;

	// ステップの更新関数
	virtual void StepUpdate() = 0;


protected:
	// どのマスに置くかを選ぶ関数
	void Select();

	// どのマスの横軸に置くかを決める関数
	virtual __int8 SelectHorizontal() = 0;

	// どのマスの縦軸に置くかを決める関数
	virtual __int8 SelectVertical()   = 0;

protected:
	// どのマスに置くか決めたかどうかを保存する変数
	bool m_Selected;

	// 置かれた場所の横軸を保存する変数
	__int8 m_SelectX;

	// 置かれた場所の縦軸を保存する変数
	__int8 m_SelectY;

	// グリッド参照用変数

	// オブジェクトを識別するための変数
	const ObjectType m_ObjectType;

};

#endif