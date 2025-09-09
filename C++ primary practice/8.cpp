#include <iostream>
void find(int num,int a[])
{
    int i = 0;
    int j = 6;
    int t = (i + j) / 2;
    while (a[t] != num && i <= j)
    {
        if (a[t] > num)
        {
            j = t - 1;
        }else{
            i = t + 1;
        }
        t = (i + j) / 2;
    }
    std::cout << t << std::endl;
}
    int main()
{
    int a[] = { 1,2,3,4,5,6,7};
    find(6,a);
    return 0;
}