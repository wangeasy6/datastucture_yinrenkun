#include "dataList.h"
#include "MySort.h"
#include "person.h"
#include <fstream>
using namespace std;

// ������RadixSort�㷨��������
// ȡperson��Ԫ��p�Ĺؼ���ĵ�dλ���ֵ�ֵ��radixΪ������
int getDigit(person &p, int d, int R = radix){
	long key = p.getID();
	key = key<0?(-key):key;
	for (int i = 1; i < d; i++){
		key = key/R;
	}
	return key%R;
}

// MySort.h�еĸ������㷨ʹ��ʾ����
// ���ڸ������㷨�У�����RadixSort�⣬��������������������һ����
// ��ˣ�����ֻ����RadixSort�������������е�ĳһ����ʾ�������㷨��ʹ�á�
int main(){
	ifstream fin("persons.txt");
	assert(fin);
	dataList<person,long> sc1, sc2;
	assert(fin >> sc1);
	sc2 = sc1;

	cout << "The origin datalist is:\n" << sc1 << endl;
	int (*gd)(person &,int,int) = getDigit;
	RadixSort<person,long>(sc1, 0, sc1.Length()-1, 3, gd);//#ģ��ʵ�����ݳ������壬������ʽָ��
	cout << "Use RadixSort to sort the datalist, then the list is:\n" << sc1 << endl;

	cout << "====================================================\n";
	sc1=sc2;
	BubbleSort(sc1, 0, sc1.Length()-1);
	cout << "Use BubbleSort to sort the datalist, then the list is:\n" << sc1 << endl;

	cout << "====================================================\n";
	sc1=sc2;
	ShakerSort(sc1, 0, sc1.Length()-1);
	cout << "Use ShakerSort to sort the datalist, then the list is:\n" << sc1 << endl;

	cout << "====================================================\n";
	sc1=sc2;
	SelectSort(sc1, 0, sc1.Length()-1);
	cout << "Use SelectSort( to sort the datalist, then the list is:\n" << sc1 << endl;

	cout << "Press enter to continue!\n";
	char ch;
	cin.get(ch);

	cout << "====================================================\n";
	sc1=sc2;
	InsertSort(sc1, 0, sc1.Length()-1);
	cout << "Use InsertSort to sort the datalist, then the list is:\n" << sc1 << endl;

	cout << "====================================================\n";
	sc1=sc2;
	BinaryInsertSort(sc1, 0, sc1.Length()-1);
	cout << "Use BinaryInsertSort to sort the datalist, then the list is:\n" << sc1 << endl;

	cout << "====================================================\n";
	sc1=sc2;
	ShellSort(sc1, 0, sc1.Length()-1);
	cout << "Use ShellSort to sort the datalist, then the list is:\n" << sc1 << endl;

	cout << "====================================================\n";
	sc1=sc2;
	QuickSort(sc1, 0, sc1.Length()-1);
	cout << "Use QuickSort to sort the datalist, then the list is:\n" << sc1 << endl;

	cout << "Press enter to continue!\n";
	cin.get(ch);

	cout << "====================================================\n";
	sc1=sc2;
	MergeSort(sc1, 0, sc1.Length()-1);
	cout << "Use MergeSort to sort the datalist, then the list is:\n" << sc1 << endl;

	cout << "====================================================\n";
	sc1=sc2;
	HeapSort(sc1, 0, sc1.Length()-1);
	cout << "Use HeapSort to sort the datalist, then the list is:\n" << sc1 << endl;

	cout << "====================================================\n";
	sc1=sc2;
	BSTSort(sc1, 0, sc1.Length()-1);
	cout << "Use BSTSort to sort the datalist, then the list is:\n" << sc1 << endl;

	cout << "====================================================\n";
	sc1=sc2;
	CountSort(sc1, 0, sc1.Length()-1);
	cout << "Use CountSort to sort the datalist, then the list is:\n" << sc1 << endl;

	cout << "Press enter to exit!\n";
	cin.get(ch);

	return 0;
}

