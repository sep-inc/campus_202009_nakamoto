using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BlockManager : MonoBehaviour
{
    [SerializeField] GameObject BlockPrefab = null;

    // 操作中のブロックを保存する変数
   // private GameObject OperationBlock = null;
    // 操作するブロックの最初の場所を保存する変数
   // [SerializeField] GameObject StartBlockPoint = null;

    // 次に落ちてくるブロックを保存する変数
    public GameObject[] NextBlock = null;
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
            Debug.Log(NextBlockPoint[i]);
            NextBlock[i] = CreateBlock(NextBlockPoint[i].transform.position);
            // if (NextBlockPoint[i]) NextBlock[i] = CreateBlock(NextBlockPoint[i].transform.position);
        }
    }

    // Update is called once per frame
    void Update()
    {
        
        
    }

    
    private GameObject CreateBlock(Vector3 pos_)
    {
        GameObject gameObject = Instantiate(BlockPrefab, pos_, Quaternion.identity);

        Block block = gameObject.GetComponent<Block>();
        block.Create(BlocksDefinition.BlockListArray[Random.Range(0, 7)]);

        return gameObject;
    }
}
