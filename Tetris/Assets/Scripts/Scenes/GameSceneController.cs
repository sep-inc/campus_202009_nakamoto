using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GameSceneController : SceneControllerBase
{
    [SerializeField] GameObject blockManager;
    BlockManager blockManagerScript;

    private void Start()
    {
        blockManagerScript = blockManager.GetComponent<BlockManager>();
    }

    // Update is called once per frame
    void Update()
    {
        if (blockManagerScript.cannotCreate == true)
        {
            ChangeScene();
        }
    }

    public override void ChangeScene()
    {
        SceneController.LoadNextScene();
    }
}
