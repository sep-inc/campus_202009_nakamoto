using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public static class BlockShapeL
{
    private static int[,] BlockData = new int[BlocksDefinition.BLOCK_DATA_HEIGHT, BlocksDefinition.BLOCK_DATA_WIDTH]
    {
        { 0,0,0,0,0},
        { 0,0,0,1,0},
        { 0,1,1,1,0},
        { 0,0,0,0,0},
        { 0,0,0,0,0},
    };

    public static int[,] GetBlockData() { return BlockData; }

    public static Color GetBlockColor() { return Color.white; }
}
