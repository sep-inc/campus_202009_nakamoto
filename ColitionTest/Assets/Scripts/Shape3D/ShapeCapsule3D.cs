using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ShapeCapsule3D : Shape3D
{
    [SerializeField] private GameObject line_end = default;
    [SerializeField] private float radius = 1f;


    public Vector3 EndPos => line_end.transform.position;
    public float Radius => radius;


    public override Shape3DList GetShape() { return Shape3DList.SHAPE_CAPSULE_3D; }


    public override bool IsJudgable(Shape3DList shape_)
    {
        switch (shape_)
        {
            case Shape3DList.SHAPE_CAPSULE_3D:
            case Shape3DList.SHAPE_SPHERE:
                return true;

            default:
                break;
        }

        return false;
    }


    public override bool HitTest(Shape3D shape_)
    {
        switch(shape_.GetShape())
        {
            case Shape3DList.SHAPE_CAPSULE_3D:
                {
                    ShapeCapsule3D capsule3D = (ShapeCapsule3D)shape_;
                    if (HitTest(capsule3D) == true)
                    {
                        return true;
                    }
                }
                break;

            case Shape3DList.SHAPE_SPHERE:
                {
                    SgapeSphere sgapeSphere = (SgapeSphere)shape_;
                    if (My.Collition3D.CheckSphereCapsule(sgapeSphere, this) == true)
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


    public bool HitTest(ShapeCapsule3D other)
    {
        // 自分の原点から相手の原点から終点までの線の最短距離を算出
        float A_CD = MyMath.CalcPointLineDist(transform.position, other.transform.position, other.line_end.transform.position);
        // 自分の終点から相手の原点から終点までの線の最短距離を算出
        float B_CD = MyMath.CalcPointLineDist(line_end.transform.position, other.transform.position, other.line_end.transform.position);
        // 相手の原点から自分の原点から終点までの線の最短距離を算出
        float C_AB = MyMath.CalcPointLineDist(other.transform.position, transform.position, line_end.transform.position);
        // 相手の原点から自分の原点から終点までの線の最短距離を算出
        float D_AB = MyMath.CalcPointLineDist(other.line_end.transform.position, transform.position, line_end.transform.position);

        // 一番距離が短いのを採用する
        float min_distance = Mathf.Min(A_CD, B_CD, C_AB, D_AB);

        // お互いの半径を足したものを算出
        float sum_radius = radius + other.radius;

        // 一番距離が短い線がお互いの半径を足したもの以下なら当たり
        if (min_distance <= sum_radius)
        {
            return true;
        }

        return false;
    }


    public Vector3 GetLineCenterPos()
    {
        Vector3 ret_center_pos = Vector3.zero;

        ret_center_pos.x = (transform.position.x + line_end.transform.position.x) / 2f;
        ret_center_pos.y = (transform.position.y + line_end.transform.position.y) / 2f;
        ret_center_pos.z = (transform.position.z + line_end.transform.position.z) / 2f;

        return ret_center_pos;
    }


    private void OnDrawGizmos()
    {
        Vector3 start_to_end = line_end.transform.position - transform.position;
        Vector3 left_vec = new Vector3(-start_to_end.y, start_to_end.x, 0f);
        left_vec.Normalize();

        Vector3 s_a = transform.position + (left_vec * radius);
        Vector3 e_a = s_a + (start_to_end.normalized * start_to_end.magnitude);


        Vector2 s_b = Vector2.one;
        s_b.x = transform.position.x - (left_vec.x * radius);
        s_b.y = transform.position.y - (left_vec.y * radius);

        Gizmos.color = Color.green;
        Gizmos.DrawWireSphere(transform.position, 0.1f);
        Gizmos.DrawWireSphere(line_end.transform.position, 0.1f);
        Gizmos.DrawWireSphere(transform.position, radius);
        Gizmos.DrawWireSphere(line_end.transform.position, radius);
        Gizmos.DrawLine(transform.position, line_end.transform.position);
        Gizmos.DrawLine(transform.position + (left_vec * radius), line_end.transform.position + (left_vec * radius));
        Gizmos.DrawLine(transform.position - (left_vec * radius), line_end.transform.position - (left_vec * radius));
    }
}
