/**
 * @brief 利用链式队列实现逐行打印杨辉三角的前n行
 */

#include <stdio.h>
#include <iostream>
#include "LinkedQueue.h"

void YANGVI(int n){
    LinkedQueue<int> q;
    int i = 1, j, s = 0, k = 0, t, u;
    q.EnQueue(i); q.EnQueue(i);
    for(i = 1; i<=n; i++)
    {
        cout << endl;
        q.EnQueue(k);
        for(j = 1; j<=i+2; j++)
        {
            q.DeQueue(t);
            u = s+t;
            q.EnQueue(u);
            s = t;
            if(j!=i+2)
                cout << s << " ";
        }
    }
}

int main()
{
    cout << "YANGVI(6):";
    YANGVI(6);
    return 0;
}