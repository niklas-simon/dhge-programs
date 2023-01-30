using System;
using System.Threading;
using System.Threading.Tasks;

class TestClass
{
    static int get_tries2(int number) {
        int tries = 0;
        while (number > 1) {
            if (number % 2 == 0) {
                number /= 2;
            } else {
                number = 3 * number + 1;
            }
            tries++;
        }
        return tries;
    }
    static void Main(string[] args)
    {
        Parallel.For(1, Int32.Parse(args[0]), i =>
            {
                Console.WriteLine("{0}: {1} tries", i, get_tries2(i));
            }
        );
    }
}