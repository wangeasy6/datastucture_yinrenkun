//ԭ�ṩ����������ģ�������E����data��K����data.key������E�������ޣ�������һ��key���ݳ�Ա��
//ʵ��ֻ��E������E�ıȽ�����Ϊ��ؼ��ֵıȽϣ�����Ҫ���һ���Թؼ��ֽ������ء�Ϊ��̲�һ�£�δ�޸�
#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H
#include <cassert>
#include <iostream>
#include <string>
using namespace std;

class element{
public:
	string key;
	element(string st=""){
		key=st;
	}
	bool operator<(element el){//����
		return key<el.key;
	}
	bool operator>(element el){//����
		return key>el.key;
	}
	friend ostream& operator << (ostream &out, element &el){
	out << el.key;
	return out;
	}
};
template <typename E, typename K>struct BSTNode{
	E data;
	BSTNode<E,K> *left, *right;
	BSTNode(){
		left = NULL;
		right = NULL;
	}
	BSTNode(E &d, BSTNode<E,K> *L = NULL, BSTNode<E,K> *R = NULL){
		data = d;
		left = L;
		right = R;
	}
	~BSTNode(){}
	void setData(const E &d){
		data = d;
	}
	E getData(){
		return data;
	}
	bool operator < (const E &x){
		return data < x;
	}  
	bool operator > (const E &x){
		return data > x;
	}
	bool operator == (const E &x){
		return data == x;
	}
	bool operator <= (const E &x){
		return data <= x;
	}  
	bool operator >= (const E &x){
		return data >= x;
	}
	bool operator != (const E &x){
		return data != x;
	}
};

//�����������ඨ��
template <typename E, typename K>class BST{
public:
	BST(){
		root = NULL;
	}
	BST(K value);
//	BST(BSTNode<E,K> * temp):root(temp){}	//����һ��ǳ����
	BST(BST & bst){
		if (this != & bst){					//�����Ҹ���
			root=Copy(bst.root);	//������
		}
	}
	~BST(){
		makeEmpty();
	}
	BSTNode<E,K>* getRoot(){
		return root;
	}
	BSTNode<E,K> *getLeft(){
		return left;
	}
	BSTNode<E,K> *getRight(){
		return right;
	}
	void OpticBST(int p[], int q[], E a[], int n);
	BSTNode<E,K>* Search(const K x){
		return Search(x,root);
	}
	void CreatOpt(BSTNode<E, K> *&prt,int** &R,E a[],int i,int j);	//�������������ã���������������
	BST<E,K>& operator = (/*const*/ BST<E,K> &R);
	void makeEmpty(){
		makeEmpty (root); root = NULL;
	}
	bool isEmpty(){
		return root == NULL;
	}
	void PrintTree(ostream &out = cout)const {   //�������ʽ���	
		PrintTree(root, out);
	}
	void PrintData(ostream &out = cout)const{    //�������
		PrintData(root, out);
	}
	bool DelMax();
	bool DelMin();
	E Min(){
		return Min(root)->data;
	}
	E Max(){
		return Max(root)->data;
	}
	bool Insert(E &e1){
		return Insert(e1, root);
	}
	bool Remove(K x){
		return Remove(x, root);
	}
	friend istream& operator >> (istream &in, BST<E,K> &R){
		while (!in.eof()){
			E elem;
			assert(in >> elem);
			R.Insert(elem);
		}
		return in;
	}
	friend ostream& operator << (ostream &out, BST<E,K> &R){
		out << "The structure of the Binary Search tree is: \n";
		R.PrintTree(out);
		out << "\n\nThe data printed by inorder in the tree is: \n";
		R.PrintData(out);
		out << endl;
		return out;
	}
protected:
	BSTNode<E, K> *root;
	K RefValue;		//����ֹͣ��־
	BSTNode<E, K>* Search(K x, BSTNode<E,K> *ptr);	//�ݹ飺����
	void makeEmpty(BSTNode<E,K> *&ptr);				//�ݹ飺�ÿ�
	void PrintTree(BSTNode<E,K> *ptr, ostream &out)const;	//�ݹ飺��ӡ�������ṹ
	void PrintData(BSTNode<E,K> *ptr, ostream &out)const;	//�ݹ飺��ӡ���������
	BSTNode<E,K>* Copy(/*const*/ BSTNode<E,K> *& ptr);	//�ݹ飺����
	BSTNode<E,K>* Min(BSTNode<E,K> *ptr);			//�ݹ飺����С
	BSTNode<E,K>* Max(BSTNode<E,K> *ptr);			//�ݹ飺�����
	bool Insert(E &e1, BSTNode<E,K> *&ptr);	//�ݹ飺����
	bool Remove(K x, BSTNode<E,K> *&ptr);			//�ݹ飺ɾ��
};

//˽�к������ڵ�ǰ��ptrΪ���Ķ�����������������x�Ľ�㡣
//���ҵ����������ظý��ĵ�ַ������������NULLֵ��
template <typename E, typename K>BSTNode<E,K>* BST<E,K>::Search(K x, BSTNode<E,K> *ptr){
	if (ptr == NULL){
		return NULL; 
	}
	BSTNode<E,K> *temp = ptr;
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
}

