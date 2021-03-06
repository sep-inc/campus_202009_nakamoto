﻿using System.Collections;
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

    public const int BLOCK_DATA_WIDTH  = 5;
    public const int BLOCK_DATA_HEIGHT = 5;
}
