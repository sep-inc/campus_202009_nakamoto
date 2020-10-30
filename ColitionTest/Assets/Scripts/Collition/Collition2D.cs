using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace My
{
    public class Collition2D
    {

        public static bool ChecCircleRect(ShapeCircle circle_, ShapeRect rect_)
        {
            // 円の中心点から矩形の四隅の一番近い点を保存する変数
            Vector2 near_pos = circle_.transform.position;

            // 円の中心点を保存する変数
            Vector2 circle_center_pos = circle_.transform.position;

            // 矩形の中心点を保存する変数
            Vector2 rect_center_pos = rect_.transform.position;

            // 円の中心点から矩形の一番近い点を探す
            if (circle_center_pos.x < rect_center_pos.x - rect_.Size.x / 2) near_pos.x = rect_center_pos.x - rect_.Size.x / 2;
            else if (circle_center_pos.x > rect_center_pos.x + rect_.Size.x / 2) near_pos.x = rect_center_pos.x + rect_.Size.x / 2;

            if (circle_center_pos.y < rect_center_pos.y - rect_.Size.y / 2) near_pos.y = rect_center_pos.y - rect_.Size.y / 2;
            else if (circle_center_pos.y > rect_center_pos.y + rect_.Size.y / 2) near_pos.y = rect_center_pos.y + rect_.Size.y / 2;


            float distance = Vector2.Distance(circle_center_pos, near_pos);


            if (distance < circle_.Radius)
            {
                return true;
            }

            return false;
        }


        public static bool CheckCircleLine(ShapeCircle circle_, ShapeLine line_)
        {
            // 線の原点から終点までのベクトル
            Vector2 start_to_end    = line_.EndPos - line_.StartPos;
            // 線の原点から円の中心点までのベクトル
            Vector2 start_to_center = (Vector2)circle_.transform.position - line_.StartPos;
            // 線の終点から円の中心点までのベクトル
            Vector2 end_to_center   = (Vector2)circle_.transform.position - line_.EndPos;
            // 線の原点から終点までのベクトルを正規化したベクトル
            Vector2 normal_start_to_end = start_to_end.normalized;

            // 点の中心から線に向けて射影した長さを算出
            float distance_projection = MyMath.Vec2Cross(start_to_center, normal_start_to_end);
            
            // 射影した長さが半径を超えていたら当たっていない
            if (Mathf.Abs(distance_projection) > circle_.Radius) return false;


            // 線を起点とした線の原点から円の中心点の角度と線の終点から円の中心点の角度が、
            // 鋭角と鈍角ともに存在していた場合あたっている
            if (Vector2.Dot(start_to_center, start_to_end) * Vector2.Dot(end_to_center, start_to_end) <= 0f)
            {
                return true;
            }
            else
            {
                // 線の原点から円の中心点の長さが円の半径よりも短かったら当たり
                // もしくは線の終点から円の中心点の長さが円の半径よりも短かったら当たり
                if (start_to_center.magnitude < circle_.Radius ||
                    end_to_center.magnitude < circle_.Radius)
                {
                    return true;
                }
            }

            return false;
        }


        // 円のカプセルの当たり判定
        public static bool CheckCircleCapsule(ShapeCircle circle_, ShapeCapsule capsule_)
        {
            // 線の原点から終点までのベクトル
            Vector2 start_to_end = capsule_.EndPos - capsule_.StartPos;
            // 線の原点から円の中心点までのベクトル
            Vector2 start_to_center = (Vector2)circle_.transform.position - capsule_.StartPos;
            // 線の終点から円の中心点までのベクトル
            Vector2 end_to_center = (Vector2)circle_.transform.position - capsule_.EndPos;
            // 線の原点から終点までのベクトルを正規化したベクトル
            Vector2 normal_start_to_end = start_to_end.normalized;
            // 円の半径とカプセルの半径を足した値
            float sum_radius = circle_.Radius + capsule_.Radius;

            // 点の中心から線に向けて射影した長さを算出
            float distance_projection = MyMath.Vec2Cross(start_to_center, normal_start_to_end);

            // 射影した長さが円とカプセルの半径を足したものを超えていたら当たっていない
            if (Mathf.Abs(distance_projection) > sum_radius) return false;


            // 線を起点とした線の原点から円の中心点の角度と線の終点から円の中心点の角度が、
            // 鋭角と鈍角ともに存在していた場合あたっている
            if (Vector2.Dot(start_to_center, start_to_end) * Vector2.Dot(end_to_center, start_to_end) <= 0f)
            {
                return true;
            }
            else
            {
                // 線の原点から円の中心点の長さが円とカプセルの半径を足したものよりも短かったら当たり
                // もしくは線の終点から円の中心点の長さが円とカプセルの半径を足したものよりも短かったら当たり
                if (start_to_center.magnitude < sum_radius ||
                    end_to_center.magnitude < sum_radius)
                {
                    return true;
                }
            }

            return false;
        }
    }
}