//˽�к���������ptrΪ���Ķ����������в���ֵΪe1�Ľ�㡣
//�����������к�e1�Ľ���򲻲��룬����false�����ɹ����룬����true.
template <typename E, typename K>bool BST<E,K>::Insert(E &e1, BSTNode<E,K> *&ptr){	  
	if (ptr == NULL){   //�½����ΪҶ������	
		ptr = new BSTNode<E,K>(e1);
		assert(ptr);
		return true;
	}
	if (e1 < ptr->data){			//����������
	
		return Insert(e1, ptr->left);
	}
	if (e1 > ptr->data){	//����������
		return Insert(e1, ptr->right);
	}
	return false;			//x��������,���ٲ���
}

//����һ��Ԫ������, ����һ�ö���������
template <typename E, typename K>BST<E,K>::BST(K value){
	E x;
	root = NULL;		//�ÿ���
	RefValue = value;
	cout << "Please input the value of each node,end input with "<<value<<" : "<<endl;
	cin >> x;				//��������
	while ( x != RefValue){	//RefValue��һ�����������־	
		Insert(x, root);
		cin >> x;			//���룬����������
	}
}

template<typename E, typename K>BSTNode<E,K>* BST<E,K>::Copy(/*const*/ BSTNode<E,K> *& ptr){//������ptrΪ��������
	if (!ptr){			//����
		return NULL;
	}
	/*if (!root){//��
		delete[] root;
	}*/
	BSTNode<E,K>* p/*root*/ = new BSTNode<E,K>(ptr->data);
	p->left=Copy(ptr->left);//��
	p->right=Copy(ptr->right);//��
	return /*this->root*/ p;
}

template<typename E, typename K>void BST<E,K>::makeEmpty(BSTNode<E, K> *& ptr){
	if (!ptr){
		return;
	}
	makeEmpty(ptr->left);
	makeEmpty(ptr->right);
	delete ptr;
}

template<typename E, typename K>bool BST<E,K>::DelMax(){
	if (!root){
		return false;
	}
	BSTNode<E,K> *pre = root, *cur = pre->right;
	if (!root->right){//ֻ������������������ɾ��ԭ�����
		root = pre->left;
		delete pre;
		return true;
	}
	while (cur->right){//�������ұ����
		pre = cur;
		cur = cur->right;
	}
	pre->right = cur->left;
	delete cur;
	return true;
}

template<typename E, typename K>bool BST<E,K>::DelMin(){
	if (!root){
		return false;
	}
	BSTNode<E,K> *pre = root, *cur = pre->left;
	if (!root->left){//ֻ�����������������С��ɾ��ԭ�����
		root = pre->right;
		delete pre;
		return true;
	}
	while (cur->left){//�����������С
		pre = cur;
		cur = cur->left;
	}
	pre->left = cur->right;
	delete cur;
	return true;
}

template<typename E, typename K>BSTNode<E,K>* BST<E,K>::Min(BSTNode<E,K> *ptr){
	if (!ptr){
		return NULL;
	}
	BSTNode<E,K> *temp = ptr;
	while (temp->left){
		temp=temp->left;
	}
	return temp;
}

template<typename E, typename K>BSTNode<E,K>* BST<E,K>::Max(BSTNode<E,K> *ptr){
	if (!ptr){
		return NULL;
	}
	BSTNode<E,K> *temp=ptr;
	while (temp->right){
		temp=temp->right;
	}
	return temp;
}

template<typename E, typename K>BST<E,K>& BST<E,K>::operator = (/*const*/ BST<E, K> &R){
	if (this != & R){					//�����Ҹ���
		root=/*return BST<E,K>(*/Copy(R.root)/*)*/;	//������
	}
	return *this;
}


//���� ptr Ϊ���Ķ�����������ɾ���� x �Ľ��
template <typename E, typename K>bool BST<E,K>::Remove(K x, BSTNode<E,K> *& ptr){
	if (!ptr){
		return false;
	}

	BSTNode<E,K> *temp;
	if (x < ptr->data.key){ //����������ִ��ɾ��
		return Remove(x, ptr->left);
	}
	else if (x > ptr->data.key){//����������ִ��ɾ��
			return Remove(x, ptr->right);
		}
		else if (ptr->left != NULL && ptr->right != NULL){//ptrָʾ�ؼ���Ϊx�Ľ�㣬����������Ů
				temp = ptr->right;		//����������Ѱ�����µ�һ�����
				while (temp->left != NULL){
					temp = temp->left;
				}
		ptr->data = temp->data;	//�øý�����ݴ����������ݣ�������������ֵΪȡ��x�Ľ�㣨temp���͸���㣩
		return Remove(temp->data.key, ptr->right);//ɾ��temp���
	}
	else{//ptrָʾ�ؼ���Ϊx�Ľ����һ����Ů
		temp = ptr;
		if (ptr->left == NULL){
			ptr = ptr->right;
		}
		else{
			ptr = ptr->left;
		}
		delete temp;
		return true;
	}
}

