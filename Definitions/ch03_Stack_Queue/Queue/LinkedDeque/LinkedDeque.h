#ifndef LINKEDDEQUE_H
#define LINKEDDEQUE_H
#include "..\LinkedQueue\LinkedQueue.h"

/**
 * @brief 双端队列（链表表示）
 */
template <typename T>
class LinkedDeque:public LinkedQueue<T>{
public:
	LinkedDeque(){};
	~LinkedDeque(){};
	bool getHead(T &x)const;
	bool getTail(T &x)const;
	/// @brief 同 EnQueueTail
	bool EnQueue(const T &x){
		return EnQueueTail(x);
	}
	bool EnQueueHead(const T &x);
	bool EnQueueTail(const T &x);
	/// @brief 同 DeQueueHead
	bool DeQueue(T &x){
		return DeQueueHead(x);
	}
	bool DeQueueHead(T &x);
	bool DeQueueTail(T &x);
};

template <typename T>bool LinkedDeque<T>::getHead(T &x)const{
	T temp;
	bool tag = LinkedQueue<T>::getFront(temp);
	x = temp;
	return tag;
}

template <typename T>bool LinkedDeque<T>::getTail(T &x)const{
	if (!this->front)
	{
		return false;
	}
	x = this->rear->data;
	return true;
}

template <typename T>bool LinkedDeque<T>::EnQueueHead(const T &x){
	LinkNode<T> *p = new LinkNode<T>(x);
	if (!p)	return false;
	p->link = this->front;
	this->front = p;
	if (!this->front->link)	this->rear = this->front;
	return true;
}

template <typename T>bool LinkedDeque<T>::EnQueueTail(const T &x){
	return LinkedQueue<T>::EnQueue(x);
}

template <typename T>bool LinkedDeque<T>::DeQueueHead(T &x){
	T temp;
	bool tag = LinkedQueue<T>::DeQueue(temp);
	x = temp;
	return tag;
}

template <typename T>bool LinkedDeque<T>::DeQueueTail(T &x){
	if (!this->front)	return false;
	if (this->front == this->rear){
		x = this->rear->data;
		this->front = this->rear = NULL;
		return true;
	}
	LinkNode<T> *p = this->front;
	while (p->link != this->rear)	p = p->link;
	x = this->rear->data;
	p->link = NULL;
	this->rear = p;
	return true;
}
#endif
