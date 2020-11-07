using System.Collections;
using System.Collections.Generic;
using System.Runtime.InteropServices.WindowsRuntime;
using Unity.Collections.LowLevel.Unsafe;
using UnityEditor.Experimental.TerrainAPI;
using UnityEditorInternal;
using UnityEngine;

public class AI : MonoBehaviour
{
    public bool On { get; private set; } = false;
    
    [SerializeField] int fallMagnification = 1;

    // ステージ管理クラス
    [SerializeField] GameObject stageControllerObject = null;
    private StageController stageScript = null;
    
    // ブロック管理クラス
    [SerializeField] GameObject blockManager = null;
    private BlockManager blockManagerScript = null;
    
    // ブロッククラス(操作中)
    private GameObject block = null;
    private Block blockScript = null;


    // 目的地
    List<Vector3> destinationPos = null;
    // 回転する回数
    private int rotationNum = 0;
    // ストックするかどうか
    private bool isStockBlock = false;

    // 一列消した時の評価得点
    [SerializeField] int eraseOneLineScore   = 0;
    // 埋められない穴ができた時の評価得点
    [SerializeField] int unfilledHolesScore  = 0;
    // 縦3マスの穴ができた時の評価得点
    [SerializeField] int vertical3HolesScore = 0;


    // Start is called before the first frame update
    void Start()
    {
        destinationPos = new List<Vector3>();
        stageScript = stageControllerObject.GetComponent<StageController>();
        blockManagerScript = blockManager.GetComponent<BlockManager>();
    }

    // Update is called once per frame
    void Update()
    {
        if (Input.GetKeyDown(KeyCode.A))
        {
            On = !On;
        }

        if (!On) return;

        // 操作中のブロックが無ければ、ブロック管理クラスから操作中のブロックの情報をもらう
        if (block == null)
        {
            block = blockManagerScript.OperationBlock;
            if (block)
            {
                blockScript = block.GetComponent<Block>();
                int score = -10000;

                // 操作中のブロックの当たりデータを取得
                int[,] block_data = blockScript.BlockData;

                SelectBlock(ref score, block_data);


                // ストックのブロックを取得する
                GameObject stock_block = blockManagerScript.StockBlock;

                // 取得できなければ、次に操作できるブロックを取得
                if (stock_block == null)
                {
                    stock_block = blockManagerScript.NextBlock;

                    if (stock_block == null) return;
                }

                Block block_script = stock_block.GetComponent<Block>();

                // 操作中のブロックの当たりデータを取得
                block_data = block_script.BlockData;
                int temp_score = score;
                SelectBlock(ref score, block_data);
                if (temp_score < score)
                {
                    isStockBlock = true;
                }
            }
        }

        // ブロックの情報がなければ返す
        if (block == null) return;

        // もしストックのフラグが立っていたら
        if (isStockBlock == true)
        {
            // ブロックをストックする
            blockManagerScript.Stock();

            // 交換した後のブロックの情報をもらう
            block = blockManagerScript.OperationBlock;

            // ブロックスクリプトの取得
            blockScript = block.GetComponent<Block>();

            // フラグをオフにする
            isStockBlock = false;
        }
        
        // 回転が0より上なら右に回転してカウントを減らす
        if (rotationNum > 0)
        {
            blockScript.RightRotation();
            rotationNum--;
        }

        if (destinationPos.Count == 0) { return; }

        // ブロックのX軸が目的地のX軸と違った場合目的地のX軸の方向に移動する
        if (block.transform.position.x != destinationPos[0].x)
        {
            if (block.transform.position.x > destinationPos[0].x) blockScript.MoveLeft();
            else if (block.transform.position.x < destinationPos[0].x) blockScript.MoveRight();
        }
        // もしX軸が目的地なら高速落下させる
        if (block.transform.position.x == destinationPos[0].x)
        {
            for (int i = 0; i < fallMagnification; ++i) blockScript.FastFall();
        }

        // もし目的地なら戦闘の目的地を削除
        if (block.transform.position.x == destinationPos[0].x
            && block.transform.position.y == destinationPos[0].y
            && destinationPos.Count != 1)
        {
            destinationPos.RemoveAt(0);
        }

    }

  
    private void SelectBlock(ref int score_, int[,] blockData_)
    {
        for (int i = 0; i < 4; ++i)
        {
            // 移動可能な場所を探す
            List<Vector3> able_pos = FindAbleMove(blockData_);

            // 移動可能な場所で一番評価が高い場所を選ぶ
            foreach (Vector3 pos in able_pos)
            {
                int tmp_score = BlockEvaluation(pos, blockData_);

                // 一番スコアの高い場所のX軸を保存する
                if (tmp_score > score_)
                {
                    // 移動できない場合は更新しない
                    if (CanMove(pos, blockData_) == false) continue;

                    // スコアを保存する
                    score_ = tmp_score;

                    // 右に何回回転するかを保存する
                    rotationNum = i;
                }

            }

            // 当たりデータを右に90度回転する
            ArrayRotate.RightRotate(ref blockData_, BlocksDefinition.BLOCK_DATA_WIDTH, BlocksDefinition.BLOCK_DATA_HEIGHT);
        }

    }


