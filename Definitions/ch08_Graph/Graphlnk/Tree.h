#ifndef TREE_H
#define TREE_H
#include <iostream>
#include <string>
#include "SeqQueue.h"
using namespace std;

template <typename T>struct TreeNode{
	T data;
	TreeNode<T> *firstChild, *nextSibling;
	TreeNode(T value = 0, TreeNode<T> *fc = NULL, TreeNode<T> *ns = NULL)
		:firstChild(fc), nextSibling(ns){
		data = value;
	}
};

template <typename T>class Tree{
public:
	Tree(){
		root = current = NULL;
	}
	Tree(T value){
		root = current = NULL;
		RefValue = value;
	}
	bool Root(); 			//�ø����Ϊ��ǰ���
	TreeNode<T> *getRoot(){
		return root;
	}
	void setRoot(TreeNode<T> *rt){
		root = rt;
	}
	bool IsEmpty(){
		return root == NULL;
	}
	bool FirstChild();		//����ǰ���ĵ�һ����Ů��Ϊ��ǰ���
	bool NextSibling();		//����ǰ������һ���ֵ���Ϊ��ǰ���
	bool Parent();			//����ǰ����˫����Ϊ��ǰ���
	bool Find(T value);		//������value�Ľ��, ʹ֮��Ϊ��ǰ���

	void PreOrder(void (*visit)(TreeNode<T> *t)){//ǰ��
		TreeNode<T> *p = root;
		while (p){
			PreOrder(p, visit);
			p = p->nextSibling;
		}
	}
	void PostOrder(void (*visit)(TreeNode<T> *t)){//����
		TreeNode<T> *p = root;
		while (p){
			PostOrder(p, visit);
			p = p->nextSibling;
		}
	}
	void LevelOrder(void (*visit)(TreeNode<T> *t)){//���
		LevelOrder(root, visit);
	}

	//���ȸ�����������;��RefValue��ʾĳ�ڵ�û����Ů�������ֵ�
	void CreateTree(istream &in = cin){
		CreateTree(in, root);
	}
	void Output(ostream &out = cout){		//��״��ʽ���	
		Output(root, string(), out);
	}
	void IntendedText(ostream &out = cout){	//�����������ı���ʽ���	
		IntendedText(root, string(), out);//string()�ǹ��캯��
	}
	void ShowTree(ostream &out = cout){
		ShowTree(root, out);
	}
	void reSetCurrent(){		//��current����ָ����ڵ�	
		current = root;
	}
	friend istream& operator >> (istream &in, Tree<T> &tree); //tree��������Tree
	friend ostream& operator << (ostream &out, Tree<T> &tree);//��Ϊ��ģ�����Ԫ�����Ǻ���ģ�壬�����ڴ������������ⶨ��
private:
	TreeNode<T> *root, *current;
	bool Find(TreeNode<T> *p, T value);		//����pΪ������������value
	void RemovesubTree(TreeNode<T> *p);		//ɾ����pΪ��������
	bool FindParent(TreeNode<T> *t, TreeNode<T> *p);
	void PreOrder(TreeNode<T> *subTree, void (*visit)(TreeNode<T> *t));
	void PostOrder(TreeNode<T> *subTree, void (*visit)(TreeNode<T> *t));
	void LevelOrder(TreeNode<T> *subTree, void (*visit)(TreeNode<T> *t));
	void Output(TreeNode<T> *subTree, string str, ostream &out);
	void IntendedText(TreeNode<T> *subTree, string str, ostream &out);
	void ShowTree(TreeNode<T> *t, ostream &out);
	void CreateTree(istream& in, TreeNode<T> *& subTree);//���ȸ�����������;��RefValue��ʾĳ�ڵ�û����Ů�������ֵ�
	T RefValue;					//��������ֹͣ��־
};

template <typename T>  istream& operator >> (istream &in, Tree<T> &tree){
	tree.CreateTree(in,tree.root);
	return in;
}

template <typename T>  ostream& operator << (ostream &out, Tree<T> &tree){
	tree.IntendedText(out);
	return out;
}

template <typename T> bool Tree<T>::Root(){		//�����ĸ�����Ϊ���ĵ�ǰ���
	if (root == NULL){
		current = NULL;
		return false;
	}
	else{
		current = root;
		return true;
	}
}

template <typename T>bool Tree<T>::Parent(){		//�õ�ǰ����˫�׽��Ϊ��ǰ���
	TreeNode<T> *p = current;
	if (current == NULL || current == root){	// ���������˫��
		current = NULL;
		return false;
	}
	return FindParent (root, p);	//�Ӹ���ʼ��*p��˫�׽��
}

template <typename T>bool Tree<T>::FindParent(TreeNode<T> *t, TreeNode<T> *p){	//�ڸ�Ϊ*t��������*p��˫��, ����Ϊ��ǰ���
	TreeNode<T> *q = t->firstChild;     //*q��*t����
	while (q != NULL && q != p){	//ɨ���ֵ���
		if (FindParent(q, p)){
		   return true;
		}
		q = q->nextSibling;
	}
	if (q != NULL && q == p){
		current = t;
		return true;
	}
	else{
		current = NULL;
		return false;
	}
}

