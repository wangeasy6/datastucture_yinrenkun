#include <fstream>
#include "CircList.h"
using namespace std;

// 循环链表示例：求解约瑟夫问题

template <class T>
void Josephus(CircList<T>& js, int n, int m)
{
    CircLinkNode<T> *p = js.Locate(1), *pre = js.getHead();
    int i,j;
    for(i = 0; i<n; i++)
    {
        for (j = 1; j<m; j++)
        {
            pre = p;
            p = p->link;
            if(p == js.getHead())
            {
                pre = js.getHead();
                p = p->link;
            }
        }

        cout << "Out:" << p->data << endl;
        // cout << js;
        pre->link = p->link;
        delete p;
        p = pre->link;
        if(p == js.getHead())
        {
            pre = js.getHead();
            p = p->link;
        }
    }
}

int main(){
    cout << "Please input n and m:";
    int n, m;
    cin >> n >> m;
    if (n < 1 || m < 1 || n<=m)
    {
        cout << "Invalid input." << endl;
        exit(0);
    }

    CircList<int> list;
    for (int i = 1; i <= n; i++)
        list.Insert(i-1,i);
    cout << "Origin List:" << list << endl;
    Josephus(list, n, m);
}