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
                    Vector3 pos = Vector3.zero;
                    pos.x = x - 2;
                    pos.y = y - 2;

                    Vector3 wpos = transform.position;
                    wpos.x += pos.x;
                    wpos.y += pos.y;
                    BlockObject[create_count] = Instantiate(BlockCell, wpos, Quaternion.identity, this.transform);
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
        Rotate();

        Fall();

        Move();


    }

    // 落下処理
    private void Fall()
    {
        FallTimer += Time.deltaTime;

        FallInterval = Input.GetKey(KeyCode.DownArrow) ? .05f : 1f;

        if (FallTimer > FallInterval)
        {
            Vector3 next_pos = transform.position;
            next_pos.y--;
            if (StageControllerScript.AableMove(ref next_pos, ref BlockData) == false)
            {
                is_landing = true;

                foreach(GameObject gameObject in BlockObject)
                {
                    StageControllerScript.SetBlock(gameObject);
                }
                Destroy(gameObject);
            }
            FallTimer = 0;
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
        // 左回り
        if (Input.GetKeyDown(KeyCode.E))
        {
            int[,] new_block_data = new int[5, 5];

            for(int y = 0; y < 5; ++y)
            {
                for(int x = 0; x < 5; ++x)
                {
                    new_block_data[5 - x - 1, y] = BlockData[y, x];
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

        // 右周り
        else if (Input.GetKeyDown(KeyCode.Q))
        {
            int[,] new_block_data = new int[5, 5];

            for (int y = 0; y < 5; ++y)
            {
                for (int x = 0; x < 5; ++x)
                {
                    new_block_data[x, 5 - y - 1] = BlockData[y, x];
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
