#ifndef GENLIST_H
#define GENLIST_H

#include <iostream>
#include <cassert>
#include <cstdlib>
#include "SeqList.h"

// ����������ṹ����
template <typename T>class GenListNode{
public:
	GenListNode(){
		mark = 0;
		utype = 0;
		tlink = NULL;
		info.ref = 0;
	}
	GenListNode(GenListNode<T> &RL)	{
		mark = RL.mark;
		utype = RL.utype;
		tlink = RL.tlink;
		info = RL.info;
	}

	int utype;					// =0/1/2
	int mark;					// ���ʱ��
	GenListNode<T> *tlink;		// ָ��ͬһ����һ������ָ��
	union{
		int ref;				// utype=0: ��ͷ��������ü���
		T value;				// utype=1: Ԫ�أ����ԭ�ӽ����ֵ
		GenListNode<T> *hlink;	// utype=2: �ӱ�����ӱ�ͷָ��
	}info;
};

// �������ֵ����ṹ����
template <typename T>class Items{
public:
	int utype;					// =0/1/2
	int mark;					// ���ʱ��
	union{
		int ref;				// utype=0: ��ͷ��������ü���
		T value;				// utype=1: Ԫ�أ������ֵ
		GenListNode<T> *hlink;	// utype=2: �ӱ�����ӱ�ͷָ��
	}info;
	Items(){
		utype = 0;
		mark = 0;
	}
	Items(Items<T> &RL){
		utype = RL.utype;
		mark = RL.mark;
		info = RL.info;
	}
};

// �������Ķ���
template <typename T>class GenList{
public:
	GenList();
	~GenList();
	bool Head(Items<T> &x);
	bool Tail(GenList<T> &lt);
	GenListNode<T> *First();
	GenListNode<T> *Next(GenListNode<T> *elem);
	void Copy(const GenList<T> &R);
	int Length();
	int depth();
	void delvalue(const T &x);
	void Print(ostream &out = cout) {Print(first, out);}
	bool equal(GenList<T>& t){
		return equal(first,t.first);
	}
	friend istream& operator >> (istream &in, GenList<T> &L){
		SeqList<T> Ls1;
		SeqList<GenListNode<T> *> Ls2;
		L.CreateList (in, L.first, Ls1, Ls2);	//�����洢�ṹ
		GenListNode<T> *p = L.first;            //ɾ�������ͷ����������ӱ���
		L.first = L.first->info.hlink;
		delete p;
		return in;
	}
	friend ostream& operator << (ostream &out, GenList<T> &L){
		L.Print(out);
		return out;
	}
private:
	GenListNode<T> *first;
	GenListNode<T> *Copy(GenListNode<T> *ls);
	int Length(GenListNode<T> *ls);
	int depth(GenListNode<T> *ls);
	bool equal(GenListNode<T> *s, GenListNode<T> *t);
	void delvalue(GenListNode<T> *ls, const T &x);
	void Remove(GenListNode<T> *ls);
	void Print(GenListNode<T>* p, ostream &out);
	void CreateList(istream &in, GenListNode<T> *& ls, 
			SeqList<T> &L1, SeqList <GenListNode<T> *> &L2);
};

template <typename T>GenList<T>::GenList(){
	first = new GenListNode<T>;
	assert(first);
}

template <typename T>GenList<T>::~GenList(){
	Remove(first);
}

template <typename T>bool GenList<T>::Head(Items<T> &x){//���ر�ͷԪ��ֵ
	if (first){
		x.utype = first->tlink->utype;
		x.info = first->tlink->info;
		return true;
	}
	else	return false;
}

template <typename T>bool GenList<T>::Tail(GenList<T> &lt){//���ر�β
	if (first->tlink){
		lt.first->utype = 0;
		lt.first->info.ref = 0;
		lt.first->tlink = Copy(first->tlink->tlink);
		return true;
	}
	else	return false;
}

