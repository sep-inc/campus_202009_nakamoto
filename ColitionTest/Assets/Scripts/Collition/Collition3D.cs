using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace My
{
    public class Collition3D
    {

        public static bool CheckSphereAABB(SgapeSphere sphere_, ShapeAABB aabb_)
        {
            // 球の中心点から一番近いAABBの点を探す
            Vector3 near_pos = sphere_.transform.position;

            if (near_pos.x < aabb_.Min.x)      near_pos.x = aabb_.Min.x;
            else if (near_pos.x > aabb_.Max.x) near_pos.x = aabb_.Max.x;

            if (near_pos.y < aabb_.Min.y) near_pos.y = aabb_.Min.y;
            else if (near_pos.y > aabb_.Max.y) near_pos.y = aabb_.Max.y;

            if (near_pos.z < aabb_.Min.z) near_pos.z = aabb_.Min.z;
            else if (near_pos.z > aabb_.Max.z) near_pos.z = aabb_.Max.z;

            // 一番近いAABBの点から球の中心点までの距離を算出
            float near_pos_to_center_pos = Vector3.Distance(near_pos, sphere_.transform.position);

            if (near_pos_to_center_pos < sphere_.Radius)
            {
                return true;
            }
           
            return false;
        }


        public static bool CheckSphereSegment(SgapeSphere sphere_, ShapeSegment segment_)
        {
            float distance = MyMath.CalcPointLineDist(sphere_.transform.position, segment_.StartPos, segment_.EndPos);

            if (distance < sphere_.Radius)
            {
                return true;
            }

            return false;
        }


        public static bool CheckSphereCapsule(SgapeSphere sphere_, ShapeCapsule3D capsule_)
        {
            float distance = MyMath.CalcPointLineDist(sphere_.transform.position, capsule_.StartPos, capsule_.EndPos);

            if (distance < sphere_.Radius + capsule_.Radius)
            {
                return true;
            }

            return false;
        }
    }
}