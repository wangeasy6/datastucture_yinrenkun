#ifndef GRAPH_H
#define GRAPH_H
#include "MinSpanTree.h"
#include "MinHeap.h"
#include "UFSets.h"
#include "SeqQueue.h"
#include "Tree.h"
const int maxWeight = 100000;

// ͼ�ĳ�����ඨ��#��Ȩ����ͼ
// TΪ��������ͣ�EΪ��Ȩֵ�����ͣ�һ��ӦΪĳһ�������͡�
template <typename T, typename E>class Graph{
public:
	Graph(int sz){
		maxVertices = sz;
		numVertices = 0;
		numEdges = 0;
	}
	virtual ~Graph(){};
	bool GraphEmpty() const{				//��ͼ�շ�	
		return (numEdges == 0);
	}	
	bool GraphFull() const{					//��ͼ���� 	
		return (numVertices == maxVertices || 
			numEdges == maxVertices*(maxVertices-1)/2);//����ͼ������ͼ������2
	}
	int NumberOfVertices(){				//���ص�ǰ������	
		return numVertices;
	}
	int NumberOfEdges(){					//���ص�ǰ����	
		return numEdges;
	}
	void DFS();						    //������ȱ���ͼ��������е���ͨ����
	void BFS();						    //������ȱ���ͼ��������е���ͨ����
	void DFSTree(Tree<T> &tree);		//��������Ů-���ֵ������ʾ��DFS����ɭ�֡�
	void Components();					//��������������������ͨͼ����ͨ�������㷨
	void Kruskal(MinSpanTree<T,E> &MST);//��С������
	void Prim(MinSpanTree<T,E> &MST);
	
	friend istream& operator >> (istream &in, Graph<T,E> &G){
		int i, j, k, n, m;
		T e1, e2;
		E weight;
		in >> n >> m;				//���붥���������
		for (i = 0; i < n; i++){	//�������붥��ֵ
			in >> e1;
			G.insertVertex(e1);
		}
		i = 0;
		while (i < m){
			assert(in >> e1 >> e2 >> weight);	//��������ߵ�������ֵ����Ȩֵ
			j = G.getVertexPos(e1);				//ȡ��Ӧ�����±�
			k = G.getVertexPos(e2);
			if (j == -1 || k == -1){			//ȡ��Ӧ���㲻����
				cout << "Input error!\n";
			}
			else{
				G.insertEdge(j, k, weight);		//�ɶ����±��Ȩֵ�����
				i++;
			}
		}
		return in;
	}
	friend ostream& operator << (ostream &out, Graph<T,E> &G){
		int i, j, n, m;
		T e1, e2;
		E weight;
		n = G.NumberOfVertices();		//�����������
		m = G.NumberOfEdges();
		out << "Number of Vertices: " << n << endl;
		out << "Number of Edges: " << m << endl;
		out << "The edges in the graph are:\n";
		for (i = 0; i < n; i++){
			for (j = i + 1; j < n; j++){
				weight = G.getWeight(i, j);
				if (weight > 0 && weight < maxWeight){
					e1 = G.getValue(i);	//���±�ȡ�ö���ֵ
					e2 = G.getValue(j);
					out << "(" << e1 << "," << e2 << "," << weight << ")" << endl;
				}
			}
		}
		return out;
	}

	// ͼ���������ʵ�ֵ�һЩ�ӿ�
	virtual T getValue(int i) = 0;							//ȡλ��Ϊi�Ķ����е�ֵ
	virtual E getWeight(int v1, int v2) = 0;				//���ر�(v1,v2)�ϵ�Ȩֵ
	virtual bool insertVertex(const T &vertex) = 0;			//��ͼ�в���һ������vertex
	virtual bool removeVertex(int v) = 0;					//��ͼ��ɾ��һ������v
	virtual bool insertEdge(int v1, int v2, E weight) = 0;	//����ȨֵΪweight�ı�(v1,v2)
	virtual bool removeEdge(int v1, int v2) = 0;			//ɾ����(v1,v2)
	virtual int getFirstNeighbor(int v) = 0;				//ȡ����v�ĵ�һ���ڽӶ���
	virtual int getNextNeighbor(int v, int w) = 0;			//ȡv���ڽӶ���w����һ�ڽӶ���
	virtual int getVertexPos(const T &vertex) = 0;			//��������vertex��ͼ�е�λ��
protected:
	int maxVertices;			//ͼ����󶥵���
	int numEdges;				//��ǰ����
	int numVertices;			//��ǰ������
	void DFS(int v, bool visited[]);					   //������ȱ���ͼ���ӹ���
	void DFSTree(int v, bool visited[], TreeNode<T> *& subTree);
};


