using System;
using System.Collections;
using System.Collections.Generic;
using UnityEditor;
using UnityEditorInternal;
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
    private bool isLanding = false;

    // 一度だけ行いたい処理のフラグ変数
    private bool OnceCall = false;
    // 生成されたときに既に動けない場合trueになる変数
    private bool cannotMove = false;


    /*
        ブロック初期化関数
        生成時に1度だけ呼ぶ
    */
    public void Create(BlocksDefinition.BlockList block_, GameObject stageController_)
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


        StageControllerObj = stageController_;
        StageControllerScript = StageControllerObj.GetComponent<StageController>();

    }
    // 着地したかどうかを返す関数
    public bool IsLanding() { return isLanding; }
    public bool CannotMove() { return cannotMove; }


    public void MyUpdate()
    {
        // 生成時に動けない場合の処理
        if (OnceCall == false)
        {
            OnceCall = true;

            Vector3 pos = transform.position;

            if (StageControllerScript)
            {
                if (StageControllerScript.AbleMove(ref pos, ref BlockData) == false)
                {
                    cannotMove = true;
                }
            }
        }

        // 落下処理
        Fall();

        // 回転処理
        Rotate();

        // 移動処理
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
            if (StageControllerScript.AbleMove(ref next_pos, ref BlockData) == false)
            {
                // 移動できない場合
                // 着地フラグをtrueにする
                isLanding = true;

                StageControllerScript.SetBlock(BlockObject);
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

            if (StageControllerScript.AbleMove(ref next_pos, ref BlockData))
            {
                transform.Translate(1, 0, 0, Space.World);
            }
        }

        // 左キーが押されたとき
        else if (Input.GetKeyDown(KeyCode.LeftArrow))
        {
            Vector3 next_pos = transform.position;
            next_pos.x--;

            if (StageControllerScript.AbleMove(ref next_pos, ref BlockData))
            {
                transform.Translate(-1, 0, 0, Space.World);
            }
        }
    }


    // 回転処理
    private void Rotate()
    {
        // 回転したかどうかを保存する変数
        bool is_rotate = false;

        // 回転後のブロックの情報を保存する変数
        int[,] new_block_data = new int[5, 5];


        // 右回り
        if (Input.GetKeyDown(KeyCode.E))
        {
            // 配列を並べ替える
            for (int y = 0; y < 5; ++y)
            {
                for (int x = 0; x < 5; ++x)
                {
                    new_block_data[y, x] = BlockData[4 - x, y];
                }
            }
            is_rotate = true;
        }

        // 左回り
        else if (Input.GetKeyDown(KeyCode.Q))
        {
            for (int y = 0; y < 5; ++y)
            {
                for (int x = 0; x < 5; ++x)
                {
                    new_block_data[y, x] = BlockData[x, 4 - y];
                }
            }
            is_rotate = true;
        }


        // もし回転しなかったらreturn
        if (!is_rotate) return;


        // 回転できるかを調べる
        Vector3 pos = transform.position;
        if (StageControllerScript.AbleMove(ref pos, ref new_block_data) == true)
        {


            BlockData = new_block_data;

            is_rotate = true;
        }
        else
        {
            is_rotate = false;

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
                Vector3 around_pos = element;
                if (StageControllerScript.AbleMove(ref around_pos, ref new_block_data) == true)
                {
                    // ずれせる場合はずらす
                    transform.position = around_pos;
                    BlockData = new_block_data;
                    is_rotate = true;
                    break;
                }
            }
        }

        // もし回転できる場合、回転後のブロックのデータで再構築する
        if (is_rotate == true)
        {
            // 新しいブロックを作成
            int create_count = 0;
            for (int y = 0; y < 5; ++y)
            {
                for (int x = 0; x < 5; ++x)
                {
                    if (BlockData[y, x] == 1)
                    {
                        // 中心からの距離
                        Vector3 to_center_vec = Vector3.zero;
                        to_center_vec.x = x - 2;
                        to_center_vec.y = y - 2;

                        // 配列に合わせるためy軸だけ反転させる
                        to_center_vec.y = -to_center_vec.y;

                        // 中心からベクトル分足した距離で生成する
                        pos = transform.position;
                        pos.x += to_center_vec.x;
                        pos.y += to_center_vec.y;
                        Destroy(BlockObject[create_count]);
                        BlockObject[create_count] = Instantiate(BlockCell, pos, Quaternion.identity, this.transform);
                        BlockObject[create_count].GetComponent<MeshRenderer>().material.color = BlockColor;
                        create_count++;
                    }
                }

                if (create_count == 4) break;
            }
        }

    }


    
}
