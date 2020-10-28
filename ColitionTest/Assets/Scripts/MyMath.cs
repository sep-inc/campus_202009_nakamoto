using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MyMath
{
    // 二次元の外積
    public static float Vec2Cross(Vector2 vec1_, Vector2 vec2_)
    {
        float ret_dot_scalar = 0f;
        ret_dot_scalar = (vec1_.x * vec2_.y) - (vec2_.x * vec1_.y);

        return ret_dot_scalar;
    }

    // 線分と線分の当たり判定
    public static bool HitLineLine(Vector3 lineStartA_, Vector3 lineEndA_, Vector3 lineStartB_, Vector3 lineEndB_)
    {
        Vector3 startA_to__startB = lineStartB_ - lineStartA_;
        Vector3 startA_to_endA = lineEndA_ - lineStartA_;
        Vector3 startB_to_endB = lineEndB_ - lineStartB_;

        Vector3 cross1 = Vector3.Cross(startA_to_endA, startB_to_endB);

        float plana_factor = Vector3.Dot(startA_to__startB, cross1);

        if (Mathf.Abs(plana_factor) < 0.0001f && cross1.sqrMagnitude > 0.0001f)
        {
            return true;
        }

        return false;
    }


    // 点と線の最短距離を返す関数
    public static float CalcPointLineDist(Vector3 p, Vector3 lineStart_, Vector3 lineEnd_)
    {
        Vector3 start_to_end = lineEnd_ - lineStart_;
        float length = start_to_end.magnitude;
        start_to_end.Normalize();
        float k = Vector3.Dot(p - lineStart_, start_to_end);
        k = Mathf.Clamp(k, 0, length);

        Vector3 a = lineStart_ + k * start_to_end;

        return Vector3.Distance(a, p);
    }
    
    
}
