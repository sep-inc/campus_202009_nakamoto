using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ResultSceneController : MonoBehaviour
{
    // Update is called once per frame
    void Update()
    {
        // 左クリックが押されたらシーンを遷移する
        if (Input.GetMouseButtonDown(0))
        {
            SceneController.LoadNextScene();
        }
    }
}
