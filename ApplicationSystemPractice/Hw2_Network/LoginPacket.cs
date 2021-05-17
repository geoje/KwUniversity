namespace Hw2_Network
{
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
