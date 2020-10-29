using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ShapeLine : Shape2D
{
    [SerializeField] private GameObject line_end   = default;

    public Vector2 EndPos => line_end.transform.position;

    public override bool IsJudgable(Shape2DList shape_)
    {
        switch (shape_)
        {
            case Shape2DList.SHAPE_CIRCLE:
            case Shape2DList.SHAPE_LINE:
                return true;

            default:
                break;
        }

        return false;
    }


    public override Shape2DList GetShape() { return Shape2DList.SHAPE_LINE; }

    public override bool HitTest(Shape2D shape_)
    {
        switch (shape_.GetShape())
        {
            case Shape2DList.SHAPE_LINE:
                {
                    ShapeLine line = (ShapeLine)shape_;
                    if (HitTest(line) == true)
                    {
                        return true;
                    }
                }
                break;

            case Shape2DList.SHAPE_CIRCLE:
                {
                    ShapeCircle circle = (ShapeCircle)shape_;

                    if (My.Collition2D.CheckCircleLine(circle, this) == true)
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

    public bool HitTest(ShapeLine other)
    {
        // 始点から終点までのベクトルを算出
        Vector2 start_to_end         = new Vector2(line_end.transform.position.x - transform.position.x, line_end.transform.position.y - transform.position.y);

        // 自身の始点から相手の始点までのベクトルを算出
        Vector2 start_to_othre_start = new Vector2(other.transform.position.x - transform.position.x, other.transform.position.y - transform.position.y);

        // 自身の始点から相手の終点までのベクトルを算出
        Vector2 start_to_othre_end   = new Vector2(other.line_end.transform.position.x - transform.position.x, other.line_end.transform.position.y - transform.position.y);

        float dot1 = MyMath.Vec2Cross(start_to_end, start_to_othre_start);
        float dot2 = MyMath.Vec2Cross(start_to_end, start_to_othre_end);

       
        if (dot1 * dot2 >= 0)
        {
            return false;
        }

        start_to_end         = new Vector2(other.line_end.transform.position.x - other.transform.position.x, other.line_end.transform.position.y - other.transform.position.y);
        start_to_othre_start = new Vector2(transform.position.x - other.transform.position.x, transform.position.y - other.transform.position.y);
        start_to_othre_end   = new Vector2(line_end.transform.position.x - other.transform.position.x, line_end.transform.position.y - other.transform.position.y);

        dot1 = MyMath.Vec2Cross(start_to_end, start_to_othre_start);
        dot2 = MyMath.Vec2Cross(start_to_end, start_to_othre_end);

        if (dot1 * dot2 < 0)
        {
            return true;
        }

        return false;
    }

    
    private void OnDrawGizmos()
    {

        Gizmos.color = Color.green;
        Gizmos.DrawWireSphere(transform.position, 0.1f);
        Gizmos.DrawWireSphere(line_end.transform.position, 0.1f);
        Gizmos.DrawLine(transform.position, line_end.transform.position);
    }
}
