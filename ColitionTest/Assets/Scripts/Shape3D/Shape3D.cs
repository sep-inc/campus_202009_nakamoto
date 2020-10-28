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

    abstract public Shape3DList GetShape();

    abstract public bool HitTest(Shape3D shape_);
}