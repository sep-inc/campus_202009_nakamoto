using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SgapeSphere : Shape3D
{
    [SerializeField] private float radius = 1;

    public float Radius => radius;


    
    public override bool IsJudgable(Shape3DList shape_)
    {
        switch (shape_)
        {
            case Shape3DList.SHAPE_AABB:
            case Shape3DList.SHAPE_CAPSULE_3D:
            case Shape3DList.SHAPE_SEGMENT:
            case Shape3DList.SHAPE_SPHERE:
                return true;

            default:
                break;
        }

        return false;
    }



    public override bool HitTest(Shape3D shape_)
    {
        switch (shape_.GetShape())
        {
            case Shape3DList.SHAPE_CAPSULE_3D:
                {
                    ShapeCapsule3D capsule3D = (ShapeCapsule3D)shape_;

                    if (My.Collition3D.CheckSphereCapsule(this, capsule3D) == true)
                    {
                        return true;
                    } 
                }
                break;

            case Shape3DList.SHAPE_AABB:
                {
                    ShapeAABB shapeAABB = (ShapeAABB)shape_;
                    if (My.Collition3D.CheckSphereAABB(this, shapeAABB) == true)
                    {
                        return true;
                    }
                }
                break;

            case Shape3DList.SHAPE_SEGMENT:
                {
                    ShapeSegment shapeSegment  = (ShapeSegment)shape_;
                    if (My.Collition3D.CheckSphereSegment(this, shapeSegment) == true)
                    {
                        return true;
                    }
                }
                break;

            case Shape3DList.SHAPE_SPHERE:
                {
                    SgapeSphere sgapeSphere = (SgapeSphere)shape_;
                    if (HitTest(sgapeSphere) == true)
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


    public override Shape3DList GetShape() { return Shape3DList.SHAPE_SPHERE; }


    public bool HitTest(SgapeSphere other)
    {
        Vector3 to_other_vec = other.transform.position - transform.position;

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
