#ifndef AVLTREE_H
#define AVLTREE_H
#include <cassert>
#include <iostream>
#include <string>
using namespace std;
//#include "BST.h"
#include "SeqStack.h"

//AVL�������ඨ��  
template <typename E, typename K>struct AVLNode /*: public BSTNode<E,K>*/{
	int bf;
	E data;
	AVLNode<E,K> *left, *right;
	AVLNode(){
		left = NULL;
		right = NULL;
		bf = 0;
	}
	AVLNode(E d, AVLNode<E,K> *l = NULL, AVLNode<E,K> *r = NULL){
		data = d;
		left = l;
		right = r;
		bf = 0;
	}
};

//ƽ��Ķ�����������AVL���ඨ��
template <typename E, typename K>class AVLTree /*: public BST<E,K>*/{
public:
	AVLTree(){
		root = NULL;
	}
	AVLTree(K Ref){
		RefValue = Ref;
		root = NULL;
	}
	int Height()const{
		return Height(root);
	}
	bool Insert(E &e1){
		return Insert(root, e1);
	}
	bool Remove(K x, E &e1){
		return Remove(root, x, e1);
	}
	AVLNode<E,K> *Search(K x)const{
		return Search(x,root);
	}
	void PrintTree(ostream &out = cout)const{    //�������ʽ���	
		PrintTree(root, out);
	}
	void PrintData(ostream &out = cout)const{    //�������	
		PrintData(root, out);
	}
	friend istream& operator >> (istream& in,AVLTree<E,K>& Tree){
		E data;
		while (!in.eof()){
			assert(in >> data);
			Tree.Insert(data);
		}
		return in;
	}
	friend ostream& operator << (ostream &out, AVLTree<E,K> &R){
		out << "The structure of the AVL tree is: \n";
		R.PrintTree(out);
		out << "\n\nInorder traversal of AVL tree: \n";	//��ʾ��AVL�����������
		R.Traverse(R.root, out);				//����������������������
		out << "\n\nThe datail of the tree is: \n";
		R.PrintData(out);
		return out;									//�������Ԫ��
	}
protected:
//	K RefValue;
	AVLNode<E,K> *root;
	int Height(AVLNode<E,K> *ptr)const; 
	bool Insert(AVLNode<E,K> *&ptr, E &e1);
	bool Remove(AVLNode<E,K> *&ptr, K x, E &e1);
	void RotateL(AVLNode<E,K> *&ptr);
	void RotateR(AVLNode<E,K> *&ptr);
	void RotateLR(AVLNode<E,K> *&ptr);
	void RotateRL(AVLNode<E,K> *&ptr);
	void Traverse(AVLNode<E,K> *ptr, ostream &out)const;
	void PrintTree(AVLNode<E,K> *ptr, ostream &out)const;
	void PrintData(AVLNode<E,K> *ptr, ostream &out)const;
	AVLNode<E,K> *Search(K x, AVLNode<E,K> *par)const;
};

template <typename E, typename K>AVLNode<E,K> *AVLTree<E,K>::Search(K x, AVLNode<E,K> *ptr)const{
	if (ptr == NULL){
		return NULL; 
	}
	AVLNode<E,K> *temp = ptr;
	while (temp){
		if (temp->data == x){
			return temp;
		}
		if (temp->data > x){
			temp = temp->left;
		}
		else{
			temp = temp->right;
		}
	}
	return NULL;
/*	if (!par)//δ���ö԰�����
		return NULL;
	if (x == par->data)
		return par;
    AVLNode<E,K> *p;
	if ((p = Search(x,par->left))!=NULL)
		return p;
	else
		return Search(x,par->right);*/
}

template <typename E, typename K>int AVLTree<E,K>::Height(AVLNode<E,K> *ptr)const{
	if (!ptr){
		return 0;
	}
	int n=Height(ptr->left);
	int m=Height(ptr->right);
	return n<m ? m+1 : n+1;
}
//���±����Ӧ�̲ĵ�ͼ�����̲�ͼȱ��һЩ�м䲽�裬Ҫ������������
//����������������: ������ת���¸���ptr
template <typename E, typename K>void AVLTree<E,K>::RotateL(AVLNode<E,K> *& ptr){
	AVLNode<E,K> *subL = ptr;			//����ԭ���ĸ����
	ptr = subL->right;					//ԭ��������Ů����Ϊ�¸�
	subL->right = ptr->left;			//ptr��Ϊ�¸�ǰж������Ů����Ϊԭ��������Ů
	ptr->left = subL;					//������ptr��Ϊ�¸���ԭ����Ϊ�¸�������Ů
	ptr->bf = subL->bf = 0;				//��дƽ���
}


//����������������, ��ת���¸���ptr
template <typename E, typename K>void AVLTree<E,K>::RotateR(AVLNode<E,K> *& ptr){ 
	AVLNode<E,K> *subR = ptr;
	ptr = subR->left;					//ԭ��������Ů��Ϊ�¸�
	subR->left = ptr->right;			//�¸�ԭ����Ů��Ϊԭ��������Ů
	ptr->right = subR;					//ԭ����Ϊ�¸�������Ů
	ptr->bf = subR->bf = 0;				//��дƽ���
}

