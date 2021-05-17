using System;

namespace Hw2_Network
{
    [Serializable]
    public class LoginPacket : Packet
    {
        public string id;

        public LoginPacket(string id)
        {
            Type = PacketType.Login;
            this.id = id;
        }
    }
}
