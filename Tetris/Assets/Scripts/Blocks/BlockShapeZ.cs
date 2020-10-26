using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public static class BlockShapeZ
{
    private static int[,] BlockParam = new int[5, 5]
    {
        { 0,0,0,0,0},
        { 0,1,1,0,0},
        { 0,0,1,1,0},
        { 0,0,0,0,0},
        { 0,0,0,0,0},
    };
    // ブロックシェイプクラスの作成

    public static int[,] GetBlockData() { return BlockParam; }

    public static Color GetBlockColor() { return Color.red; }


    public static BlocksDefinition.BlockList GetBlockType() { return BlocksDefinition.BlockList.BLOCK_Z; }
}
