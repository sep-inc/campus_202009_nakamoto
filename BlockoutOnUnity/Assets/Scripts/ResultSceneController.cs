using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class ResultSceneController : MonoBehaviour
{
    [SerializeField] GameObject result_object     = null;
    [SerializeField] GameObject click_text_object = null;

    // Start is called before the first frame update
    void Start()
    {
        Text result_text = result_object.GetComponent<Text>();
        result_text.text = GameController.result_string;

        StartCoroutine("BlinkUI");
    }

    private void Update()
    {
        // 左クリックが押されたらシーンを遷移する
        if (Input.GetMouseButtonDown(0))
        {
            SceneContoller.LoadNextScene();
        }
    }

    IEnumerator BlinkUI()
    {
        bool is_blink = true;
        while (true)
        {
            is_blink = !is_blink;
            click_text_object.SetActive(is_blink);
            yield return new WaitForSeconds(0.5f);
        }
    }
}
