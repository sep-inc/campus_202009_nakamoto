using System.Collections;
using System.Collections.Generic;
using UnityEngine;

using UnityEngine.UI;

public class GameController : MonoBehaviour
{
    [SerializeField]
    GameObject ball = null;

    // バー
    [SerializeField]
    GameObject bar = null;

    // 残機
    [SerializeField]
    int RemainNum = 0;

    // 結果を表示するためのtextオブジェクト
    [SerializeField]
    GameObject result_text = null;

    // ボールの発射キーを表示するためのtextオブジェクト
    [SerializeField]
    GameObject start_text  = null;

    // ブロックの数を保存する変数
    public int Block_Num;

    // ボールが発射されたかどうかを保存する変数
    bool is_ball_start;

    // ゲームオーバー変数
    public bool GameOver { get; set; }


    // Start is called before the first frame update
    void Start()
    {
        GameOver = false;

        is_ball_start = false;
        start_text.SetActive(true);

        // ブロックの数をタグをみて保存する
        Block_Num = GameObject.FindGameObjectsWithTag("Block").Length;
    }   

    // Update is called once per frame
    void Update()
    {
        // ブロックが0になったらゲームクリア
        if (Block_Num == 0)
        {
            Text text = result_text.GetComponent<Text>();
            text.text = "ゲームクリア!!";
            result_text.SetActive(true);

            Ball ball_script = ball.GetComponent<Ball>();
            ball_script.NotifyGameClear();

            return;
        }

        // 残機が0になったらゲームオーバー
        if (RemainNum == 0)
        {
            Text text = result_text.GetComponent<Text>();
            text.text = "ゲームオーバー";
            result_text.SetActive(true);
            GameOver = true;

            return;
        }


        // もしボールが発射されていなければ
        if (is_ball_start == false)
        {
            // 発射テキストを表示
            start_text.SetActive(true);

            // スペースキーが押されたら
            if (Input.GetKeyDown(KeyCode.Space))
            {
                // 発射通知をボールに送る
                Ball ball_component = ball.GetComponent<Ball>();
                ball_component.NotifyFire();
                is_ball_start = true;

                start_text.SetActive(false);
            }
        }
    }
    

    // ボールが死んだ際この関数が呼ばれる
    public void NotifyBallDead()
    {
        // 残機を減らす
        RemainNum--;
        // 残機が0じゃなければボールを生成
        if (RemainNum != 0)
        {
            is_ball_start = false;
            start_text.SetActive(true);

            Vector3 pos = bar.transform.position;
            pos.y += bar.transform.localScale.y;
            ball = Instantiate(ball, pos, Quaternion.identity);
        }
    }


    // ブロックが死んだ歳この関数が呼ばれる
    public void NotifyBlockDead()
    {
        // ブロックの数を減らす
        Block_Num--;
    }
}
