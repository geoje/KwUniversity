using System;

namespace CatchMind_Network
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
