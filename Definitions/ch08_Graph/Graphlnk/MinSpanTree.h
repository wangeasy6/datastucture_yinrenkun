#ifndef MINSPANTREE_H
#define MINSPANTREE_H
#include <iostream>
#include <cassert>
using namespace std;

const double maxValue = 99999999.0;  	//�����ɱ�ʾ�ġ������в����ܳ��ֵĴ���
const int DefaultSize2=50;

//��С�������߽���������
template <typename T, typename E>struct MSTEdgeNode{//TΪ�������ͣ���ʵ����������δ��
	int tail, head;					//������λ��
	E key;							//���ϵ�Ȩֵ,Ϊ���ؼ���
	MSTEdgeNode(){					//���캯��	
		tail = -1;
		head = -1;
		key = 0;
	}		
/*	MSTEdgeNode<T,E>& operator = (const MSTEdgeNode<T,E> &x){//������Ĭ��
		tail=x.tail;
		head=x.head;
		key=x.key;
		return *this;
	}*/
	friend bool operator < (MSTEdgeNode<T,E> &n1, MSTEdgeNode<T,E> &n2);//��ģ�����Ԫ���������Ǻ���ģ��
	friend bool operator > (MSTEdgeNode<T,E> &n1, MSTEdgeNode<T,E> &n2);//���Ա��������������������ⶨ��
	friend bool operator == (MSTEdgeNode<T,E> &n1, MSTEdgeNode<T,E> &n2);
	friend bool operator <= (MSTEdgeNode<T,E> &n1, MSTEdgeNode<T,E> &n2);
};
template <typename T, typename E> bool operator < (MSTEdgeNode<T,E> &n1, MSTEdgeNode<T,E> &n2){//ֻ����������ܶ���Ϊ����ģ��
	return n1.key < n2.key;
}
template <typename T, typename E> bool operator > (MSTEdgeNode<T,E> &n1, MSTEdgeNode<T,E> &n2){
	return n1.key > n2.key;
}
template <typename T, typename E> bool operator == (MSTEdgeNode<T,E> &n1, MSTEdgeNode<T,E> &n2){
	return n1.key == n2.key;
}
template <typename T, typename E> bool operator <= (MSTEdgeNode<T,E> &n1, MSTEdgeNode<T,E> &n2){
	return n1.key <= n2.key;
}

//��С���������ඨ��
template <typename T, typename E>class MinSpanTree{
protected:
	MSTEdgeNode<T,E> *edgevalue;			//�ñ�ֵ�����ʾ��
	int maxSize, n;							//��������Ԫ�ظ����͵�ǰ����
public:
	MinSpanTree(int sz = DefaultSize2 /*- 1*/){
		maxSize = sz;
		n = 0;
		edgevalue = new MSTEdgeNode<T,E>[sz];
		assert(edgevalue);
	}
	bool Insert(MSTEdgeNode<T,E> &item);	//����item���뵽���У������нڵ��������򷵻�false;
	void output();							//�Զ��庯����˳��������б�
};


template<class T,class E>bool MinSpanTree<T,E>::Insert(MSTEdgeNode<T,E> &item){	
	if(n == maxSize){
		return false;
	}
	edgevalue[n] = item;
	n++;
	return true;
}

template<class T,class E>void MinSpanTree<T,E>::output(){
	for(int i=1; i<=n; i++){
		cout<<"Edge "<<i<<" : "<<"head = "<<edgevalue[i-1].head<<" ; tail = "<<edgevalue[i-1].tail<<" ; key = "<<edgevalue[i-1].key<<endl;
	}
}

#endif
