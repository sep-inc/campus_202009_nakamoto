using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public abstract class Shape2D : MonoBehaviour
{
    public enum Shape2DList
    {

        SHAPE_CIRCLE,       // 円
        SHAPE_RECT,         // 矩形 
        SHAPE_CAPSULE_2D,   // 2Dカプセル
        SHAPE_LINE,         // 線2D
    }

    // 形を返す関数
    abstract public Shape2DList GetShape();

    // 当たり判定を行う関数
    abstract public bool HitTest(Shape2D shape_);

    // 当たり判定を行うかどうかを決める関数
    abstract public bool IsJudgable(Shape2DList shape_);
}
