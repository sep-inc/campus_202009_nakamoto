#ifndef OBJECTTYPE_H_
#define OBJECTTYPE_H_

/*
	オブジェクトのタイプ
*/
enum class ObjectType : unsigned char
{
	TYPE_PlAYER,	// プレイヤー
	TYPE_ENEMY,		// エネミー
	TYPE_EMPTY,		// 空
};

#endif