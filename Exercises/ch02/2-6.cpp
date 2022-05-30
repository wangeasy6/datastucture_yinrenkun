#include <iostream>
using namespace std;

template <class T>
void reverseN(T *org, int n)
{
    if (n < 2)
        return;

    T t;
    for (int i = 0; i < n/2; i++)
    {
        t = org[i];
        org[i] = org[n-i-1];
        org[n-i-1] = t;
    }
}

void printArray(int *a, int n)
{
    for (int i = 0; i<n; i++)
    {
        cout << "#" << i+1 << ":" << a[i] << endl;
    }
}

int main()
{
    int a[10] = {1,2,3,4,5,6,7,8,9,10};
    cout << "Origin:" << endl;
    printArray(a, 10);
    reverseN(a, 5);
    cout << "reverseN(a, 5):" << endl;
    printArray(a, 10);
    reverseN(a, 2);
    cout << "reverseN(a, 2):" << endl;
    printArray(a, 10);

    return 0;
}