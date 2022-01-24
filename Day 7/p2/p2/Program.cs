using System;
using System.Collections.Generic;
using System.Linq;

namespace p2
{
    class Program
    {
        static void Main(string[] args)
        {
            var input = System.IO.File.ReadAllText("../../../input.txt").Split(",").Select(int.Parse).ToArray();
            var average = input.Sum() / input.Length;
            var results = new List<int>();

            // Arbitrarily chose 5. Thought first about doing from and to 1 std dev from the mean, but 5+- worked lol
            for (var i = average - 5; i < average + 5; i++)
            {
                var fuelUsed = 0;
                foreach (var number in input)
                {
                    for (var j = 0; j <= Math.Abs(number - i); j++)
                    {
                        fuelUsed += j;
                    }
                }

                results.Add(fuelUsed);
            }
            
            Console.WriteLine($"Result: {results.Min()}");
        }
    }
}