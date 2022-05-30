#ifndef SORTEDLIST_H
#define SORTEDLIST_H
#include <iostream>
#include "SeqList.h"
using namespace std;

extern const int defaultSize;

long Fib(int n){
	int i;
	if (n == 0 || n == 1){
		return n;
	}
	int twoback = 0, oneback = 1, current;
	for ( i = 2; i <= n; i++){
		current = twoback + oneback;
		twoback = oneback;
		oneback = current;
	}
	return current;
}

template <typename E, typename K>class SortedList:public SeqList<E>{
public:
	void Insert(const K k1, E &e1);
	bool Remove(const K k1, E &e1);
	int Search(K k1)const;
	int BinarySearch(K k1)const;
	int BinarySearch(K k1, int low, int high)const;
	int FibonacciSearch(K k1)const;
};

template <typename E, typename K>void SortedList<E,K>::Insert(const K k1, E &e1){//���������
	int i,j;
	for (i = 0; i <= last; i++)	{	//���ԸĽ�Ϊ�Ƚ����ƶ�һ�����
		if (data[i] == k1){			//�ҵ��Ǹ���
			data[i] = e1;
			return;
		}
		if (data[i] > k1){			//δ�ҵ��ǲ���
			break;
		}
	}
	for (j = last; j >= i; j--){	//���ƺ����
		data[j+1] = data[j];
	}
	data[i] = e1;
	last++;
}

template <typename E, typename K>bool SortedList<E,K>::Remove(const K k1, E &e1){
	if (last == -1){
		return false;
	}
	int i,j;
	for (i = 0; i <= last; i++){
		if (data[i] > k1){
			return false;
		}
		if (data[i] == k1){
			e1 = data[i];
			break;
		}
	}
	for (j = i; j <= last; j++){
		data[j] = data[j+1];
	}
	last--;
	return true;
}

template <typename E, typename K>int SortedList<E,K>::Search(K k1)const{//˳�����
	int i;
	for ( i = 0; i <= last; i++){
		if (data[i] == k1){
			return i+1;
		}
		if (data[i] > k1){
			break;
		}
	}
	return 0;
}

template <typename E, typename K>int SortedList<E, K>::BinarySearch(K k1, int low, int high)const{//�ݹ�԰����
	int mid = 0;
	if (low <= high){
		mid = (low + high) / 2;
		if (data[mid-1] < k1){
		   mid = BinarySearch(k1, mid +1, high);
		}
		else if (data[mid-1] > k1){
		   mid = BinarySearch(k1, low, mid-1);
		}
	}
	return mid;
}

template <typename E, typename K> int SortedList<E,K>::BinarySearch(K k1)const{//�����԰����
	int high = last + 1, low = 1, mid;
	while (low <= high){		 
		mid = (low + high) / 2;
		if (data[mid-1] < k1){
			low = mid+1;
		}			
		else if (data[mid-1] > k1){
				high = mid-1;
			}
			else{
				return mid;
			}
	}
    return 0;
}

template <typename E, typename K>	int SortedList<E,K>::FibonacciSearch(K k1)const{//쳲���������
	int i = 1,j;
	while (Fib(i) < last+1){	//FibҲҪ���㣬����*0.618�����;��ð�����һ��ӳ�����Fibֵ
		i++;
	}
	if (i < 3){
		return BinarySearch(k1);
	}
	if (Fib(i) > last+1){
		for ( j = last+1; j < Fib(i)-1; j++){	//�����Ԫ�أ��ƽ�ָ�����Ƽ���
			data[j] = data[j-1] + 1;
		}
	}
	int d1 = Fib(i-2), d2 = Fib(i-3), mid = Fib(i-1);
	while (d2 >= 0 && d1 >= 0){
		if (data[mid-1] < k1){
			mid = mid + d2;
			d1 = d1 - d2;
			d2 = d2 - d1;
		}
		else if (data[mid-1] > k1){
				mid = mid - d2;
				int tmp = d1;
				d1 = d2;
				d2 = tmp - d2;
			}
			else{
				return (mid-1 > last)?0:mid;
			}
	}
    return 0;
}
#endif
