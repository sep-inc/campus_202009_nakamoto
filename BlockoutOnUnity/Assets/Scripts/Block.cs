﻿using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Block : MonoBehaviour
{
    [SerializeField]
    GameObject game_controller = null;
    private GameController controller_component;

    // Start is called before the first frame update
    void Start()
    {
        controller_component = game_controller.GetComponent<GameController>();
    }

    // Update is called once per frame
    void Update()
    {
    }

    // ゲームオーバーの通知を受け取った時の処理
    public void NotifyGameOver()
    {
        // このオブジェクトを消す
        Rigidbody rigidbody = gameObject.GetComponent<Rigidbody>();
        rigidbody.isKinematic = false;
        rigidbody.useGravity = true;
        rigidbody.constraints = RigidbodyConstraints.None;
    }

    private void OnCollisionEnter(Collision collision)
    {
        // もしボールと当たったら
        if (collision.gameObject.tag == "Ball")
        {
            // 当たったことを管理クラスに通知する
            controller_component.NotifyBlockDead();

            // 自身を消す
            Destroy(gameObject);
        }
    }

}
