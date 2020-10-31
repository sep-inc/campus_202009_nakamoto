using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TitleScenecontroller : SceneControllerBase
{
    // Update is called once per frame
    void Update()
    {
        // 左クリックが押されたらシーンを遷移する
        if (Input.GetMouseButtonDown(0))
        {
            ChangeScene();
        }
    }

    public override void ChangeScene()
    {
        SceneController.LoadNextScene();
    }
}
