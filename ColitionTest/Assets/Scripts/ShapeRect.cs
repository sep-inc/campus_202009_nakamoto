using System.Collections;
using System.Collections.Generic;
using System.Drawing;
using UnityEngine;

public class ShapeRect : MonoBehaviour
{
    [SerializeField] private Vector2 size = Vector2.one;

    public bool HitTest(ShapeRect other)
    {
        Vector2 to_other_vec = other.transform.position - transform.position;
        if (to_other_vec.x < 0f) to_other_vec.x = -to_other_vec.x;
        if (to_other_vec.y < 0f) to_other_vec.y = -to_other_vec.y;

         Vector2 size_1 = new Vector2((size.x + other.size.x) / 2, (size.y + other.size.y) / 2);

        if (to_other_vec.x < size_1.x
            && to_other_vec.y < size_1.y)
        {
            return true;
        }

        return false;
    }


    private void OnDrawGizmos()
    {
        Gizmos.DrawWireCube(transform.position, size);

    }
}
