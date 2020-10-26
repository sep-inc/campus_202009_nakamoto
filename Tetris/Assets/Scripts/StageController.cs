using System;
using System.Collections;
using System.Collections.Generic;
using System.Security.Cryptography;
using UnityEngine;
using UnityEngine.UIElements;

public class StageController : MonoBehaviour
{ 
    [SerializeField] GameObject Stage = null;
    private GameObject[,] OnStageBlockData = null;
    const int STAGE_WIDTH  = 10;
    const int STAGE_HEIGHT = 20;

    private void Start()
    {
        OnStageBlockData = new GameObject[STAGE_HEIGHT, STAGE_WIDTH];
    }
    
    // 移動可能かどうかを判定する関数
    public bool AableMove(ref Vector3 pos_, ref int[,] blockData_)
    {
        // 検索範囲を算出
        Vector2[] search_range = new Vector2[4];
        int count = 0;
       
        for (int y = 0; y < 5; ++y)
        {
            for(int x = 0; x < 5; ++x)
            {
                if (blockData_[y,x] == 1)
                {
;                   search_range[count] = new Vector2(pos_.x + (x - 2), pos_.y + -(y - 2));
                    search_range[count].y = 19 - search_range[count].y;
                    count++;
                }
            }
        }

        foreach(Vector2 element in search_range)
        {
            // 左壁と当たっている場合
            if (element.x < 0) return false;
            // 右壁と当たっている場合
            if (element.x >= STAGE_WIDTH) return false;

            if (element.y < 0) continue;
            if (element.y >= STAGE_HEIGHT) return false;

            if (OnStageBlockData[(int)element.y, (int)element.x] != null) return false;
        }

        return true;
    }


    public void SetBlock(GameObject block_)
    {
        OnStageBlockData[19 - (int)block_.transform.position.y, (int)block_.transform.position.x] = block_;
        block_.transform.parent = Stage.transform;
        
        // 消せるかどうかの判定
        CheckErase();
    }


    private void CheckErase()
    {
        List<int> erace_line = new List<int>();
        
        // 下の行から調べる
        for (int y = STAGE_HEIGHT -1; y >= 0 ; --y)
        {
            for(int x = 0; x < STAGE_WIDTH; ++x)
            {
                //1つでもnullのオブジェクトがあれば次の行を調べる
                if (OnStageBlockData[y, x] == null) break;

                // 1行すべてにブロックがあった場合その列をリストに追加
                if (x == STAGE_WIDTH - 1)
                {
                    erace_line.Add(y);
                }
            }
        }

        // もし消せる行があった場合
        if (erace_line.Count == 0) return;



       while(erace_line.Count != 0)
       {
           // 最初の要素を取得
           int line = erace_line[0];
       
           for(int i = 0; i < STAGE_WIDTH; ++i)
           {
               Destroy(OnStageBlockData[line, i]);
           }
       
           //for(int y = line - 1; y <= 0; --y)
           //{
           //    for(int x = 0; x < STAGE_WIDTH; ++x)
           //    {
           //        OnStageBlockData[y + 1, x] = OnStageBlockData[y, x];
           //        if (OnStageBlockData[y, x]) OnStageBlockData[y, x].transform.Translate(0, -1, 0, Space.World);
           //    }
           //}
       
           erace_line.RemoveAt(0);
       }        
        
        
    
    }


}