//������ȱ���ͼ��������е���ͨ����
template<typename T, typename E> void Graph<T,E>::DFS(){
	int i, n = NumberOfVertices();		//ȡͼ�ж������
	bool *visited = new bool[n]; 		//������������
	for (i = 0; i < n; i++){			//��������visited��ʼ��	
		visited[i] = false;
	}
	for(i=0;i<n;i++){					//#��ÿ�����㿪ʼ������һ�α�����
		if(!visited[i]){				//#�����������飬��һ�˱����ѷ��ʹ��ĸ����㲻����Ϊ����㡣���������������ͨ�����������ظ���
			DFS(i, visited); 			//�Ӷ���0��ʼ�����������
			cout<<endl;
		}
	}
	delete [] visited;					//�ͷ�visited
}

//�Ӷ���λ��v����, ��������ȵĴ���������пɶ������δ���ʹ��Ķ��㡣
//�㷨���õ�һ����������visited, ���ѷ��ʹ��Ķ��������ʱ�ǡ�
template<typename T, typename E>void Graph<T,E>::DFS(int v, bool visited[]){
	cout << getValue(v) << ' ';			//���ʶ���v
	visited[v] = true;	 				//����v�����ʱ��
	int w = getFirstNeighbor(v); 		//�Ҷ���v�ĵ�һ���ڽӶ���w
	while (w != -1){					//���ڽӶ���w���ڡ�#ע����Ϊ�ڽӶ�����Ŀ������ʹ��ѭ����䣬������ͬ�����������ͬ	
		if (visited[w] == false){		//��wδ���ʹ�, �ݹ���ʶ���w		
			DFS(w, visited);
		}
		w = getNextNeighbor(v, w);		//ȡv����w�����һ���ڽӶ���
	}
}

//������ȱ���ͼ��������е���ͨ����
template <typename T, typename E>void Graph<T,E>::BFS(){
	int i,v, w, n = NumberOfVertices();		//ͼ�ж������
	bool *visited = new bool[n];	
	for (i = 0; i < n; i++){
		visited[i] = false;
	}
	SeqQueue<int> Q;
	for (i = 0; i < n; i++){	//#��ÿ�����㿪ʼ������һ�α�����
		if (visited[i] == true){//#�����������飬��һ�˱����ѷ��ʹ��ĸ����㲻����Ϊ����㡣���������������ͨ�����������ظ���
			continue;
		}
		cout << getValue(i) << ' ';				//���ʶ���v
		visited[i] = true;						//���ѷ��ʱ��
		Q.EnQueue(i);							//���������, ʵ�ֲַ����
		while (!Q.IsEmpty()){					//ѭ��, �������н��		
			Q.DeQueue(v/*i*/);					//��������ı���Ʊ���i
			w = getFirstNeighbor(v/*i*/);			//��һ���ڽӶ���
			while (w != -1){						//���ڽӶ���w����			
				if (!visited[w]){				//��δ���ʹ�				
					cout << getValue(w) << ' ';	//����
					visited[w] = true; 		
					Q.EnQueue(w);				//����w������
				}
				w = getNextNeighbor(v/*i*/, w);		//�Ҷ���i����һ���ڽӶ���
			}
		}//���ѭ�����ж��пշ�
		cout << endl;
	}
    delete [] visited;
}

//��������������������ͨͼ����ͨ�������㷨
template<typename T, typename E> void Graph<T,E>::Components(){
	int i, n = NumberOfVertices();		//ȡͼ�ж������
	bool *visited = new bool[n]; 		//������������
	for (i = 0; i < n; i++){				//��������visited��ʼ��	
		visited[i] = false;
	}
	int j=1;
	for(i=0;i<n;i++){
		if(!visited[i]){
			cout << "Component " << j << ":" << endl;
			DFS(i, visited); 			//�Ӷ���0��ʼ�����������
			j++;
			cout << endl;
		}
	}
	delete [] visited;					//�ͷ�visited
}

