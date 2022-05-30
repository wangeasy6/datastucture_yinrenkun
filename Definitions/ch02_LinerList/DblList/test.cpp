#include "DblList.h"
#include <fstream>
#include <cassert>
using namespace std;

int main()
{
	DblList<int> list(-1);
	ifstream fin("list.txt");
	assert(fin);
	fin >> list;
	cout << "The initial list in the file is:\n" << list << endl;

	DblList<int> list_copy_1(list);
    cout << "List Copy:\n" << list_copy_1 << endl;

    cout << "List Length:" << list.Length() << endl;
    cout << "Head Addr:" << list.getHead() << " - Locate(1) Addr:" << list.Locate(1) << endl;
    cout << "List getHead:" << list.getHead() -> data << endl;
    cout << "List Search(2):" << list.Search(2) -> data << endl;
    cout << "List Locate(2):" << list.Locate(2) -> data << endl;
    int elem;
    elem = 12;
    cout << "List Insert(2,12):"<< boolalpha << list.Insert(2,elem, 1) << list << endl;
    cout << "List Remove(2):"<< boolalpha << list.Remove(2, elem, 1) << list << endl;
    cout << "List IsEmpty():"<< boolalpha << list.IsEmpty() << endl;
    list.makeEmpty();
    cout << "List makeEmpty()" << endl;
    cout << "List IsEmpty():"<< boolalpha << list.IsEmpty() << endl;

    return 0;
}

