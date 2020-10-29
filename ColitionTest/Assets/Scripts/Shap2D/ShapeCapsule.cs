using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ShapeCapsule : Shape2D
{
    [SerializeField] private GameObject line_start = default;
    [SerializeField] private GameObject line_end   = default;
    [SerializeField] private float      radius     = 1f;


    public Vector2 StartPos => line_start.transform.position;
    public Vector2 EndPos => line_end.transform.position;
    public float Radius => radius;


    public override bool IsJudgable(Shape2DList shape_)
    {
        switch (shape_)
        {
            case Shape2DList.SHAPE_CAPSULE_2D:
            case Shape2DList.SHAPE_CIRCLE:
                return true;

            default:
                break;
        }

        return false;
    }

    public override Shape2D.Shape2DList GetShape() { return Shape2DList.SHAPE_CAPSULE_2D; }

    public override bool HitTest(Shape2D shape_)
    {
        switch (shape_.GetShape())
        {
            case Shape2DList.SHAPE_CAPSULE_2D:
                {
                    ShapeCapsule capsule = (ShapeCapsule)shape_;
                    if (HitTest(capsule) == true)
                    {
                        return true;
                    }
                }
                break;

            case Shape2DList.SHAPE_CIRCLE:
                {
                    ShapeCircle circle = (ShapeCircle)shape_;

                    if (My.Collition2D.CheckCircleCapsule(circle, this) == true)
                    {
                        return true;
                    }
                }
                break;

            default:
                break;
        }

        return false;
    }


    public bool HitTest(ShapeCapsule other)
    {

        float A_CD = MyMath.CalcPointLineDist(line_start.transform.position, other.line_start.transform.position, other.line_end.transform.position);
        float B_CD = MyMath.CalcPointLineDist(line_end.transform.position, other.line_start.transform.position, other.line_end.transform.position);
        float C_AB = MyMath.CalcPointLineDist(other.line_start.transform.position, line_start.transform.position, line_end.transform.position);
        float D_AB = MyMath.CalcPointLineDist(other.line_end.transform.position, line_start.transform.position, line_end.transform.position);

        float min_distance = Mathf.Min(A_CD, B_CD, C_AB, D_AB);
        float distance = radius + other.radius;
        if (min_distance <= distance)
        {
            return true;
        }
        
        return false;
    }
    

    public Vector3 GetLineCenterPos()
    {
        Vector3 ret_center_pos = Vector3.zero;

        ret_center_pos.x = (line_start.transform.position.x + line_end.transform.position.x) / 2f;
        ret_center_pos.y = (line_start.transform.position.y + line_end.transform.position.y) / 2f;

        return ret_center_pos;
    }
    

    private void OnDrawGizmos()
    {
        Vector3 start_to_end = line_end.transform.position - line_start.transform.position;
        Vector3 left_vec = new Vector3(-start_to_end.y, start_to_end.x, 0f);
        left_vec.Normalize();

        Vector3 s_a = line_start.transform.position + (left_vec * radius);
        Vector3 e_a = s_a + (start_to_end.normalized * start_to_end.magnitude);


        Vector2 s_b = Vector2.one;
        s_b.x = line_start.transform.position.x - (left_vec.x * radius);
        s_b.y = line_start.transform.position.y - (left_vec.y * radius);

        Gizmos.color = Color.green;
        Gizmos.DrawWireSphere(line_start.transform.position, 0.1f);
        Gizmos.DrawWireSphere(line_end.transform.position, 0.1f);
        Gizmos.DrawWireSphere(line_start.transform.position, radius);
        Gizmos.DrawWireSphere(line_end.transform.position, radius);
        Gizmos.DrawLine(line_start.transform.position, line_end.transform.position);
        Gizmos.DrawLine(line_start.transform.position + (left_vec * radius), line_end.transform.position + (left_vec * radius));
        Gizmos.DrawLine(line_start.transform.position - (left_vec * radius), line_end.transform.position - (left_vec * radius));
    }
}