template <typename T>GenListNode<T> *GenList<T>::First(){//���ر�ͷ
	return first->tlink;
}

template <typename T>GenListNode<T> *GenList<T>::Next(GenListNode<T> *elem){//����ֱ�Ӻ��
	return elem->tlink;
}

template <typename T>
void GenList<T>::Copy(const GenList<T> &R){//�������
	first = Copy(R.first);
}

template <typename T>GenListNode<T>* GenList<T>::Copy(GenListNode<T> *ls){//����ʵ��δ������ref��ʶ���䣬equal()����ͬ��Remove()��ref>1©ɾ
	GenListNode<T> *q = NULL;
	if (ls){
		q = new GenListNode<T>;
		q->utype = ls->utype;
		switch (ls->utype){
		case 0:
			q->info.ref = ls->info.ref;
			break;
		case 1:
			q->info.value = ls->info.value;cout<<q->info.value<<endl;
			break;
		case 2:
			q->info.hlink = Copy(ls->info.hlink);
			break;
		}
		q->tlink = Copy(ls->tlink);
	}
	return q;
}

template <typename T>int GenList<T>::Length(){//������ȣ�ͬһ���Ԫ����
	return Length(first)-1;
}

template <typename T>int GenList<T>::Length(GenListNode<T> *ls){
	return (ls == NULL)?0:(1+Length(ls->tlink));
}

template <typename T>int GenList<T>::depth(){
	return depth(first);
}

template <typename T>int GenList<T>::depth(GenListNode<T> *ls){//��������
	if (!ls){
		return 1;
	}
	GenListNode<T> *temp = ls->tlink;
	int m = 0, n;
	while (temp){
		if (temp->utype == 2){
			n = depth(temp->info.hlink);
			if (m < n){
				m = n;
			}
		}
		temp = temp->tlink;
	}
	return m+1;
}

template <typename T>bool GenList<T>:: equal(GenListNode<T> *s, GenListNode<T> *t){//������Ƿ���ȣ������ù������
	bool x;
	if (s->tlink == NULL && t->tlink == NULL)	return true;
	if (s->tlink && t->tlink && s->tlink->utype == t->tlink->utype)	{
		if (s->tlink->utype == 1){
			x = (s->tlink->info.value == t->tlink->info.value)?true:false;
		}
		if (s->tlink->utype == 2){
			x = equal(s->tlink->info.hlink, t->tlink->info.hlink);
		}
		if (s->tlink->utype == 0){
			if(s->tlink->info.ref== t->tlink->info.ref) x=true;
			else x=false;
		}
		if (x)	{
			return equal(s->tlink, t->tlink);
		}
	}
	return false;
}

template <typename T>void GenList<T>::delvalue(const T &x){//ɾ������ֵ���
	delvalue(first, x);
}
template <typename T>void GenList<T>::delvalue(GenListNode<T> *ls, const T &x){
	if (ls->tlink)	{
		GenListNode<T> *p = ls->tlink;
		while (p && (p->utype == 1 && p->info.value == x)){
			cout<<p->info.value;
			ls->tlink = p->tlink;
			delete p;
			p = ls->tlink;
		}
		if (p){
			if (p->utype == 2){
				cout<<'#'<<endl;
				delvalue(p->info.hlink, x);//������һ���
			}
			delvalue(p, x);//�ɱ���㿪ʼ
		}
	}
}

template <typename T>void GenList<T>::Remove(GenListNode<T> *ls){//ɾ��ָ���ӱ������ù������
	ls->info.ref--;
	if (ls->info.ref <= 0){
		GenListNode<T> *q;
		while (ls->tlink){
			q = ls->tlink;
			if (q->utype == 2){
				Remove(q->info.hlink);
				if (q->info.hlink->info.ref <= 0){
					delete q->info.hlink;
				}
			}
			ls->tlink = q->tlink;
			delete q;
		}
	}
}


