using System.Collections;
using System.Collections.Generic;
using UnityEngine;

using UnityEngine.UI;

public class Ball : MonoBehaviour
{
    // 速度　1秒間ですすむ速度
    [SerializeField]
    float Speed = 0f;

    private bool once;

    private GameObject bar;

    private GameObject start_text;

    new Rigidbody rigidbody;

    private GameObject game_controller;
    private GameController controller_component;

    // Start is called before the first frame update
    void Start()
    {
        // Rigidbodyを取得
        rigidbody = GetComponent<Rigidbody>();

        once = false;

        // バーオブジェクトを探す
        bar = GameObject.Find("Bar");

        start_text = GameObject.Find("StartText");
        
        // バーと親子関係にする
        transform.parent = bar.gameObject.transform;

        game_controller = GameObject.Find("GameController");
        controller_component = game_controller.GetComponent<GameController>();
    }

    // Update is called once per frame
    void Update()
    {
        // 始めの一度だけ
        if (once == false)
        {
            // スペースキーが押されたら
            if (Input.GetKeyDown(KeyCode.Space))
            {
                // textを削除
                start_text.SetActive(false);

                // バーとの親子関係を解消する
                transform.parent = null;

                // 右斜めに力を加える
                rigidbody.AddForce(new Vector3(10f, 10f, 0f) * Speed);

                once = true;
            }
        }

        // クリアしたらこのオブジェクトを消す
        if (controller_component.GameClear)
        {
            Destroy(gameObject);
        }
    }

    private void OnCollisionEnter(Collision collision)
    {
        // もし下の壁と当たったら
        if (collision.gameObject.tag == "DeadWall")
        {

            // ボールが死んだことをゲーム管理クラスに伝える
            controller_component.NotifyBallDead();
            start_text.SetActive(true);

            // このオブジェクトを削除
            Destroy(gameObject);
        }
    }


}
