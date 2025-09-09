#include <iostream>
#include <vector>
using namespace std;
void buble(int a[5])
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4 - i; j++)
        {
            if (a[j] > a[j+1])
            {
                int tmp = a[j];
                a[j] = a[j+1];
                a[j+1] = tmp;
            }
            
        }
        
    }
    
}
int main()
{
    int a[5] = {4,5,1,3,2};
    buble(a);
    for(const auto& element : a)
    {
        cout << element << endl;
    }
return 0;
}
