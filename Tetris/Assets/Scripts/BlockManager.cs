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
    //private GameObject StockBlock = null;
    // ストック中のブロックの場所を保存する変数
   // [SerializeField] GameObject StockBlockPoint = null;


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
            OperationBlock = NextBlock[0];
            OperationBlock.transform.position = StartBlockPoint.transform.position;
            NextBlock[0] = null;

            OperationBlockScript = OperationBlock.GetComponent<Block>();
        }

        // 次に落ちてくるブロック1番目が空なら
        if (NextBlock[0] == null)
        {
            NextBlock[0] = NextBlock[1];
            NextBlock[0].transform.position = NextBlockPoint[0].transform.position;
            NextBlock[1] = NextBlock[2];
            NextBlock[1].transform.position = NextBlockPoint[1].transform.position;

            NextBlock[2] = CreateBlock(NextBlockPoint[2].transform.position);

        }

        if (OperationBlockScript) OperationBlockScript.MyUpdate();

        if (OperationBlockScript && OperationBlockScript.IsLanding())
        {
            OperationBlock = null;
            OperationBlockScript = null;
        }

    }

    
    private GameObject CreateBlock(Vector3 pos_)
    {
        GameObject gameObject = Instantiate(BlockPrefab, pos_, Quaternion.identity);

        Block block = gameObject.GetComponent<Block>();
        block.Create(BlocksDefinition.BlockListArray[Random.Range(0, 7)]);

        return gameObject;
    }
}
