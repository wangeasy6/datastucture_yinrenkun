#ifndef BINARY_TREE
#define BINARY_TREE

#include <string>
#include <cassert>
#include <iostream>
using namespace std;
#include "LinkedStack.h"
#include "LinkedQueue.h"

/**
 * @brief ��������� <data, *lChild, *rChild>
 */
template <typename T>struct BinTreeNode{
	T data;
	BinTreeNode<T> *leftChild;
	BinTreeNode<T> *rightChild;

	BinTreeNode():leftChild(NULL), rightChild(NULL){}
	BinTreeNode(T x, BinTreeNode<T> *l = NULL, BinTreeNode<T> *r = NULL)
		:leftChild(l), rightChild(r){
		data = x;
	}
};

/**
 * @brief ������������洢��
 */
template <typename T>class BinaryTree{
public:
	BinaryTree():root(NULL){}
	BinaryTree(T value):root(NULL){
		RefValue = value;
	}
	BinaryTree(BinaryTree<T> &s){
		if (this != &s){
			root=Copy(s.root);
		}
	}
	~BinaryTree(){
		destroy(root);
	}
	bool IsEmpty(){
		return root == NULL;
	}
	bool Find(T &x){
		return Find(root,x);
	}
	int Height(){
		return Height(root);
	}
	int Size(){
		return Size(root);
	}
	BinTreeNode<T> *Parent(BinTreeNode <T> *t){
		return (root == NULL || root ==  t)?NULL:Parent(root, t);
	}
	BinTreeNode<T> *LeftChild(BinTreeNode<T> *t){
		return (t != NULL)?t->leftChild:NULL;
	}
	BinTreeNode<T> *RightChild(BinTreeNode<T> *t){
		return (t != NULL)?t->rightChild:NULL;
	}
	BinTreeNode<T> *getRoot()const{
		return root;
	}
	/// @brief ǰ�����
	void PreOrder(void (*visit)(BinTreeNode<T> *t)){
		PreOrder(root, visit);
	}
	/// @brief �������
	void InOrder(void (*visit)(BinTreeNode<T> *t)){
		InOrder (root, visit);
	}
	/// @brief �������
	void PostOrder(void (*visit)(BinTreeNode<T> *t)){
		PostOrder(root, visit);
	}	
	bool Insert(T item){
		return Insert(root, item);
	}
	//for E524
	void CreateCompBinTree(T *CBT, int num){//������ȫ������
		CreateCompBinTree(CBT, num, 0, root);
	}
	//for E530
	/// @brief ����������
	void printBinTree(ostream &out = cout){
		printBinTree(root, out);
	}	
	/// @brief �������ı����
	void Output(ostream &out = cout){
		out << "The structure of the binary tree is:\n";
		Output(root, string(" "), out);
		out << endl;
	}
	/// @brief ��������
	void levelOrder(void (*visit)(BinTreeNode<T> *t));
	/// @brief �ǵݹ�ǰ�����
	void PreOrder1(void (*visit) (BinTreeNode<T> *t));
	/// @brief �ǵݹ��������
	void InOrder1(void (*visit) (BinTreeNode<T> *t));
	/// @brief �ǵݹ�������
	void PostOrder1(void (*visit) (BinTreeNode<T> *t));
	friend istream& operator >> (istream &in, BinaryTree<T> &Tree){//���������
		Tree.CreateBinTree(in, Tree.root);
		return in;
	}
	// show bintree in the form of genlist
	friend ostream& operator << (ostream& out, BinaryTree<T>& Tree){//����������
		Tree.printBinTree(out);
		out << endl;
		return out;
	}
protected:
	BinTreeNode<T> *root;		//�������ĸ�ָ��
	T RefValue;				//��������ֹͣ��־
	/// @brief �ݹ齨��������
	void CreateBinTree(istream &in, BinTreeNode<T> *& subTree);
	/// @brief ������ȫ������
	void CreateCompBinTree(T *CBT, int num, int rt, BinTreeNode<T> *& subTree);
	/// @brief ��������ӡ
	void printBinTree(BinTreeNode<T> *subTree, ostream &out);
	/// @brief ��Ŀ¼�ṹ��ʽ���������
	void Output(BinTreeNode<T> *subTree, string str, ostream &out);
	/// @brief �ڽ���ĳ������������Ϊx�Ľ��
	bool Insert(BinTreeNode<T> *& subTree, T &x);
	/// @brief ����Ӷ�����
	void destroy(BinTreeNode<T> *& subTree) ;
	/// @brief ��������Ѱ������Ϊx�Ľ��
	bool Find(BinTreeNode<T> *subTree, T &x)const;
	/// @brief ���ƶ�����r
	BinTreeNode<T> *Copy(BinTreeNode<T> *r);
	/// @brief ����
	int Height(BinTreeNode<T> *subTree)const ;
	/// @brief ���Ľڵ���
	int Size(BinTreeNode<T> *subTree)const;
	/// @brief ���������Ҹ����
	BinTreeNode<T> *Parent(BinTreeNode<T> *subTree, BinTreeNode<T> *t) ;
	/// @brief �������
	void Traverse(BinTreeNode<T> *subTree, ostream &out);
	/// @brief ǰ�����
	void PreOrder(BinTreeNode<T> *subTree, void (*visit)(BinTreeNode<T> *t));
	/// @brief �������
	void InOrder(BinTreeNode<T> *subTree, void (*visit)(BinTreeNode<T> *t));
	/// @brief �������
	void PostOrder(BinTreeNode<T> *subTree, void (*visit)(BinTreeNode<T> *t));
};

