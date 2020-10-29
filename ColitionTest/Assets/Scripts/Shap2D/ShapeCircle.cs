using System.Collections;
using System.Collections.Generic;
using System.Security.Cryptography;
using UnityEngine;

public class ShapeCircle : Shape2D
{
    // Start is called before the first frame update
    [SerializeField] float radius = 1f;

    public float Radius => radius;

    public override bool IsJudgable(Shape2DList shape_)
    {
        switch (shape_)
        {
            case Shape2DList.SHAPE_CAPSULE_2D:
            case Shape2DList.SHAPE_CIRCLE:
            case Shape2DList.SHAPE_LINE:
            case Shape2DList.SHAPE_RECT:
                return true;

            default:
                break;
        }

        return false;
    }

    public override Shape2DList GetShape() { return Shape2DList.SHAPE_CIRCLE; }

    public override bool HitTest(Shape2D shape_)
    {
        switch (shape_.GetShape())
        {
            case Shape2DList.SHAPE_CIRCLE:
                {
                    ShapeCircle circle = (ShapeCircle)shape_;

                    if (HitTest(circle) == true)
                    {
                        return true;
                    }
                }
                break;

            case Shape2DList.SHAPE_RECT:
                {
                    ShapeRect rect = (ShapeRect)shape_;
                    if (My.Collition2D.ChecCircleRect(this, rect) == true)
                    {
                        return true;
                    }
                }
                break;

            case Shape2DList.SHAPE_LINE:
                {
                    ShapeLine line = (ShapeLine)shape_;
                    if (My.Collition2D.CheckCircleLine(this, line) == true)
                    {
                        return true;
                    }
                }
                break;

            case Shape2DList.SHAPE_CAPSULE_2D:
                {
                    ShapeCapsule capsule = (ShapeCapsule)shape_;
                    if (My.Collition2D.CheckCircleCapsule(this, capsule) == true)
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


    public bool HitTest(ShapeCircle other)
    {
        Vector2 to_other_vec = other.transform.position - transform.position;

        if (to_other_vec.magnitude <= radius + other.radius)
        {
            return true;
        }

        return false;
    }

    private void OnDrawGizmos()
    {
        Gizmos.DrawWireSphere(transform.position, radius);
    }
}