//��ͼ�ĵ�һ�����������������ȱ���ͼ��
//����������Ů-���ֵ������ʾ��DFS����ɭ�֡�
template<typename T, typename E> void Graph<T,E>::DFSTree(Tree<T> &tree){
	TreeNode<T> *p, *q;
	int v, n = NumberOfVertices();		//ȡͼ�ж������
	bool *visited = new bool[n]; 		//������������
	for (v = 0; v < n; v++){			//��������visited��ʼ��	
		visited[v] = false;
	}
	for(v = 0; v < n; v++){				//#��ÿ�����㿪ʼ������һ�α�����
		if(!visited[v]){				//#�����������飬��һ�˱����ѷ��ʹ��ĸ����㲻����Ϊ����㡣���������������ͨ�����������ظ���
			p = new TreeNode<T>(getValue(v));
			if (!tree.getRoot()){
				tree.setRoot(p);
			}
			else{
				q->nextSibling = p;
			}
			q = p;
			DFSTree(v, visited, p); 	//�Ӷ���0��ʼ�����������
		}
	}
	delete [] visited;					//�ͷ�visited
}

//��ͼ�Ķ���v��������������ȴ������ͼ��������subTreeΪ������������
//�����subTree�����ϲ��㷨�д�����
//�㷨���õ�һ����������visited, ���ѷ��ʹ��Ķ��������ʱ�ǡ�
template<typename T, typename E>void Graph<T,E>::DFSTree(int v, bool visited[], TreeNode<T> *& subTree){
	bool first = true;
	visited[v] = true;	 				//����v�����ʱ��
	TreeNode<T> *p, *q;
	int w = getFirstNeighbor(v); 		//�Ҷ���v�ĵ�һ���ڽӶ���w
	while (w != -1){						//���ڽӶ���w����	
		if (visited[w] == false){		//��wδ���ʹ�, �ݹ���ʶ���w		
			p = new TreeNode<T>(getValue(w));
			if (first){
				subTree->firstChild = p;//��һ���ڽӶ�����Ϊ����Ů
				first = false;
			}
			else{
				q->nextSibling = p;//�����ڽӶ�����Ϊ���ֵ�
			}
			q = p;
			DFSTree(w, visited, q);
		}
		w = getNextNeighbor(v, w);		//ȡv����w�����һ���ڽӶ���
	}
}

// ����С������
template <typename T, typename E>void Graph<T,E>::Kruskal(MinSpanTree<T,E> &MST){
	MSTEdgeNode<T,E> ed;				//�߽�㸨����Ԫ
	int u, v, count;
	int n = NumberOfVertices();			//������
	int m = NumberOfEdges();			//����
	MinHeap<E,MSTEdgeNode<T,E> > H(m);	//��С��,�ؼ�������ΪE
	UFSets F(n);						//���鼯
	for (u = 0; u < n; u++){
		for (v = u+1; v < n; v++){
			if (getWeight(u,v) != 0){//#��Ӧ�ߴ���
				ed.tail = u;
				ed.head = v;
				ed.key = getWeight(u, v);
				H.Insert(ed);			//�����
			}
		}
	}
	count = 1;							//��С�����������������
	while (count < n){					//����ִ��, ȡn-1����	
		H.RemoveMin(ed);				//����С�����˳�����СȨֵ�ı�ed
		u = F.Find(ed.tail);
		v = F.Find(ed.head);			//ȡ���������ڼ��ϵĸ�u��v
		if (u != v){						//����ͬһ����, ˵������ͨ		
			F.SimpleUnion(u, v);		//�ϲ�, ��ͨ����
			MST.Insert(ed);				//�ñߴ�����С������
			count++;
		}
	} 
}

