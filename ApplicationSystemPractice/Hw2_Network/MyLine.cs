using System.Drawing;

namespace Hw2_Network
{
    public class MyLine : MyShape
    {
        public override void Draw(Graphics graphics)
        {
            graphics.DrawLine(new Pen(Color.Black, thick), start, end);
        }
    }
}
