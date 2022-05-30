#ifndef GRAPHLNK_H
#define GRAPHLNK_H
#include "Graph.h"
#include <iostream>
#include <cassert>
using namespace std;

extern const int maxWeight;							//����������ֵ(=)

const int DefaultVertices = 30;						//Ĭ����󶥵���(=n)

//�ڽӱ�ʵ�ֵ�ͼ��
template <typename T, typename E>struct Edge{		//�߽��Ķ���
	int dest;										//�ߵ���һ����λ��
	E cost;											//���ϵ�Ȩֵ
	Edge<T,E> *link;								//��һ������ָ��
	Edge() {}										//���캯��
	Edge(int num, E weight){						//���캯��	
		dest = num;
		cost = weight;
		link = NULL;
	}
	bool operator != (Edge<T,E> &R)const{			//�б߲��ȷ�#ֻ������ͬһ�еĵ�������
		return (dest != R.dest);
	}	
};

//����Ķ���
template <typename T, typename E>struct Vertex{
	T data;					//���������
	Edge<T,E> *adj;			//�������ͷָ��
};

template <typename T, typename E>class Graphlnk : public Graph<T,E>{			//ͼ���ඨ��
public:
	Graphlnk(int sz = DefaultVertices);	//���캯��
	~Graphlnk();						//��������
	T getValue(int i){	//���ظ��ڽӶ���ı�ţ����������򷵻�0		//ȡλ��Ϊi�Ķ����е�ֵ	
		return (i >= 0 && i < NumberOfVertices()) ? NodeTable[i].data : 0;
	}

	E getWeight(int v1, int v2);						//���ر�(v1,v2)�ϵ�Ȩֵ
	bool insertVertex(const T& vertex);					//��ͼ�в���һ������vertex
	bool removeVertex(int v);							//��ͼ��ɾ��һ������v
	bool insertEdge(int v1, int v2, E weight);			//��ͼ�в���һ����(v1,v2)
														//����һ����������ʾ���붥���ֵ������true��ʾ����ɹ�

	bool removeEdge(int v1, int v2);					//��ͼ��ɾ��һ����(v1,v2)
	int getFirstNeighbor(int v);						//ȡ����v�ĵ�һ���ڽӶ���
														//���ص�һ���ڽӶ���ı�ţ��������ڻ�����������򷵻�-1

	int getNextNeighbor(int v, int w);					//ȡv���ڽӶ���w����һ�ڽӶ���

	int getVertexPos(const T &vertex){					//��������vertex��ͼ�е�λ��	
		for (int i = 0; i < numVertices; i++){
			if (NodeTable[i].data == vertex){
				return i;
			}
		}
		return -1; 
	}
private:
	Vertex<T,E> *NodeTable;								//����� (���������ͷ���)
};

//-----------------------------------------------------------------------------------------------------
//���캯��������һ���յ��ڽӱ�
template <typename T, typename E>Graphlnk<T,E>::Graphlnk(int sz):Graph<T,E>(sz){
	NodeTable = new Vertex<T,E>[maxVertices];		//�������������
	assert(NodeTable);
	for (int i = 0; i < maxVertices; i++){
		NodeTable[i].adj = NULL;
	}
}

//����������ɾ��һ���ڽӱ�
template <typename T, typename E>Graphlnk<T,E>::~Graphlnk(){				
	for (int i = 0; i < numVertices; i++ ){		//ɾ�����������еĽ��	
		Edge<T,E> *p = NodeTable[i].adj; 		//�ҵ����Ӧ��������׽��
		while (p != NULL){						//���ϵ�ɾ����һ�����		
			NodeTable[i].adj = p->link;
			delete p;
			p = NodeTable[i].adj;
		}
	} 
	delete []NodeTable;  			//ɾ�����������
}

//�������ر�(v1,v2)�ϵ�Ȩֵ, ���ñ߲���ͼ��, ��������Ȩֵ0��
template <typename T, typename E>E Graphlnk<T,E>::getWeight(int v1, int v2){
	if (v1 != -1 && v2 != -1){
		Edge<T,E> *p = NodeTable[v1].adj;			//V1�ĵ�һ�������ı�
		while (p != NULL && p->dest != v2){			//Ѱ���ڽӶ���v2		
			p = p->link;
		}
		if (p != NULL){
			return p->cost;				//�ҵ��˱�, ����Ȩֵ
		}
	}
	return 0;										//��(v1,v2)������
}

template <typename T, typename E>bool Graphlnk<T,E>::insertVertex(const T& vertex){
	//��ͼ�Ķ�����в���һ���¶���vertex��������ɹ�����������true, ���򷵻�false��
	if (numVertices == maxVertices){	//�������, ���ܲ���	
		return false;
	}
	NodeTable[numVertices].data = vertex;			//�����ڱ�����
	numVertices++;
	return true;
}