template <typename T>void BinaryTree<T>::CreateBinTree(istream &in, BinTreeNode<T> *& subTree){//˽�к���: �Եݹ鷽ʽ������������
	T item;
	if (in >> item){
		if (item != RefValue){
			subTree = new BinTreeNode<T>(item);		//Create Root
			assert(subTree);
			CreateBinTree(in, subTree->leftChild);	// Create left child tree
			CreateBinTree(in, subTree->rightChild);	// Create reght child tree
		}
		else
		{
			subTree = NULL;
		}
	}
}
// rt is the root of the subTree
template<typename T>void BinaryTree<T>::CreateCompBinTree(T *CBT, int num, int rt, BinTreeNode<T> *& subTree){//������ȫ������
	if (rt >= num)	{
		subTree = NULL;
	}
	else{
		subTree = new BinTreeNode<T>(CBT[rt]);
		if (subTree == NULL){
			cerr << "Memory Allocating error!" << endl;
			exit(1);
		}
		CreateCompBinTree(CBT, num, 2*rt+1, subTree->leftChild);
		CreateCompBinTree(CBT, num, 2*rt+2, subTree->rightChild);
	}
}
//E530
// print the binary tree in the form of genlist.
template <typename T>void BinaryTree<T>::printBinTree(BinTreeNode<T> *subTree, ostream &out){//��������ӡ
	if (subTree){
		out << subTree->data;
		if (subTree->leftChild || subTree->rightChild){
			out << "(";
			printBinTree(subTree->leftChild, out);
			if (subTree->rightChild){
				out << ",";
			}
			printBinTree(subTree->rightChild, out);
			out << ")";
		}
	}
}

// print the structure of the binary tree.
template <typename T>void BinaryTree<T>::Output(BinTreeNode<T> *subTree, string str, ostream &out){//��Ŀ¼�ṹ��ʽ���������
	if (!subTree)	{
		return;
	}
	out << str << subTree->data;
	if (subTree->leftChild){
		out << "����" << endl;
		if (subTree->rightChild){
			Output(subTree->leftChild, str+"����", out);
		}
		else{
			Output(subTree->leftChild, str+"����", out);
		}
	}
	if (subTree->rightChild){
		out << endl << str << "������" << endl;
		Output(subTree->rightChild, str+"����", out);
	}
}

template<typename T>bool BinaryTree<T>::Insert(BinTreeNode<T> *& subTree, T& x){//�ڽ���ĳ������������Ϊx�Ľ��
	if (!subTree){
		subTree=new BinTreeNode<T>(x);
		assert(subTree);
		return true;
	}
	else{
		return Insert(subTree->leftChild, x) || Insert(subTree->rightChild, x);//�������������ɹ���������ȥ������
	}
}

template<typename T>bool BinaryTree<T>::Find(BinTreeNode<T> *subTree, T &x)const{//��������Ѱ������Ϊx�Ľ��
	if (!subTree){
		return false;
	}
	if (subTree->data==x){
		return true;
	}
	bool p=false;
	p = Find(subTree->leftChild,x); 
	if (p)	{
		return true;
	}
	else{
		return Find(subTree->rightChild, x);
	}
}

template<typename T>BinTreeNode<T> *BinaryTree<T>::Copy(BinTreeNode<T> *r){ //�ݹ鸴�ƶ�����
	 if (!r){
		 return NULL;
	 }
	 BinTreeNode<T> *p=new BinTreeNode<T>(r->data);
	 p->leftChild = Copy(r->leftChild);
	 p->rightChild = Copy(r->rightChild);
	 return p;
}

template <typename T>void BinaryTree<T>::destroy(BinTreeNode<T> *& subTree){//����Ӷ�����
	if (subTree != NULL)	{
		destroy (subTree->leftChild);
		destroy (subTree->rightChild);
		delete subTree;
	}
}

template <typename T>int BinaryTree<T>::Height(BinTreeNode<T> *subTree)const{//����
	if (subTree == NULL){
		return 0;
	}
	else{
		int i = Height(subTree->leftChild);
		int j = Height(subTree->rightChild);
		return (i < j)?j+1:i+1;
	}
}

template <typename T>int BinaryTree<T>::Size(BinTreeNode<T> *subTree)const{//���Ľڵ���
	if (subTree == NULL)	{
		return 0;
	}
	else{
		return 1 + Size(subTree->leftChild) + Size(subTree->rightChild);
	}
}


