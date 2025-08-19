
unsigned long long int Fibonacci(int num)
{
    unsigned long long int a = 1, b = 2, fib = 0;
    switch (num)
    {
        case 1:
            fib = 1;
            break;
        case 2:
            fib = 2;
            break;
    }
    for (int i = 3; i <= num; i++)
    {
        fib = a + b;
        if (i % 2)
            a = fib;
        else
            b = fib;
    }
    return fib;
}