//�ڴ�Ȩͼ�в���һ����(v1,v2), 
//���˱ߴ��ڻ������������������false, ���򷵻�true��
template <typename T, typename E>bool Graphlnk<T,E>::insertEdge(int v1, int v2, E weight){
	if (v1 >= 0 && v1 < numVertices && v2 >= 0 && v2 < numVertices){
		Edge<T,E> *q, *p = NodeTable[v1].adj;		//v1��Ӧ�ı�����ͷָ��
		while (p != NULL && p->dest != v2){ 		//Ѱ���ڽӶ���v2		
			p = p->link;
		}
		if (p != NULL){				//�ҵ��˱�, ������		
			return false;
		}
		p = new Edge<T,E>;			//����, �����½��
		q = new Edge<T,E>;
		p->dest = v2;
		p->cost = weight;
		p->link = NodeTable[v1].adj; 				//����v1������
		NodeTable[v1].adj = p;
		
		q->dest = v1;
		q->cost = weight;
		q->link = NodeTable[v2].adj; 				//����v2������
		NodeTable[v2].adj = q;
		numEdges++;
		return true;
	}
	return false;
}

//��������λ��Ϊv�ĵ�һ���ڽӶ����λ��, ����Ҳ���, ��������-1��
template <typename T, typename E>int Graphlnk<T,E>::getFirstNeighbor(int v){
	if (v != -1){									//����v����	
		Edge<T,E> *p = NodeTable[v].adj;			//��Ӧ�������һ���߽��
		if (p != NULL){								//����, ���ص�һ���ڽӶ���		
			return p->dest;
		}
	}
	return -1;										//��һ���ڽӶ��㲻����
}

//��������v���ڽӶ���w����һ���ڽӶ����λ��, 
//��û����һ���ڽӶ���, ��������-1��
template <class T,class E>int Graphlnk<T,E>::getNextNeighbor(int v, int w){
	if (v != -1){									//����v����	
		Edge<T,E> *p = NodeTable[v].adj;			//��Ӧ�������һ���߽��
		while (p != NULL && p->dest != w){			//Ѱ���ڽӶ���w		
			p = p->link;
		}
		if (p != NULL && p->link != NULL){
			return p->link->dest; 					//������һ���ڽӶ���
		}
	}
	return -1; 										//��һ�ڽӶ��㲻����
}

//��ͼ��ɾ��һ����(v1, v2)
template <typename T, typename E>bool Graphlnk<T,E>::removeEdge(int v1, int v2){
	if (v1!= -1 && v2 != -1){
		Edge<T,E> *p = NodeTable[v1].adj, *q = NULL, *s = p;
		while (p != NULL && p->dest != v2){	 			//v1��Ӧ���������ұ�ɾ��		
			q = p;
			p = p->link;
		}
		if (p != NULL){									//�ҵ���ɾ�߽��		
			if (p == s){
				NodeTable[v1].adj = p->link;			//�ý���Ǳ������׽��
			}
			else{										//����, ��������			
				q->link = p->link;
			}
			delete p;
		}
		else{											//û���ҵ���ɾ�߽��		
			return false;
		}
		p = NodeTable[v2].adj;							//v2��Ӧ��������ɾ��
		q = NULL, s = p;
		while (p->dest != v1){							//Ѱ�ұ�ɾ�߽��		
			q = p;
			p = p->link;
		}
		if (p == s){									//�ý���Ǳ������׽��
		
			NodeTable[v2].adj = p->link;
		}
		else{
			q->link = p->link;							//����, ��������
		}
		delete p; 
		numEdges--;
		return true;
	}
	return false;										//û���ҵ����
}

template <typename T, typename E>bool Graphlnk<T,E>::removeVertex(int v){
	//��ͼ��ɾ��һ��ָ������v, v�Ƕ���š���ɾ���ɹ�, ��������true, ���򷵻�false��
	if (numVertices == 1 || v < 0 || v >= numVertices){
		return false;
	}
	//��ջ򶥵�ų�����Χ
	Edge<T,E> *p, *s,*t;  int k;
	while (NodeTable[v].adj != NULL){				//ɾ����v�������������н��
		p = NodeTable[v].adj;  k = p->dest;			//ȡ�ڽӶ���k
		s = NodeTable[k].adj;  t = NULL;			//�ҶԳƴ�ŵı߽��
		while (s != NULL && s->dest != v){
			t = s;  s = s->link;
		}
		if (s != NULL){								//ɾ���Գƴ�ŵı߽��		
			if (t == NULL){
				NodeTable[k].adj = s->link;
			}
			else{
				t->link = s->link;
			}
			delete s;
		}
		NodeTable[v].adj = p->link;					//�������v�ı�������
		delete p;
		numEdges--;									//�붥��v������ı�����һ
	}
	numVertices--;									//ͼ�Ķ��������1
	NodeTable[v].data = NodeTable[numVertices].data;//�#�����һ������������
	NodeTable[v].adj = NodeTable[numVertices].adj;
	p = NodeTable[v].adj;
	while (p != NULL){								//��������Ķ����±���ˣ���Ӧ�ߵı��Ҫ�ı�
		s = NodeTable[p->dest].adj;
		while (s!= NULL){
			if (s->dest == numVertices){
				s->dest = v;//�޸Ķ�Ӧ�߶�����±�
				break;
			}
			else{
				s = s->link;
			}
		}
	}
	return true;
}
#endif
