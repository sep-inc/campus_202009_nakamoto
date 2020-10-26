using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BlocksDefinition
{
    // ブロックの種類
    public enum BlockList
    {
        BLOCK_I,
        BLOCK_J,    
        BLOCK_L,
        BLOCK_O,
        BLOCK_S,
        BLOCK_T,
        BLOCK_Z,
        BLOCK_NUM,
    };


    public struct BlockData
    {
        bool Flag;
        Color Color;
    }
    

    public static BlockList[] BlockListArray = new BlockList[(int)BlockList.BLOCK_NUM]
    {
        BlockList.BLOCK_I,
        BlockList.BLOCK_J,
        BlockList.BLOCK_L,
        BlockList.BLOCK_O,
        BlockList.BLOCK_S,
        BlockList.BLOCK_T,
        BlockList.BLOCK_Z,
    };

    
}