template <typename T> BinTreeNode<T> *BinaryTree<T>::Parent(BinTreeNode<T> *subTree, BinTreeNode<T> *t){//���������Ҹ����
	if (subTree == NULL){
		return NULL;
	}
	if (subTree->leftChild == t || subTree->rightChild == t ){
		return subTree;
	}
	BinTreeNode <T> *p;
	if ((p = Parent(subTree->leftChild, t)) != NULL){
		return p;
	}
	else{
		return Parent(subTree->rightChild, t);
	}
}

template <typename T>void BinaryTree<T>::Traverse(BinTreeNode<T> *subTree, ostream &out){//ǰ���������������
	if (subTree){
		out << subTree->data << ' ';
		Traverse(subTree->leftChild, out);
		Traverse(subTree->rightChild, out);
	}
}

template <typename T>void BinaryTree<T>::PreOrder(BinTreeNode<T>* subTree, void (*visit)(BinTreeNode<T> *t)){
	if (subTree != NULL){
		visit(subTree);
		PreOrder(subTree->leftChild, visit);
		PreOrder(subTree->rightChild, visit);
	}
}

template <typename T>void BinaryTree<T>::InOrder(BinTreeNode<T> *subTree, void (*visit)(BinTreeNode<T> *t)){
	if (subTree != NULL){
		InOrder(subTree->leftChild, visit); 
		visit(subTree);
		InOrder(subTree->rightChild, visit);
	}
}

template <typename T>void BinaryTree<T>::PostOrder(BinTreeNode<T> *subTree, void (*visit)(BinTreeNode<T> *t)){
	if (subTree != NULL ){
		PostOrder(subTree->leftChild, visit);	
		PostOrder(subTree->rightChild, visit);
		visit (subTree);
	}
}

template <typename T>void BinaryTree<T>::PreOrder1(void (*visit) (BinTreeNode<T> *t) ) {//�ǵݹ�ǰ�����
     LinkedStack<BinTreeNode<T>*> S;
     BinTreeNode<T> *p = root; 
     S.Push (NULL);
	 while (p != NULL) {
          	visit(p);			   //���ʽ��
 	      if (p->rightChild != NULL)
               S.Push (p->rightChild);  //Ԥ����ָ����ջ��
		  if (p->leftChild != NULL) 
               p = p->leftChild;	//��������
 	      else S.Pop(p);		//������Ϊ�գ��ɶ�ջ����
     }
}

template <typename T> void BinaryTree<T>::InOrder1(void (*visit) (BinTreeNode<T> *t)) {//�ǵݹ��������
     LinkedStack<BinTreeNode<T>*> S;  
	 BinTreeNode<T> *p = root; 
     do {
          while (p != NULL) {	//����ָ���������ƶ�
               S.Push (p); 		//��������;����ջ
               p = p->leftChild;
          }
          if (!S.IsEmpty()) {		//ջ����ʱ��ջ
               S.Pop (p);  visit (p);	//��ջ, ����
               p = p->rightChild;	//����ָ���������Ů
          }
     } while (p != NULL || !S.IsEmpty ());
}

template <typename T>struct stkNode {
	BinTreeNode<T> *ptr;      //�����ָ��	        
	enum{L, R}tag;               //��ջ��ǣ�����˵��Ϊö�ٱ�����tag�Ƶ����ұߡ����������bool��
	stkNode (BinTreeNode<T> *N = NULL){
		ptr=N;
		tag=L;
	}	           //���캯��
};

template <typename T>void BinaryTree<T>::PostOrder1(void (*visit) (BinTreeNode<T> *t)){//�ǵݹ�������
     LinkedStack<stkNode<T> > S;
	 stkNode<T> w; 
     BinTreeNode<T> * p = root;     //p�Ǳ���ָ��
	 do {
		while (p != NULL) {	
		     w.ptr = p;
			 w.tag = stkNode<T>::L;//ö�����Ͷ�����struct stkNode�У��綨��Ϊȫ���Ծͼ���
			 S.Push (w);   
		     p = p->leftChild;					}
	 	int continue1 = 1;	    //����ѭ�����, ����R
		while (continue1 && !S.IsEmpty ()) {
		     S.Pop (w);  p = w.ptr;
		     switch (w.tag) {   	//�ж�ջ����tag���
			 case stkNode<T>::L:  w.tag = stkNode<T>::R;
				 S.Push (w);
				 continue1 = 0;
				 p = p->rightChild;  break;
			 case stkNode<T>::R:  visit (p);   break;
			 }
	 	}
     } while (!S.IsEmpty ());	//���������������
     cout << endl;
}

template <typename T>void BinaryTree<T>::levelOrder (void (*visit) (BinTreeNode<T> *t)) {//��������
     if (root == NULL) return;
     LinkedQueue<BinTreeNode<T> * > Q;
     BinTreeNode<T> *p = root;   
     visit (p);   Q.EnQueue (p); 	
     while (!Q.IsEmpty ()) {
          Q.DeQueue (p);
          if (p->leftChild != NULL) {
			  visit (p->leftChild);
			  Q.EnQueue (p->leftChild);
          }
          if (p->rightChild != NULL) {
			  visit (p->rightChild);
			  Q.EnQueue (p->rightChild);
          }
     }
}

#endif
