using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BlockManager : MonoBehaviour
{
    [SerializeField] GameObject BlockPrefab = null;
    [SerializeField] GameObject StagecontrollerObject = null;
    private StageController stageControllerScript = null;

    // 操作中のブロックを保存する変数
    public GameObject OperationBlock { get; private set; } = null;
    private Block OperationBlockScript = null;

    // 操作するブロックの最初の場所を保存する変数
    [SerializeField] GameObject StartBlockPoint = null;

    // 次に落ちてくるブロックを保存する変数
    private GameObject[] nextBlocks = null;
    // 次に落ちてくるブロックの場所を保存する変数
    [SerializeField] GameObject[] NextBlockPoint = null;

    // ストック中のブロックを保存する変数
    public GameObject StockBlock { get; private set; } = null;
    // ストック中のブロックの場所を保存する変数
    [SerializeField] GameObject StockBlockPoint = null;

    public bool cannotCreate { get; private set; } = false;

    public GameObject NextBlock => nextBlocks[0];

    // ブロックの影
    [SerializeField] GameObject shadowObject = null;
    private const int SHADOW_BLOCK_NUM = 4;
    private GameObject[] blockShadow = null;

    private bool gameStarted = false;


    // Start is called before the first frame update
    void Start()
    {
        nextBlocks = new GameObject[NextBlockPoint.Length];

        // 次に生成されるオブジェクトの初期化
        for (int i = 0; i < NextBlockPoint.Length; ++i)
        {
            nextBlocks[i] = this.CreateBlock(NextBlockPoint[i].transform.position);
        }

        stageControllerScript = StagecontrollerObject.GetComponent<StageController>();

        blockShadow = new GameObject[SHADOW_BLOCK_NUM];
        // 影オブジェクトの生成
        for (int i = 0; i < SHADOW_BLOCK_NUM; ++i)
        {
            blockShadow[i] = Instantiate(shadowObject, Vector3.zero, Quaternion.identity, transform);
        }
    }

    // Update is called once per frame
    void Update()
    {
        if (gameStarted == false) return;

        // もしブロック生成したときに動けなかった場合ゲームオーバー
        if (OperationBlockScript)
        {
            if (OperationBlockScript.CannotMove() == true)
            {
                cannotCreate = true;
                return;
            }
        }

        // 操作しているブロックがなかった場合
        if (OperationBlock == null)
        {
            // 次に落ちてくるブロックの1番目を持ってくる
            OperationBlock = nextBlocks[0];
            OperationBlock.transform.position = StartBlockPoint.transform.position;
            nextBlocks[0] = null;

            // コンポーネントを取得しておく
            OperationBlockScript = OperationBlock.GetComponent<Block>();
        }

        // 次に落ちてくるブロックの1番目が空なら
        if (nextBlocks[0] == null)
        {
            for(int i = 0; i < nextBlocks.Length - 1; ++i)
            {
                // 上にずらす
                nextBlocks[i] = nextBlocks[i + 1];
                nextBlocks[i].transform.position = NextBlockPoint[i].transform.position;
            }

            // 最後のブロックを生成する
            nextBlocks[nextBlocks.Length - 1] = CreateBlock(NextBlockPoint[nextBlocks.Length - 1].transform.position);

        }

        // 操作中のブロックの更新を行う
        if (OperationBlockScript) OperationBlockScript.MyUpdate();


        // 操作中のブロックが着地した場合操作できないようにする
        if (OperationBlockScript && OperationBlockScript.IsLanding())
        {
            OperationBlock = null;
            OperationBlockScript = null;
        }

        
        // 操作しているブロックがある場合落下地点に影を付ける
        if (OperationBlock != null)
        {

            // 現在のブロックデータを取得する
            int[,] block_data = OperationBlockScript.BlockData;
            Vector3 pos = OperationBlock.transform.position;
            const int center_pos = 2;

            // 現在の位置からの落下地点を予測する
            //bool tmp = false;
            for(int y = (int)pos.y; y >= 0; --y)
            {
                pos.y = y;

                // Yがステージの高さを超えていた時の処理
                if (pos.y >= StageController.STAGE_HEIGHT) continue;

                // 移動できなくなったら
                if (stageControllerScript.AbleMove(ref pos, ref block_data) == false)
                {
                    // 1つ前の座標を保存する
                    pos.y += 1;
                    break;
                }
            }

            // 落下地点でのブロックの座標を求める
            Vector3[] blocks_pos = new Vector3[4];
            int num = 0;

            for (int y = 0; y < BlocksDefinition.BLOCK_DATA_HEIGHT; ++y)
            {
                for (int x = 0; x < BlocksDefinition.BLOCK_DATA_WIDTH; ++x)
                {
                    if (block_data[y, x] == 1)
                    {
                        Vector3 to_center_vec = Vector3.zero;
                        to_center_vec.x = x - center_pos;
                        to_center_vec.y = y - center_pos;

                        to_center_vec.y = -to_center_vec.y;

                        Vector3 tem_pos = pos;
                        tem_pos.x += to_center_vec.x;
                        tem_pos.y += to_center_vec.y;
                        tem_pos.z = pos.z;
                        blocks_pos[num] = tem_pos;
                        num++;
                    }
                }
            }

            int count = 0;
            foreach(Vector3 block_pos in blocks_pos)
            {
                blockShadow[count].transform.position = block_pos;
                count++;
            }

        }

        // Sキーが押されたらブロックをストックする
        if (Input.GetKeyDown(KeyCode.S))
        {
            // ストック
            Stock();
        }


    }

    
    // ブロックをランダムで生成する関数
    private GameObject CreateBlock(Vector3 pos_)
    {
        // ブロックの生成
        GameObject gameObject = Instantiate(BlockPrefab, pos_, Quaternion.identity);

        // スクリプトの取得
        Block block = gameObject.GetComponent<Block>();

        // ブロックの初期化
        block.Create((BlocksDefinition.BlockList)Random.Range(0, (int)BlocksDefinition.BlockList.BLOCK_NUM), StagecontrollerObject);

        return gameObject;
    }


    // ブロックのストック
    public void Stock()
    {
        // ストックが空かどうかを調べる
        if (StockBlock == null) {
            // 空の場合ストックに入れて操作中ブロックをストックに保存する
            StockBlock = OperationBlock;
            StockBlock.transform.position = StockBlockPoint.transform.position;
            
            OperationBlock = nextBlocks[0];
            OperationBlock.transform.position = StartBlockPoint.transform.position;
            nextBlocks[0] = null;

            // コンポーネントを取得しておく
            OperationBlockScript = OperationBlock.GetComponent<Block>();
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

    public void NoticeGameStart()
    {
        gameStarted = true;
    }
}
