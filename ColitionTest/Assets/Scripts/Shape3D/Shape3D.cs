using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public abstract class Shape3D : MonoBehaviour
{
    public enum Shape3DList
    {

        SHAPE_SPHERE,       // 球
        SHAPE_AABB,         // AABB 
        SHAPE_CAPSULE_3D,   // 3Dカプセル
        SHAPE_SEGMENT,      // 線3D
    }

    // 形を返す関数
    abstract public Shape3DList GetShape();

    // 当たり判定を行う関数
    abstract public bool HitTest(Shape3D shape_);

    // 当たり判定を行うかどうかを決める関数
    abstract public bool IsJudgable(Shape3DList shape_);
}