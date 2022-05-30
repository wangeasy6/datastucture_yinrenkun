#ifndef WINNER_TREE
#define WINNER_TREE
#include <iostream>
using namespace std;
const int maxValue = 10000;

template <typename T>class WinnerTree{
private:
	int maxSize;	//��������ѡ����
	int n;			//��ǰ��С(�ⲿ�����)
	int lowExt;		//��Զ���ⲿ�����
	int offset;		//ƫ��(��1��Ϊ��1������)
	int *t;			//ʤ��������
	T *e;			//ѡ������
	void Play(int k, int lc, int rc);
public:
    WinnerTree(int TreeSize = 20){
		maxSize = TreeSize;
		n = 0;
		t = new int[TreeSize];
		for(int i = 0; i < TreeSize; ++i){
			t[i] = maxValue;
		}
	}		
    ~WinnerTree(){
		delete []t;
	}

    bool Initial(T a[], int size);
    bool rePlay (int i);
    void Update(){
		e[t[1]] = maxValue;
	}
    T Winner()const{//ȡ����ʤ��	
		return (n != 0) ? e[t[1]] : 0;
	}
	int Winner(int i)const{//ȡ��i��ʤ��	
		return (i < n) ? t[i] : 0;
	}
	int Winner(int a, int b){//ȡ������ʤ��a,b��ʤ��	
		return (e[a] <= e[b]) ? a : b;
	}
};
template <typename T>bool WinnerTree<T>::Initial(T a[], int size){
    if (size > maxSize || size < 2){
		return false;
	}
	n = size;
	e = a;

    int i, s;
    for (s = 1; 2*s <= n-1; s += s);  //����s=2^log2(n-1)
    lowExt = 2*(n-s);
	offset = 2*s-1;
    for (i = 2; i <= lowExt; i += 2){	//��Զ���������	
		Play((offset+i)/2, i-1, i);		//ѡ��i-1��i����, ʤ������˫��(offset+i)/2
	}
	// �����������
    if (n%2 == 0){
		i = lowExt+2;
	}
    else{ //��nΪ����ʱ,�ڽ��Ҫ���������	
        Play(n/2, t[n-1], lowExt+1);
		i = lowExt+3;
    }
	// iΪ����ʣ���㣬���������ⲿ������
    for ( ; i <= n; i += 2){
        Play((i-lowExt+n-1)/2, i-1, i);
	}

    return true;
}

//ͨ������������ʼ������t[k]����ʼ����, lc��rc��
//t[k]������Ů������Ů��
template <typename T>void WinnerTree<T>::Play(int k, int lc, int rc){
    t[k] = Winner (lc, rc);	//��e[lc]��e[rc]��ѡ��ʤ��
    while (k > 1 && k%2 != 0){	//������Ů���ϱ���, ֱ����	
        t[k/2] = Winner(t[k-1], t[k]);
        k /= 2;			//�������
    }
}

//���Ԫ��iֵ�ĸı�,������֯ʤ������
template <typename T>bool WinnerTree<T>::rePlay(int i){
	if (i <= 0 || i > n){
		return false;
	}
    int k, lc, rc;			//������㼰��������Ů
    if (i <= lowExt){		//��Զ����������	
        k = (offset+i)/2;	//����i��˫��
        lc = 2*k-offset;	//��������Ů
		rc = lc+1;			//��������Ů
    }
    else{					//��Զ����������	
        k = (i-lowExt+n-1)/2;
        if (2*k == n-1){
			lc = t[2*k];
			rc = i; 
		}
        else{
			lc = 2*k-n+1+lowExt;
			rc = lc+1;
		}
    }               ?w     h     for ( ; k >= 1; k /= 2){		//������ϱ���ֱ����	
		if(2 * k + 1 >= n)		{
			t[k] = Winner(t[2*k], lowExt+1);
		}
		else{
			t[k] = Winner(t[2*k], t[2*k+1]);
		}
	}
	return true;
}

#endif
