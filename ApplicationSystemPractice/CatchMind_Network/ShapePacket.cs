using System;
using System.Collections.Generic;

namespace CatchMind_Network
{
    [Serializable]
    public class ShapePacket : Packet
    {
        public List<MyShape> shapes;

        public ShapePacket(List<MyShape> shapes)
        {
            Type = PacketType.Shape;
            this.shapes = shapes;
        }
    }
}
