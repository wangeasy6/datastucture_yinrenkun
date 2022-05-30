#ifndef STATICLINKEDLIST_H
#define STATICLINKEDLIST_H
#include <iostream>
using namespace std;

const int DefaultSize = 50;
const int maxData =32767;
const int radix = 6/*4*/;//С������,���������С��λ�����йأ���������0~999������radixȡ10����λ��dȡ3��10��3�η�����1000��������radixȡ6����λ��dȡ4��6��4�η�����1000��

template <typename T>struct Element{
    T key;
    int link;
	Element(){
		link = 0;
	}
	Element(T x, int next = 0){
		key = x;
		link = next;
	}
};

template <typename T>class StaticLinkedList{
public:
	StaticLinkedList(int sz = DefaultSize){
        maxSize = sz;  n = 0; 
        Vector = new Element<T>[sz];
    }
	Element<T>& operator [] (int i){
		return Vector[i];
	}
	void input();					//�Զ��庯������������һ������
	void input(T *A, int size);
	void output();//�Զ��庯�����������һ������
	void aoutput(){
		int i;
		for(i=1;i<=n;i++) cout<<Vector[i].key<<" ";
		cout<<endl;
	}
	int Length(){return n;}			//�Զ��庯�������ر�
private:
	Element<T> *Vector;				//�洢Ԫ�ص�����
	int maxSize;	     			//���Ԫ�ظ���
    int n;							//��ǰԪ�ظ���
};

template <typename T>void StaticLinkedList<T>::input(){
	cout << "please input the number of nodes : " << endl;
	int c;
	cin >> c;
	cout << "Please input the value of these nodes : ";
	for (int i = 1; i <= c; i++){
		cin >> Vector[i].key;
		Vector[i].link = i+1;
	}
	Vector[c].link = 0;
	Vector[0].link = 1;
	n = c;
}

template <typename T>void StaticLinkedList<T>::input(T *A, int c){
	for (int i = 1; i <= c; i++){
		Vector[i].key = A[i-1];;
		Vector[i].link = i+1;
	}
	Vector[c].link = 0;
	Vector[0].link = 1;
	n = c;
}


template <typename T>void StaticLinkedList<T>::output(){
	int p=Vector[0].link;
	for(int i = 0; i < n; i++){
		cout << Vector[p].key << " ";
		p = Vector[p].link;
	}
}

template <typename T>int getDigit(Element<T> &e1, int d, int R = radix){
	T key = e1.key;
	key = key<0?(-key):key;
	for (int i = 1; i < d; i++){
		key = key/R;
	}
	return key%R;
}

// ��������
template <typename T>void insertSort(StaticLinkedList<T> &L){
    L[0].key = maxData;   
    L[0].link = 1;
	L[1].link = 0;
	int i, pre, p;
    for (i = 2; i <= L.Length(); i++)	{	
        p = L[0].link;
        pre = 0;
        while (L[p].key <= L[i].key)        {
			pre = p;
			p = L[p].link;
		}
        L[i].link = p;
		L[pre].link = i;
	}
}

// ѡ������
template <typename T>void selectSort(StaticLinkedList<T> &L){
    int f = L[0].link, p, q, r, s;  //pΪ�����������ָ�룬q�����sָ�����r�����
    L[0].link = 0;
    while (f != 0){
        p = s = f;
		q = r = 0;
        while (p != 0){
			if (L[p].key > L[s].key ){
				s = p;
				r = q;
			}
			q = p;  p = L[p].link;
		}
		if (s == f ){
			f = L[f].link;
		}
		else{
			L[r].link = L[s].link;
		}
		L[s].link = L[0].link;//����ʱ��ǰ���ɣ�������ĵ���β
		L[0].link = s;
	}
}

template <typename T>int ListMerge(StaticLinkedList<T> &L, int s1, int s2){//s1��s2Ϊ����������ĵ�1������±�
    int k = 0,  i = s1,  j = s2; 
    while (i != 0 && j != 0){
        if (L[i].key <= L[j].key){
			L[k].link = i;
			k = i;
			i = L[i].link;
		}
        else{
			L[k].link = j;
			k = j;
			j = L[j].link;
		}
	}
	if (i == 0){
		L[k].link = j;
	}
	else{
		L[k].link = i;
	}
	return L[0].link;
}

// �鲢����
template <typename T>int rMergeSort(StaticLinkedList<T> &L, int left, int right){
    if (left >= right){
		return left;
	}
    int mid = (left+right)/2;
	L[mid].link=0;
	return ListMerge(L, rMergeSort(L,left, mid),
					rMergeSort(L, mid+1,right));
}

// LSD��������
template <typename T>void radixSort(StaticLinkedList<T> &L, int d, int (*getDigit)(Element<T> &, int, int)){
	int rear[radix], front[radix];
	int i, j, k, last, current, n = L.Length();
	for (i = 0; i < n; i++){
		L[i].link = i+1;
	}
	L[n].link = 0;
	current = 1;
	for (i = d; i >= 1; i--){
		for (j = 0; j < radix; j++){
			front[j] = 0;
		}
		while (current != 0){
			k = getDigit(L[current], d-i+1, radix);
			if (front[k] == 0){
				front[k] = current;
			}
			else{
				L[rear[k]].link = current;
			}
			rear[k] = current;
			current = L[current].link;
		}
		j = 0;
		while (front[j] == 0){
			j++;
		}
		L[0].link = current = front[j];
		last = rear[j];
		for (k = j+1; k < radix; k++){
			if (front[k] != 0){
				L[last].link = front[k];
				last = rear[k];
			}
		}
		L[last].link = 0;
	}
}

template <typename T>void ReArrange(StaticLinkedList<T> &L){
	int i = 1, head = L[0].link;//#ȱ.link
	Element<T> temp;
	while (head != 0){
		temp = L[head];
		L[head] = L[i];
		L[i] = temp;
		L[i].link = head;
		head = temp.link;
		i++;
		while (head < i && head > 0){
			head = L[head].link;
		}
	}
}
#endif
