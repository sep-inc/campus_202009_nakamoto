using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ShapeLine : MonoBehaviour
{
    [SerializeField] private GameObject line_start = default;
    [SerializeField] private GameObject line_end   = default;


    public bool HitTest(ShapeLine other)
    {
        // 始点から終点までのベクトルを算出
        Vector2 start_to_end         = new Vector2(line_end.transform.position.x - line_start.transform.position.x, line_end.transform.position.y - line_start.transform.position.y);

        // 自身の始点から相手の始点までのベクトルを算出
        Vector2 start_to_othre_start = new Vector2(other.line_start.transform.position.x - line_start.transform.position.x, other.line_start.transform.position.y - line_start.transform.position.y);

        // 自身の始点から相手の終点までのベクトルを算出
        Vector2 start_to_othre_end   = new Vector2(other.line_end.transform.position.x - line_start.transform.position.x, other.line_end.transform.position.y - line_start.transform.position.y);

        float dot1 = MyMath.Vec2Cross(start_to_end, start_to_othre_start);
        float dot2 = MyMath.Vec2Cross(start_to_end, start_to_othre_end);

       
        if (dot1 * dot2 >= 0)
        {
            return false;
        }

        start_to_end         = new Vector2(other.line_end.transform.position.x - other.line_start.transform.position.x, other.line_end.transform.position.y - other.line_start.transform.position.y);
        start_to_othre_start = new Vector2(line_start.transform.position.x - other.line_start.transform.position.x, line_start.transform.position.y - other.line_start.transform.position.y);
        start_to_othre_end   = new Vector2(line_end.transform.position.x - other.line_start.transform.position.x, line_end.transform.position.y - other.line_start.transform.position.y);

        dot1 = MyMath.Vec2Cross(start_to_end, start_to_othre_start);
        dot2 = MyMath.Vec2Cross(start_to_end, start_to_othre_end);

        if (dot1 * dot2 < 0)
        {
            return true;
        }

        return false;
    }

    public Vector2 GetLineCenterPos()
    {
        Vector2 ret_center_pos = Vector2.one;

        ret_center_pos.x = (line_start.transform.position.x + line_end.transform.position.x) / 2f;
        ret_center_pos.y = (line_start.transform.position.y + line_end.transform.position.y) / 2f;

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
