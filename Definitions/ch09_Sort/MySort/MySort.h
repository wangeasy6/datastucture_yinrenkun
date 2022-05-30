#ifndef MYSORT_H
#define MYSORT_H
#include "dataList.h"
#include "SeqStack.h"
#include "BST.h"
const int M = 8;
const int radix = 10;

// ð������
template <typename E, typename K> void BubbleSort(dataList<E,K> &L, int left, int right);
// ����������ɨ���ð�������㷨
template <typename E, typename K> void ShakerSort(dataList<E,K> &L, int left, int right);
// ֱ��ѡ��������㷨
template <typename E, typename K> void SelectSort(dataList<E,K>& L, int left, int right);
// ֱ�Ӳ��������㷨
template <typename E, typename K> void InsertSort(dataList<E,K> &L, int left, int right);
// �۰���������㷨
template <typename E, typename K> void BinaryInsertSort(dataList<E,K> &L, int left, int right);
// ϣ������
template <typename E, typename K> void ShellSort(dataList<E,K> &L, int left, int right);
// ���������㷨
template <typename E, typename K> void QuickSort(dataList<E,K> &L, int left, int right);
// �Ľ��Ĺ鲢�����㷨
template <typename E, typename K> void MergeSort(dataList<E,K> &L, int left, int right);
// �������㷨
template <typename E, typename K> void HeapSort(dataList<E,K> &L, int left, int right);
// MST�����㷨�����λ���ȵĻ��������㷨��
// getDigit����������������
template <typename E, typename K> void RadixSort(dataList<E,K> &L, int left, int right,
					int d, int (*getDigit)(E&elem, int d, int Radix));
// BST����
template <typename E, typename K> void BSTSort(dataList<E,K> &L, int left, int right);
// ��������
template <typename E, typename K> void CountSort(dataList<E,K> &L, int left, int right);

// ð������
template <typename E, typename K>void BubbleSort(dataList<E,K> &L, int left, int right){
    int pass = left + 1;
	bool exchange = true;
    while (pass <= right && exchange){
        exchange = false;
        for (int j = right;  j >= pass;  j--){
            if (L[j-1] > L[j]){
                L.Swap(j-1, j);
	            exchange = true;
            }
		}
        pass++;
    }
}

// E917
// �����������ð�������㷨
//�����˶Ա�L��ǰ���, �Ƚ����ڵ�������, �������򼴽���, 
//ֱ���ѲμӱȽ������������������������Ƶ�����β����
//ż���˴Ӻ���ǰ, �Ƚ����ڵ�������, �������򼴽���, 
//ֱ���ѲμӱȽ���������������С���������Ƶ�����ǰ�ˡ�
template <typename E, typename K>void ShakerSort(dataList<E,K> &L, int left, int right){
	int low = left, high = right, i, j;
	while (low < high){					//���ȽϷ�Χ����һ������ʱ���� 	
		j = low;						//����Ԫ�ؽ���λ��
		for (i = low; i < high; i++){	//��������
		
			if (L[i] > L[i+1]){			//��������			
				L.Swap(i, i+1); 		//����
				j = i;					//�����ұ������������λ��j
			}
		}
		high = j;						//�ȽϷ�Χ�Ͻ���С��j
		for (i = high; i > low; i--){	//��������		
			if (L[i-1] > L[i]){			//��������			
				L.Swap(i-1, i);  		//����
				j = i;					//������������������λ��j
			}
		}
		low = j;						//�ȽϷ�Χ�½���С��j
	}
}

// ֱ��ѡ��������㷨
template <typename E, typename K>
void SelectSort(dataList<E,K> &L, int left, int right){
	for (int i = left; i < right; i++)	{
		int k = i;
		for (int j = i+1; j <= right; j++){
			if (L[j] < L[k]) k = j;
		}
		if (k != i){
			L.Swap(i, k);
		}
	}
}

// ֱ�Ӳ��������㷨
template <typename E, typename K>void InsertSort(dataList<E,K> &L, int left, int right){
	E temp;
	int i, j;
	for (i = left + 1; i <= right; i++){
		if (L[i] < L[i-1]){
			temp = L[i];
			j = i - 1;
			do{
				L[j+1] = L[j];
				j--;
			} while (j >= left && temp < L[j]);
			L[j+1] = temp;
		}
	}
}

// �۰���������㷨
template <typename E, typename K>void BinaryInsertSort(dataList<E,K> &L, int left, int right){
	E temp;
	int low, high, mid;
	for (int i = left + 1; i <= right; i++){
		temp = L[i];
		low = left;
		high = i - 1;
		while (low <= high){
			mid = (low + high) / 2;
			if (temp < L[mid]){
				high = mid - 1;
			}
			else{
				low = mid + 1;
			}
		}
		for (int k = i - 1; k >= low; k--){
			L[k+1] = L[k];
		}
		L[low] = temp;
	}
}

// ϣ������
template <typename E, typename K>void ShellSort(dataList<E,K> &L, int left, int right){
	int i, j, gap = right - left + 1;
	E temp;
    do{
        gap = gap/3 + 1;
        for (i = left + gap; i <= right; i++){
            if (L[i] < L[i-gap]){
                temp = L[i];  j = i-gap;
                do{
                    L[j+gap] = L[j];
					j = j-gap;
                } while (j >= left && temp < L[j]);
                L[j+gap] = temp;
            }
		}
    } while (gap > 1);
}

// ���������㷨
template <typename E, typename K>void QuickSort(dataList<E,K> &L, int left, int right){
	if (right - left <= M){
		InsertSort(L, left, right);
	}
	else{
		int pivotpos = L.Partition(left, right);
		QuickSort(L, left, pivotpos-1);
		QuickSort(L, pivotpos+1, right);
	}
}

