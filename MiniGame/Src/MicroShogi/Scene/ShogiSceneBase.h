#ifndef SHOGISCENEBASE_H_
#define SHOGISCENEBASE_H_

#include <string>

/**
* @brief 将棋のシーンの基底クラス
*/
class ShogiSceneBase
{
public:
	/**
	* @brief   デストラクタ
	*/
	ShogiSceneBase(){}

	/**
	* @brief   コンストラクタ
	*/
	~ShogiSceneBase(){}

	/**
	* @brief   更新関数
	* @details 各シーンで更新する処理を書く
	*/
	virtual void Update() = 0;
	
	/**
	* @brief   描画関数
	* @details 各シーンで描画する処理を書く
	*/
	virtual void Draw()   = 0;

protected:
	//! 描画用文字列
	std::string m_DrawStr;
	
};

#endif