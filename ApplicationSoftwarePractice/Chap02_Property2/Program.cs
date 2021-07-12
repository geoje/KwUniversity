using System;

namespace Property2
{
    abstract class Shape
    {
        public abstract double Area { get; set; }
    }
    class Square : Shape
    {
        public double side;

        public Square(double side)
        {
            this.side = side;
        }
        public override double Area {
            get => side * side;
            set => side = Math.Sqrt(value);
        }
    }
    class Cube : Shape
    {
        public double side;

        public Cube(double side)
        {
            this.side = side;
        }
        public override double Area {
            get => 6 * side * side;
            set => side = Math.Sqrt(value / 6);
        }
    }
    class Program
    {
        static void Main(string[] args)
        {
            // Input the side
            Console.Write("Enter the side: ");
            double side = double.Parse(Console.ReadLine());

            // Compute the areas
            Square s = new Square(side);
            Cube c = new Cube(side);

            // Display the results
            Console.WriteLine("Area of the square = {0:F2}", s.Area);
            Console.WriteLine("Area of the cube   = {0:F2}", c.Area);

            // Input the area
            Console.Write("Enter the area: ");
            double area = double.Parse(Console.ReadLine());

            // Compute the sides
            s.Area = area;
            c.Area = area;

            Console.WriteLine("Side of the square = {0:F2}", s.side);
            Console.WriteLine("Side of the cube   = {0:F2}", c.side);
        }
    }
}
