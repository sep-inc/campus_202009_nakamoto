using System;
using System.Collections;
using System.Collections.Generic;
using System.Security.Cryptography;
using UnityEngine;
using UnityEngine.UIElements;

public class StageController : MonoBehaviour
{ 
    [SerializeField] GameObject Stage = null;
    public const int STAGE_WIDTH  = 10;
    public const int STAGE_HEIGHT = 20;

    // サウンド
    private AudioSource audioSource;

    // 落下サウンド
    [SerializeField] AudioClip fallSound;

    public GameObject[,] StageBlockData { get; private set; } = null;

    private void Start()
    {
        StageBlockData = new GameObject[STAGE_HEIGHT, STAGE_WIDTH];

        audioSource = GetComponent<AudioSource>();
    }
    
    // 移動可能かどうかを判定する関数
    public bool AbleMove(ref Vector3 pos_, ref int[,] blockData_)
    {

        const int block_num = 4;
        const int block_square_center_pos = 2;

        // 検索要素を算出
        Vector2[] search_index = new Vector2[block_num];
        int count = 0;
       
        for (int y = 0; y < BlocksDefinition.BLOCK_DATA_HEIGHT; ++y)
        {
            for(int x = 0; x < BlocksDefinition.BLOCK_DATA_WIDTH; ++x)
            {
                if (blockData_[y,x] == 1)
                {
                    search_index[count] = new Vector2(pos_.x + (x - block_square_center_pos), pos_.y + -(y - block_square_center_pos));

                    // 配列に変換
                    search_index[count].y = (STAGE_HEIGHT - 1) - search_index[count].y;
                    
                    count++;
                }
            }
        }

        foreach(Vector2 element in search_index)
        {
            // 左壁と当たっている場合
            if (element.x < 0) return false;
            // 右壁と当たっている場合
            if (element.x >= STAGE_WIDTH) return false;
            // 下の壁と当たっている場合
            if (element.y >= STAGE_HEIGHT) return false;
            // 上の壁と当たっている場合
            if (element.y < 0) continue;

            // ステージのブロックと重なっている場合
            if (StageBlockData[(int)element.y, (int)element.x] != null) return false;
        }

        // すべての条件に入らなければ移動可能
        return true;
    }


    public void SetBlock(GameObject[] block_)
    {
        const int stage_height = STAGE_HEIGHT - 1;

        foreach (GameObject element in block_)
        {
            if (element.transform.position.x >= STAGE_WIDTH) continue;
            else if (element.transform.position.x < 0) continue;
            if (element.transform.position.y >= STAGE_HEIGHT) continue;
            else if (element.transform.position.y < 0) continue;

            if (!element) continue;
            StageBlockData[stage_height - (int)element.transform.position.y, (int)element.transform.position.x] = element;
            element.transform.parent = Stage.transform;
        }
        
        // 消せるかどうかの判定
        CheckErase();
    }


    private void CheckErase()
    {
        // 削除する行を保存する変数
        List<int> erace_line = new List<int>();
        
        // 下の行から調べる
        for (int y = STAGE_HEIGHT -1; y >= 0 ; --y)
        {
            for(int x = 0; x < STAGE_WIDTH; ++x)
            {
                //1つでもnullのオブジェクトがあれば次の行を調べる
                if (StageBlockData[y, x] == null) break;

                // 1行すべてにブロックがあった場合その列をリストに追加
                if (x == STAGE_WIDTH - 1)
                {
                    erace_line.Add(y);
                }
            }
        }

        // もし消せる行があった場合
        if (erace_line.Count == 0) return;

        // 昇順でソートする
        erace_line.Sort();
        
        // erace_line.Sort();
        while (erace_line.Count != 0)
        {
            // 最初の要素を取得
            int line = erace_line[0];
        
            // オブジェクトを1行消す
            for(int i = 0; i < STAGE_WIDTH; ++i)
            {
                Destroy(StageBlockData[line, i]);
            }
            
            
            // 消した行より上の行を一段さげる
            for (int y = line - 1; y >= 0; --y)
            {
                for (int x = 0; x < STAGE_WIDTH; ++x)
                {
                    if (y >= STAGE_HEIGHT || y < 0) continue;
                    if (x >= STAGE_WIDTH  || x < 0) continue;
                        
                    StageBlockData[y + 1, x] = StageBlockData[y, x];
                    if (StageBlockData[y, x]) StageBlockData[y, x].transform.Translate(0, -1, 0, Space.World);
                }
            }
            
            // 消した行をリストから削除 
            erace_line.RemoveAt(0);
        }

        audioSource.PlayOneShot(fallSound);
    }


}
