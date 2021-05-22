using System;

namespace CatchMind_Network
{
    [Serializable]
    public class AnswerPacket : Packet
    {
        public string answer;
        public bool success = false;

        public AnswerPacket(string answer)
        {
            Type = PacketType.Answer;
            this.answer = answer;
        }
        public AnswerPacket(bool success)
        {
            Type = PacketType.Answer;
            this.success = success;
        }
    }
}
