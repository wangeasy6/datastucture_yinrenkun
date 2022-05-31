#include <fstream>
#include "LinkedList.h"
using namespace std;

int main(){
    List<int> list;
    // ifstream fin("list.txt");
    // assert(fin);
    // fin >> list;
    // cout << "The initial list in the file is:\n" << list << endl;
    list.input(0, INR);

    List<int> list_copy_1(list);
    cout << "List Copy:\n" << list_copy_1 << endl;

    List<int> list_copy_2;
    list_copy_2 = list;
    cout << "List Copy =:\n" << list_copy_2 << endl;

    cout << "List Length:" << list.Length() << endl;
    cout << "Head Addr:" << list.getHead() << " - Locate(1) Addr:" << list.Locate(1) << endl;
    cout << "List getHead:" << list.getHead() -> data << endl;
    cout << "List Search(2):" << list.Search(2) -> data << endl;
    cout << "List Locate(2):" << list.Locate(2) -> data << endl;
    int elem;
    cout << "List getData(2):"<< boolalpha << list.getData(2,elem);
    cout << " "<< elem << endl;
    elem = 11;
    list.setData(1,elem);
    cout << "List setData(1,11):"  << list << endl;
    elem = 12;
    cout << "List Insert(2,12):"<< boolalpha << list.Insert(2,elem) << list << endl;
    cout << "List Remove(2):"<< boolalpha << list.Remove(2, elem) << list << endl;
    list.Sort();
    cout << "List Sort():" << list << endl;
    cout << "List IsEmpty():"<< boolalpha << list.IsEmpty() << endl;
    list.makeEmpty();
    cout << "List makeEmpty()" << endl;
    cout << "List IsEmpty():"<< boolalpha << list.IsEmpty() << endl;

    return 0;
}