#ifndef WINNER_TREE
#define WINNER_TREE
#include <iostream>
using namespace std;
const int maxValue = 10000;

template <typename T>class WinnerTree{
private:
	int maxSize;	//允许的最大选手数
	int n;			//当前大小(外部结点数)
	int lowExt;		//最远层外部结点数
	int offset;		//偏移(加1即为第1个外结点)
	int *t;			//胜者树数组
	T *e;			//选手数组
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
    T Winner()const{//取最终胜者	
		return (n != 0) ? e[t[1]] : 0;
	}
	int Winner(int i)const{//取第i个胜者	
		return (i < n) ? t[i] : 0;
	}
	int Winner(int a, int b){//取两外结点胜者a,b的胜者	
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
    for (s = 1; 2*s <= n-1; s += s);  //计算s=2^log2(n-1)
    lowExt = 2*(n-s);
	offset = 2*s-1;
    for (i = 2; i <= lowExt; i += 2){	//最远层外结点比赛	
		Play((offset+i)/2, i-1, i);		//选手i-1和i比赛, 胜者升入双亲(offset+i)/2
	}
	// 处理其他结点
    if (n%2 == 0){
		i = lowExt+2;
	}
    else{ //当n为奇数时,内结点要与外结点比赛	
        Play(n/2, t[n-1], lowExt+1);
		i = lowExt+3;
    }
	// i为最左剩余结点，处理其他外部结点比赛
    for ( ; i <= n; i += 2){
        Play((i-lowExt+n-1)/2, i-1, i);
	}

    return true;
}

//通过比赛对树初始化。在t[k]处开始比赛, lc和rc是
//t[k]的左子女和右子女。
template <typename T>void WinnerTree<T>::Play(int k, int lc, int rc){
    t[k] = Winner (lc, rc);	//在e[lc]和e[rc]间选出胜者
    while (k > 1 && k%2 != 0){	//从右子女向上比赛, 直到根	
        t[k/2] = Winner(t[k-1], t[k]);
        k /= 2;			//到父结点
    }
}

//针对元素i值的改变,重新组织胜者树。
template <typename T>bool WinnerTree<T>::rePlay(int i){
	if (i <= 0 || i > n){
		return false;
	}
    int k, lc, rc;			//比赛结点及其左右子女
    if (i <= lowExt){		//最远层外结点的情况	
        k = (offset+i)/2;	//计算i的双亲
        lc = 2*k-offset;	//计算左子女
		rc = lc+1;			//计算右子女
    }
    else{					//次远层外结点的情况	
        k = (i-lowExt+n-1)/2;
        if (2*k == n-1){
			lc = t[2*k];
			rc = i; 
		}
        else{
			lc = 2*k-n+1+lowExt;
			rc = lc+1;
		}
    }               ?w     h     for ( ; k >= 1; k /= 2){		//逐层向上比赛直到根	
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
