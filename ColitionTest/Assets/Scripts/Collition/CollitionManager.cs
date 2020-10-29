using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CollitionManager : MonoBehaviour
{
    [SerializeField] Shape2D[] shape2D_list = default;
    [SerializeField] Shape3D[] shape3D_list = default;



    private void OnDrawGizmos()
    {
        // 2Dのオブジェクト同士の当たり判定
        for (int i = 0; i < shape2D_list.Length; ++i)
        {
            for (int j = i + 1; j < shape2D_list.Length; ++j)
            {
                if (shape2D_list[i].IsJudgable(shape2D_list[j].GetShape()) == false) continue;
                Gizmos.color = shape2D_list[i].HitTest(shape2D_list[j]) ? Color.red : Color.white;
                Gizmos.DrawLine(shape2D_list[i].transform.position, shape2D_list[j].transform.position);
            }
        }


        // 3Dのオブジェクト同士の当たり判定
        for (int i = 0; i < shape3D_list.Length; ++i)
        {
            for (int j = i + 1; j < shape3D_list.Length; ++j)
            {
                if (shape3D_list[i].IsJudgable(shape3D_list[j].GetShape()) == false) continue;
                Gizmos.color = shape3D_list[i].HitTest(shape3D_list[j]) ? Color.red : Color.white;
                Gizmos.DrawLine(shape3D_list[i].transform.position, shape3D_list[j].transform.position);
            }
        }

    }
}
