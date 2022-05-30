#include <iostream>

using namespace std;

#define ARR_LEN(array) sizeof(array) / sizeof(array[0])

int split(int *A, int a_n, int B[], int *C)
{
    for(int i=0, b_n=0, c_n=0; i < a_n; i++)
    {
        if(A[i] > 0)
            B[b_n++] = A[i];
        else
            C[c_n++] = A[i];
    }
    return 0;
}

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
    int A[7] = {1, 2, -1, -2, 5, -6, 7};
    int B[4], C[3];

    cout << "(A):" << endl;
    printArray(A, ARR_LEN(A));

    split(A, ARR_LEN(A), B, C);

    cout << "(B):" << endl;
    printArray(B, ARR_LEN(B));

    cout << "(C):" << endl;
    printArray(C, ARR_LEN(C));

    return 0;
}