template <typename T, typename E>void Graph<T,E>::Prim(MinSpanTree<T, E> &MST){
	MSTEdgeNode<T, E> ed; //�߽�㸨����Ԫ
	int i, u, v, count;				
	int n = NumberOfVertices();	  //������	
	int m = NumberOfEdges();	  //����
//	int u = getVertexPos(u0);		  //��ʼ�����
	u = 0;
	MinHeap <E,MSTEdgeNode<T, E> > H(m);  //��С��
	bool *Vmst = new bool[n];   //��С���������㼯��
	for (i = 0; i < n; i++) Vmst[i] = false;	
	Vmst[u] = true;		        //u ����������
	count = 1;
	do{			        //����	
		v = getFirstNeighbor(u); 
		while (v != -1){	 //���u�����ڽӶ���		
			if (!Vmst[v]){	        //v����mst��			
				ed.tail = u;  ed.head = v;
				ed.key = getWeight(u, v);
				H.Insert(ed);	        //(u,v)�����
			}     //���д�����u��mst��, v����mst�еı�
			v = getNextNeighbor(u, v); 
		} 
		while (!H.IsEmpty() && count < n)		{ 
			H.RemoveMin(ed);	         //ѡ���о���СȨ�ı�
			if (!Vmst[ed.head])			{
				MST.Insert(ed);       //������С������
				u = ed.head;
				Vmst[u] = true;//u�������������㼯��
				count++;  
				break;
			}
		}
	} while (count < n);
}


//////////////////////////////////////////////////////////////////

//Dijkstra
//Graph��һ����Ȩ����ͼ��
//dist[j], 0��j<n, �ǵ�ǰ�󵽵ĴӶ���v������j�����·������,
//path[j], 0��j<n, ����󵽵����·����
template <typename T, typename E>void ShortestPath(Graph<T,E> &G, T v, E dist[], int path[]){
    int n = G.NumberOfVertices();
    bool *S = new bool[n]; 	   //���·�����㼯
    int i, j, k;  E w, min;
    for (i = 0; i < n; i++)	{
	    dist[i] = G.getWeight(v, i);
        S[i] = false;
        if (i != v && dist[i] < maxValue) path[i] = v;
        else path[i] = -1;
    }
    S[v] = true;  dist[v] = 0;     	//����v���붥�㼯��
    for (i = 0; i < n-1; i++){       //�����������·��	
        min = maxValue;
		int u = v; 					//ѡ����S�о������·���Ķ���u
        for (j = 0; j < n; j++){			
            if (!S[j] && dist[j] < min){
				u = j;
				min = dist[j];
			}
		}
        S[u] = true;	               	//������u���뼯��S
        for (k = 0; k < n; k++){       	//�޸�		
            w = G.GetWeight(u, k);
            if (!S[k] && w < maxValue && dist[u]+w < dist[k]){ //����kδ����S   			            
                dist[k] = dist[u]+w; 
                path[k] = u;     		//�޸ĵ�k�����·��
            }    
        }
    }
}

//�������Ȩͼ���еı߾��и���Ȩֵ��
//�Ӷ���v�ҵ�����������������·���� 
template <typename T, typename E>void Bellman_Ford(Graph<T, E>& G, int v, E dist[], int path[]){
    E w;  int i, k, u, n = G.NumberOfVertices();
    for (i = 0; i < n; i++){        //����dist1[i]	
        dist[i] = G.getWeight(v, i);
        if (i != v && dist[i] < maxValue){
			path[i] = v;
		}
        else{
			path[i] = -1;
		}
    }
    for (k = 2; k < n; k++){     //����dist2[i]��distn-1[i]	
        for (u = 0; u < n; u++){
            if (u != v){
                for (i = 0; i < n; i++){
                    w = G.getWeight(i, u);
					if (w > 0 && w < maxValue && dist[u] > dist[i]+w){
                        dist[u] = dist[i]+w;
                        path[u] = i;
                    }
                }
			}
		}
	}
}

//a[i][j]�Ƕ���i��j֮������·�����ȡ�
//path[i][j]����Ӧ·���϶���j��ǰһ����Ķ���š�
template <typename T, typename E>void Floyd(Graph<T,E> &G, E **a, int **path){
	int i, j, k, n = G.NumberOfVertices();
    for (i = 0; i < n; i++){    	//����a��path��ʼ��	
        for (j = 0; j < n; j++){
            a[i][j] = G.getWeight (i,j);
			if (i != j && a[i][j] < maxValue){
				path[i][j] = i;
			}
			else{
				path[i][j] = 0;
			}
        }
	}
    for (k = 0; k < n; k++){   //���ÿһ��k, ����a(k)��path(k)			
        for (i = 0; i < n; i++){
            for (j = 0; j < n; j++){
				if (a[i][k] + a[k][j] < a[i][j]){
                    a[i][j] = a[i][k] + a[k][j];
                    path[i][j] = path[k][j]; 
                    //����·������, �ƹ� k �� j
                }
			}
		}
	}
}

// ͨ��path���������·���ĺ���
#endif