template <typename E, typename K>void AVLTree<E,K>::RotateLR(AVLNode<E,K> *& ptr){
	AVLNode<E,K> *subR = ptr;
	AVLNode<E,K> *subL = subR->left;
	ptr = subL->right;					//������
	subL->right = ptr->left;			//ptr��Ϊ�¸�ǰж������Ů����Ϊԭ��������Ů
	ptr->left = subL;					//������ptr��Ϊ�¸���ԭ����Ϊ�¸�������Ů
	if (ptr->bf <= 0){					//��תǰ�����½���ptr���������
		subL->bf = 0;
	}
	else{								//�����½���ptr���������
		subL->bf = -1;
	}
	subR->left = ptr->right;
	ptr->right = subR;	
	if (ptr->bf == -1){					//��תǰ�����½���ptr���������
		subR->bf = 1;
	}
	else{								//�����½���ptr���������
		subR->bf = 0;
	}
	ptr->bf = 0;
}

template <typename E, typename K>
void AVLTree<E,K>::RotateRL(AVLNode<E,K> *& ptr){
	AVLNode<E,K> *subL = ptr;
	AVLNode<E,K> *subR = subL->right;
	ptr = subR->left;
	subR->left = ptr->right; 
	ptr->right = subR;
	if (ptr->bf >= 0){
		subR->bf = 0;
	}
	else{
		subR->bf = 1;
	}
	subL->right = ptr->left;
	ptr->left = subL;
	if (ptr->bf == 1){
		subL->bf = -1;
	}
	else{
		subL->bf = 0;
	}
	ptr->bf = 0;
}

//����ptrΪ����AVL���в�����Ԫ��e1,
//�������ɹ�,��������true,���򷵻�false��
template <typename E, typename K>bool AVLTree<E,K>::Insert(AVLNode<E,K> *& ptr, E &e1){
	AVLNode<E,K> *pr = NULL, *p = ptr, *q;
	int d;
	SeqStack<AVLNode<E,K>*> st;
	while (p != NULL){					//Ѱ�Ҳ���λ��	
		if (e1 == p->data) return false;//�ҵ�����e1�Ľ��,������
		pr = p;  st.Push(pr);			//������ջ�������·��
		if (e1 < p->data) p = p->left;
		else p = p->right;
	}
	p = new AVLNode<E,K>(e1);			//�����½��,data=e1,bf=0
	assert(p);
	if (pr == NULL){						//����,�½���Ϊ�����	
		ptr = p;
		return true;
	}
	if (e1 < pr->data){					//�½�����	
		pr->left = p;
	}
	else{
		pr->right = p;
	}
	//����ƽ�⻯
	while (st.IsEmpty() == false){
		st.Pop(pr);						//��ջ���˳������
		if (p == pr->left){				//����������ƽ������		
			pr->bf--;
		}
		else{
			pr->bf++;
		}
		if (pr->bf == 0){				//��1�����,|bf|=0,ƽ���˳�		
			break;
		}
		if (pr->bf == 1 || pr->bf == -1){//��2�����,|bf|=1		
			p = pr;
		}
		else{							//��3�����,|bf|=2		
			d = (pr->bf < 0) ? -1 : 1;	//����˫��ת��־
			if (p->bf == d){				//�����ƽ������ͬ��,����ת			
				if (d == -1)				{
					RotateR(pr);		//�ҵ���ת
				}
				else{
					RotateL(pr);		//����ת
				}
			}
			else{							//�����ƽ�����ӷ���,˫��ת
				if (d == -1){
					RotateLR(pr);		//�������˫��ת,��<���� 
				}
				else{
					RotateRL(pr);		//���Һ���˫��ת,��>����
				}
			}
			break;						//�������ϵ���
		}//�������������
	}
	// ���ڵڶ��������Ҫ�����ӽ������ķ�����ݵ���
	if (st.IsEmpty() == true){			//���������ĸ����	
		ptr = pr;
	}
	else{								//�м���������	
		st.getTop(q);
		if (q->data > pr->data){		
			q->left = pr;
		}
		else{
			q->right = pr;
		}
	}
	return true;
}

