using System.Collections;
using System.Collections.Generic;
using System.Security.Cryptography;
using UnityEngine;

public class ShapeCircle : MonoBehaviour, Shape
{
    // Start is called before the first frame update
    [SerializeField] float radius = 1f;

    public bool HitTest(ShapeCircle other)
    {
        Vector2 to_other_vec = other.transform.position - transform.position;

        if (to_other_vec.magnitude <= radius + other.radius)
        {
            return true;
        }

        return false;
    }

    public ShapeList GetShape() { return ShapeList.SHAPE_CIRCLE; }


    private void OnDrawGizmos()
    {
        Gizmos.DrawWireSphere(transform.position, radius);
    }
}
