using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ShapeCapsule3D : MonoBehaviour
{
    [SerializeField] private GameObject line_start = default;
    [SerializeField] private GameObject line_end = default;
    [SerializeField] private float radius = 1f;


    public bool HitTest(ShapeCapsule3D other)
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


    float CalcPointLineDist(Vector3 p, Vector3 lineStart_, Vector3 lineEnd_)
    {
        Vector3 start_to_end = lineEnd_ - lineStart_;
        float length = start_to_end.magnitude;
        start_to_end.Normalize();
        float k = Vector3.Dot(p - lineStart_, start_to_end);
        k = Mathf.Clamp(k, 0, length);

        Vector3 a = lineStart_ + k * start_to_end;

        return Vector3.Distance(a, p);
    }


    public Vector3 GetLineCenterPos()
    {
        Vector3 ret_center_pos = Vector3.zero;

        ret_center_pos.x = (line_start.transform.position.x + line_end.transform.position.x) / 2f;
        ret_center_pos.y = (line_start.transform.position.y + line_end.transform.position.y) / 2f;
        ret_center_pos.z = (line_start.transform.position.z + line_end.transform.position.z) / 2f;

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