    // おける場所を検索する
    private List<Vector3>　FindAbleMove(int[,] blockData_)
    {
        // 戻り値用
        List<Vector3> ret_vector = new List<Vector3>();

        // ブロックの当たりデータを取得
        int[,] block_data = blockData_;

        int min_x = 0;
        int max_x = 0;

        bool find = false;
        // X軸検索範囲の左端
        for(int x = 0; x < BlocksDefinition.BLOCK_DATA_WIDTH; ++x)
        {
            for(int y = 0; y < BlocksDefinition.BLOCK_DATA_HEIGHT; ++y)
            {
                if (block_data[y,x] == 1)
                {
                    min_x = (BlocksDefinition.BLOCK_DATA_WIDTH / 2) - x;
                    find = true;
                    break;
                }
            }
            
            if (find) break;
        }

        find = false;
        // X軸検索範囲の右端
        for (int x = BlocksDefinition.BLOCK_DATA_WIDTH - 1; x >= 0; --x)
        {
            for (int y = 0; y < BlocksDefinition.BLOCK_DATA_HEIGHT; ++y)
            {
                if (block_data[y, x] == 1)
                {
                    max_x = StageController.STAGE_WIDTH + ( (BlocksDefinition.BLOCK_DATA_WIDTH / 2) - x );
                    find = true;
                    break;
                }
            }
            
            if (find) break;
        }


        // 横一列を検索する
        //bool tmp = false;
      
        for (int x = min_x; x < max_x; ++x)
        {
            bool can_add = true;

            for (int y = 0; y < StageController.STAGE_HEIGHT; ++y)
            {
                Vector3 pos = new Vector3(x, y, 0);
                // ステージのしたから見て行って移動できるなら追加する
                if (stageScript.AbleMove(ref pos, ref block_data) == true)
                {
                    if (can_add == false) continue;
                    
                    ret_vector.Add(new Vector3(pos.x, pos.y, 0));
                    can_add = false;
                }
                // もし移動できなかったら追加可能状態にする
                else
                {
                    can_add = true;
                }

            }
        }

        return ret_vector;
    }


