#include "SeqList.h"
#include <iostream>
#include <fstream>
#include "limits.h"
using namespace std;

// (1)
template <class T>
T DelMin(SeqList<T> &seq){
    int len = seq.Length();
    if(len <= 0)
    {
        cerr << "[DelMin] List is null." << endl;
        exit(0);
    }

    int index = 0, i = 0;
    T t, min = INT_MAX;
    for(; i < len; i++)
    {
        seq.getData(i+1, t);
        if (min > t)
        {
            min = t;
            index = i+1;
        }
    }
    if(i == index)
        seq.Remove(len, t);
    else
    {
        seq.setData(index, t);
        seq.Remove(len, t);
    }
    return min;
}

// (2)
template <class T>
T DelIndex(SeqList<T> &seq, int i)
{
    T t;
    if (!seq.Remove(i, t))
    {
        cerr << "[DelIndex] Error index:" << i << endl;
        exit(0);
    }
    return t;
}

// (3)
template <class T>
void InsertNew(SeqList<T> &seq, int i, T& x)
{
    if(!seq.Insert(i, x))
    {
        cerr << "[InsertNew] Error index:" << i << endl;
        exit(0);
    }
}

// (4)
template <class T>
void DelX(SeqList<T> &seq, T& x)
{
    int i = seq.Search(x);
    if(i)
    {
        seq.Remove(i, x);
    }
    else
    {
        cerr << "[DelX] Not Find:" << x << endl;
        exit(0);
    }
}

// (5)
template <class T>
void DelRange(SeqList<T> &seq, T& min, T& max)
{
    if(min >= max)
    {
        cerr << "[DelRange] min big than max." << endl;
        exit(0);
    }
    int len = seq.Length();
    if (len <= 0)
    {
        cerr << "[DelRange] List is null." << endl;
        exit(0);
    }

    T t;
    for(int i = 1; i<=len; i++)
    {
        seq.getData(i, t);
        if(min<t && t<max){
            seq.Remove(i, t);
            cout << "[DelRange] Remove:" << t << endl;
            i--;
            len--;
        }
    }
}

// (6)
template <class T>
void DelOrderedRange(SeqList<T> &seq, T& min, T& max)
{
    if(min >= max)
    {
        cerr << "[DelOrderedRange] min big than max." << endl;
        exit(0);
    }
    int len = seq.Length();
    if (len <= 0)
    {
        cerr << "[DelOrderedRange] List is null." << endl;
        exit(0);
    }

    T t;
    for(int i = 1; i<=len; i++)
    {
        seq.getData(i, t);
        if(t>min)
        {
            for(; i<=len, t<max; i++)
            {
                if(t<max)
                {
                    seq.Remove(i, t);
                    cout << "[DelOrderedRange] Remove:" << t << endl;
                    seq.getData(i, t);
                    i--;
                    len--;
                }
                else
                    break;
            }
            break;
        }
    }
}

// (7)
template <class T>
SeqList<T>* MergeList(const SeqList<T> &seq1,const SeqList<T> &seq2)
{
    SeqList<T> *seq3 = new SeqList<T>;
    int len = seq1.Length() + seq2.Length();
    T s1,s2;
    for(int i = 0,i1=1,i2=1; i < len; i++)
    {
        if (seq1.getData(i1, s1))
        {
            if (seq2.getData(i2, s2))
            {
                if(s1 < s2)
                {
                    seq3->Insert(i, s1);
                    i1++;
                }
                else
                {

                    seq3->Insert(i, s2);
                    i2++;
                }
            }
            else
            {
                    seq3->Insert(i, s1);
                    i1++;
            }
        }
        else
        {
            if(seq2.getData(i2, s2))
            {
                seq3->Insert(i, s2);
                i2++;
            }
        }
    }
    return seq3;
}

// (8)
template <class T>
void ListTrim(SeqList<T> *seq)
{
    int len = seq->Length();
    T t, tt;
    for(int i = 1; i<len; i++)
    {
        if(seq->getData(i, t))
            for(int j = i+1; j<len; j++)
            {
                seq->getData(j, tt);
                if(t == tt)
                {
                    seq->Remove(j, tt);
                    j--;
                    len--;
                }
            }
    }
}

int main(int argc, char const *argv[])
{
    SeqList<int> list;
    ifstream fin("list.txt");
    assert(fin);
    fin >> list;
    cout << "The initial list in the file is:\n" << list << endl;

    // (1)
    cout << "\nDelMin:" << DelMin(list);
    list.output();

    // (2)
    cout << "\nDelIndex(2):" << DelIndex(list, 2);
    list.output();
    // cout << "DelIndex(0):" << DelIndex(list, 0) << endl;
    // list.output();
    // cout << "DelIndex(15):" << DelIndex(list, 15) << endl;
    // list.output();

    // (3)
    int x = 20;
    InsertNew(list, 3, x);
    cout << "\nInsertNew(3, 20):";
    list.output();

    // (4)
    // x = 21;
    DelX(list, x);
    cout << "\nDelX(20)";
    list.output();

    // (5)
    int s = 6, t = 9;
    DelRange(list, s, t);
    cout << "\nDelRange(6,9):";
    list.output();

    // (6)
    s = 2, t = 6;
    DelOrderedRange(list, s, t);
    cout << "\nDelOrderedRange(2,6):";
    list.output();

    // (7)
    SeqList<int> list1, list2;
    int i = 1;
    for(; i < 5; i++)
        list1.Insert(i-1, i);
    for(i = 3; i < 7; i++)
        list2.Insert(i-3, i);
    list1.output();
    list2.output();

    SeqList<int> *list3;
    list3 = MergeList(list1, list2);
    // MergeList(list1, list2).output();
    list3->output();

    // (8)
    ListTrim(list3);
    cout << "\nList3 Trim:";
    list3->output();
    delete list3;

    return 0;
}