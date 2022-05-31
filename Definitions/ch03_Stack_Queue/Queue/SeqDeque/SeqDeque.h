#ifndef SEQDEQUE_H
#define SEQDEQUE_H
#include "..\SeqQueue\SeqQueue.h"

/**
 * @brief ˫�˶��У������ʾ��
 */
template <typename T>class SeqDeque:public SeqQueue<T>{
public:
	SeqDeque(int sz = 50):SeqQueue<T>(sz){};
	~SeqDeque(){};//��̬���������飬���û�������������ͷ�
	bool getHead(T &x)const;
	bool getTail(T &x)const;
	/// @brief ͬ EnQueueTail
	bool EnQueue(const T &x){
		return EnQueueTail(x);
	}
	bool EnQueueHead(const T &x);
	bool EnQueueTail(const T &x);
	/// @brief ͬ DeQueueHead
	bool DeQueue(T &x){
		return DeQueueHead(x);
	}
	bool DeQueueHead(T &x);
	bool DeQueueTail(T &x);
};

template <typename T>bool SeqDeque<T>::getHead(T &x)const{
	T temp;
	bool tag = SeqQueue<T>::getFront(temp);
	x = temp;
	return tag;
}

template <typename T>bool SeqDeque<T>::getTail(T &x)const{
	if (this->front == this->rear)	return false;
	x = this->elements[(this->rear-1+this->maxSize)%this->maxSize];
	return true;
}

template <typename T>bool SeqDeque<T>::EnQueueHead(const T &x){
	if ((this->rear+1)%this->maxSize == this->front)	return false;
	this->front = (this->front-1+this->maxSize)%this->maxSize;//��Ϊfrontָ�����Ԫ�أ��������ƺ����
	this->elements[this->front] = x;
	return true;
}

template <typename T>bool SeqDeque<T>::EnQueueTail(const T &x){
	return SeqQueue<T>::EnQueue(x);
}

template <typename T>bool SeqDeque<T>::DeQueueTail(T &x){
	if (this->front == this->rear)	return false;
	this->rear = (this->rear-1+this->maxSize)%this->maxSize;
	return true;
}

template <typename T>bool SeqDeque<T>::DeQueueHead(T &x){
	T temp;
	bool tag = SeqQueue<T>::DeQueue(temp);
	x = temp;
	return tag;
}
#endif