    // 評価する関数
    private int BlockEvaluation(Vector3 pos_, int[,] blockData_)
    {
        // 戻り値用のスコアを保存する変数
        int ret_score = 0;

        const int center_pos = 2;
        const int block_num = 4;

        Vector3[] blocks_pos = new Vector3[block_num];


        int num = 0;
        // ブロックの座標を算出
        for (int y = 0; y < BlocksDefinition.BLOCK_DATA_HEIGHT; ++y)
        {
            for (int x = 0; x < BlocksDefinition.BLOCK_DATA_WIDTH; ++x)
            {
                if (blockData_[y, x] == 1)
                {
                    Vector3 to_center_vec = Vector3.zero;
                    to_center_vec.x = x - center_pos;
                    to_center_vec.y = y - center_pos;

                    to_center_vec.y = -to_center_vec.y;

                    Vector3 pos = pos_;
                    pos.x += to_center_vec.x;
                    pos.y += to_center_vec.y;
                    pos.y = (StageController.STAGE_HEIGHT - 1) - pos.y;
                    pos.z = 0;
                    blocks_pos[num] = pos;
                    num++;
                }
            }
        }


        GameObject[,] tmp_stage_data = stageScript.StageBlockData;
        int[,] stage_data = new int[StageController.STAGE_HEIGHT, StageController.STAGE_WIDTH];

        // ステージの情報をint型に変換
        for (int y = 0; y < StageController.STAGE_HEIGHT; ++y)
        {
            for (int x = 0; x < StageController.STAGE_WIDTH; ++x)
            {
                if (tmp_stage_data[y,x] != null)
                {
                    stage_data[y, x] = 1;
                }
                else
                {
                    stage_data[y, x] = 0;
                }
            }
        }

        // 自身の上にブロックがあるかどうかを調べる
        foreach (Vector3 block_pos in blocks_pos)
        {
            if (block_pos.x >= StageController.STAGE_WIDTH
                || block_pos.x < 0)
            {
                continue;
            }

            if (block_pos.y - 1 >= StageController.STAGE_HEIGHT
                || block_pos.y - 1 < 0)
            {
                continue;
            }

            if (stage_data[(int)block_pos.y - 1, (int)block_pos.x] == 1)
            {
                ret_score += 500;
            }
        }


        // 仮のステージに保存する
        foreach (Vector3 block_pos in blocks_pos)
        {
            if (block_pos.x < 0 || block_pos.x >= StageController.STAGE_WIDTH)  continue;
            if (block_pos.y < 0 || block_pos.y >= StageController.STAGE_HEIGHT) continue;
            
            stage_data[(int)block_pos.y, (int)block_pos.x] = 1;
        }


        // 1列揃うかどうか
        for (int y = 0; y < StageController.STAGE_HEIGHT; ++y)
        {
            for (int x = 0; x < StageController.STAGE_WIDTH; ++x)
            {
                //1つでもnullのオブジェクトがあれば次の行を調べる
                if (stage_data[y, x] == 0) break;

                // 1行すべてにブロックがあった場合
                if (x == StageController.STAGE_WIDTH - 1)
                {
                    ret_score += eraseOneLineScore;
                }
            }
        }

        // 端っこか
        foreach (Vector3 block_pos in blocks_pos)
        {
            // ステージの中心
            const int stage_center_pos = StageController.STAGE_WIDTH / 2;

            // ステージの中心から離れているほど得点が上がる
            ret_score += (int)Mathf.Abs(block_pos.x - stage_center_pos);
        }

        // ステージの下のほうにあればあるほど得点が上がる
        foreach (Vector3 block_pos in blocks_pos)
        {
            ret_score += (int)block_pos.y;
        }

        // 自身の下にブロックがなかった場合
        foreach (Vector3 block_pos in blocks_pos)
        {
            if (block_pos.x >= StageController.STAGE_WIDTH
                || block_pos.x < 0)
            {
                continue;
            }
            
            if (block_pos.y + 1 >= StageController.STAGE_HEIGHT
                || block_pos.y + 1 < 0)
            {
                continue;
            }

            if (stage_data[(int)block_pos.y + 1, (int)block_pos.x] == 0)
            {
                ret_score += unfilledHolesScore;
            }
        }

        // 縦3マスの穴ができないか
        foreach (Vector3 block_pos in blocks_pos)
        {
            Vector3 right_pos = new Vector3(block_pos.x + 1, block_pos.y, block_pos.z);

            if (right_pos.y >= StageController.STAGE_HEIGHT
                || right_pos.y < 0) 
            {
                continue;
            }
            // もし右が壁かブロックの場合continue
            if (right_pos.x >= StageController.STAGE_WIDTH
                || stage_data[(int)right_pos.y, (int)right_pos.x] == 1)
            {
                continue;
            }
            // 何もなければ
            else
            {
                // さらにその右を見て、壁かブロックなら
                if (right_pos.x + 1 >= StageController.STAGE_WIDTH
                 || stage_data[(int)right_pos.y, (int)right_pos.x + 1] == 1)
                {
                    
                    // 下二つが空か確かめる
                    for(int i = 1; i < 3; ++i)
                    {
                        // もし壁かブロックがあるなら終了
                        if (right_pos.y + i >= StageController.STAGE_HEIGHT
                            || stage_data[(int)right_pos.y + i, (int)right_pos.x] == 1)
                        {
                            break;
                        }

                        // 下二つが空なら3段の穴ができるので得点を下げる
                        if (i == 2)
                        {
                            ret_score += vertical3HolesScore;
                        }
                    }

                }
            }


            Vector3 left_pos = new Vector3(block_pos.x - 1, block_pos.y, block_pos.z);

            // もし左が壁かブロックの場合continue
            if (left_pos.x < 0
                || stage_data[(int)left_pos.y, (int)left_pos.x] == 1)
            {
                continue;
            }
            // 何もなければ
            else
            {
                // さらにその左を見て、壁かブロックなら
                if ((left_pos.x - 1) < 0
                 || stage_data[(int)left_pos.y, (int)left_pos.x - 1] == 1)
                {

                    // 下二つが空か確かめる
                    for (int i = 1; i < 3; ++i)
                    {
                        // もし壁かブロックがあるなら終了
                        if (left_pos.y + i >= StageController.STAGE_HEIGHT
                            || stage_data[(int)left_pos.y + i, (int)left_pos.x] == 1)
                        {
                            break;
                        }

                        // 下二つが空なら3段の穴ができるので得点を下げる
                        if (i == 2)
                        {
                            ret_score += vertical3HolesScore;
                        }
                    }

                }
            }

        }


        return ret_score;
    }


