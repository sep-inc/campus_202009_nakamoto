using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public static class BlockShapeL
{
    private static int[,] BlockParam = new int[5, 5]
    {
        { 0,0,0,0,0},
        { 0,0,0,1,0},
        { 0,1,1,1,0},
        { 0,0,0,0,0},
        { 0,0,0,0,0},
    };

    public static int[,] GetBlockData() { return BlockParam; }

    public static Color GetBlockColor() { return Color.white; }
}
