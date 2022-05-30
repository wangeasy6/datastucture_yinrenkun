#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <iostream>
#include <cassert>
using namespace std;

const int DefaultSize = 100;
enum KindOfStatus {Active,Empty,Deleted};			//Ԫ�ط��� (�/��/ɾ)

//ɢ�б��ඨ��
template <typename E, typename K>class HashTable{
public:
	HashTable(const int d, int sz = DefaultSize); 	//���캯��
	~HashTable() {delete []ht; delete []info;}		//��������
	HashTable<E,K>& operator = (const HashTable<E,K> &ht2);
	bool Search(const K k1, E &e1);					//��ɢ�б�������k1
	bool Insert(const E &e1);						//��ɢ�б��в���e1
	bool Remove(const K k1, E &e1);					//��ɢ�б���ɾ��e1
	void makeEmpty();								//��ɢ�б�Ϊ��
	void output();  //���
//	HashTable<E,K>& operator = (const HashTable<E,K> &ht2);
	friend ostream& operator << (ostream &out, HashTable<E,K> &ht2){
		for(int i = 0; i < ht2.TableSize; i++){
			if(ht2.info[i] == Active){
				out << "#" << i << ":\t"<< ht2.ht[i] << endl;
			}
			else if (ht2.info[i] == Empty){
					out << "#" << i << ":\tEmpty!" << endl;
				}
				else if (ht2.info[i] == Deleted){
					out << "#" << i << ":\tDeleted!" << endl;
					}
		}
		return out;
	}
	friend istream& operator >> (istream &in, HashTable<E,K> &ht2){
		E data;
		while (!in.eof()){
			assert(in >> data);
			ht2.Insert(data);
		}
		return in;
	}
private:
	int divitor;									//ɢ�к����ĳ���
	int CurrentSize, TableSize;						//��ǰͰ�������Ͱ��
	E *ht;											//ɢ�б�洢����
	KindOfStatus *info;								//״̬����
	int FindPos(const K k1) const;					//ɢ�к���:�����ʼͰ��
/*	int operator == (E &e1) {return *this == e1;}	//#�����غ�����Ԫ���еȡ�
	int operator != (E &e1) {return *this != e1;}	//���غ�����Ԫ���в���*/
};

//���캯��
template <typename E, typename K>HashTable<E,K>::HashTable(int d, int sz){
	divitor = d;
	TableSize = sz;
	CurrentSize = 0;
	ht = new E[TableSize];
	info = new KindOfStatus[TableSize];
	for (int i = 0; i < TableSize; i++){
		info[i] = Empty;
	}
}

// ˽�к���
// ������һ��ɢ�б��йؼ�����k1ƥ���Ԫ�أ�
// �����ɹ����������ظ�Ԫ�ص�λ�ã�
// ���򷵻ز���㣨������㹻�Ŀռ䣩
template <typename E, typename K>int HashTable<E,K>::FindPos(const K k1)const{
	int i = k1 % divitor;			//�����ʼͰ��
	int j = i;						//j�Ǽ����һ��Ͱ�±�
	do{
		if (info[j] == Empty || info[j] == Active && ht[j] == k1){
			return j;
		}
		j = (j+1) % TableSize;		//����ѭ������, ����һ����Ͱ 
	} while (j != i);
	return j;						//תһȦ�ص���ʼ��, ������, ʧ��
}

// ʹ������̽�鷨��ɢ�б�ht(ÿ��Ͱ����һ��Ԫ��)������k1��
// ���k1�ڱ��д���, ��������true,�������ò���e1�����ҵ���Ԫ�أ�
// ���k1���ڱ���, �򷵻�false��
template <typename E, typename K>bool HashTable<E,K>::Search(const K k1, E &e1){
	int i = FindPos(k1);  			//����
	if (info[i] != Active || ht[i] != k1){
		return false;
	}
	e1 = ht[i];
	return true;
}

//���ɢ�б�
template <typename E, typename K>void HashTable<E,K>::makeEmpty(){
	for (int i = 0; i < TableSize; i++){
		info[i] = Empty;                 //ֻ�轫info�����
	}
	CurrentSize = 0;
}

// ��ht��������e1��
// ���ҵ����ٲ���, ��δ�ҵ�, ��������, ���ٲ���, ����false��
// ���ҵ�λ�õı�־��Empty��Deleted, ���۱��Ƿ�����, x����, ����true��
template <typename E, typename K>bool HashTable<E,K>::Insert(const E &e1){
	K k1 = e1.key;					//���غ�������ȡ�ؼ���
	int i = FindPos(k1);			//��ɢ�к�������Ͱ��
	if (info[i] != Active){			//��Ͱ��,�����Ԫ��	
		ht[i] = e1;
		info[i] = Active;
		CurrentSize++;
		return true;
	}
	if (info[i] == Active && ht[i] == e1){
		cout << "Element existed !"<< endl;
		return false;
	}
	cout << "Table is full !"<< endl;
	return false;
}

// ��ht����ɾ��Ԫ��k1��
// �������Ҳ���k1, ����Ȼ�ҵ�k1, �����Ѿ��߼�ɾ����, �򷵻�false��
// �����ڱ���ɾ��Ԫ��k1, ����true, �������ò���e1�еõ�����
template <typename E, typename K>bool HashTable<E,K>::Remove(const K k1, E& e1){
	int i = FindPos(k1);
	if (info[i] == Active && ht[i]==k1){			//�ҵ�ҪɾԪ��, ���ǻԪ��	
		e1 = ht[i];
		info[i] = Deleted;		 	//���߼�ɾ����־, ������������ɾ��
		CurrentSize--;
		return true;			  	//ɾ���������, ���سɹ���־
	}
	else{						  	//�����ޱ�ɾԪ��, ���ز��ɹ���־	
		return false;
	}
}

template <typename E, typename K>HashTable<E,K>& HashTable<E,K>::operator = (const HashTable<E,K> &ht2){
	if (this != &ht2){
		delete []ht;               //������ƣ���Ϊ��С���ܲ�һ��
		delete []info;
		TableSize = ht2.TableSize;
		ht = new E[TableSize];
		info = new E[TableSize];
		for (int i = 0; i < TableSize; i++){
			ht[i] = ht2.ht[i];
			info[i] = ht2.info[i];
		}
		CurrentSize = ht2.CurrentSize;
	}
	return *this;
}

template <typename E, typename K>void HashTable<E,K>::output(){
	for(int i = 0; i<TableSize; i++)	{
		if(info[i] == Active){
			cout << "#" << i << ":\t"<< ht[i] << endl;
		}
		else if (info[i] == Empty){
				cout << "#" << i << ":\tEmpty!" << endl;
			}
			else if (info[i] == Deleted){
					cout << "#" << i << ":\tDeleted!" << endl;
				}
	}
}

#endif
