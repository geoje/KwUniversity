using System;
using System.Drawing;

namespace Hw2_Network
{
    [Serializable]
    public class MyRect : MyShape
    {
        protected Rectangle rect;

        public Rectangle GetRect() => rect;

        public override void SetPosition(Point start, Point end)
        {
            if (start != Point.Empty) this.start = start;
            if (end != Point.Empty) this.end = end;

            rect = new Rectangle(
                Math.Min(this.start.X, this.end.X),
                Math.Min(this.start.Y, this.end.Y),
                Math.Abs(this.start.X - this.end.X),
                Math.Abs(this.start.Y - this.end.Y)
                );
        }
        public override void Draw(Graphics graphics)
        {
            graphics.DrawRectangle(new Pen(Color.Black, thick), rect);
        }
    }
}
