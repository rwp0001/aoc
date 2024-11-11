using System;
using System.Diagnostics;

namespace _2023
{
    internal class Program
    {
        static void Main(string[] args)
        {
            Stopwatch timer = new();
            timer.Start();

            Day05a Day = new();

            Console.WriteLine($"Time: {timer.Elapsed.ToString()}");
        }
    }
}




