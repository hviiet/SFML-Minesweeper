#include <iostream>
using namespace std;
int main()
{
    int count = 0;
    for (int i = 10000; i <= 99999; i++)
    {
        int a = i / 10000;
        int b = (i / 1000) % 10;
        int c = (i / 100) % 10;
        int d = (i / 10) % 10;
        int e = i % 10;
        if (a + b + c + d + e == 7)
            count++;
    }
    cout << count << endl;
}