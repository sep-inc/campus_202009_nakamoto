using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Bar : MonoBehaviour
{
    
    [SerializeField]
    float Speed = 0;

    // 移動範囲の左端
    [SerializeField]
    float move_range_min = 0;

    // 移動範囲の右端
    [SerializeField]
    float move_range_max = 0;

    new Rigidbody rigidbody;
    
    // Start is called before the first frame update
    void Start()
    {
        rigidbody = GetComponent<Rigidbody>();
    }

    // Update is called once per frame
    void Update()
    {
        // 右キーが入力されたら
        if (Input.GetKey(KeyCode.RightArrow))
        {
            transform.Translate(Speed * Time.deltaTime, 0, 0);

            if (transform.position.x >= move_range_max)
            {
                Vector3 vector = transform.position;
                vector.x = move_range_max;
                transform.position = vector;
            }
        }

        // 左キーが入力されたら
        if (Input.GetKey(KeyCode.LeftArrow))
        {
            transform.Translate(-Speed * Time.deltaTime, 0, 0);

            if (transform.position.x <= move_range_min)
            {
                Vector3 vector = transform.position;
                vector.x = move_range_min;
                transform.position = vector;
            }
        }

    }

    

}
