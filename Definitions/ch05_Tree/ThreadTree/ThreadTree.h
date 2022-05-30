#ifndef THREADTREE
#define THREADTREE

// �����������Ľ����
template <typename T>struct ThreadNode{
	int ltag, rtag;	//������־
	ThreadNode<T> *leftChild, *rightChild; //��������Ůָ��
	T data;			//�������
	ThreadNode(const T item){
		data = item;
		leftChild = NULL;
		rightChild = NULL;
		ltag = 0;
		rtag = 0;
	}
};

// ������������
template <typename T>class ThreadTree{
protected:
	ThreadNode<T> *root;
	void createInThread(ThreadNode<T> *current, ThreadNode<T> *& pre);
	ThreadNode<T> *parent(ThreadNode<T> *t);
public:
	ThreadTree(){
		root = NULL;
	}
	~ThreadTree(){
		destroy(root);
	}
	void InitThreadTree();
	void createInThread(); //������������������
	bool FindTh (const T &value);	//����������������value,�ɹ���true,����currentΪ�˽��;����false
	ThreadNode<T> *First(ThreadNode<T> *current);	//Ѱ�������µ�һ�����
	ThreadNode<T> *Last(ThreadNode<T> *current);	//Ѱ�����������һ�����
	ThreadNode<T> *Next(ThreadNode<T> *current);	//Ѱ�ҽ���������µĺ�̽��
	ThreadNode<T> *Prior(ThreadNode<T> *current);	//Ѱ�ҽ���������µ�ǰ�����
	void InOrder(void (*visit)(ThreadNode<T> *t));	//���������������������
	void PreOrder(void (*visit)(ThreadNode<T> *t));	//��������������ǰ�����
	void PostOrder(void (*visit)(ThreadNode<T> *t));	//�������������ĺ������	
	bool Find (const T &value);	//�ڳ������������value,�ɹ���true,����currentΪ�˽��;����false
	ThreadNode<T>* /*&*/ getCurrent(){//����current,����Ǹ���
		return current;
	}
	void destroy(ThreadNode<T> *& subTree);
private:
	ThreadNode<T> *current;
	bool Find(ThreadNode<T> *p, const T &value);			//����pΪ���ĳ��������������value
	bool setRoot(const T &rt){                              //���ø�ֵΪrt
		root = new ThreadNode<T>(rt);
		if(root) return true;
		else return false;
	}
	static ThreadNode<T>* &leftChild (ThreadNode<T> *t){//��������Ů
		return t->leftChild;
	}
	static ThreadNode<T>* &rightChild (ThreadNode<T> *t){
		return t->rightChild;                //��������Ů
	}
	bool MakeLink(const T ex, const T ap, char linkmark); 
	void Print(ThreadNode<T>* /*&*/p, int i);//p������Ϊ���ã�����ʵ��ָ��root���ƶ������ܱ����л��ƻ���
};
//-----------------------------------------------------------------------------------------------------------------
template <typename T>void ThreadTree<T>::destroy(ThreadNode<T> *& subTree){//����Ӷ�����
	if (subTree != NULL){
		destroy (subTree->leftChild);
		destroy (subTree->rightChild);
		delete subTree;
	}
}

template<typename T>bool ThreadTree<T>::Find(const T &value){//�������������������ʹ��
	if(!root){
		return 0;
	}
	else{
		return Find(root, value);
	}
}

template<typename T>bool ThreadTree<T>::Find(ThreadNode<T> *p, const T &value){//����pΪ������������value
	if (!p)	{
		return false;
	}
	if(p->data == value){
		current = p;                 //�ҵ���currentָ��ý��
		return true;
	}
	else{
		return Find(p->leftChild,value) || Find(p->rightChild, value);//����ҵ��󲻻���ȥ�ұ�
	}
}


template<typename T>bool ThreadTree<T>::MakeLink(const T ex, const T ap, char linkmark){//������ap����Ϊ������Ϊex������Ů
	if(linkmark != eptmark) {//������־		
		ThreadNode<T> *p = new ThreadNode<T>(ap);//��apת��Ϊ���
		if(Find(ex))                             //��ex,��Ϊcurrent
		cout << "cu " << current -> data << endl;
		if(current) {
			switch(linkmark) {
                case 'l': current -> leftChild = p; 
					cout << "input success!" << endl;break;//��������Ů��ϵ
                case 'r': current -> rightChild = p; 
					cout << "input success!" << endl;break;//��������Ů��ϵ
				default: cout << "error! please reinput again!" << endl;
			}
			return false;//���ؼ٣�����
		}
		else {
			cout << "error! please reinput again!" << endl;
			return false;
		}
	}
	else return true;//�����棬����
}

template<typename T>void ThreadTree<T>::InitThreadTree(){
	cout << "please input the root node" << endl;//��������
	char elem1, elem2, elem3;
	cin >> elem1;
	while(1){
		if(setRoot(elem1)) {
			cout << "input success!" << endl;
			break;
		}
		else cout << "error! please reinput again!"  << endl;
	}
	cout << "please enter link between nodes, one existed and one to be inserted" << endl;
    cout << "e.g (Parent) (leftChild) l or (Parent) (rightChild) r" << endl;
	//�������������н�㣬Ҫ��elem1Ϊ�Ѽ���Ľ��
	//elem2Ϊ�½���㣬�Ҷ�����Ů��ϵ
	while(1){
        cin >> elem1 >> elem2 >> elem3;//����ʽ����
		if(MakeLink(elem1, elem2, elem3)) break;//��������
	}
	cout << "treeview" << endl;
	Print(root,0);
	return;
}

template<typename T>
void ThreadTree<T>::Print(ThreadNode<T>* /*&*/p, int i) {//ǰ�������ӡ
	if(p) {
		for(int j = 0; j < i; ++j) cout << '\t';	//iΪ�Ʊ������
		cout << p->data << endl;//�����ǰ���	    
		if(ThreadTree<T>::leftChild(p) || ThreadTree<T>::rightChild(p)){//���󣬺���һ����Ȼ�������󣬵���Ҷ��ֹ
			++i;//���
			Print(ThreadTree<T>::leftChild(p), i);//�ݹ����������
			Print(ThreadTree<T>::rightChild(p), i);//�ݹ����������
		}
	}
	return;
}

#endif
