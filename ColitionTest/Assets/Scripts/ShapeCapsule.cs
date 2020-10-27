using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ShapeCapsule : MonoBehaviour
{
    [SerializeField] private GameObject line_start = default;
    [SerializeField] private GameObject line_end   = default;
    [SerializeField] private float      radius     = 1f;


    public bool HitTest(ShapeCapsule other)
    {

        float A_CD = CalcPointLineDist(line_start.transform.position, other.line_start.transform.position, other.line_end.transform.position);
        float B_CD = CalcPointLineDist(line_end.transform.position, other.line_start.transform.position, other.line_end.transform.position);
        float C_AB = CalcPointLineDist(other.line_start.transform.position, line_start.transform.position, line_end.transform.position);
        float D_AB = CalcPointLineDist(other.line_end.transform.position, line_start.transform.position, line_end.transform.position);

        float min_distance = Mathf.Min(A_CD, B_CD, C_AB, D_AB);
        float distance = radius + other.radius;
        if (min_distance <= distance)
        {
            return true;
        }
        
        return false;
    }


    float CalcPointLineDist(Vector2 p, Vector2 lineStart_, Vector2 lineEnd_)
    {
        float a = lineEnd_.x - lineStart_.x;
        float b = lineEnd_.y - lineStart_.y;
        float a2 = a * a;
        float b2 = b * b;
        float r2 = a2 + b2;
        float tt = -(a * (lineStart_.x - p.x) + b * (lineStart_.y - p.y));

        if (tt < 0)
        {
            return Mathf.Sqrt((lineStart_.x - p.x) * (lineStart_.x - p.x) + (lineStart_.y - p.y) * (lineStart_.y - p.y));
        }
        else if(tt > r2)
        {
            return Mathf.Sqrt((lineEnd_.x - p.x) * (lineEnd_.x - p.x) + (lineEnd_.y - p.y) * (lineEnd_.y - p.y));
        }

        float f1 = a * (lineStart_.y - p.y) - b * (lineStart_.x - p.x);
        return Mathf.Sqrt((f1 * f1) / r2);
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
