#ifndef DIFINITION_H_
#define DIFINITION_H_

#define PLAYER_ON
#define ENEMY_ON
#define ITEM_ON

#define STAGE_WIDTH  13
#define STAGE_HEIGHT 13

#define PLAYER_INIT_POS_X 3
#define PLAYER_INIT_POS_Y 6

// ìGÇÃêî
#define ENEMY_NUM 3

// ÉAÉCÉeÉÄÇÃêî
#define ITEM_NUM  5

enum class ObjectType : int
{
	TYPE_EMPTY,
	TYPE_WALL,
	TYPE_PLAYER,
	TYPE_ENEMY,
	TYPE_ITEM,
};


#endif