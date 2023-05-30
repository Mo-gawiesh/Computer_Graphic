using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace задача
{
    class Program
    {
        static void Main(string[] args)
        {
            int m = 6;
            int[,] a = new int[m, m];//создаем массив А
            Random rnd = new Random();
            for (int i = 0; i < m; i++)
            {
                for (int j = 0; j < m; j++)
                {
                    a[i, j] = rnd.Next(0, 5);
                }
            }
            Console.WriteLine("Исходный массив:");
            Show(a, m);
            int[,] b = new int[m, m];//создаем массив B

            List<int> Neighbor = new List<int>();
            Search(a, m, Neighbor, b);
            Console.WriteLine("Полученный массив");
            Show(b, m);
            Console.ReadKey();
        }
        static void Show(int[,] arr, int m)
        {
            for (int i = 0; i < m; i++)
            {
                for (int j = 0; j < m; j++)
                    Console.Write("{0}\t", arr[i, j]);

                Console.WriteLine();
            }
        }
        static void Elements(int[,] a, int x, int y, int m, int[,] b)
        {
            List<int> Neighbor = new List<int>();
            try
            {
                Neighbor.Add(a[x - 1, y - 1]);
                Neighbor.Add(a[x, y - 1]);
                Neighbor.Add(a[x - 1, y]);
                Neighbor.Add(a[x + 1, y + 1]);
                Neighbor.Add(a[x + 1, y]);
                Neighbor.Add(a[x, y + 1]);
                Neighbor.Add(a[x + 1, y - 1]);
                Neighbor.Add(a[x - 1, y + 1]);
            }
            catch
            {
                Exception e;
            }
        }
        static void Search(int[,] a, int m, List<int> Neighbor, int[,] b)
        {
            for (int i = 0; i < m; i++)
            {
                for (int j = 0; j < m; j++)
                {
                    Elements(a, i, j, m, b);
                    if (Neighbor.Contains(a[i, j]))
                    {
                        b[i, j] = 1;
                    }
                    else
                    {
                        b[i, j] = 0;
                    }
                }
            }
        }
    }
}