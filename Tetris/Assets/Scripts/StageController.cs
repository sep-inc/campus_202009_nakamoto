using System.Collections;
using System.Collections.Generic;
using System.Security.Cryptography;
using UnityEngine;
using UnityEngine.UIElements;

public class StageController : MonoBehaviour
{
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
;                   search_range[count] = new Vector2(pos_.x + (x - 2), pos_.y + (y - 2));
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
        block_.transform.parent = this.transform;
    }

}