    private bool CanMove(Vector3 pos_, int[,] blockData_)
    {
        int block_width = 0;
        List<Vector3> destination_pos = new List<Vector3>();

        // 目的地を追加
        destination_pos.Add(pos_);

        for (int x = 0; x < BlocksDefinition.BLOCK_DATA_HEIGHT; ++x)
        {
            for(int y = 0; y < BlocksDefinition.BLOCK_DATA_WIDTH; ++y)
            {
                if (blockData_[y,x] == 1)
                {
                    block_width++;
                    break;
                }
            }
        }

        Vector3 pos = pos_;

        // 着地地点から上にいけるか
        for (int i = 0; i < StageController.STAGE_HEIGHT - (int)pos_.y; ++i)
        {
            pos.y++;
            // もし真上に動けない場合
            if (stageScript.AbleMove(ref pos, ref blockData_) == false)
            {
                bool can_avoided = false;
                // ブロックの左右に移動できるか調べる
                for (int j = 1; j <= block_width; ++j)
                {
                    Vector3 right_pos = pos;
                    Vector3 left_pos = pos;

                    right_pos.x += j;
                    if (stageScript.AbleMove(ref right_pos, ref blockData_) == true)
                    {
                        pos = right_pos;
                        destination_pos.Insert(0, pos);
                        can_avoided = true;
                        break;
                    }

                    left_pos.x -= j;
                    if (stageScript.AbleMove(ref left_pos, ref blockData_) == true)
                    {
                        pos = left_pos;
                        destination_pos.Insert(0, pos);
                        can_avoided = true;
                        break;
                    }
                }

                if (can_avoided == false) return false;
            }

        }

        destinationPos = new List<Vector3>(destination_pos);
        return true;
    }

}