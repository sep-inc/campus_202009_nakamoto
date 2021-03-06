#include "Disk.h"
#include "../System/Drawer.h"
#include "../System/Input.h"
#include "Global.h"
#include <stdio.h>
#include <string.h>

/*======================================*/
/*             ステップ更新関数         */
/*======================================*/
void Hanoi::Disk::StepUpdate()
{
	// 現在のステップを参照する
	switch (m_CurrentStep)
	{
	case DiskStep::STEP_INIT:
		// 初期化
		this->Init();
		m_CurrentStep = DiskStep::STEP_UPDATE;
		break;

	case DiskStep::STEP_UPDATE:
		// 移動元を選ぶ
		m_SelectColumnSource = SelectSouce();
		
		// 移動先を選ぶ
		m_SelectColumnDist   = SelectDist();

		// 移動元と移動先を入れ替える
		Swap(m_SelectColumnSource, m_SelectColumnDist);

		// クリア判定
		if (ClearJudgment() == true) {
			g_GameClear = true;
		}

		break;

	default:
		break;
	}
}


/*======================================*/
/*             初期化関数               */
/*======================================*/
void Hanoi::Disk::Init()
{
	// 真ん中の列と右の列を空で埋める
	for (int y = 0; y < 3; ++y) {
		for (int x = 1; x < 3; ++x) {
			m_Disk[y][x] = DiskType::DISK_EMPTY;
		}
	}

	// 左を下らか大中小と並べる
	m_Disk[2][0] = DiskType::DISK_LARGE;
	m_Disk[1][0] = DiskType::DISK_MEDIUM;
	m_Disk[0][0] = DiskType::DISK_SMALL;
}


/*======================================*/
/*             描画関数                 */
/*======================================*/
void Hanoi::Disk::Draw()
{
	char disk_str[256] = { "\0" };

	// 左上から順番に入っているディスクを見て文字列に格納していく
	for (int y = 0; y < 3; ++y) {
		for (int x = 0; x < 3; ++x) {
			if      ( m_Disk[y][x] == DiskType::DISK_EMPTY  )  Drawer::GetInstance().SetDrawBuffer(x, y, "□□□□□\t");
			else if ( m_Disk[y][x] == DiskType::DISK_SMALL  )  Drawer::GetInstance().SetDrawBuffer(x, y, "□□■□□\t");
			else if ( m_Disk[y][x] == DiskType::DISK_MEDIUM )  Drawer::GetInstance().SetDrawBuffer(x, y, "□■■■□\t");
			else if ( m_Disk[y][x] == DiskType::DISK_LARGE  )  Drawer::GetInstance().SetDrawBuffer(x, y, "■■■■■\t");
		}
	}
	Drawer::GetInstance().SetDrawBuffer(0, 4, "　　1\t\t　　2\t\t　　3\n");
}

/*======================================*/
/*     どの列を選ばれたかを返す関数     */
/*======================================*/
__int8 Hanoi::Disk::SelectColumn()
{
	__int8 select_column = -1;
	while (true)
	{
		int key = Input::GetKey();

		if (key == -1) {
			continue;
		}

		if (key == KEY_1)		 { select_column = 0; break; }
		else if (key == KEY_2) { select_column = 1; break; }
		else if (key == KEY_3) { select_column = 2; break; }
		else {
			// もしそれ123以外のキーが押された場合
			printf("もう一度選んでください\n");
		}

	}

	return select_column;
}


/*=============================================*/
/*    　　　　 移動元を選ぶ関数                */
/*=============================================*/
__int8 Hanoi::Disk::SelectSouce()
{
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COORD{ 0,5 });

	printf("移動元を選んでください\n1 or 2 or 3\n");

	return SelectColumn();
}


/*=============================================*/
/*    　　　　 移動先を選ぶ関数      　        */
/*=============================================*/
__int8 Hanoi::Disk::SelectDist()
{
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COORD{ 0,5 });

	printf("移動先を選んでください\n1 or 2 or 3\n");

	return SelectColumn();
}


/*==============================================================*/
/* 移動元と移動先を入れ替え可能かを判定して入れ替える関数       */
/*==============================================================*/
void Hanoi::Disk::Swap(__int8 souceColumn_, __int8 distColumn_)
{
	// 移動元のディスクを保存する変数
	__int8 souce_disk = -1;
	
	// 移動元の列の上から確認していき空じゃなかったら保存する
	for ( int i = 0; i < 3; ++i ) {
		if ( m_Disk[i][souceColumn_] != DiskType::DISK_EMPTY )
		{
			souce_disk = i;
			break;
		}
	}

	// 空じゃなけれ選択できないのでリターン
	if ( souce_disk == -1 ) return;

	// 移動できるかを調べる
	// 移動先の列を下から調べていく
	for (int i = 0; i < 3; ++i) {

		// もし空ななら入れ替える
		if (m_Disk[2 - i][distColumn_] == DiskType::DISK_EMPTY)
		{
			DiskType temp = m_Disk[2 - i][distColumn_];
			m_Disk[2 - i][distColumn_] = m_Disk[souce_disk][souceColumn_];
			m_Disk[souce_disk][souceColumn_] = temp;
			break;
		}
		
		// 移動元のディスクと入換え先のディスクを比較して移動元のほうが大きければ入換えできない
		if ((__int8)m_Disk[souce_disk][souceColumn_] >= (__int8)m_Disk[2 - i][distColumn_])
		{
			break;
		}
	}

}


/*=============================================*/
/*    　　　　クリア判定を行う関数       　    */
/*=============================================*/
bool Hanoi::Disk::ClearJudgment()
{
	// 一番右の列を調べる

	// 一番上が円盤小でなかったら違う
	if      ( m_Disk[0][2] != DiskType::DISK_SMALL  )  return false;
	// 真ん中が円盤中でなかったら違う
	else if ( m_Disk[1][2] != DiskType::DISK_MEDIUM )  return false;
	// 一番下が円盤中でなかったら違う
	else if ( m_Disk[2][2] != DiskType::DISK_LARGE  )  return false;
	
	//全てのif分が通らなかったらクリア
	return true;
}
