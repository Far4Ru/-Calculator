#ifndef FACTORIAL_H
#define FACTORIAL_H
long double factorial(int N)
{
    if(N < 0)
        return 0;
    if (N == 0)
        return 1;
    else
        return N * factorial(N - 1);
}
#endif // FACTORIAL_H
