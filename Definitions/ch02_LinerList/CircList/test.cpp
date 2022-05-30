#include <fstream>
#include "CircList.h"
using namespace std;

int main(){
    CircList<int> list;
    ifstream fin("list.txt");
    assert(fin);
    fin >> list;
    cout << "The initial list in the file is:\n" << list << endl;
    // list.input(0, INR);

    CircList<int> list_copy_1(list);
    cout << "CircList Copy:\n" << list_copy_1 << endl;

    CircList<int> list_copy_2;
    list_copy_2 = list;
    cout << "CircList Copy =:\n" << list_copy_2 << endl;

    cout << "CircList Length:" << list.Length() << endl;
    cout << "Head Addr:" << list.getHead() << " - Locate(1) Addr:" << list.Locate(1) << endl;
    cout << "CircList getHead:" << list.getHead() -> data << endl;
    cout << "CircList Search(2):" << list.Search(2) -> data << endl;
    cout << "CircList Locate(2):" << list.Locate(2) -> data << endl;
    int elem;
    cout << "CircList getData(2):"<< boolalpha << list.getData(2,elem);
    cout << " "<< elem << endl;
    elem = 11;
    list.setData(1,elem);
    cout << "CircList setData(1,11):"  << list << endl;
    elem = 12;
    cout << "CircList Insert(2,12):"<< boolalpha << list.Insert(2,elem) << list << endl;
    cout << "CircList Remove(2):"<< boolalpha << list.Remove(2, elem) << list << endl;
    list.Inverse();
    cout << "CircList Inverse():" << list << endl;
    cout << "CircList IsEmpty():"<< boolalpha << list.IsEmpty() << endl;
    list.makeEmpty();
    cout << "CircList makeEmpty()" << endl;
    cout << "CircList IsEmpty():"<< boolalpha << list.IsEmpty() << endl;

}