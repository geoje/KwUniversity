namespace Hw2_Network
{
    public class AnswerPacket : Packet
    {
        public string answer;
        public bool success = false;

        public AnswerPacket(string answer)
        {
            this.answer = answer;
        }
        public AnswerPacket(bool success)
        {
            this.success = success;
        }
    }
}
