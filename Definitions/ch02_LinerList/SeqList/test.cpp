#include "SeqList.h"
#include <fstream>
#include <cassert>
using namespace std;

void SearchTest(SeqList<int>& list){
    int i, elem;
    while (1){
        cout << "Input the element you want to search: ";
        cin >> elem;
        if (!cin){
            cin.clear();
            cin.ignore(100,'\n');
            break;
        }
        if (elem < 0)   break;
        i = list.Search(elem);
        if (i != 0)
            cout << "The index of element " << elem << " is " << i << ".\n";
        else
            cout << "The element is not exist!\n";
    }
}

void LocateTest(SeqList<int>& list){
    int i, elem;
    while (1){
        cout << "Input the element you want to get locate: ";
        cin >> i;
        if (!cin){
            cin.clear();
            cin.ignore(100,'\n');
            break;
        }
        elem = list.Locate(i);
        if(elem)
            cout << "The locate " << i << " is " << elem << ".\n";
        else
            cout << "The locate is not exist!\n";
    }
}

void GetDataTest(SeqList<int>& list){
    int i, elem;
    while (1){
        cout << "Input the element you want to get locate: ";
        cin >> i;
        if (!cin){
            cin.clear();
            cin.ignore(100,'\n');
            break;
        }
        if(list.getData(i, elem))
            cout << "The locate " << i << " is " << elem << ".\n";
        else
            cout << "The locate is not exist!\n";
    }
}

void SetDataTest(SeqList<int>& list){
    int i, elem;
    while (1){
        cout << "Input the you want to set <i value>: ";
        cin >> i >> elem;
        if (!cin){
            cin.clear();
            cin.ignore(100,'\n');
            break;
        }
        if(list.setData(i, elem))
            cout << list;
        else
            cout << "The locate is not exist!\n";
    }
}

int main(){
    SeqList<int> list(5);
    ifstream fin("list.txt");
    assert(fin);
    fin >> list;
    cout << "The initial list in the file is:\n" << list << endl;

    SeqList<int> list_copy_1(list);
    cout << "List Copy:\n" << list_copy_1 << endl;

    SeqList<int> list_copy_2;
    list_copy_2 = list;
    cout << "List Copy =:\n" << list_copy_2 << endl;

    cout << "List Size:" << list.Size() << endl;
    cout << "List Length:" << list.Length() << endl;
    cout << "List IsEmpty:" << list.IsEmpty() << endl;
    cout << "List IsFull:" << list.IsFull() << endl;

    int i, elem;


    while(1){
        cout << "========================================\n";
        cout << "Test: 1.Search 2.Locate 3.getData 4.setData 5.Insert  6.Remove\n";
        cout << "Please enter test item serial number.(q Exit)";
        cout << "\n----------------------------------------\n";
        cin >> i;
        if (!cin) break;
        switch(i){
            case 1:
                SearchTest(list);
                break;
            case 2:
                LocateTest(list);
                break;
            case 3:
                GetDataTest(list);
                break;
            case 4:
                SetDataTest(list);
                break;
            default:
                break;
        }

    }
    return 0;

    cout << "1. Test the Insert(int i, T &elem):\n";
    while (1)   {
        cout << "Input the index i and data elem to insert: ";
        cin >> i >> elem;
        if (!cin)       {
            cin.clear();
            cin.ignore(100,'\n');
            break;
        }
        if (i < 0)  break;
        if (list.Insert(i, elem))   cout << "Insert successful!\n";
        else    cout << "Insert failed!\n";
    }
    cout << "\nAfter inserted\n" << list << endl;

    cout << "----------------------------------------\n";
    cout << "2. Test the Remove(int i, T &elem):\n";
    while (1)   {
        cout << "Input the index i in which you want to remove: ";
        cin >> i;
        if (!cin)       {
            cin.clear();
            cin.ignore(100,'\n');
            break;
        }
        if (i < 0)  break;
        if (list.Remove(i, elem))   cout << "The element " << elem << " has been removed!\n";
        else    cout << "Remove failed!\n";
    }
    cout << "\nAfter removed\n" << list << endl;

    cout << "----------------------------------------\n";

    list.Sort();
    cout << "After sorted:\n" << list << endl;

    cout << "\n----------------------------------------\n";
    cout << "End test!" << endl;
    return 0;
}