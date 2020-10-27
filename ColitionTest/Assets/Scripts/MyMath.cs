using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MyMath
{
    public static float Vec2Cross(Vector2 vec1_, Vector2 vec2_)
    {
        float ret_dot_scalar = 0f;
        ret_dot_scalar = (vec1_.x * vec2_.y) - (vec2_.x * vec1_.y);

        return ret_dot_scalar;
    }

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
}