//����ptrΪ����AVL����ɾ���ؼ���Ϊx�Ľ�㡣
//���ɾ���ɹ�,��������true,ͬʱͨ������e1���ر�ɾ���Ԫ�أ�
//���ɾ��ʧ����������false�� 
template <typename E, typename K>bool AVLTree<E,K>::Remove(AVLNode<E,K> *& ptr, K x, E &e1){
	AVLNode<E,K> *pr = NULL, *p = ptr, *q, *ppr;
	int d, dd = 0;
	SeqStack<AVLNode<E,K>*> st;
	while (p != NULL){					//Ѱ��ɾ��λ��	
		if (x == p->data.key){			//�ҵ�����x�Ľ��,ֹͣ����		
			break;
		}
		pr = p;  st.Push(pr);			//������ջ�������·��
		if (x < p->data.key){
			p = p->left;
		}
		else{
			p = p->right;
		}
	}

	if (p == NULL){						//δ�ҵ���ɾ���,ɾ��ʧ��	
		return false;
	}
	e1 = p->data;

	if (p->left && p->right){			//��ɾ�����������Ů	
		pr = p;  st.Push(pr);
		q = p->left;					//��p��������p��ֱ��ǰ��
		while (q->right){
			pr = q;
			st.Push(pr);
			q = q->right;
		}
		p->data = q->data;				//��q��ֵ�p
		p = q;							//��ɾ���ת��Ϊq
	}
	//���°�����˫��Ůת����ĺ�ԭ���ͷ�˫��Ů�ġ�
	//ͬʱ����Ҳ��������Ů������Ů
	if (p->left){						//��ɾ���p���ֻ��һ����Ůq	
		q = p->left;
	}
	else{
		q = p->right;					//����Ůʱ��qΪNULL
	}
	if (pr == NULL){					//��ɾ���Ϊ�����,�丸���Ϊ��
		ptr = q;
	}
	else{								//��ɾ��㲻�Ǹ����	
		if (pr->left == p){				//����		
			pr->left = q;
		}
		else{
			pr->right = q;
		}
		while (st.IsEmpty() == false){	//����ƽ�⻯		
			st.Pop(pr);					//��ջ���˳������
			if(q==NULL){				//����������ƽ�����ӡ�����Ů
				pr->bf=0;
			}
			else{						//����Ů
				if (pr->right == q){
					pr->bf--;			//ɾ���ұ�
				}
				else{
					pr->bf++;			//ɾ�����
				}
			}
			if (st.IsEmpty() == false){
				st.getTop(ppr);			//��ջ��ȡ���游���
				dd = (ppr->left == pr) ?-1 : 1;	//��ת�����ϲ����ӷ���
			}
			else{						//ջ��,��ת�����ϲ�����			
				dd = 0;
			}
			if (pr->bf == 1 || pr->bf == -1){ 	//ͼ7.20,|bf|=1			
				break;
			}
			if (pr->bf != 0){			//|bf|=2			
				if (pr->bf < 0) {d = -1;  q = pr->left;}
				else{					//��qָʾ�ϸߵ�����				
					d = 1;
					q = pr->right;
				}
				if (q->bf == 0){			//ͼ7.22				
					if (d == -1){
						RotateR(pr);		//�ٲμ�ͼ7.15
						pr->bf = 1;
						pr->right->bf = -1;	//#��
					}
					else{
						RotateL(pr);
						pr->bf = -1;
						pr->left->bf = 1;	//#��
					}
					//��ת���¸����ϲ�����
					if (dd == -1){
						ppr->left = pr;
					}
					else if (dd == 1){
						ppr->right = pr;
					}
					break;
				}
				if (q->bf == d){			//�����ƽ������ͬ��,ͼ7.23				
					if (d == -1){		//�ҵ���ת					
						RotateR(pr);
					}
					else{				//����ת					
						RotateL(pr);
					}
				}
				else{					//�����ƽ�����ӷ���,ͼ7.24				
					if (d == -1){		//�������˫��ת,��<���� 					
						RotateLR(pr);
					}
					else{				//���Һ���˫��ת,��>����					
						RotateRL(pr);
					}
				}
				//��ת���¸����ϲ�����
				if (dd == -1){
					ppr->left = pr;
				}
				else if (dd == 1){
					ppr->right = pr;
				}
			}
			q = pr;						//ͼ7.21,|bf|=0
		}
		if (st.IsEmpty() == true){		//���������ĸ����		
			ptr = pr;
		}
	}
	delete p;
	return true;
}


template <typename E, typename K>void AVLTree<E,K>::Traverse(AVLNode<E,K> *ptr, ostream &out)const{
	if (ptr != NULL){					//���ǿ�	
		Traverse(ptr->left, out);		//�������������
		out << ptr->data.key << ' ';	//�����������
		Traverse(ptr->right, out);		//�������������
	}
}

template<typename E, typename K>void AVLTree<E,K>::PrintTree(AVLNode<E,K> *ptr, ostream &out)const{
	if (!ptr){
		return;
	}
	out << ptr->data.key;
	if (ptr->left == NULL && ptr->right == NULL){
		return;
	}
	out << "(";
	PrintTree(ptr->left, out);
	out << ',';
	PrintTree(ptr->right, out);
	out << ")";
}

template<typename E, typename K>void AVLTree<E,K>::PrintData(AVLNode<E,K> *ptr, ostream &out)const{
	if (ptr){
		PrintData(ptr->left, out);
		out << ptr->data <<'\t'<< ptr->bf << endl;
		PrintData(ptr->right, out);
	}
}
#endif
