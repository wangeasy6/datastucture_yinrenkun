#ifndef MINHEAP_H
#define MINHEAP_H
#include <iostream>
#include <cassert>
using namespace std;
const int DefaultSize=50;

template <typename T,typename Item> class MinHeap{// TΪ�ؼ�����������ͣ�ItemΪ��¼�Ľṹ����
public:
	MinHeap(int sz = DefaultSize);//���캯���������ն�
	MinHeap(Item arr[], int n);	//���캯����ͨ��һ�����齨��
	~MinHeap(){
		delete []heap;
	}
	bool Insert(const Item &x);
	bool RemoveMin(Item &x);
	bool IsEmpty()const{
		return currentSize == 0;
	}
	bool IsFull()const{
		return currentSize == maxHeapSize;
	}	
	void MakeEmpty(){
		currentSize = 0;
	}

	void output(){//�Զ��庯����˳�������С��Ԫ��	
		for(int i = 0; i<currentSize; i++)
			cout<<heap[i]<<" ";
		cout<<endl;
	}

private: 
	Item *heap;						//�����С����Ԫ�ص�����
	int currentSize;				//��С���е�ǰԪ�ظ���
	int maxHeapSize;				//��С���������Ԫ�ظ���
	void siftDown(int start, int m);//��start��m�»�������Ϊ��С��
	void siftUp(int start);			//��start��0�ϻ�������Ϊ��С��
};

// ���캯���������ն�
template <typename T,typename Item>MinHeap<T,Item>::MinHeap(int sz){
	maxHeapSize = (DefaultSize < sz) ? sz : DefaultSize;
	heap = new Item[maxHeapSize];
	assert(heap);
	currentSize = 0;
}

// ���캯����ͨ��һ�����齨��
template <typename T,typename Item> MinHeap<T,Item>::MinHeap(Item arr[], int n)
{
	maxHeapSize = (DefaultSize < n) ? n : DefaultSize;	
	heap = new Item[maxHeapSize]; 
	assert(heap);
	for (int i = 0; i < n; i++ )
	{
		heap[i] = arr[i];
	}
	currentSize = n;
	int currentPos = (currentSize-2)/2;		//���������λ��:����֧���
	while (currentPos >= 0)					//�Ե������������γɶ�
	{
		siftDown(currentPos, currentSize -1);	//�ֲ����������»�����
		currentPos--;							//����ǰ��һ����֧���
	}
}

//˽�к�������С�ѵ��»������㷨
template <typename T,typename Item>void MinHeap<T,Item>::siftDown(int start, int m){
	int i = start, j = 2*i+1;//j��i������Ůλ��
	Item temp = heap[i]; 			
	while (j <= m){//����Ƿ����λ��	
		//��jָ������Ů�е�С��
		if (j < m && heap[j] > heap[j+1]){
			j++;
		}
		if (temp <= heap[j]){
			break;
		}
		else{
			heap[i] = heap[j];
			i = j;
			j = 2*j+1;
		}
	}
	heap[i] = temp;	//�ط�temp���ݴ��Ԫ��
}

// ˽�к�������С�ѵ��ϻ������㷨
template <typename T,typename Item>void MinHeap<T,Item>::siftUp(int start){
	int j = start, i = (j-1)/2;
	Item temp = heap[j];
	while (j > 0){ //�ظ����·������ֱ���	
		if (heap[i] <= temp){
			break;
		}
		else{
			heap[j] = heap[i];
			j = i;
			i = (i-1)/2;
		}
	}
	heap[j] = temp;	//�ط�temp���ݴ��Ԫ��
}

// ��������: ��x���뵽��С����
template <typename T,typename Item>bool MinHeap<T,Item>::Insert(const Item &x){
	if (currentSize == maxHeapSize){	//����	
		cerr << "Heap Full" << endl;
		return false;
	}
	heap[currentSize] = x;	//����
	siftUp(currentSize);	//���ϵ���
	currentSize++;			//�Ѽ�����1
	return true;
}

// ������������С�ѵ�ɾ���㷨
template <typename T,typename Item>bool MinHeap<T,Item>::RemoveMin(Item &x){
	if (!currentSize){	//�ѿ�, ����false	
		cout << "Heap empty" << endl;
		return false;
	}
	x = heap[0];		// ������СԪ��
	heap[0] = heap[currentSize-1];	//���Ԫ����������
	currentSize--;
	siftDown(0, currentSize-1);		//�������µ���Ϊ��
	return true;
}

#endif