// �ӹ������ַ�������s����, ����һ����ͷ���Ĺ����Ҫ��TΪchar�͡�
// �ڱ�L1�洢��д��ĸ�ı���, �ڱ�L2�洢������Ӧ�ӱ���ĵ�ַ��
template <typename T>void GenList<T>::CreateList(istream& in, GenListNode<T> *& ls, 
			SeqList<T> &L1, SeqList <GenListNode<T> *> &L2){
	T chr; 
	in >> chr;
	cout<<chr; 
	//����һ���ַ���ֻ���ܶ���#�������ź���ĸ
	if (isalpha(chr) && isupper(chr) || chr == '('){ //��д��ĸ��'('	
		bool b=true;
		ls = new GenListNode<T>;          //���ӱ���
		cout<<'&';
		ls->utype = 2;		
		if (isalpha(chr) && isupper(chr)){ //��������,�����ӱ�		
			int n = L1.Length();
			int m = L1.Search(chr);
			if (m != 0){                  //�ñ��ѽ���
				b=false;                  //����
				ls->info.hlink = *L2.getData(m);//���ӱ��ַ
				ls->info.hlink->info.ref++;		//���ü�����1
				cout<<'@';
				in >> chr;
				if (chr != '('&&chr!=','&&chr != ')') exit(1);	//������ظ�'('��','��')'
				if(chr=='(')
					do{
						in>>chr; //��������ֻ����������������ݳ������
					}while(chr!=')');
				else if(chr==','||chr == ')') in.putback(chr);//���Ż�')'�ͻػ�����
			} 	
			else{       //�ñ�δ����
				ls->info.hlink = new GenListNode<T>;         //������ͷ���
				L1.Insert(n, chr);                           //�����������ַ
				L2.Insert(n, ls->info.hlink);
				in >> chr;
				cout<<chr; 
				cout<<'%';  
				ls->info.hlink->utype = 0;
				ls->info.hlink->info.ref = 1;
				if (chr != '(') exit(1);	//������ظ�'('
				CreateList(in, ls->info.hlink->tlink, L1, L2);//�ݹ齨�ӱ�
			}
		}
		else{//�����ӱ�
			ls->info.hlink = new GenListNode<T>;
			cout<<'%';  
			ls->info.hlink->utype = 0;         //��ͷ���
			ls->info.hlink->info.ref = 1;
			CreateList(in, ls->info.hlink->tlink, L1, L2);//�ݹ齨�ӱ�
		}
		CreateList(in, ls, L1, L2);                   //�ݹ齨��̱�
	}
	else if (isalpha(chr) && islower(chr)){	//��ԭ�ӽ�㡣���������ڽ���TΪcharʱ��Ч
			ls = new GenListNode<T>;
			cout<<'*'; 
			ls->utype = 1;
			ls->info.value = chr;//����Ӧ���н��ַ���T���;�������һһ��Ӧ�ı����հѾ������ݴ���info.value
			CreateList(in, ls, L1, L2);
		}
		else if (chr == ','){ 		//����̽��	
				if (ls->tlink) delete ls->tlink;
				ls->tlink = new GenListNode<T>;
				CreateList(in, ls->tlink, L1, L2); 
			}
			else if (chr == ')')	ls->tlink = NULL;  //����β
				else if (chr == '#')	ls = NULL; //�ձ�, ����β
}

//��ӡ����
template<typename T>
void GenList<T>::Print(GenListNode<T>* p, ostream &out){
	if (!p)
		return;                           //pΪNULL����
	if (p->utype==1)                      //ԭ�ӽ��
		out << (p->info).value << "   ";
	else if (p->utype == 0)               //���ӱ�ͷ���
			while (p->tlink){			  //��ע�˾�,��Ϊ�޷���ָ�룬������while��ʽѭ��
				Print(p->tlink, out);
				p=p->tlink;               //���غ�����
			}
		else	Print(p->info.hlink, out);//�ӱ���
}

#endif
