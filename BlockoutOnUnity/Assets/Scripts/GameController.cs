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

    // ブロックの数を保存する変数
    public int Block_Num;

    // ゲームオーバー変数
    public bool GameOver { get; set; }

    // ゲームクリア変数
    public bool GameClear { get; set; }

    // 結果を表示するためのtextオブジェクト
    private GameObject result_text;


    // Start is called before the first frame update
    void Start()
    {
        GameOver = false;
        GameClear = false;

        // ブロックの数をタグをみて保存する
        Block_Num = GameObject.FindGameObjectsWithTag("Block").Length;

        result_text = GameObject.Find("ResultText");
    }   

    // Update is called once per frame
    void Update()
    {
        // ブロックが0になったらゲームクリア
        if (Block_Num == 0)
        {
            GameClear = true;
        }

        // もしゲームオーバーの場合ゲームオーバーと表示する
        if (GameOver)
        {
            Text text = result_text.GetComponent<Text>();
            text.text = "ゲームオーバー";
            result_text.SetActive(true);
            return;
        }

        // もしゲームクリアの場合ゲームクリアと表示する
        if (GameClear)
        {
            Text text = result_text.GetComponent<Text>();
            text.text = "ゲームクリア!!";
            result_text.SetActive(true);

            

            return;
        }

    }
    

    // ボールが死んだ際この関数が呼ばれる
    public void NotifyBallDead()
    {
        // 残機を減らす
        RemainNum--;
        // 残機が0になったらゲームオーバー
        if (RemainNum == 0)
        {
            GameOver = true;
        }
        else
        {
            // 残機が残っている場合ボールを生成する
            Vector3 pos = bar.transform.position;
            pos.y += bar.transform.localScale.y;
            Instantiate(ball, pos, Quaternion.identity);
        }
    }


    // ブロックが死んだ歳この関数が呼ばれる
    public void NotifyBlockDead()
    {
        // ブロックの数を減らす
        Block_Num--;
    }
}
