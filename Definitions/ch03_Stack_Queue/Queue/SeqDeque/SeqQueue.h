#ifndef SEQQUEUE_H
#define SEQQUEUE_H
#include <cassert>
#include <iostream>
using namespace std;

template <typename T>class SeqQueue{
public:
	SeqQueue(int sz = 50);
	~SeqQueue(){
		delete[] elements;
	}
	bool EnQueue(const T &x);	//����
	bool DeQueue(T &x);			//����
	bool getFront(T &x)const;
	void makeEmpty(){
		front = rear = 0;
	}
	bool IsEmpty()const{
		return front == rear;
	}
	bool IsFull()const{
		return (rear+1)%maxSize == front;//�����㷨
	}
	int getSize()const{
		return (rear-front+maxSize)% maxSize;//�ر�ע��˴��㷨
	}
	friend ostream& operator<<(ostream & os,SeqQueue<T> &Q){
		os << "front = " << Q.front << ", rear = " << Q.rear << endl;
		for (int i = Q.front; i != Q.rear; i = (i+1) % Q.maxSize){
			os << "#" << i <<": " << Q.elements[i] << endl;
		}			
		os << "Queue Size: " << Q.getSize() << endl;
		return os;
	}
protected:
	int rear, front;
	T *elements;
	int maxSize;
};

template <typename T>SeqQueue<T>::SeqQueue(int sz){
	front = 0;
	rear = 0;
	maxSize = sz;
	elements = new T[maxSize];
	assert(elements != NULL);
}

// �ú����ɸĽ�
template <typename T>bool SeqQueue<T>::EnQueue(const T &x){
	if (IsFull())	return false;
	elements[rear] = x;
	rear = (rear+1) % maxSize;
	return true;
}


// �ú����ɸĽ�
template <typename T>bool SeqQueue<T>::DeQueue(T &x){
	if (IsEmpty())	return false;
	x = elements[front];
	front = (front+1) % maxSize;
	return true;
}

template <typename T>bool SeqQueue<T>::getFront(T &x)const{
	if (IsEmpty())	return false;
	x = elements[front];
	return true;
}
#endif