template<typename E, typename K>void BST<E,K>::PrintTree(BSTNode<E,K> *ptr, ostream &out)const{
	if (!ptr){
		return;
	}
	out << ptr->data/*.key*/;
	if (ptr->left == NULL && ptr->right == NULL){
		return;
	}
	out << "(";
	PrintTree(ptr->left, out);
	out << ',';
	PrintTree(ptr->right, out);
	out << ")";
}

template<typename E, typename K>void BST<E,K>::PrintData(BSTNode<E,K> *ptr, ostream &out)const{
	if (ptr){
		PrintData(ptr->left, out);
		out << ptr->data << endl;
		PrintData(ptr->right, out);
	}
}

template <typename E, typename K>void BST<E,K>::OpticBST(int p[], int q[], E a[], int n){//#�޸�
	//����n����ͬ������a[1]<a[2]<...<a[n],�Լ����ǵ�Ȩֵp[j],1<=j<=n,������������֮���ⲿ����Ȩֵ�ֱ�Ϊq[i],
	//0<=i<=n�����㷨����a[i+1],...,a[j]�����Ŷ���������T[i][j]�Ĵ���C[i][j],T[i][j]�ĸ�R[i][j]��ȨW[i][j]
	int **R,**C,**W;
	int i, j, k, m, min, u;
	R=new int*[n+1];
	for(i=0;i<=n;i++) R[i]=new int[n+1];
	C=new int*[n+1];
	for(i=0;i<=n;i++) C[i]=new int[n+1];
	W=new int*[n+1];
	for(i=0;i<=n;i++) W[i]=new int[n+1];

	cout<<"\n�������ؼ��뼯�ϣ�"<<endl;
	for(i=0;i<=n;i++) cout<<a[i]<<'\t';
	cout<<"\n����ڲ����Ȩֵ��"<<endl;
	for(i=0;i<=n;i++) cout<<p[i]<<'\t';
	cout<<"\n����ⲿ���Ȩֵ��"<<endl;
	for(i=0;i<=n;i++) cout<<q[i]<<'\t';

	for(i=0;i<=n;i++)
		for(j=0;j<=n;j++){						//����������
			W[j][i]=0;
			C[j][i]=0;
			R[j][i]=0;
		}

	for (i = 0; i < n; i++){
		W[i][i] = q[i];
		C[i][i] = R[i][i] = 0;					//��ʼ��
		W[i][i+1] = W[i][i] + p[i+1] + q[i+1];	//����ֻ��һ���ڲ���㣬�����ⲿ�������Ŷ���������
		R[i][i+1] = i + 1;						//��Щ���ĸ���i+1
		C[i][i+1] = W[i][i+1];					//��Щ�����ܴ�Ȩ·�����ȣ����ۣ�
	}
	W[n][n] = q[n];
	R[n][n] = C[n][n] = 0;
	for (m = 2; m <= n; m++){					//�������m���ڲ��������Ŷ���������
		for (i = 0; i <= n - m; i++){
			j = i + m;							//��ǰһ���������ϼ�һ�ڲ�����һ�ⲿ���
			W[i][j] = W[i][j-1] + p[j] + q[j];

			min = C[i+1][j];
			u = i + 1;							//�ٶ�i+1Ϊ�����������
			for (k = i + 2; k <= j; k++){
				if (C[i][k-1] + C[k][j] < min){
					min = C[i][k-1] + C[k][j];
					u = k;						//������i+2,...,jΪ����ѡ������С����min�����Ϊu
				}
			}
			C[i][j] = W[i][j] + min;
			R[i][j] = u;
		}
	}
	cout<<"\n����ۼ�Ȩֵ�����飺"<<endl;
	for(i=0;i<=n;i++){
		for(j=0;j<=n;j++) cout<<W[i][j]<<'\t';
		cout<<endl;
	}
	cout<<"\n������������飺"<<endl;
	for(i=0;i<=n;i++){
		for(j=0;j<=n;j++) cout<<C[i][j]<<'\t';
		cout<<endl;
	}
	cout<<"\n����������飺"<<endl;
	for(i=0;i<=n;i++){
		for(j=0;j<=n;j++) cout<<R[i][j]<<'\t';
		cout<<endl;
	}

	CreatOpt(root,R,a,0,n);

	for(i=0;i<=n;i++){
		delete[] R[i];
		delete[] C[i];
		delete[] W[i];
	}
	delete []R;
	delete []C;
	delete []W;
}
	
template <typename E, typename K>void BST<E,K>::CreatOpt(BSTNode<E, K> *&prt,int** &R,E a[],int i,int j){	//#���ӡ��������������ã���������������
	int k=R[i][j];
	Insert(a[k],prt);
	if(i!=(k-1)) CreatOpt(prt,R,a,i,k-1);	//ȡR�ĶԽ���Ԫ����ֹͣ
	if(k!=j) CreatOpt(prt,R,a,k,j);			//ȡR�ĶԽ���Ԫ����ֹͣ
}
#endif
