using System;
using System.Drawing;

namespace Hw2_Network
{
    [Serializable]
    public abstract class MyShape
    {
        protected int thick;
        protected bool isSolid;
        protected Point start, end;

        public MyShape()
        {
            thick = 1;
            isSolid = true;
        }

        public int GetThick() => thick;
        public bool GetSolid() => isSolid;
        public Point GetStartPos() => start;
        public Point GetEndPos() => end;

        public void SetProperty(int thick, bool isSolid)
        {
            this.thick = thick;
            this.isSolid = isSolid;
        }
        public virtual void SetPosition(Point start, Point end)
        {
            if (start != Point.Empty) this.start = start;
            if (end != Point.Empty) this.end = end;
        }

        public abstract void Draw(Graphics graphics);
    }
}
