using System;
using System.Drawing;

namespace Hw2_Network
{
    public class MyRect : MyShape
    {
        protected Rectangle rect;

        public void SetRect(Point start, Point end, int thick, bool isSolid)
        {
            rect = new Rectangle(Math.Min(start.X, end.X), Math.Min(start.Y, end.Y),
                Math.Abs(start.X - end.X), Math.Abs(start.Y - end.Y));
            this.thick = thick;
            this.isSolid = isSolid;
        }

        public Rectangle GetRect() => rect;

        public override void Draw(Graphics graphics)
        {
            graphics.DrawRectangle(new Pen(Color.Black, thick), rect);
        }
    }
}
