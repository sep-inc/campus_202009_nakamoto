using System.Collections;
using System.Collections.Generic;
using TMPro;
using UnityEngine;
using UnityEngine.UI;

public class GameSceneController : SceneControllerBase
{
    [SerializeField] GameObject blockManager = null;
    BlockManager blockManagerScript = null;

    private bool gameStarted = false;

    private float timer = 0f;
    [SerializeField] GameObject blockgroundFilm = null;

    [SerializeField] GameObject numberTextObject = null;
    private TextMeshProUGUI numberText = null;

    [SerializeField] GameObject aiObject = null;
    private AI aiScript = null;
    [SerializeField] bool AIOn = false;

    [SerializeField] GameObject modeTextObject = null;
    private Text modeText = null;

    private void Start()
    {
        blockManagerScript = blockManager.GetComponent<BlockManager>();
        
        // フィルムをアクティブにする
        blockgroundFilm.SetActive(true);
        
        numberTextObject.SetActive(true);
        numberText = numberTextObject.GetComponent<TextMeshProUGUI>();

        aiScript = aiObject.GetComponent<AI>();
        modeText = modeTextObject.GetComponent<Text>();

        modeText.text = AIOn ? "自動" : "手動";
    }

    // Update is called once per frame
    void Update()
    {
        // 生成できなくなったらシーンを変える
        if (blockManagerScript.cannotCreate == true)
        {
            ChangeScene();
        }

        // ゲームが始まっていなかったら
        if (!gameStarted)
        {
            // スタートの演出を行い終了したら
            if (StartDirecting() == true)
            {
                // スタートフラグをonoに
                gameStarted = true;

                // 演出用オブジェクトの破棄
                Destroy(blockgroundFilm);
                Destroy(numberTextObject);

                // 通知
                blockManagerScript.NoticeGameStart();
            }
        }

        // Aキーで操作モード切替
        if (Input.GetKeyDown(KeyCode.A))
        {
            AIOn = !AIOn;
            modeText.text = AIOn ? "自動" : "手動";
        }

        if (AIOn)
        {
            aiScript.MyUpdate();
        }
    }

    public override void ChangeScene()
    {
        SceneController.LoadNextScene();
    }

    // スタートの演出
    private bool StartDirecting()
    {
        timer += Time.deltaTime;

        int num = 3 - (int)timer;

        numberText.text = num.ToString();

        if (timer >= 3f)
        {
            return true;
        }

        return false;
    }
}
