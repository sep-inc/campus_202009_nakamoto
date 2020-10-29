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

    abstract public Shape2DList GetShape();

    abstract public bool HitTest(Shape2D shape_);

    abstract public bool IsJudgable(Shape2DList shape_);
}
