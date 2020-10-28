using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ShapeAABB : Shape3D
{
    [SerializeField] private Vector3 size = Vector3.one;
    private Vector3 min;
    private Vector3 max;


    public Vector3 Min => min;
    public Vector3 Max => max;

    public override bool HitTest(Shape3D shape_)
    {
        switch (shape_.GetShape())
        {
            case Shape3DList.SHAPE_AABB:
                {
                    ShapeAABB shapeAABB = (ShapeAABB)shape_;
                    if (HitTest(shapeAABB) == true)
                    {
                        return true;
                    }
                }
                break;

            case Shape3DList.SHAPE_SPHERE:
                {
                    SgapeSphere sgapeSphere = (SgapeSphere)shape_;
                    if (My.Collition3D.CheckSphereAABB(sgapeSphere, this) == true)
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


    public override Shape3DList GetShape() { return Shape3DList.SHAPE_AABB; }
    

    public bool HitTest(ShapeAABB other)
    {
        if (min.x > other.max.x) return false;
        if (max.x < other.min.x) return false;
        if (min.y > other.max.y) return false;
        if (max.y < other.min.y) return false;
        if (min.z > other.max.z) return false;
        if (max.z < other.min.z) return false;
        
        return true;
    }
    
    private void OnDrawGizmos()
    {
        max = transform.position + (size / 2f);
        min = transform.position - (size / 2f);
     
        Gizmos.DrawWireCube(transform.position, size);
        Gizmos.DrawWireSphere(transform.position - size/2, 0.2f);
        Gizmos.DrawWireSphere(transform.position + size/2, 0.2f);
    }
}
