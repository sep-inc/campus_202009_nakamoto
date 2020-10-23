#include "CharacterPlayer.h"
#include "../../../System/Drawer.h"
#include "../../../System/Input.h"
#include "../../PacManDefinition.h"
#include "../Stage.h"

using namespace PacMan;

PacMan::CharacterPlayer::CharacterPlayer(Stage* stage_) :
	StageCharacter{ stage_ }
{
}

void PacMan::CharacterPlayer::Init()
{
	this->SetPos(IVec2(PLAYER_INIT_POS_X, PLAYER_INIT_POS_Y));

}

void PacMan::CharacterPlayer::Update()
{

	this->Move();
	
}

void PacMan::CharacterPlayer::Draw()
{
	Drawer::GetInstance().SetDrawBuffer(m_Pos.m_X, m_Pos.m_Y, "〇");
}

void PacMan::CharacterPlayer::Move()
{
	int key = Input::GetKey();

	// キーが入力されていなければ下の判定をせずに返す
	if (key == -1) return;

	IVec2 next_pos = m_Pos;
	// 上キーが押されたとき
	if (key == KEY_UP)         next_pos.m_Y--;
	// 下キーが押されたとき
	else if (key == KEY_DOWN)  next_pos.m_Y++;
	// 左キーが押されたとき
	else if (key == KEY_LEFT)  next_pos.m_X--;
	// 右キーが押されたとき
	else if (key == KEY_RIGHT) next_pos.m_X++;
	// それ以外のキーが押されたら移動しないので下の判定をせずに返す
	else return;

	// 移動先に壁がなかったら移動する
	if (m_RefStage->GetStageObject(next_pos) != ObjectType::TYPE_WALL) {
		m_RefStage->SetStage(m_Pos, next_pos, this->GetObjectType());
		m_Pos = next_pos;
		m_RefStage->HitItem(m_Pos);
	}
}
