#include "EnemyAIChase.h"
#include "../../../../Utility/Calc.h"

PacMan::EnemyAIChase::EnemyAIChase(IVec2* enemyPos_, EnemyParameter* enemyParam_, Stage* stage_) :
	EnemyAIBase{ enemyPos_ , enemyParam_ ,stage_ }
{
}

ActionStateList PacMan::EnemyAIChase::Update()
{
	// もし性格がAかCならプレイヤーに向かって進む、
	if (m_EnemyParam->m_Personality == EnemyPersonalityList::PERSONALITY_A || m_EnemyParam->m_Personality == EnemyPersonalityList::PERSONALITY_C)
	{
		// もし見失ったらアクションを徘徊にする
		if (Chase() == false) return ActionStateList::ACTION_SAUNTERING;
	}
	// もし性格がBなら先を読んで行動する
	else if (m_EnemyParam->m_Personality == EnemyPersonalityList::PERSONALITY_B) {
		// 一定フレームでアクションを徘徊にする
		if (Forestall() == false) return ActionStateList::ACTION_SAUNTERING;

	}
	
	// 敵をまだ見失っていないので、追いかける状態のまま
	return ActionStateList::ACTION_CHASE;
}

/*
	先回りで追いかける
*/
bool PacMan::EnemyAIChase::Forestall()
{
	// もしプレイヤーがいた場合,追いかける
	IVec2 player_pos;
	if (FoundPlayer(m_RefEnemyPos, m_RefStage, 11, &player_pos) == true) {

		// もしプレイヤーを見つけた場合追跡リストをクリアする
		m_EnemyParam->m_TraceList.clear();
		// プレイヤーの位置を保存しておく
		m_PlayerOldPos = player_pos;

		// プレイヤーの方向を算出する
		IVec2 enemy_to_player_vec = player_pos - *m_RefEnemyPos;
		if (enemy_to_player_vec.m_X != 0)enemy_to_player_vec.m_X /= Calc::Abs(enemy_to_player_vec.m_X);
		if (enemy_to_player_vec.m_Y != 0)enemy_to_player_vec.m_Y /= Calc::Abs(enemy_to_player_vec.m_Y);

		m_EnemyParam->m_Direction = enemy_to_player_vec;
		return true;
	}
	// プレイヤーが見つからなかった場合かる前のフレームでも見つかってなかったら、見失ったのでfalseを返す
	else if (m_PlayerOldPos.m_X == -1 || m_PlayerOldPos.m_Y == -1) return false;
	// プレイヤーが見つからなかったが、前のフレームでプレイヤーを見つけていた場合
	else {
		
		// もし追跡リストがなくなるまで移動する
		if (!m_EnemyParam->m_TraceList.empty()) {
			m_EnemyParam->m_Direction = m_EnemyParam->m_TraceList.front() - *m_RefEnemyPos;
			m_EnemyParam->m_TraceList.erase(std::begin(m_EnemyParam->m_TraceList));
			return true;
		}

		// もし、見失ったら、プレイヤーの移動した方向を検索する

		// プレイヤーを見失った位置から、直線上にプレイヤーが存在するかを調べる
		// もしいなかったら見失ったのでfalseを返す
		if (FoundPlayer(&m_PlayerOldPos, m_RefStage, 11, &player_pos) == false) { return false; }


		// いた場合移動できる方向が複数になるまで移動する方向を予測する
		while (true)
		{
			// プレイヤーの移動した方向を算出する
			IVec2 player_vec = player_pos - m_PlayerOldPos;
			if (player_vec.m_X != 0)player_vec.m_X /= Calc::Abs(player_vec.m_X);
			if (player_vec.m_Y != 0)player_vec.m_Y /= Calc::Abs(player_vec.m_Y);

			// プレイヤーの移動した方向に対して、左向きのベクトルを算出する
			IVec2 left_direction{ player_vec.m_Y, -player_vec.m_X };



			// プレイヤーの移動可能な方向の数を保存する変数
			int able_move_num = 0;

			// プレイヤーの次に移動するであろう座標を保存する変数
			IVec2 player_next_pos;

			// プレイヤーの次に移動するであろう移動ベクトルを保存する変数
			IVec2 move_vec;

			// 前向きに移動できるかを調べる
			player_next_pos = player_pos + player_vec;
			if (m_RefStage->GetStageObject(player_next_pos) != ObjectType::TYPE_WALL) {
				
				// 移動できる場合そのベクトルを保存する
				move_vec = player_next_pos - player_pos;

				// 移動可能数を足す
				able_move_num++;
			}

			// 左向きに移動できるかを調べる
			player_next_pos = player_pos + left_direction;
			if (m_RefStage->GetStageObject(player_next_pos) != ObjectType::TYPE_WALL) {
				// 移動できる数が1以上ならbreak
				if (able_move_num >= 1)break;

				// 移動できる場合そのベクトルを保存する
				move_vec = player_next_pos - player_pos;

				// 移動可能数を足す
				able_move_num++;
			}

			// 向いている方向に対して右にすすめるか
			player_next_pos = player_pos - left_direction;
			if (m_RefStage->GetStageObject(player_next_pos) != ObjectType::TYPE_WALL) {
				// 移動できる数が1以上ならbreak
				if (able_move_num >= 1)break;
				
				// 移動できる場合そのベクトルを保存する
				move_vec = player_next_pos - player_pos;

				// 移動可能数を足す
				able_move_num++;
			}

			// 位置を更新する
			m_PlayerOldPos = player_pos;
			player_pos = player_pos + move_vec;
		}

		// プレイヤーの移動するであろう場所に最短経路で移動する
		m_RefStage->FindShortestPath(&m_EnemyParam->m_TraceList, *m_RefEnemyPos, player_pos);

		
		if (m_EnemyParam->m_TraceList.empty())return false;
		
		// 移動する方向を保存する
		m_EnemyParam->m_Direction = m_EnemyParam->m_TraceList.front() - *m_RefEnemyPos;
		m_EnemyParam->m_TraceList.erase(std::begin(m_EnemyParam->m_TraceList));
	}

	return true;
}

/*
	追いかける
*/
bool PacMan::EnemyAIChase::Chase()
{
	// もし追跡リストがなくなるまで移動する
	if (!m_EnemyParam->m_TraceList.empty()) {
		m_EnemyParam->m_Direction = m_EnemyParam->m_TraceList.front() - *m_RefEnemyPos;
		m_EnemyParam->m_TraceList.erase(std::begin(m_EnemyParam->m_TraceList));
		return true;
	}

	IVec2 player_pos;

	// 自身の位置から4方向の直線上にプレイヤーがいるかを調べる
	if (FoundPlayer(m_RefEnemyPos, m_RefStage, 11, &player_pos) == false) return false;

	// いた場合、敵とプレイヤーのベクトルを算出する
	IVec2 enemy_to_player_vec = player_pos - *m_RefEnemyPos;
	// ベクトルを単位化する
	if (enemy_to_player_vec.m_X != 0)enemy_to_player_vec.m_X /= Calc::Abs(enemy_to_player_vec.m_X);
	if (enemy_to_player_vec.m_Y != 0)enemy_to_player_vec.m_Y /= Calc::Abs(enemy_to_player_vec.m_Y);

	// 次に移動する方向をプレイヤーの方向にセットする
	m_EnemyParam->m_Direction = enemy_to_player_vec;
	return true;
}

void PacMan::EnemyAIChase::Init()
{
	m_PlayerOldPos.m_X = -1;
	m_PlayerOldPos.m_Y = -1;
}
