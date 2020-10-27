﻿using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ShapeSegment : MonoBehaviour
{
    [SerializeField] private GameObject line_start = default;
    [SerializeField] private GameObject line_end = default;


    public bool HitTest(ShapeSegment other)
    {
        Vector3 line1 = line_end.transform.position - line_start.transform.position;
        Vector3 line2 = other.line_end.transform.position - other.line_start.transform.position;

        bool hit1 = MyMath.HitLineLine(line_start.transform.position, line1, other.line_start.transform.position, line2);
        bool hit2 = MyMath.HitLineLine(other.line_start.transform.position, line2, line_start.transform.position, line1);

        if (hit1 && hit2)
        {
            return true;
        }

        return false;
    }


    public Vector3 GetLineCenterPos()
    {
        Vector3 ret_center_pos = Vector2.one;

        ret_center_pos.x = (line_start.transform.position.x + line_end.transform.position.x) / 2f;
        ret_center_pos.y = (line_start.transform.position.y + line_end.transform.position.y) / 2f;
        ret_center_pos.z = (line_start.transform.position.z + line_end.transform.position.z) / 2f;

        return ret_center_pos;
    }


    private void OnDrawGizmos()
    {

        Gizmos.color = Color.green;
        Gizmos.DrawWireSphere(line_start.transform.position, 0.1f);
        Gizmos.DrawWireSphere(line_end.transform.position, 0.1f);
        Gizmos.DrawLine(line_start.transform.position, line_end.transform.position);
    }
}
