using System;
namespace Answer
{
    class Program
    {
        static private void Main()
        {
            Console.Write("a: ");
            var a = double.Parse(Console.ReadLine());
            Console.Write("b: ");
            var b = double.Parse(Console.ReadLine());
            a = a <= b ? 0 : a;
            Console.WriteLine();
            Console.WriteLine("a: {0}", a);
            Console.WriteLine("b: {0}", b);
            Console.ReadKey();
        }
    }
}