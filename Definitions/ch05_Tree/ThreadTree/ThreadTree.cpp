#include "ThreadTree.h"

template <typename T>void ThreadTree<T>::createInThread(){
	ThreadNode<T> *pre = NULL;		//ǰ�����ָ��
	if (/*!*/root){					//��
		createInThread(root, pre);	//�������������������
		pre->rightChild = NULL;		//�����������һ�����
		pre->rtag = 1;
	}
}

//ͨ���������, �Զ���������������
template <typename T>void ThreadTree<T>::createInThread(ThreadNode<T> *current, ThreadNode<T> *& pre){
	if (!current){
		return;
	}	
	createInThread(current->leftChild, pre); // ������������	
	if (current->leftChild == NULL){         //������ǰ����ǰ������
	  current->leftChild = pre;
	  current->ltag = 1;
	}	
	if (pre != NULL && pre->rightChild == NULL){//����ǰ�����ĺ������
		pre->rightChild = current;
		pre->rtag = 1; 
	}
	pre = current;//ǰ������,��ǰָ����ǰ����	
	createInThread(current->rightChild, pre);//�ݹ�, ������������
}

template <typename T>ThreadNode<T>* ThreadTree<T>::First(ThreadNode<T> *current){// ������currentΪ������������ĵ�һ�����
    ThreadNode<T> *p = current;	
    while (p->ltag == 0){
		p = p->leftChild;//�����½�㣨��һ����Ҷ��㣩
	}
    return p;
}

template <typename T>ThreadNode<T> * ThreadTree <T>::Next(ThreadNode<T> *current){// ���ؽ��current��������ĺ�̽��
    ThreadNode<T> *p = current->rightChild;
    if (current->rtag == 0){	//rtag == 0, ��ʾ������Ů	
		return First (p);
	}
    else{	//rtag == 1, ֱ�ӷ��غ������	
		return p;
	}
}

template <typename T>ThreadNode<T> *ThreadTree<T>::Last(ThreadNode<T> *current){// ������currentΪ����������������һ�����
	ThreadNode<T> *p = current;
	//�����½�㣨��һ����Ҷ��㣩
	while (p->rtag == 0){
		p = p->rightChild;//�����½�㣨��һ����Ҷ��㣩
	}
	return p;
}

template <typename T>ThreadNode<T> *ThreadTree<T>::Prior(ThreadNode<T> *current){// �������������ǰ�����
	//�������������������������н��current�������µ�ǰ����㡣
	ThreadNode<T> *p = current->leftChild;
	if (current->ltag == 0){	//�������������������һ�����	
		return Last(p);
	}
	else{ //ltag==1, ֱ�ӷ���ǰ������	
		return p;
	}
}
template<typename T>bool ThreadTree<T>::FindTh(const T &value){//������������ʹ��
	ThreadNode<T> *p;
    for (p = First(root); p != NULL; p = Next(p)){
		if(p->data==value){
			current=p;
			return true;
		}
	}
	return false;
}

template <typename T>void ThreadTree <T>::InOrder(void (*visit)(ThreadNode<T> *t)){//�������
    ThreadNode<T> *p;
    for (p = First(root); p != NULL; p = Next(p)){
		visit (p);
	}
}

template <typename T>void ThreadTree<T>::PreOrder(void (*visit)(ThreadNode<T> *t)){// ǰ�����
	ThreadNode<T> *p = root;
	while (p){
		visit(p);				//���ʸ����
		if (p->ltag == 0){		//������Ů,��Ϊ���		
			p = p->leftChild;
		}
		else if (p->rtag == 0){	//������Ů,��Ϊ���		
			p = p->rightChild;
		}
		else{
			while (p != NULL && p->rtag == 1){	//�غ���������,ֱ��������Ů�Ľ��			
				p = p->rightChild;
			}
			if (p != NULL){	//����Ů��Ϊ���			
				p = p->rightChild;
			}
		}
	}
}

template <typename T>void ThreadTree<T>::PostOrder(void (*visit)(ThreadNode<T> *p)){
	ThreadNode<T> *t = root;
	//Ѱ�Һ����һ�����
	while (t->ltag == 0 || t->rtag == 0){
		if (t->ltag == 0){
			t = t->leftChild;
		}
		else if (t->rtag == 0){
			t = t->rightChild;
		}
	}
	visit(t);	//���ʵ�һ�����
	ThreadNode<T> *p;
	while ((p = parent(t)) != NULL)	{
		if (p->rightChild == t || p->rtag == 1){	//*t��*p�ĺ�����		
			t = p;
		}
		else{	//����t�Ƶ�*p��������		
			t = p->rightChild;
			while (t->ltag == 0 || t->rtag == 0){	
				if (t->ltag == 0){
					t = t->leftChild;
				}
				else if (t->rtag == 0){
					t = t->rightChild;
				}
			}
		}
		visit(t);
	}
}

template <typename T>ThreadNode<T> *ThreadTree<T>::parent(ThreadNode<T> *t){
	ThreadNode<T> *p;
	if (t == root){
		return NULL;
	}
	for (p = t; p->ltag == 0; p = p->leftChild);//��*tΪ��������һ����㣬��ǰ����*t������
	if (p->leftChild != NULL){//��ָ����ǰ�������ý����ȫ��(tΪroot)�����һ������ǰ��
		p=p->leftChild;//�ҵ�����
		if(p->rightChild != t/*&&p->leftChild != t*/)//������Ǹ����
			for(p = p->rightChild; //����һ��
			/*rightChild != t&&*/p->leftChild != t;//��t�Ƿ�p����Ů������һ�����ҵ�
			p = p->leftChild);//�����ߵ���
	}
	else{//�ý����ȫ��(tΪroot)�����һ��㣬��ǰ�������뻻һ������ȥ�ұ��Һ��
		for (p = t; p->rtag == 0; p = p->rightChild);//��*tΪ���������һ�����
		p=p->rightChild;//�ҵ�����
		if(p->leftChild != t/*&&p->rightChild != t*/)
		for (p = p->leftChild;//����һ��
			 /*p->leftChild != t&&*/p->rightChild != t;
			p = p->rightChild);//�����ߵ���,�����ҵ�
	}
	return p;
}
