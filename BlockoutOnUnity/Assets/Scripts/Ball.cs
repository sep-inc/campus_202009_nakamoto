using System.Collections;
using System.Collections.Generic;
using UnityEngine;

using UnityEngine.UI;

public class Ball : MonoBehaviour
{
    // 速度　1秒間ですすむ速度
    [SerializeField]
    float speed = 0f;

    [SerializeField]
    GameObject bar;

    [SerializeField]
    GameObject game_controller;

    new Rigidbody rigidbody;

    // Start is called before the first frame update
    void Start()
    {
        // Rigidbodyを取得
        rigidbody = GetComponent<Rigidbody>();
        
        // バーと親子関係にする
        transform.parent = bar.gameObject.transform;
    }

    // Update is called once per frame
    void Update()
    {
    }


    // ボール生成直後にゲームコントローラーとバーをセットするための関数
    public void SetGameObject(GameObject gameController_, GameObject bar_)
    {
        game_controller = gameController_;
        bar = bar_;
    }

    // ボールの発射通知がきたら発射する
    public void NotifyFire()
    {
        // バーとの親子関係を解消する
        transform.parent = null;

        // 右斜めに力を加える
        rigidbody.AddForce(new Vector3(10f, 10f, 0f) * speed);
    }

    // ゲームクリア通知を受け取った時の処理
    public void NotifyGameClear()
    {
        // このオブジェクトを消す
        Destroy(gameObject);
    }

    private void OnCollisionEnter(Collision collision)
    {
        // もし下の壁と当たったら
        if (collision.gameObject.tag == "DeadWall")
        {

            // ボールが死んだことをゲーム管理クラスに伝える
            game_controller.GetComponent<GameController>().NotifyBallDead();

            // このオブジェクトを削除
            Destroy(gameObject);
        }
    }

}
