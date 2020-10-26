using System;
using System.Collections;
using System.Collections.Generic;
using UnityEditor;
using UnityEngine;

public class Block : MonoBehaviour
{
    [SerializeField] GameObject StageControllerObj = null;
    private StageController StageControllerScript = null;

    [SerializeField] GameObject BlockCell = null;
    private GameObject[] BlockObject;
    private int[,] BlockData;
    private Color BlockColor;

    private float FallTimer = 0f;
    private float FallInterval = 1f;

    // ブロック着地したかどうかを保存する変数
    private bool is_landing = false;

    private void Start()
    {
        StageControllerObj = GameObject.Find("StageManager");
        StageControllerScript = StageControllerObj.GetComponent<StageController>();
    }

    /*
        ブロック初期化関数
        生成時に1度だけ呼ぶ
    */
    public void Create(BlocksDefinition.BlockList block_)
    {
        BlockObject = new GameObject[4];

        switch (block_)
        {
            case BlocksDefinition.BlockList.BLOCK_I:
                BlockData = BlockShapeI.GetBlockData();
                BlockColor = BlockShapeI.GetBlockColor();
                break;
            case BlocksDefinition.BlockList.BLOCK_J:
                BlockData = BlockShapeJ.GetBlockData();
                BlockColor = BlockShapeJ.GetBlockColor();
                break;
            case BlocksDefinition.BlockList.BLOCK_L:
                BlockData = BlockShapeL.GetBlockData();
                BlockColor = BlockShapeL.GetBlockColor();
                break;
            case BlocksDefinition.BlockList.BLOCK_O:
                BlockData = BlockShapeO.GetBlockData();
                BlockColor = BlockShapeO.GetBlockColor();
                break;
            case BlocksDefinition.BlockList.BLOCK_S:
                BlockData = BlockShapeS.GetBlockData();
                BlockColor = BlockShapeS.GetBlockColor();
                break;
            case BlocksDefinition.BlockList.BLOCK_T:
                BlockData = BlockShapeT.GetBlockData();
                BlockColor = BlockShapeT.GetBlockColor();
                break;
            case BlocksDefinition.BlockList.BLOCK_Z:
                BlockData = BlockShapeZ.GetBlockData();
                BlockColor = BlockShapeZ.GetBlockColor();
                break;
            default:
                break;
        }


        int create_count = 0;
        for (int y = 0; y < 5; ++y)
        {
            for (int x = 0; x < 5; ++x)
            {
                if (BlockData[y, x] == 1)
                {
                    Vector3 to_center_vec = Vector3.zero;
                    to_center_vec.x = x - 2;
                    to_center_vec.y = y - 2;

                    to_center_vec.y = -to_center_vec.y;

                    Vector3 pos = transform.position;
                    pos.x += to_center_vec.x;
                    pos.y += to_center_vec.y;
                    BlockObject[create_count] = Instantiate(BlockCell, pos, Quaternion.identity, this.transform);
                    BlockObject[create_count].GetComponent<MeshRenderer>().material.color = BlockColor;
                    create_count++;
                }
            }

            if (create_count == 4) break;
        }


    }
    // 着地したかどうかを返す関数
    public bool IsLanding() { return is_landing; }


    public void MyUpdate()
    {
        Fall();

        Rotate();

        Move();
    }

    // 落下処理
    private void Fall()
    {
        // タイマーを進める
        FallTimer += Time.deltaTime;

        // 下キーが押されていたら落下間隔を短くする
        FallInterval = Input.GetKey(KeyCode.DownArrow) ? .05f : 1f;

     
        if (FallTimer > FallInterval)
        {
            // 次に落ちる座標を算出する
            Vector3 next_pos = transform.position;
            next_pos.y--;

            // 落ちた先にが移動できるかどうかを調べる
            if (StageControllerScript.AableMove(ref next_pos, ref BlockData) == false)
            {
                // 移動できない場合
                // 着地フラグをtrueにする
                is_landing = true;

                for (int i = 0; i < 4; ++i)
                {
                    StageControllerScript.SetBlock(BlockObject[i]);
                }
                Destroy(gameObject);
            }

            // 移動できる場合
            // タイマーを初期化
            FallTimer = 0;
            // 移動する
            transform.Translate(0, -1, 0, Space.World);
        }
    }

    // 左右の移動処理z
    private void Move()
    {
        // 右キーが押されたとき
        if (Input.GetKeyDown(KeyCode.RightArrow))
        {
            Vector3 next_pos = transform.position;
            next_pos.x++;

            if (StageControllerScript.AableMove(ref next_pos, ref BlockData))
            {
                transform.Translate(1, 0, 0, Space.World);
            }
        }

        // 左キーが押されたとき
        else if (Input.GetKeyDown(KeyCode.LeftArrow))
        {
            Vector3 next_pos = transform.position;
            next_pos.x--;

            if (StageControllerScript.AableMove(ref next_pos, ref BlockData))
            {
                transform.Translate(-1, 0, 0, Space.World);
            }
        }
    }

    private void Rotate()
    {
        // 右回り
        if (Input.GetKeyDown(KeyCode.E))
        {
            // 回転後のブロックの情報を保存する変数
            int[,] new_block_data = new int[5, 5];

            // 配列を並べ替える
            for(int y = 0; y < 5; ++y)
            {
                for(int x = 0; x < 5; ++x)
                {
                    new_block_data[y, x] = BlockData[4 - x, y];
                }
            }

            Vector3 pos = transform.position;
            if (StageControllerScript.AableMove(ref pos, ref new_block_data) == true)
            {
                BlockData = new_block_data;
                transform.Rotate(new Vector3(0, 0, -90));
            }
            else
            {
                // もし壁があった場合左右にずらせるかを調べる
                Vector3[] vector = new Vector3[4]
                {
                    new Vector3(pos.x + 1,pos.y,0),
                    new Vector3(pos.x + 2,pos.y,0),
                    new Vector3(pos.x - 1,pos.y,0),
                    new Vector3(pos.x - 2,pos.y,0),
                };

                foreach (Vector3 element in vector)
                {
                    Vector3 tmp = element;
                    if (StageControllerScript.AableMove(ref tmp, ref new_block_data) == true)
                    {
                        transform.position = tmp;
                        BlockData = new_block_data;
                        transform.Rotate(new Vector3(0, 0, -90));
                        break;
                    }
                }
            }
        }

        // 左回り
        else if (Input.GetKeyDown(KeyCode.Q))
        {
            int[,] new_block_data = new int[5, 5];

            for (int y = 0; y < 5; ++y)
            {
                for (int x = 0; x < 5; ++x)
                {
                    new_block_data[y, x] = BlockData[x, 4 - y];
                }
            }

            Vector3 pos = transform.position;
            if (StageControllerScript.AableMove(ref pos, ref new_block_data) == true)
            {
                BlockData = new_block_data;
                transform.Rotate(new Vector3(0, 0, 90));
            }
            else
            {
                // もし壁があった場合左右にずらせるかを調べる
                Vector3[] vector = new Vector3[4]
                {
                    new Vector3(pos.x + 1,pos.y,0),
                    new Vector3(pos.x + 2,pos.y,0),
                    new Vector3(pos.x - 1,pos.y,0),
                    new Vector3(pos.x - 2,pos.y,0),
                };

                foreach(Vector3 element in vector)
                {
                    Vector3 tmp = element;
                    if (StageControllerScript.AableMove(ref tmp, ref new_block_data) == true)
                    {
                        transform.position = tmp;
                        BlockData = new_block_data;
                        transform.Rotate(new Vector3(0, 0, 90));
                        break;
                    }
                }
            }
        }
    }
}
