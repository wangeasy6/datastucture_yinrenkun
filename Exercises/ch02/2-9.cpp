#include <iostream>
using namespace std;

template <class T>
void Reverse(T A[], int st, int ed, int arraySize){
    if(st>ed|| ed >= arraySize){
        cerr<<"Invalid parameters."<<endl;
        return;
    }
    int md = (st+ed)/2;
    for(int i=0; i<=md-st; i++)
    {
        T temp = A[st+i];
        A[st+i] = A[ed - i];
        A[ed - i] = temp;
    }
}

template <class T>
void Exchange(T A[], int m, int n, int arraySize){
    Reverse(A, 0, m+n-1, arraySize);
    Reverse(A, 0, n-1, arraySize);
    Reverse(A, n, m+n-1, arraySize);
}

#define ARR_LEN(array) sizeof(array) / sizeof(array[0])
void printArray(int *a, int n)
{
    for (int i = 0; i<n; i++)
    {
        cout <<  a[i] << " ";
    }
    cout << endl;
}

int main(int argc, char const *argv[])
{
    int A[10] = {1,2,3,4,5,6,7,8,9,10};

    cout << "Origin:" << endl;
    printArray(A, ARR_LEN(A));

    cout << "Exchange(A, 4, 6, 10):" << endl;
    Exchange(A, 4, 6, 10);
    printArray(A, ARR_LEN(A));
    return 0;
}