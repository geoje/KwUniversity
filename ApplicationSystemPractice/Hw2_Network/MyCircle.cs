﻿using System;
using System.Drawing;

namespace Hw2_Network
{
    [Serializable]
    public class MyCircle : MyRect
    {
        public override void Draw(Graphics graphics)
        {
            graphics.DrawEllipse(new Pen(Color.Black, thick), rect);
        }
    }
}