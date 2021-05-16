using System.Drawing;

namespace Hw2_Network
{
    public class MyLine : MyShape
    {
        Point[] pos = new Point[2];

        public Point GetPoint(int index) => pos[index];

        public override void Draw(Graphics graphics)
        {
            graphics.DrawLine(new Pen(Color.Black, thick), pos[0], pos[1]);
        }
    }
}
