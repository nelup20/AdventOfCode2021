using System;
using System.Linq;

namespace p1
{
    class P1
    {
        static void Main(string[] args)
        {
            int[] input = System.IO.File.ReadAllText("../../../input.txt").Split(",").Select(int.Parse).ToArray();
            Array.Sort(input);

            int median = input[input.Length / 2];
            int result = 0;

            foreach (var elem in input)
            {
                result += Math.Abs(median - elem);
            }
            
            Console.WriteLine($"Result: {result}");
        }
    }
}
