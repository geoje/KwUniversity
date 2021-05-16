using System.Drawing;

namespace Hw2_Network
{
    public abstract class MyShape
    {
        protected int thick;
        protected bool isSolid;

        public MyShape()
        {
            thick = 1;
            isSolid = true;
        }

        public int GetThick() => thick;
        public bool GetSolid() => isSolid;

        public abstract void Draw(Graphics graphics);
    }
}
