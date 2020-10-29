using System.Collections;
using System.Collections.Generic;
using System.Linq;
using UnityEngine;
using UnityEngine.SceneManagement;

public class SceneController : MonoBehaviour
{

    // シーンリスト
    public enum SceneList
    {
        SCENE_TITLE,    // タイトルシーン
        SCENE_GAME,     // ゲームシーン
        SCENE_RESULT,   // リザルトシーン
    }


    // Dictionaryでシーン名とSceneListを対応させる
    static Dictionary<SceneList, string> scene_dictionary = new Dictionary<SceneList, string>()
    {
        {SceneList.SCENE_TITLE,   "Title"},
        {SceneList.SCENE_GAME,    "Game"},
        {SceneList.SCENE_RESULT,  "Result"},
    };


    private static SceneList GetScene()
    {
        string scene_name = SceneManager.GetActiveScene().name;
        return scene_dictionary.FirstOrDefault(c => c.Value == scene_name).Key;
    }

    private static void LoadScene(SceneList scene)
    {
        SceneManager.LoadScene(scene_dictionary[scene]);
    }

    public static void LoadNextScene()
    {
        SceneList current_scene = GetScene();

        if (current_scene == SceneList.SCENE_TITLE)
        {
            LoadScene(SceneList.SCENE_GAME);
        }
        else if (current_scene == SceneList.SCENE_GAME)
        {
            LoadScene(SceneList.SCENE_RESULT);
        }
        else if (current_scene == SceneList.SCENE_RESULT)
        {
            LoadScene(SceneList.SCENE_TITLE);
        }
    }

    public void QuitGame()
    {
        UnityEditor.EditorApplication.isPlaying = false;
        Application.Quit();
    }

    private void Awake()
    {
        DontDestroyOnLoad(gameObject);
    }

}
