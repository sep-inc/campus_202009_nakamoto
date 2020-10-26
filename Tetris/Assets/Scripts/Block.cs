using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Block : MonoBehaviour
{

    [SerializeField] GameObject BlockCell = null;
    private GameObject[] BlockObject;
    private int[,] BlockData;
    private Color BlockColor;

    public void Create(BlocksDefinition.BlockList block_)
    {
        BlockObject = new GameObject[4];

        switch (block_)
        {
            case BlocksDefinition.BlockList.BLOCK_I:
                BlockData  = BlockShapeI.GetBlockData();
                BlockColor = BlockShapeI.GetBlockColor();
                break;
            case BlocksDefinition.BlockList.BLOCK_J:
                BlockData  = BlockShapeJ.GetBlockData();
                BlockColor = BlockShapeJ.GetBlockColor();
                break;
            case BlocksDefinition.BlockList.BLOCK_L:
                BlockData  = BlockShapeL.GetBlockData();
                BlockColor = BlockShapeL.GetBlockColor();
                break;
            case BlocksDefinition.BlockList.BLOCK_O:
                BlockData  = BlockShapeO.GetBlockData();
                BlockColor = BlockShapeO.GetBlockColor();
                break;
            case BlocksDefinition.BlockList.BLOCK_S:
                BlockData  = BlockShapeS.GetBlockData();
                BlockColor = BlockShapeS.GetBlockColor();
                break;
            case BlocksDefinition.BlockList.BLOCK_T:
                BlockData  = BlockShapeT.GetBlockData();
                BlockColor = BlockShapeT.GetBlockColor();
                break;
            case BlocksDefinition.BlockList.BLOCK_Z:
                BlockData  = BlockShapeZ.GetBlockData();
                BlockColor = BlockShapeZ.GetBlockColor();
                break;
            default:
                break;
        }


        int create_count = 0;
        for(int y = 0; y < 5; ++y)
        {
            for(int x = 0; x < 5; ++x)
            {
                if (BlockData[y, x] == 1) 
                {
                    Vector3 pos = transform.position;
                    pos.x += (x - 2);
                    pos.y += (y + 2);
                    BlockObject[create_count] = Instantiate(BlockCell, pos, Quaternion.identity, this.transform);
                    BlockObject[create_count].GetComponent<MeshRenderer>().material.color = BlockColor;
                    create_count++;
                }
            }

            if (create_count == 4) break;
        }

        
    }
    
    

}
