using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BlockManager : MonoBehaviour
{
    [SerializeField] GameObject BlockPrefab = null;

    // 操作中のブロックを保存する変数
    private GameObject OperationBlock = null;
    private Block OperationBlockScript = null;
    // 操作するブロックの最初の場所を保存する変数
    [SerializeField] GameObject StartBlockPoint = null;

    // 次に落ちてくるブロックを保存する変数
    private GameObject[] NextBlock = null;
    // 次に落ちてくるブロックの場所を保存する変数
    [SerializeField] GameObject[] NextBlockPoint = null;

    // ストック中のブロックを保存する変数
    private GameObject StockBlock = null;
    // ストック中のブロックの場所を保存する変数
    [SerializeField] GameObject StockBlockPoint = null;


    // Start is called before the first frame update
    void Start()
    {
        NextBlock = new GameObject[3];

        // 次に生成されるオブジェクトの初期化
        for (int i = 0; i < NextBlockPoint.Length; ++i)
        {
            NextBlock[i] = CreateBlock(NextBlockPoint[i].transform.position);
        }
    }

    // Update is called once per frame
    void Update()
    {
        // もしブロック生成したときに動けなかった場合ゲームオーバー
        if (OperationBlockScript)
        {
            if (OperationBlockScript.CannotMove() == true)
            {
                SceneController.LoadNextScene();
            }
        }

        // 操作しているブロックがなかった場合
        if (OperationBlock == null)
        {
            // 次に落ちてくるブロックの1番目を持ってくる
            OperationBlock = NextBlock[0];
            OperationBlock.transform.position = StartBlockPoint.transform.position;
            NextBlock[0] = null;

            // コンポーネントを取得しておく
            OperationBlockScript = OperationBlock.GetComponent<Block>();
        }

        // 次に落ちてくるブロックの1番目が空なら
        if (NextBlock[0] == null)
        {
            // 1番目に2番目を入れる
            NextBlock[0] = NextBlock[1];
            NextBlock[0].transform.position = NextBlockPoint[0].transform.position;

            // 2番目に3番目を入れる
            NextBlock[1] = NextBlock[2];
            NextBlock[1].transform.position = NextBlockPoint[1].transform.position;

            // 3番目のブロックを生成する
            NextBlock[2] = CreateBlock(NextBlockPoint[2].transform.position);

        }

        // 操作中のブロックの更新を行う
        if (OperationBlockScript) OperationBlockScript.MyUpdate();

        // 操作中のブロックが着地した場合操作できないようにする
        if (OperationBlockScript && OperationBlockScript.IsLanding())
        {
            OperationBlock = null;
            OperationBlockScript = null;
        }


        // ストック
        Stock();

    }

    
    // ブロックをランダムで生成する関数
    private GameObject CreateBlock(Vector3 pos_)
    {
        GameObject gameObject = Instantiate(BlockPrefab, pos_, Quaternion.identity);

        Block block = gameObject.GetComponent<Block>();
        block.Create(BlocksDefinition.BlockListArray[Random.Range(0, 7)]);

        return gameObject;
    }


    // ブロックのストック
    private void Stock()
    {
        if (Input.GetKeyDown(KeyCode.S) == false) return;

        // ストックが空かどうかを調べる
        if (StockBlock == null) {
            // 空の場合ストックに入れて操作中ブロックをストックに保存する
            StockBlock = OperationBlock;
            StockBlock.transform.position = StockBlockPoint.transform.position;

            OperationBlock = null;
            OperationBlockScript = null;
        }
        else
        {
            // ストックがすでにある場合交換する

            GameObject temp = StockBlock;

            StockBlock = OperationBlock;
            StockBlock.transform.position = StockBlockPoint.transform.position;

            OperationBlock = temp;
            OperationBlock.transform.position = StartBlockPoint.transform.position;
            OperationBlockScript = OperationBlock.GetComponent<Block>();
        }

    }
}
