#include <iostream>
using namespace std;

template <class T>
void compactMy(T *A, int n)
{
    if (n < 1)
        return;

    for(int j,i = 0; i < n; i++)
    {
        // 0元素和下一个非0元素替换
        if(A[i] == 0)
        {
            for(j=i+1; j < n; j++)
            {
                if (A[j] != 0 )
                {
                    A[i] = A[j];
                    A[j] = 0;
                    cout << "Change :" << i << " " << j << endl;
                    break;
                }
            }
            // 0元素之后找不到非0元素，则停止
            if(j == n)
                break;
        }
    }
    return;
}

template <class T>
void compact(T *A, int n)
{
    int free = 0;
    for (int i = 0; i < n; i++)
    {
        // 找到非0，和0换
        if(A[i] != 0)
        {
            if(i!=free)
            {
                A[free] = A[i];
                A[i] = 0;
                cout << "free:"<<free<<"  i:"<<i<<endl;
            }
            free++;
        }
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
    int a[10] = {0,2,0,0,4,0,6,8,0,10};
    cout << "Origin:" << endl;
    printArray(a, 10);
    compact(a, 10);
    cout << "compact:" << endl;
    printArray(a, 10);

    return 0;
}