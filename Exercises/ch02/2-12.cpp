/*
From:�����ݽṹ����������󷽷���C++����������������2�棩.�廪��ѧ������.����������.2007 ���� ��ϰ��2.12
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