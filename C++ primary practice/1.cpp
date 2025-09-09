#include <iostream>
using namespace std;
int f(int a)
{
    return a * a * a;
}
int main()
{
    for (int i = 100; i < 1000; i++)
    {
        int a = i % 10;
        int b = i / 10 % 10;
        int c = i / 100;
        if (f(a) + f(b) + f(c) == i)
        {
            cout << i << "\n" << endl;
        }
    }
    return 0;
}