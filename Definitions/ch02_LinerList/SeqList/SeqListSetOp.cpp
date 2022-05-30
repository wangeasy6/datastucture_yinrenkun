// ˳����Ӧ�ã����ϵĲ�����ͽ�����

#include "SeqList.h"
#include <fstream>
#include <cassert>
using namespace std;

// �ϲ�˳���LA��LB���������LA���ظ�Ԫ��ֻ��1��
void Union(SeqList<int>& LA, SeqList<int>& LB)
{
    int n = LA.Length(), m = LB.Length(), i, k, x;
    for(i = 1; i<=m; i++)
    {
        LB.getData(i, x);
        k = LA.Search(x);
        if(k == 0)
        {
            LA.Insert(n, x);
            n++;
        }
    }
}

// ����Ԫ�أ��������LA
void Intersection(SeqList<int>& LA, SeqList<int>& LB)
{
    int n = LA.Length(), m = LB.Length(), i = 1, k, x;
    while(i <= n)
    {
        LA.getData(i, x);
        k = LB.Search(x);
        if (k == 0)
        {
            LA.Remove(i, x);
            n--;
        }
        else
            i++;
    }
}

int main(){
    SeqList<int> A(5);
    SeqList<int> B(5);
    A.input();
    B.input();
    SeqList<int> LA(A);
    Union(A, B);
    cout << "\nUnion:\n" << A << endl;
    Intersection(LA, B);
    cout << "Intersection:\n" << LA << endl;
    return 0;
}