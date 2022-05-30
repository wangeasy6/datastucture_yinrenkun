#ifndef SKIPLIST_H
#define SKIPLIST_H
#include <iostream>
#include <cassert>
using namespace std;
const int DefaultSize = 100;

//�������ඨ��
template <typename E, typename K>struct SkipNode{
	E data;								//������
	SkipNode<E,K> **link;				//ָ��������
	SkipNode(int size = DefaultSize){
		link = new SkipNode<E,K> *[size];
		assert(link);
	}
	~SkipNode(){
		delete []link;
	}
};

//�����ඨ��
template <typename E, typename K>class SkipList{
public:
	SkipList(K large, int maxLev = DefaultSize);//���캯��
	~SkipList();								//��������
	bool Search(const K k1, E &e1)const;		//��������
	E& getData(SkipNode<E,K> *current){
		return current?(&current->data):NULL;
	}
	bool Insert(const K k1, E &e1);		//���뺯��
	bool Remove(const K k1, E &e1);	    //ɾ������
	bool DelMin(E &e1);
	bool DelMax(E &e1);
	SkipNode<E,K>* Begin(){
		return (head->link[0] == tail)?NULL:head->link[0];
	}
	SkipNode<E,K>* Next(SkipNode<E,K> *p){
		return (p == NULL || p == tail || p->link[0] == tail)?NULL:p->link[0];
	}
	friend istream& operator >> (istream &in, SkipList<E,K> &R){
		while (!in.eof()){
			E elem;
			assert(in >> elem);
			R.Insert(elem.key, elem);
		}
		return in;
	}
	friend ostream& operator << (ostream &out, SkipList<E,K> &R){
		SkipNode<E,K> *p = R.head->link[0];
		if (p == R.tail){
			out << "The skip list is empty!\n";
		}
		while (p != R.tail){
			out << p->data << endl;
			p = p->link[0];
		}
		return out;
	}						//���������ֵ
private:
	int maxLevel;						//������������
	int Levels;							//��ǰ�ǿ����ļ���
	K TailKey;							//��TailKey�д���һ����ֵ
	SkipNode<E,K> *head;				//����ͷ���
	SkipNode<E,K> *tail;				//����β���
	SkipNode<E,K> **last;				//ָ������
	int Level();
	SkipNode<E,K> *SaveSearch(const K k1);
};

//���캯���������յĶ༶��
template <typename E, typename K>SkipList<E,K>::SkipList(K large, int maxLev){
	maxLevel = maxLev;	//�������Ŀ
	TailKey = large;	//����ɨ������ؼ���
	Levels = 0;
	head = new SkipNode<E,K>(maxLevel+1);	//����ͷ���,��maxLevel+1ָ��
	tail = new SkipNode<E,K>(0);			//����β���,��0��ָ��
	last = new SkipNode<E,K> *[maxLevel+1];	//����ĸ����༶��ָ��
	tail->data = large;
	for (int i = 0; i <= maxLevel; i++){
		head->link[i] = tail;
	}
}


//�����������ͷ���������Ԫ�ؽ��
template <typename E, typename K>SkipList<E,K>::~SkipList(){
	SkipNode<E,K> *next;
	while (head != tail){
		next = head->link[0];	//��0�����������к���
		delete head;
		head = next;
	}
	delete tail;
	delete []last;
}

//�����㷨
template <typename E, typename K>bool SkipList<E,K>::Search(const K k1, E& e1)const{
	if (k1 > TailKey){
		return false;
	}
	SkipNode<E,K> *p = head;
	for (int i = Levels; i >= 0; i--){ //����������	
		while (p->link[i]->data < k1){ //���أ�Ԫ�عؼ�����С��
			p = p->link[i];
		}
	}
	e1 = p->link[0]->data;	// p����Ҫ�ҵ�Ԫ�ص����!
	return e1 == k1; //���أ�Ԫ�عؼ����е���
}


