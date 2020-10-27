using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Foo : MonoBehaviour
{
    public delegate void MyCallback(string msg);

    // 円
    [SerializeField] private ShapeCircle shape1 = default;
    [SerializeField] private ShapeCircle shape2 = default;

    // 矩形
    [SerializeField] private ShapeRect rect1 = default;
    [SerializeField] private ShapeRect rect2 = default;

    // 線分
    [SerializeField] private ShapeLine line1 = default;
    [SerializeField] private ShapeLine line2 = default;

    // カプセル
    [SerializeField] private ShapeCapsule capsule1 = default;
    [SerializeField] private ShapeCapsule capsule2 = default;

    // 球
    [SerializeField] private SgapeSphere sphere1 = default;
    [SerializeField] private SgapeSphere sphere2 = default;

    // AABB
    [SerializeField] private ShapeAABB aabb1 = default;
    [SerializeField] private ShapeAABB aabb2 = default;

    // 線分3D
    [SerializeField] private ShapeSegment segment1 = default;
    [SerializeField] private ShapeSegment segment2 = default;

    // カプセル3D
    [SerializeField] private ShapeCapsule3D capsule3D1 = default;
    [SerializeField] private ShapeCapsule3D capsule3D2 = default;


    private void OnDrawGizmos()
    {
        Vector2 vec = shape1.transform.position - shape2.transform.position;

        if (vec.magnitude <= 10f)
        {
            // 矩形と矩形の当たり判定
            Gizmos.color = shape1.HitTest(shape2) ? Color.red : Color.white;
            Gizmos.DrawLine(shape1.transform.position, shape2.transform.position);
        }
        

        // 円と円の当たり判定
        Gizmos.color = rect1.HitTest(rect2) ? Color.red : Color.white;
        Gizmos.DrawLine(rect1.transform.position, rect2.transform.position);
       

        // 線分と線分の当たり判定
        Gizmos.color = line1.HitTest(line2) ? Color.red : Color.white;
        Gizmos.DrawLine(line1.GetLineCenterPos(), line2.GetLineCenterPos());

        // カプセルとカプセルの当たり判定
        Gizmos.color = capsule1.HitTest(capsule2) ? Color.red : Color.white;
        Gizmos.DrawLine(capsule1.GetLineCenterPos(), capsule2.GetLineCenterPos());


        // 球と球の当たり判定 
        Gizmos.color = sphere1.HitTest(sphere2) ? Color.red : Color.white;
        Gizmos.DrawLine(sphere1.transform.position, sphere2.transform.position);


        // 矩形と矩形の当たり判定
        Gizmos.color = aabb1.HitTest(aabb2) ? Color.red : Color.white;
        Gizmos.DrawLine(aabb1.transform.position, aabb2.transform.position);

        // 線分と線分の当たり判定3D
        Gizmos.color = segment1.HitTest(segment2) ? Color.red : Color.white;
        Gizmos.DrawLine(segment1.GetLineCenterPos(), segment2.GetLineCenterPos());

        // カプセル3Dとカプセル3Dの当たり判定
        Gizmos.color = capsule3D1.HitTest(capsule3D2) ? Color.red : Color.white;
        Gizmos.DrawLine(capsule3D1.GetLineCenterPos(), capsule3D2.GetLineCenterPos());
    }
}