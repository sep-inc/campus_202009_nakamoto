using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace My
{
    public class Collition2D
    {

        public static bool ChecCircleRect(ShapeCircle circle_, ShapeRect rect_)
        {
            Vector2 near_pos = circle_.transform.position;
            Vector2 circle_center_pos = circle_.transform.position;
            Vector2 rect_center_pos = rect_.transform.position;


            // 円の中心点から矩形の一番近い点を探す
            if (circle_center_pos.x < rect_center_pos.x - rect_.Size.x) near_pos.x = rect_center_pos.x - rect_.Size.x;
            else if (circle_center_pos.x > rect_center_pos.x + rect_.Size.x) near_pos.x = rect_center_pos.x + rect_.Size.x;

            if (circle_center_pos.y < rect_center_pos.y - rect_.Size.y) near_pos.y = rect_center_pos.y - rect_.Size.y;
            else if (circle_center_pos.y > rect_center_pos.y + rect_.Size.y) near_pos.y = rect_center_pos.y + rect_.Size.y;


            float distance = Vector2.Distance(circle_center_pos, near_pos);

            if (distance < circle_.Radius)
            {
                return true;
            }

            return false;
        }


        public static bool CheckCircleLine(ShapeCircle circle_, ShapeLine line_)
        {
            float distance = MyMath.CalcPointLineDist(circle_.transform.position, line_.StartPos, line_.EndPos);

            if (distance < circle_.Radius)
            {
                return true;
            }

            return false;
        }


        public static bool CheckCircleCapsule(ShapeCircle circle_, ShapeCapsule capsule_)
        {
            float distance = MyMath.CalcPointLineDist(circle_.transform.position, capsule_.StartPos, capsule_.EndPos);

            if (distance < circle_.Radius + capsule_.Radius)
            {
                return true;
            }

            return false;
        }
    }
}