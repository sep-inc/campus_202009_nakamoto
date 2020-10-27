using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SgapeSphere : MonoBehaviour
{
    [SerializeField] private float radius = 1;

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
