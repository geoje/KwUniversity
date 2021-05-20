using System;
using System.Drawing;

namespace CatchMind_Network
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
