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
    private int[,] blockData;
    private Color BlockColor;

    private float FallTimer = 0f;
    [SerializeField] float FallIntervalTime = 1f;
    [SerializeField] float FastFallMagnification = 2f;

    // ブロック着地したかどうかを保存する変数
    private bool isLanding = false;

    // 一度だけ行いたい処理のフラグ変数
    private bool OnceCall = false;
    // 生成されたときに既に動けない場合trueになる変数
    private bool cannotMove = false;

    // サウンド
    private AudioSource audioSource = null;

    // 回転、移動サウンド
    [SerializeField] AudioClip sound1 = null;


    public int[,] BlockData => blockData;

    // 着地したかどうかを返す関数
    public bool IsLanding() { return isLanding; }
    public bool CannotMove() { return cannotMove; }

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
                blockData = BlockShapeI.GetBlockData();
                BlockColor = BlockShapeI.GetBlockColor();
                break;
            case BlocksDefinition.BlockList.BLOCK_J:
                blockData = BlockShapeJ.GetBlockData();
                BlockColor = BlockShapeJ.GetBlockColor();
                break;
            case BlocksDefinition.BlockList.BLOCK_L:
                blockData = BlockShapeL.GetBlockData();
                BlockColor = BlockShapeL.GetBlockColor();
                break;
            case BlocksDefinition.BlockList.BLOCK_O:
                blockData = BlockShapeO.GetBlockData();
                BlockColor = BlockShapeO.GetBlockColor();
                break;
            case BlocksDefinition.BlockList.BLOCK_S:
                blockData = BlockShapeS.GetBlockData();
                BlockColor = BlockShapeS.GetBlockColor();
                break;
            case BlocksDefinition.BlockList.BLOCK_T:
                blockData = BlockShapeT.GetBlockData();
                BlockColor = BlockShapeT.GetBlockColor();
                break;
            case BlocksDefinition.BlockList.BLOCK_Z:
                blockData = BlockShapeZ.GetBlockData();
                BlockColor = BlockShapeZ.GetBlockColor();
                break;
            default:
                break;
        }


        const int center_pos = 2;
        int create_count = 0;
        for (int y = 0; y < BlocksDefinition.BLOCK_DATA_HEIGHT; ++y)
        {
            for (int x = 0; x < BlocksDefinition.BLOCK_DATA_WIDTH; ++x)
            {
                if (BlockData[y, x] == 1)
                {
                    Vector3 to_center_vec = Vector3.zero;
                    to_center_vec.x = x - center_pos;
                    to_center_vec.y = y - center_pos;

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

        audioSource = GetComponent<AudioSource>();
    }



    public void MyUpdate()
    {
        // 生成時に動けない場合の処理
        if (OnceCall == false)
        {
            OnceCall = true;

            Vector3 pos = transform.position;

            if (StageControllerScript)
            {
                if (StageControllerScript.AbleMove(ref pos, ref blockData) == false)
                {
                    cannotMove = true;
                }
            }
        }

        // もしEキーが押されたら右回転
        if (Input.GetKeyDown(KeyCode.E)) RightRotation();

        // もしQキーが押されたら左回転
        else if (Input.GetKeyDown(KeyCode.Q)) LeftRotation();

        // もし右キーが押されたら右に移動する
        if (Input.GetKeyDown(KeyCode.RightArrow)) MoveRight();

        // もし左キーが押されたら左に移動する
        else if (Input.GetKeyDown(KeyCode.LeftArrow)) MoveLeft();

        // 落下処理
        // タイマーを進める
        FallTimer += Input.GetKey(KeyCode.DownArrow) ? Time.deltaTime * FastFallMagnification : Time.deltaTime;
        // 一定時間たったら落下
        if (FallTimer > FallIntervalTime)
        {
            Fall();
            FallTimer = 0;
        }


    }

    // 落下処理
    private void Fall()
    {
         // 次に落ちる座標を算出する
         Vector3 next_pos = transform.position;
         next_pos.y--;

         // 落ちた先にが移動できるかどうかを調べる
         if (StageControllerScript.AbleMove(ref next_pos, ref blockData) == false)
         {
            // 移動できない場合
            // 着地フラグをtrueにする
            isLanding = true;

            StageControllerScript.SetBlock(BlockObject);
            Destroy(gameObject);
         }
         
         // 移動する
         transform.Translate(Vector3.down, Space.World);
    }

    public void FastFall()
    {
        FallTimer += Time.deltaTime * FastFallMagnification;
    }
    

    // 右に移動する処理
    public void MoveRight()
    {
        Vector3 next_pos = transform.position;
        next_pos.x++;

        if (StageControllerScript.AbleMove(ref next_pos, ref blockData))
        {
            audioSource.PlayOneShot(sound1);
            transform.Translate(Vector3.right, Space.World);
        }
    }

    // 左に移動する処理
    public void MoveLeft()
    {
        Vector3 next_pos = transform.position;
        next_pos.x--;

        if (StageControllerScript.AbleMove(ref next_pos, ref blockData))
        {
            audioSource.PlayOneShot(sound1);
            transform.Translate(Vector3.left, Space.World);
        }
    }


    // 右回転処理
    public void RightRotation()
    {
        bool rotated = false;

        // 回転後のブロックの情報を保存する変数
        int[,] new_block_data = new int[BlocksDefinition.BLOCK_DATA_HEIGHT, BlocksDefinition.BLOCK_DATA_WIDTH];

        // 右回り
        // 配列を並べ替える
        for (int y = 0; y < BlocksDefinition.BLOCK_DATA_HEIGHT; ++y)
        {
            for (int x = 0; x < BlocksDefinition.BLOCK_DATA_WIDTH; ++x)
            {
                new_block_data[y, x] = BlockData[(BlocksDefinition.BLOCK_DATA_HEIGHT - 1) - x, y];
            }
        }

        // 現在の座標を取得する
        Vector3 pos = transform.position;
        
        // 回転できるかどうかをステージに問い合わせる
        if (StageControllerScript.AbleMove(ref pos, ref new_block_data) == true)
        {
            // もし回転できるなら回転後のブロックのデータを保存する
            blockData = new_block_data;

            // ブロックを再構築
            Reloading();

            rotated = true;
        }
        // もし回転できなかった場合左右にずらせるかを調べる
        else
        {
            // 現在の座標から左右に2マス進んだ座標を作成
            Vector3[] vector = new Vector3[4]
            {
                    new Vector3(pos.x + 1,pos.y,pos.z),
                    new Vector3(pos.x + 2,pos.y,pos.z),
                    new Vector3(pos.x - 1,pos.y,pos.z),
                    new Vector3(pos.x - 2,pos.y,pos.z),
            };

            // 順番に移動できるかを調べる
            foreach (Vector3 element in vector)
            {
                Vector3 around_pos = element;
                if (StageControllerScript.AbleMove(ref around_pos, ref new_block_data) == true)
                {
                    // 移動可能な場合移動させ回転情報も保存する
                    transform.position = around_pos;
                    blockData = new_block_data;

                    // ブロックを再構築
                    Reloading();
                    rotated = true;
                    break;
                }
            }
        }
        if (rotated)
        {
            audioSource.PlayOneShot(sound1);
        }
    }

    // 左回転処理
    public void LeftRotation()
    {
        bool rotated = false;

        // 回転後のブロックの情報を保存する変数
        int[,] new_block_data = new int[BlocksDefinition.BLOCK_DATA_HEIGHT, BlocksDefinition.BLOCK_DATA_WIDTH];

        // 左回り
        // 配列を並べ替える
        for (int y = 0; y < BlocksDefinition.BLOCK_DATA_HEIGHT; ++y)
        {
            for (int x = 0; x < BlocksDefinition.BLOCK_DATA_WIDTH; ++x)
            {
                new_block_data[y, x] = BlockData[x, (BlocksDefinition.BLOCK_DATA_WIDTH - 1) - y];
            }
        }

        // 現在の座標を取得する
        Vector3 pos = transform.position;

        // 回転できるかどうかをステージに問い合わせる
        if (StageControllerScript.AbleMove(ref pos, ref new_block_data) == true)
        {
            // もし回転できるなら回転後のブロックのデータを保存する
            blockData = new_block_data;

            // ブロックを再構築
            Reloading();

            rotated = true;
        }
        // もし回転できなかった場合左右にずらせるかを調べる
        else
        {
            // 現在の座標から左右に2マス進んだ座標を作成
            Vector3[] vector = new Vector3[4]
            {
                    new Vector3(pos.x + 1,pos.y,pos.z),
                    new Vector3(pos.x + 2,pos.y,pos.z),
                    new Vector3(pos.x - 1,pos.y,pos.z),
                    new Vector3(pos.x - 2,pos.y,pos.z),
            };

            // 順番に移動できるかを調べる
            foreach (Vector3 element in vector)
            {
                Vector3 around_pos = element;
                if (StageControllerScript.AbleMove(ref around_pos, ref new_block_data) == true)
                {
                    // 移動可能な場合移動させ回転情報も保存する
                    transform.position = around_pos;
                    blockData = new_block_data;

                    // ブロックを再構築
                    Reloading();

                    rotated = true;
                    break;
                }
            }
        }

        if (rotated)
        {
            audioSource.PlayOneShot(sound1);
        }
    }


    // ブロック情報を再度読み込む
    private void Reloading()
    {
        // 現在のブロック情報からゲームオブジェクトを再度構築する

        const int center_pos = 2;

        // ブロックの生成された数をカウントする変数
        int create_count = 0;

        for (int y = 0; y < BlocksDefinition.BLOCK_DATA_HEIGHT; ++y)
        {
            for (int x = 0; x < BlocksDefinition.BLOCK_DATA_WIDTH; ++x)
            {
                if (BlockData[y, x] == 1)
                {
                    // 中心からの距離
                    Vector3 to_center_vec = Vector3.zero;
                    to_center_vec.x = x - center_pos;
                    to_center_vec.y = y - center_pos;

                    // 配列に合わせるためy軸だけ反転させる
                    to_center_vec.y = -to_center_vec.y;

                    // 中心からベクトル分足した距離で生成する
                    Vector3 pos = transform.position;
                    pos.x += to_center_vec.x;
                    pos.y += to_center_vec.y;

                    // 元のブロックは削除
                    Destroy(BlockObject[create_count]);

                    // 新しく生成する
                    BlockObject[create_count] = Instantiate(BlockCell, pos, Quaternion.identity, this.transform);
                    BlockObject[create_count].GetComponent<MeshRenderer>().material.color = BlockColor;
                    
                    // 生成出来たらカウントを足す
                    create_count++;
                }
            }

            // 生成カウントが4になったら生成終了
            if (create_count == 4) break;
        }
    }

}
