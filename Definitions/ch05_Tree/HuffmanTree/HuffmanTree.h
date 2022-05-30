#ifndef HAFFMANTREE_H
#define HAFFMANTREE_H
#include "MinHeap.h"
#include<iostream>
#include<string>
using namespace std;

//Huffman�������ඨ��
template <typename T, typename E>struct HuffmanNode{
	E data;
	HuffmanNode<T,E> *leftChild, *rightChild, *parent;
	HuffmanNode():leftChild(NULL), rightChild(NULL), parent(NULL){}//���캯��
	HuffmanNode(E elem, HuffmanNode<T,E> * pr,HuffmanNode<T,E> *left,HuffmanNode<T,E>*right) 
		:data(elem), parent(pr), leftChild(left), rightChild(right){}
	//���ز�������
	bool operator > (HuffmanNode<T,E> right){
		return data>right.data;
	}
	bool operator >= (HuffmanNode<T,E> right){
		return (data>right.data) || (data==right.data);
	}
	bool operator < (HuffmanNode<T,E> right){
		return data<right.data;
	}
	bool operator <= (HuffmanNode<T,E> right){
		return (data<right.data) || (data==right.data);
	}
	bool operator == (HuffmanNode<T,E> right){
		return data==right.data;
	}
};

//Huffman���ඨ��
template <typename T, typename E>class HuffmanTree{
public:
	HuffmanTree(E w[], int n);
	~HuffmanTree(){
		deleteTree(root);
	}
	HuffmanNode<T,E>* getRoot(){
		return root;
	}
	void output(HuffmanNode<T,E> * t, string str, ostream &out);
protected:
	HuffmanNode<T, E> *root;
	void deleteTree(HuffmanNode<T, E> * t);
	void mergeTree(HuffmanNode<T, E> *ht1,HuffmanNode<T, E> *ht2,   
		HuffmanNode<T, E> *& parent);
};


//--------------------------------------------------------------------------------------------------
template <typename T, typename E>void HuffmanTree<T,E>::deleteTree(HuffmanNode<T,E> * t){//����Ӷ����������
	if (t != NULL){
		deleteTree (t->leftChild);
		deleteTree (t->rightChild);
		delete t;
	}
}

template <typename T, typename E>void HuffmanTree<T,E>::output(HuffmanNode<T,E> * t, string str, ostream &out){//��Ŀ¼�ṹ��ʽ��������������
	if (!t){
		return;
	}
	out << str << t->data;
	if (t->leftChild){
		out << "����" << endl;
		if (t->rightChild){
			output(t->leftChild, str+"����", out);
		}
		else{
			output(t->leftChild, str+"����", out);
		}
	}
	if (t->rightChild){
		out << endl << str << "������" << endl;
		output(t->rightChild, str+"����", out);
	}
}

template <typename T, typename E>HuffmanTree<T,E>::HuffmanTree(E w[], int n){
	//����n��Ȩֵw[1]��w[n], ����Huffman��
	MinHeap<T, HuffmanNode<T,E> > hp;	//ʹ����С�Ѵ��ɭ�ֵĽ��
	HuffmanNode<T, E> *parent, *first, *second,temp;
	HuffmanNode<T, E> *NodeList/* = new HuffmanNode<T,E>[n]*/; //����һ���Խ���ɭ�֣�������������һ��һ��ɾ���ʱ����ϵͳ���Գ���
	int i;
	for (i = 0; i < n; i++){//�����𲽽���ɭ���е���ľ������ΪHuffman����Ҷ��㡣���ݷ���ɭ��
		NodeList = new HuffmanNode<T,E>;
		NodeList->data = w[i+1];
		NodeList->leftChild = NULL;
		NodeList->rightChild = NULL;
		NodeList->parent = NodeList;//��ָ��ָ���Լ�����Ϣ��Ѻ󣬳���ʱ�����ҵ���Ӧ���
		hp.Insert(*NodeList);	//ɭ����Ϣ������С����
	}
	for (i = 0; i < n-1; i++){	//n-1��, ��Huffman��	
		hp.RemoveMin(temp); 		//��Ȩֵ��С����
		first=temp.parent;			//firstָ���Ӧ����С���
		hp.RemoveMin(temp);	        //��Ȩֵ��С����
		second=temp.parent;			//secondָ���Ӧ�Ĵ�С���
		mergeTree(first, second, parent);	//�ϲ�
		hp.Insert(*parent);		//�½��������
	}
	root = parent;		//���������
	cout<<"       root = "<<root->data<<endl;
	output(root,string(),cout);
}

template <typename T, typename E>void HuffmanTree<T, E>::mergeTree(HuffmanNode<T, E> *bt1, 
		HuffmanNode<T, E> *bt2, HuffmanNode<T, E> *& parent){//pasent����Ϊ���ã�����Ϊ������
	parent = new HuffmanNode<T,E>;
	parent->leftChild = bt1;
	parent->rightChild = bt2;
	parent->parent=parent;//�鲢��ĸ����ĸ�ָ��ָ��������������Ϣ��Ѻ󣬳���ʱ�����ҵ���Ӧ����
	parent->data = bt1->data + bt2->data;		//����Ϊ������������֮��
	bt1->parent = bt2->parent = parent;		//���������������ĸ�ָ��
	cout<<bt1->data<<" and "<<bt2->data<<" union to��"<<parent->data<<endl;
}

#endif
