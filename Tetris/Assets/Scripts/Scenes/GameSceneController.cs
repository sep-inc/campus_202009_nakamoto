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
    }

    // Update is called once per frame
    void Update()
    {

        if (!gameStarted)
        {
            if (StartDirecting() == true)
            {
                gameStarted = true;
                blockgroundFilm.SetActive(false);
                numberTextObject.SetActive(false);
                blockManagerScript.NoticeGameStart();
            }
        }

        if (blockManagerScript.cannotCreate == true)
        {
            ChangeScene();
        }

        modeText.text = aiScript.On ? "自動" : "手動";
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
