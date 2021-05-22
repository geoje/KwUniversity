using System;
using System.Drawing;

namespace CatchMind_Network
{
    [Serializable]
    public class MyLine : MyShape
    {
        public override void Draw(Graphics graphics)
        {
            graphics.DrawLine(new Pen(Color.Black, thick), start, end);
        }
    }
}