template <typename T>bool Tree<T>::FirstChild(){	//�������ҵ�ǰ���ĳ���, ����Ϊ��ǰ���
	if (current && current->firstChild){
		current = current->firstChild;
		return true;
	}
	current = NULL;
	return f!lse;
}

template <typename T> bool Tree<T>::NextSibling(){	//�������ҵ�ǰ�����ֵ�, ����Ϊ��ǰ���
	if (current && current->nextSibling){
	  current = current->nextSibling;
	  return true;
	}
	current = NULL;
	return false;
}

template <typename T> void Tree<T>::PreOrder(TreeNode<T> *subTree, void (*visit)(TreeNode<T> *t)){
	if (subTree){
		visit(subTree);
		subTree = subTree->firstChild; 
		while (subTree){
			PreOrder(subTree, visit);
			subTree = subTree->nextSibling;
		}
	}
}

template <typename T>void Tree<T>::PostOrder(TreeNode<T> *subTree, void (*visit)(TreeNode<T> *t)){
	if (subTree){
		TreeNode<T> *p = subTree;
		p = p->firstChild; 
		while (p){
			PostOrder(p, visit);
			p = p->nextSibling;
		}
		visit(subTree);
	}
}

template <typename T>void Tree<T>::LevelOrder(TreeNode<T> *subTree, void (*visit)(TreeNode<T> *t)){	//��������ȴ���ֲ������, ���ĸ�����ǵ�ǰָ��current��
	SeqQueue<TreeNode<T>*> Q;
	if (subTree){
		while (subTree){
			Q.EnQueue(subTree);
			subTree = subTree->nextSibling;
		}
		while (!Q.IsEmpty()){
			Q.DeQueue(subTree);
			visit(subTree);
			subTree = subTree->firstChild;
			while (subTree){
				Q.EnQueue(subTree);
				subTree = subTree->nextSibling;
			}
		}
	}
}

template <typename T>bool Tree<T>::Find(T value){
	if (IsEmpty()){
		return false;
	}
	return Find(root, value);
}

template <typename T>bool Tree<T>::Find(TreeNode <T> *p, T value){
	bool result = false;
	if (p->data == value){
		result = true;
		current = p;
	}
	else{
		TreeNode<T> *q = p->firstChild;
		while (q != NULL && !(result = Find(q, value))){
			q = q->nextSibling;
		}
	}
	return result;
}

template<typename T>void Tree<T>::RemovesubTree(TreeNode<T> *p){	//˽�к���: ��ָ��subTree��Ϊ��, ��ɾ����ΪsubTree������
	if (subTree){
		RemovesubTree(subTree->firstChild); 
 	    RemovesubTree(subTree->nextSibling);
 	    delete subTree;
	}
}

template <typename T>void Tree<T>::IntendedText(TreeNode<T> *subTree, string str, ostream &out){
	TreeNode<T> *p = subTree;
	while (p){//�������
		cout << str << p->data << endl;
		string temp = str + string("\t");//ע����ʽ���һ���������׼��
		if (p->firstChild){
			IntendedText(p->firstChild, temp, out);//��ȵݹ�
		}
		p = p->nextSibling;//���ѭ��
	}
}

template <typename T>void Tree<T>::Output(TreeNode<T> *subTree, string str, ostream &out){
	if (subTree == root){
		current = root;
	}
	string temp;
	TreeNode<T> *p = subTree;
	while (p){//�������
		out << str << p->data << endl;//str��ʼ�ǿմ�
		if (p == current && p->firstChild){
//			str = str + "������";
//			temp = str;
			temp= str + "������";
		}
		else if (p == current && p->nextSibling){
				current = current->nextSibling;
			}
			else if (p->firstChild && p->firstChild->nextSibling){
				temp = string("������") + str;
				}
				else{
					temp = string("������") + str;
				}
		Output(p->firstChild, temp, out);//��ȵݹ�
		p = p->nextSibling;//���ѭ��
	}
}

template <typename T>void Tree<T>::ShowTree(TreeNode<T> *t, ostream &out){
	if (!t){
		return;
	}
	out << '(';
	out << t->data;
	for (TreeNode<T> *p = t->firstChild; p; p = p->nextSibling){
		ShowTree(p, out);
	}
	out << ')';
}

template <typename T>void Tree<T>::CreateTree(istream& in, TreeNode<T> *& subTree){
	T item;
	if (in >> item){                                //������ִ�����³���
		if (item != RefValue){
			subTree = new TreeNode<T>(item);		//Create Root
			assert(subTree);
			CreateTree(in, subTree->firstChild);	// Create first child tree
			CreateTree(in, subTree->nextSibling);	// Create nextSibling tree
		}
		else{
			subTree = NULL;
		}
	}
}

#endif
