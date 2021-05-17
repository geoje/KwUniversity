﻿using System.Collections.Generic;

namespace Hw2_Network
{
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
