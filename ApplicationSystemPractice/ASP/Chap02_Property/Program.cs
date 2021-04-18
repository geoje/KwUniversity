using System;

namespace Property
{
    public class Date
    {
        private int _month = 7;

        public int Month
        {
            get { return _month; }
            set { if (value > 0 && value < 13) _month = value; }
        }
    }
    class Program
    {
        static void Main(string[] args)
        {
            Date d1 = new Date();
            Console.WriteLine("Default month : {0}\n", d1.Month);

            while (true)
            {
                Console.Write("Enter month : ");
                int inputMonth = int.Parse(Console.ReadLine());
                if (inputMonth == -1) break;
                d1.Month = inputMonth;
                Console.WriteLine("Now month : {0}\n", d1.Month);
            }
        }
    }
}