// �Ľ��Ĺ鲢�����㷨
template <typename E, typename K>void MergeSort(dataList<E,K> &L, int left, int right){
	dataList<E,K> L2;
	improvedMergeSort(L, L2, left, right);
	InsertSort(L, left, right);
}
template <typename E, typename K>void improvedMergeSort(dataList<E,K> &L1, dataList<E,K> &L2, int left, int right){
	if (left >= right || right - left + 1 < M){
		return;
	}
	int mid = (left + right)/2;
	improvedMergeSort(L1, L2, left, mid);
	improvedMergeSort(L1, L2, mid + 1, right);
	improvedMerge(L1, L2, left, mid, right);
}
template <typename E, typename K>void improvedMerge(dataList<E,K> &L1, dataList<E,K> &L2, int left, int mid, int right){
	int s1 = left, s2 = right, t = left, k;
	for (k = left; k <= mid; k++){
		L2[k] = L1[k];
	}
	for (k = mid + 1; k <= right; k++){
		L2[right + mid + 1 - k] = L1[k];
	}
	while (t <= right){
		(L2[s1] <= L2[s2])?L1[t++] = L2[s1++]:L1[t++] = L2[s2--];
	}
}

// �������㷨
template <typename E, typename K>void HeapSort(dataList<E,K> &L, int left, int right){
    int i, n = right - left + 1;
    for (i = (n-2)/2; i >= 0; i--){ 	//����ת��Ϊ��	
        siftDown(L, i, n-1);
	}
    for (i = n-1; i >= 0; i--){		//�Ա�����	
        L.Swap(0, i);
		siftDown(L, 0, i-1);
    }
}

//˽�к���: �ӽ��start��ʼ��m�������±Ƚ�, 
//�����Ů��ֵ����˫�׵�ֵ, ���໥����, ��һ
//�����Ͼֲ�����Ϊ���ѡ�
template <typename E, typename K>void siftDown(dataList<E,K> &L, const int start, const int m){
    int i = start;
	int j = 2*i+1;	 //j��i������Ů
	E temp = L[i];	 //�ݴ����������
    while (j <= m){	 //���Ƚ�	
        if (j < m && L[j] < L[j+1]){	//��jָ������Ů�еĴ���		
			j++;
		}
	    if (temp >= L[j]){	 //temp������󲻵���		
			break;
		}
        else{			    //������Ů�еĴ�������		
            L[i] = L[j];
			i = j;
			j = 2*j+1;  	    //i�½�����Ůλ��
        }
    }
	L[i] = temp;		    //temp�ŵ�����λ��
}

// MSD�����㷨
template <typename E, typename K>void RadixSort(dataList<E,K> &L, int left, int right, int d, int (*getDigit)(E&,int,int)){
	int i, j, count[radix], p1, p2;
	E* auxArray=new E [right - left + 1];//#���붯̬����
	if (d <= 0){
		return;
	}
/*	if (right - left + 1 <= M){					//��С����ʱ����ֱ�Ӳ����������
		InsertSort(L, left, right);
		return;
	}*/
	for (j = 0; j < radix; j++){				//����������0
		count[j] = 0;
	}
	for (i = left; i <= right; i++){			//ͳ�Ƹ�ͰԪ������
		count[getDigit(L[i],d,radix)]++;
	}
	for (j = 1; j < radix; j++){				//ת��Ϊ��ͰԪ����ֹλ��+1��ע���1��ʼ��������1Ͱ����
		count[j] = count[j] + count[j-1];
	}
	for (i = left; i <= right; i++){
		j = getDigit(L[i],d,radix);
		auxArray[count[j]-1] = L[i];			//���䵽��������
		count[j]--;								//ע��--������Ϊ��Ͱ��ʼλ��
	}
	for (i = left, j = 0; i <= right; i++, j++){//�طŵ�ԭ����
		L[i] = auxArray[j];
	}
	delete[] auxArray;
	for (j = 0; j < radix-1; j++){
		p1 = left+count[j];
		p2 = left+count[j+1]-1;
		RadixSort<E,K>(L, p1, p2, d-1, getDigit);//#ģ��ʵ�����ݳ������壬������ʽָ��
	}
	p1 = left+count[j];							//���һͰ����
	p2 = right;
	RadixSort<E,K>(L, p1, p2, d-1, getDigit);	//#ģ��ʵ�����ݳ������壬������ʽָ��
}

// ���ڶ����������������㷨
template <typename E, typename K>void BSTSort(dataList<E,K> &L, int left, int right){
	SeqStack<BSTNode<E,K>*> S;
	BST<E,K> bst;
	for(int i = left; i <= right; i++){
		bst.Insert(L[i]);
	}
	BSTNode<E,K> *p = bst.getRoot();
	int j = left;
	do{
		while (p){
			S.Push(p);
			p = p->left;
		}
		if (!S.IsEmpty()){
			S.Pop(p);
			L[j] = p->data;
			j++;
			p = p->right;
		}
	}while (p || !S.IsEmpty());
}

// E925��������
// ��������
template <typename E, typename K>void CountSort(dataList<E,K> &L, int left, int right){
	int i, j;
	int *count = new int[right-left+1];
	dataList<E,K> tmp(right-left+1);
	for (i = left; i <= right; i++){
		count[i-left] = 0;
	}
	for (i = left; i < right; i++){
		for (j = i+1; j <= right; j++){
			if (L[j] < L[i]){
				count[i-left]++;
			}
			else{
				count[j-left]++;
			}
		}
	}
	for (i = left; i <= right; i++){
		tmp[count[i-left]] = L[i];
	}
	for (i = left; i <= right; i++){
		L[i] = tmp[i-left];
	}
}
#endif
