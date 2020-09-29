using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Bar : MonoBehaviour
{
    
    [SerializeField]
    float Speed = 0;

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

            if (transform.position.x >= 85)
            {
                Vector3 vector = transform.position;
                vector.x = 85;
                transform.position = vector;
            }
        }

        // 左キーが入力されたら
        if (Input.GetKey(KeyCode.LeftArrow))
        {
            transform.Translate(-Speed * Time.deltaTime, 0, 0);

            if (transform.position.x <= -90)
            {
                Vector3 vector = transform.position;
                vector.x = -90;
                transform.position = vector;
            }
        }

    }

    

}
