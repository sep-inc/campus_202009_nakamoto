using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TitleScenecontroller : SceneControllerBase
{
    public override void ChangeScene()
    {
        SceneController.LoadNextScene();
    }

    public void QuitGame()
    {
        SceneController.QuitGame();
    }


}
