#include <iostream>
using namespace std;

int f(int a,int sto[128]);
int find(int i,int sto[128]);



int i = 0;
int sto[128] = {0};
int main()
{
    int number;
    cin >> number;
    
    
    if (f(number,sto))
    {
        cout << "是快乐数" << endl;
    }else
    {
        cout << "不是快乐数" << endl;
    }
    

}
int f(int a,int s[128])
{
    s[i] = a;
    int next = 0;
    while (a != 0)
    {
        next += (a % 10) * (a % 10);
        a /= 10;
    }
    if (next == 1)
    {
        return 1;
    }else if (find(i,s))
    {
        return 0;
    }else{
        i++;
        return f(next,s);
    }
}
int find(int i,int s[128])
{
    for (int j = 0; j < i; j++)
    {
        if (s[j] == s[i])
        {
            return 1;
        }
        
    }
    return 0;
}
