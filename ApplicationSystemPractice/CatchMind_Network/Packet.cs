﻿using System;
using System.IO;
using System.Runtime.Serialization.Formatters.Binary;

namespace CatchMind_Network
{
    public enum PacketType
    {
        None,
        Login,
        Shape,
        Answer
    }

    [Serializable]
    public class Packet
    {
        public const int BUFFER_SIZE = 65536;
        public PacketType Type;

        public Packet()
        {
            Type = PacketType.None;
        }

        public byte[] Serialize() => Serialize(this);
        public static byte[] Serialize(object o)
        {
            using (MemoryStream ms = new MemoryStream(BUFFER_SIZE))
            {
                new BinaryFormatter().Serialize(ms, o);
                return ms.ToArray();
            }
        }
        public static Packet Deserialize(byte[] buffer)
        {
            using (MemoryStream ms = new MemoryStream(BUFFER_SIZE))
            {
                ms.Write(buffer, 0, buffer.Length);
                ms.Position = 0;

                try
                {
                    return new BinaryFormatter().Deserialize(ms) as Packet;
                }
                catch
                {
                    return null;
                }
            }
        }
    }
}