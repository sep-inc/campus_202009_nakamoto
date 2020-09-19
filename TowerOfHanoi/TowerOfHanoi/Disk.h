#ifndef DISK_H_
#define DISK_H_

/**
* @brief   円盤クラス
* @details
*/
class Disk
{
	/**
	* @enum Enum
	* 円盤の種類
	*/
	enum class DiskType : unsigned char
	{
		DISK_SMALL,    // 円盤小 □□■□□
		DISK_MEDIUM,   // 円盤中 □■■■□     
		DISK_LARGE,    // 円盤大 ■■■■■
		DISK_EMPTY,    // 円盤空 □□□□□
	};

	/**
	* @enum Enum
	* 円盤のステップ
	*/
	enum class DiskStep : unsigned char
	{
		STEP_INIT,
		STEP_UPDATE,
	};

public:
	/**
	* @brief   コンストラクタ
	* @details 必要な情報を初期化する
	*/
	Disk() :
		m_Disk{ DiskType::DISK_EMPTY },
		m_SelectColumnSource{ 0 },
		m_SelectColumnDist  { 0 },
		m_CurrentStep{ DiskStep::STEP_INIT }
	{}

	/**
	* @brief   デストラクタ
	*/
	~Disk() {}


	/**
	* @brief   初期化関数
	* @details ステップの初期化時に一度呼ばれるが、クリア後もう一度遊ぶ場合この関数を呼ぶ必要がある
	*/
	void Init();

	/**
	* @brief   ステップ更新関数
	* @details 現在のステップを参照し、そのステップの処理を行う
	*/
	void StepUpdate();

	/**
	* @brief   描画関数
	* @details ディスク情報をもとに文字列に格納して、描画クラスに渡す
	*/
	void Draw();

private:
	/**
	* @brief   どの列を選ばれたかを返す関数
	* @return  __int8 戻り値の説明
	* @details キー入力を行いどの列が選ばれたかを返す。1,2,3以外は返らない。
	*/
	__int8 SelectColumn();

	/**
	* @brief　 移動元を選ぶ関数
	* @return  __int8 移動元の列の番号
	* @details キー入力を行いどの列が選ばれたかを返す。1,2,3以外は返らない。
	*/
	__int8 SelectSouce();

	/**
	* @brief　 移動先を選ぶ関数
	* @return  __int8 移動先の列の番号
	* @details キー入力を行いどの列が選ばれたかを返す。1,2,3以外は返らない。
	*/
	__int8 SelectDist();

	/**
	* @brief   描画関数
	* @details ディスク情報をもとに文字列に格納して、描画クラスに渡す
	*/
	void Swap(__int8 souceColumn_, __int8 distColumn_);

	/**
	* @brief  クリア判定をする関数
	* @return bool クリアしていたらtrueを返す
	*/
	bool ClearJudgment();

private:
	//! 円盤配列
	DiskType m_Disk[3][3];

	//! 移動元を保存する変数
	__int8 m_SelectColumnSource;

	//! 移動先を保存する変数
	__int8 m_SelectColumnDist;

	//! 現在のステップを保存する変数
	DiskStep m_CurrentStep;
};


#endif