template <typename E, typename K>SkipNode<E,K> *SkipList<E,K>::SaveSearch(const K k1){
	if (k1 > TailKey)	{
		return NULL;
	}
	SkipNode<E,K> *p = head;
	for (int i = Levels; i >= 0; i--){ //����������	
		while (p->link[i]->data < k1) //���أ�Ԫ�عؼ�����С��
		p = p->link[i];
		last[i] = p;	//����ÿһ�������ȽϽ��, p����Ҫ�ҵ�Ԫ�ص����!
	}
	return p->link[0];	//�����ҵ��Ľ���ַ
}


//����һ������ļ��𣬸ü��� < maxLevel
template <typename E, typename K>int SkipList<E,K>::Level(){
	int lev = 0;
	while (rand() <= RAND_MAX/2){//������ķ�������0������Ϊ0.5,1��0.25,2��0.125�ȵ�
		lev++;
	}
	return (lev < maxLevel)?lev:maxLevel;
}

//�����㷨
template <typename E, typename K>bool SkipList<E,K>::Insert(const K k1, E& e1){
	if (k1 >= TailKey){
		return false;
	}
	SkipNode<E,K> *p = SaveSearch(k1); //����Ƿ��ظ���������Last��ֵ
	if (p->data == k1){ //���أ�Ԫ�ؼ��е���	
		return false;
	}
	int lev = Level(); //�������һ������
	if (lev > Levels){ //��������	
		lev = ++Levels;
		last[lev] = head;
	}
	SkipNode<E,K> *newNode = new SkipNode<E,K>(lev+1);
	newNode->data = e1;  //���أ�Ԫ�ظ�ֵ
	for (int i = 0; i <= lev; i++){	//��������	
		newNode->link[i] = last[i]->link[i]; //��i������
		last[i]->link[i] = newNode;
	}
	return true;
}


template <typename E, typename K>bool SkipList<E,K>::Remove(const K k1, E &e1){
	if (k1 > TailKey){ //�ؼ���̫��	
		return false;
	}
	SkipNode<E,K> *p = SaveSearch(k1); //������k1ƥ���Ԫ��->pF
	if (p->data != k1){ //���أ�Ԫ�عؼ����в���	
		return false;
	}
	for (int i = 0; i <= Levels && last[i]->link[i] == p; i++){
		last[i]->link[i] = p->link[i]; //����ժ�¸ý��
	}
	while (Levels > 0 && head->link[Levels] == tail){
		Levels--; //�޸ļ���
	}
	e1 = p->data;
	delete p;
	return true;
}

template <typename E, typename K>bool SkipList<E,K>::DelMin(E &e1){
	SkipNode<E,K> *p = head->link[0];
	if (p == tail){
		return false;
	}
	for (int i = 0; i <= Levels && head->link[i] == p; i++){
		head->link[i] = p->link[i]; //����ժ�¸ý��
	}
	while (Levels > 0 && head->link[Levels] == tail){
		Levels--; //�޸ļ���
	}
	e1 = p->data;
	delete p;
	return true;
}

template <typename E, typename K>bool SkipList<E,K>::DelMax(E &e1){
	int i;
	if (head->link[0] == tail){
		return false;
	}
	SkipNode<E,K> *p = head;
	for (i = Levels; i >=0; i--){
		if (p->link[0] == tail){ //��i=Levelsʱ,�������϶�������		
			last[i] = last[i+1];//�ʸ���䲻�����
			while (last[i]->link[i] != p){
				last[i] = last[i]->link[i];
			}
		}
		else{
			while (p->link[i]->data < TailKey){
				last[i] = p;
				p = p->link[i];
			}
		}
	}
	for (i = 0; i <= Levels && last[i]->link[i] == p; i++){
		last[i]->link[i] = tail; //����ժ�¸ý��
	}
	while (Levels > 0 && head->link[Levels] == tail){
		Levels--; //�޸ļ���
	}
	e1 = p->data;
	delete p;
	return true;
}
#endif
