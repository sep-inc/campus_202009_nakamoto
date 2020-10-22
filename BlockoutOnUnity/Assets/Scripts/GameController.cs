using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
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
    int remainNum = 0;

    // ボールの発射キーを表示するためのtextオブジェクト
    [SerializeField]
    GameObject start_text  = null;

    // ブロック配列
    private GameObject[] block_array;

    // ブロックの数を保存する変数
    private int block_num;

    // ボールが発射されたかどうかを保存する変数
    private bool is_ball_start;

    public static string result_string;


    // Start is called before the first frame update
    void Start()
    {
        is_ball_start = false;
        start_text.SetActive(true);

        // ブロックの数をタグをみて保存する
        block_num = GameObject.FindGameObjectsWithTag("Block").Length;

        // ブロックの配列を初期化
        block_array = GameObject.FindGameObjectsWithTag("Block");
    }   

    // Update is called once per frame
    void Update()
    {
        // ブロックが0になったらゲームクリア
        if (block_num == 0)
        {
                       
            // ボールに通知する
            ball.GetComponent<Ball>().NotifyGameClear();

            result_string = "ゲームクリア！！";

            // 次のシーンに遷移
            SceneContoller.LoadNextScene();
            return;
        }
        // 残機が0になったらゲームオーバー
        else if (remainNum == 0)
        {            
            // 生きているブロックに通知する
            for(int i = 0; i < block_array.Length; ++i)
            {
                if (block_array[i] == null)
                {
                    continue;
                }

                block_array[i].GetComponent<Block>().NotifyGameOver();
            }

            result_string = "ゲームオーバー";

            // 次のシーンに遷移
            SceneContoller.LoadNextScene();
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
        remainNum--;
        // 残機が0じゃなければボールを生成
        if (remainNum != 0)
        {
            is_ball_start = false;
            start_text.SetActive(true);

            Vector3 pos = bar.transform.position;
            pos.y += bar.transform.localScale.y;
            ball = Instantiate(ball, pos, Quaternion.identity);
            ball.GetComponent<Ball>().SetGameObject(gameObject, bar);
        }
    }


    // ブロックが死んだ歳この関数が呼ばれる
    public void NotifyBlockDead()
    {
        // ブロックの数を減らす
        block_num--;
    }
}
