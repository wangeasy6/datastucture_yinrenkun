/*
From:《数据结构（用面向对象方法与C++语言描述）》（第2版）.清华大学出版社.殷人昆主编.2007 —— 练习题2.12
*/

#include "definition\sequential_list.h"

using namespace std;

void merge(SeqList<int>& A, SeqList<int>& B, SeqList<int>& C)
{
    int al = A.Length();
    int bl = B.Length();
    cout << al << " : " << bl << endl;
    int t1, t2;
    int ci = 0, ai = 1, bi = 1;
    while(ai <= al && bi <= bl)
    {
        A.getData(ai, t1);
        B.getData(bi, t2);
        // cout << ci << ":" << t1 << " vs " << t2 << endl;
        if(t1 < t2)
        {
            C.Insert(ci, t1);
            ai++;
        }
        else
        {
            C.Insert(ci, t2);
            bi++;
        }
        ci++;
    }
    for(; ai <= al; ai++,ci++)
    {
        A.getData(ai, t1);
        C.Insert(ci, t1);
    }
    for(; bi <= bl; bi++,ci++)
    {
        B.getData(bi, t2);
        C.Insert(ci, t2);
    }
}

int main(int argc, char const *argv[])
{
    SeqList<int> A, B, C;
    int t;
    for(int i = 0; i < 5; i++)
    {
        t = i*2;
        A.Insert(i, t);
    }
    for(int i = 1; i <= 3; i++)
    {
        t = i*2-1;
        B.Insert(i-1, t);
    }

    A.output();
    B.output();
    merge(A, B, C);
    C.output();

    return 0;
}