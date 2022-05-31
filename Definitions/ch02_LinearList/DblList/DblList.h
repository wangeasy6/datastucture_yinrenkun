#ifndef DBLLIST_H
#define DBLLIST_H

//

#include <iostream>
#include <cassert>
using namespace std;

template <typename T>struct DblNode{
	T data;
	DblNode<T> *rLink, *lLink;
	DblNode(DblNode<T> *l = NULL, DblNode<T> *r = NULL){
		lLink = l;
		rLink = r;
	}
	DblNode(T value, DblNode<T> *l = NULL, DblNode<T> *r = NULL){
		data = value;
		lLink = l;
		rLink = r;
	}
};

/** @brief ˫����������ͷ��㣩 */
template <typename T>class DblList{
public:
	DblList(T uniqueVal){
		first = new DblNode<T>(uniqueVal);
		assert(first);
		first->rLink = first->lLink = first;
	}
	~DblList()	{//��������������
		makeEmpty();
		delete first;//�ͷŸ���ͷ���
	}
	int Length()const;
	void makeEmpty(){//��
		DblNode<T> *q;
		while (first->rLink != first){//���฽��ͷ���
			q = first->rLink;//�Ȳ�����ָ��
			first->rLink = q->rLink;
			delete q;
		}
		first->lLink=first;//�����
	}
	DblNode<T> *getHead()const{
		return first;
	}
	DblNode<T> *Search(const T &x, int d = 1);
	DblNode<T> *Locate(int i, int d = 1);
	//�������ж�λ���Ϊi(��0)�Ľ��, d=0��ǰ����
	//��,d��0����̷���
	bool Insert(int i, const T &x, int d = 1);
	//�ڵ�i���������һ��������ֵx���½��,d=0
	//��ǰ������,d��0����̷���
	bool Remove(int i, T &x, int d);
	bool IsEmpty(){
		return first->rLink == first;
	}
	bool IsFull(){
		return false;
	}
	friend istream& operator >> (istream& in, DblList<T> &dbl){//��
		int i = 0;
		T data;
		dbl.makeEmpty();
		while (!in.eof()){
			in >> data;
			dbl.Insert(i, data, 1);
			i++;
		}
		return in;
	}

	friend ostream & operator << (ostream &out, DblList <T> &dbl)	{
		DblNode <T> *p= dbl.first->rLink;
		while ( p!=dbl.first ){
			out << p->data <<'\t';
			p = p->rLink;
		}
		cout << endl;
		return out;
	}
private:
	DblNode<T> *first;
};

template <typename T>int DblList<T>::Length()const{
	DblNode<T> * current = first->rLink; int count = 0;
	while(current != first){
		current = current->rLink;
		count++;
	}
	return count;
}

template <typename T>DblNode<T> *DblList<T>::Locate(int i, int d){//d==1����
	if (first->rLink == first || i==0){
		return first;
	}
	DblNode<T> *current = (d == 0)?first->lLink:first->rLink;
	while (current != first && --i > 0){
		current = (d == 0)?current->lLink:current->rLink;
	}
	return (current == first)?NULL:current;
}

template <typename T>DblNode<T> *DblList<T>::Search(const T &x, int d){//�˺���������������ν
	DblNode<T> *current = (d == 0)?first->lLink:first->rLink;
	while (current != first && current->data != x)	{
		current = (d == 0)?current->lLink:current->rLink;
	}
	return (current == first)?NULL:current;
}

template <typename T>bool DblList<T>::Insert(int i, const T &x, int d){
	//����һ��������ֵx���½��, �����䰴 d ָ���ķ�����뵽��i�����֮��
	DblNode<T> *current = Locate(i, d);
	if (current == NULL){
		return false;    //����ʧ��
	}
	DblNode<T> *newNode = new DblNode<T>(x);
	assert(newNode);
	if (d == 0){		//ǰ������:���ڵ�i��������	
		newNode->lLink = current->lLink;
		current->lLink = newNode;
		newNode->lLink->rLink = newNode;
		newNode->rLink = current;
	}
	else{			//��̷���:���ڵ�i��������	
		newNode->rLink = current->rLink;
		current->rLink = newNode;
		newNode->rLink->lLink = newNode;
		newNode->lLink = current;
	}
	return true;
}

template <typename T>
bool DblList<T>::Remove(int i, T &x, int d){
	//��˫��ѭ�������а�d��ָ����ɾ����i����㡣
	DblNode<T> *current = Locate(i, d);
	if (current == NULL)
	{
		return false; 	      //ɾ��ʧ��
	}
	current->rLink->lLink = current->lLink;
	current->lLink->rLink = current->rLink;	
	x = current->data;
	delete current;
	return true;
}
#endif
