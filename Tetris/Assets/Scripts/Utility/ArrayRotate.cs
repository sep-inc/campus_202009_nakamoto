using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ArrayRotate
{
    public static void RightRotate(ref int[,] array_, int xLength_, int yLength_)
    {
        int[,] new_array_data = new int[yLength_, xLength_];
        for (int y = 0; y < yLength_; ++y)
        {
            for (int x = 0; x < xLength_; ++x)
            {
                new_array_data[y, x] = array_[(yLength_ - 1) - x, y];
            }
        }
        array_ = new_array_data;
    }

    public static void LeftRotate(ref int[,] array_, int xLength_, int yLength_)
    {
        int[,] new_array_data = new int[yLength_, xLength_];
        for (int y = 0; y < yLength_; ++y)
        {
            for (int x = 0; x < xLength_; ++x)
            {
                new_array_data[y, x] = array_[x, (xLength_ - 1) - y];
            }
        }
        array_ = new_array_data;
    }
}
