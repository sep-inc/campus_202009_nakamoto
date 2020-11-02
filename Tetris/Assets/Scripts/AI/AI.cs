using System.Collections;
using System.Collections.Generic;
using System.Runtime.InteropServices.WindowsRuntime;
using Unity.Collections.LowLevel.Unsafe;
using UnityEngine;

public class AI : MonoBehaviour
{
    [SerializeField] GameObject stageControllerObject;
    [SerializeField] GameObject blockManager;

    private GameObject[,] stageData;
    private StageController stageScript;
    private GameObject block;
    private Block blockScript;

    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        
    }



    // おける場所を検索する
    private List<Vector3>　FindAbleMove()
    {
        // 戻り値用
        List<Vector3> ret_vector = new List<Vector3>();

        // ブロックの当たりデータを取得
        int[,] block_data = blockScript.BlockData;

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
        for (int x = min_x; x <= max_x; ++x)
        {
            for(int y = StageController.STAGE_HEIGHT - 1; y >= 0; --y)
            {
                Vector3 pos = new Vector3(x, y, 0);
                if (stageScript.AbleMove(ref pos, ref block_data) == false)
                {
                    // いけなかった一つ上の段を保存する
                    ret_vector.Add(new Vector3(x, y + 1, 0));

                    break;
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
        for(int y = 0; y < BlocksDefinition.BLOCK_DATA_HEIGHT; ++y)
        {
            for(int x = 0; x < BlocksDefinition.BLOCK_DATA_WIDTH; ++y)
            {
                if (blockData_[y,x] == 1)
                {
                    // 中心からのベクトル
                    Vector3 center_to_pos = new Vector3(x - center_pos, y - center_pos, 0);
                    blocks_pos[num] = pos_ + center_to_pos;
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

        // 仮のステージに保存する
        foreach (Vector3 block_pos in blocks_pos)
        {
            stage_data[(StageController.STAGE_HEIGHT - 1) - (int)block_pos.y, (int)block_pos.x] = 1;
        }


        // 1列揃うかどうか
        for (int y = 0; y < StageController.STAGE_HEIGHT; ++y)
        {
            for (int x = 0; x < StageController.STAGE_WIDTH; ++x)
            {
                //1つでもnullのオブジェクトがあれば次の行を調べる
                if (stage_data[y, x] == 1) break;

                // 1行すべてにブロックがあった場合その列をリストに追加
                if (x == StageController.STAGE_WIDTH - 1)
                {
                    ret_score += 100;
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

        // ステージの下のほうにあればあるほど得点が上がるa
        foreach (Vector3 block_pos in blocks_pos)
        {
            ret_score += (int)block_pos.y;
        }

        // 自身の下にブロックがなかった場合
        foreach (Vector3 block_pos in blocks_pos)
        {
            if (block_pos.x + 1 >= StageController.STAGE_HEIGHT) continue;
            if (stage_data[(int)block_pos.y + 1, (int)block_pos.x] == 0)
            {
                ret_score -= 50;
            }
        }


        return ret_score;
    }


}