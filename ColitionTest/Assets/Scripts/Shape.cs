using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public enum ShapeList
{
    SHAPE_CIRCLE,       // 円
    SHAPE_RECT,         // 矩形
    SHAPE_LINE,         // 線2D
    SHAPE_CAPSULE_2D,   // 2Dカプセル
    SHAPE_SPHERE,       // 球
    SHAPE_AABB,         // AABB 
    SHAPE_CAPSULE_3D,   // 3Dカプセル
    SHAPE_SEGMENT,      // 線3D
}

public interface Shape
{
    ShapeList GetShape();
}