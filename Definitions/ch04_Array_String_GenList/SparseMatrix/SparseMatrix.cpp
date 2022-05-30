#include "SparseMatrix.h"
#include <iostream>
#include <cassert>
using namespace std;

template <typename E>SparseMatrix<E>::SparseMatrix(int mT, int Rw, int Cl){
    Rows = Rw;
	Cols = Cl;
	Terms=0;         //���
	maxTerms = mT;   //�޸�
    smArray = new Triple<E>[maxTerms];//�޸�
	assert(smArray);
}

template <typename E>SparseMatrix<E>::SparseMatrix(SparseMatrix<E>& x){
    Rows = x.Rows;
	Cols = x.Cols;
	Terms=x.Terms;         //���
	maxTerms =x.maxTerms;   //�޸�
    smArray = new Triple<E>[maxTerms];//�޸�
	assert(smArray);
	int i;
	for(i=0;i<=Terms;i++) smArray[i]=x.smArray[i];
}

template <typename E>SparseMatrix<E> SparseMatrix<E>::Transpose(){
	SparseMatrix<E> B(maxTerms,Cols,Rows);                    //�޸�
	if (Terms > 0){
		int CurrentB = 0;
		int i, k;
		for (k = 0; k < Cols; k++){       //���к�ɨ��
			for (i = 0; i < Terms; i++){  //�����������к�Ϊk����Ԫ��
				if (smArray[i].col == k){ //��������ת�þ�����Ԫ������
					B.smArray[CurrentB].row = k;	
	                B.smArray[CurrentB].col = smArray[i].row;
	                B.smArray[CurrentB].value=smArray[i].value;	
 	                CurrentB++;
				}
			}
		}
	}
	B.Terms=Terms;
	return B;
}

template <typename E>SparseMatrix<E> SparseMatrix<E>::FastTranspos(){//����ת��
    int *rowSize = new int[Cols];       //��Ԫ����������
    int *rowStart = new int[Cols];      //����ʼλ������
	SparseMatrix<E> /*B(Rows,Cols,Terms)*/B(maxTerms,Cols,Rows);
	B.Terms=Terms;
    if (Terms > 0)	{
        int i, j;
        for (i = 0; i < Cols; i++){
			rowSize[i] = 0;
		}
	    for (i = 0; i < Terms; i++){//������Ԫ����������
			rowSize[smArray[i].col]++; 
		}
        rowStart[0] = 0;	
        for (i = 1; i < Cols; i++){//��������ʼλ������
			rowStart[i] = rowStart[i-1]+rowSize[i-1];
		}
	    for (i = 0; i < Terms; i++)		{			
			j = rowStart [smArray[i].col];
			B.smArray[j].row = smArray[i].col;
			B.smArray[j].col = smArray[i].row;
			B.smArray[j].value = smArray[i].value;
			rowStart [smArray[i].col]++;//����һ��Ԫ�غ󣬶�Ӧ����ʼλ����++��ָ��������һ��Ԫ��λ��		
		}
	}
	B.Terms=Terms;
    delete []rowSize;
	delete []rowStart;
	return B;
}

template <typename E>SparseMatrix<E> SparseMatrix<E>::Add(SparseMatrix<E> &b){
	SparseMatrix<E> result(Terms+b.Terms,Rows,Cols);
	if ( Rows != b.Rows || Cols != b.Cols){//��������һ�£��������
		cout << "Incompatible matrices" << endl;
		return result;
	}
	int i = 0, j = 0, index_a, index_b; result.Terms = 0;
	while (i < Terms && j < b.Terms){                        //�鲢�㷨
		index_a = Cols*smArray[i].row+smArray[i].col;        //��Чһά�����±�
		index_b = Cols*b.smArray[j].row+b.smArray[j].col;
		if (index_a < index_b){
			result.smArray[result.Terms] = smArray[i];
			i++;
		}
		else if (index_a > index_b){
			result.smArray[result.Terms] = b.smArray[j];
			j++;
		}
		else{
			result.smArray[result.Terms] = smArray[i];
			result.smArray[result.Terms].value= smArray[i].value + b.smArray[j].value;
			i++; j++;
		}
		result.Terms++;
	}

	for ( ; i < Terms; i ++){
		result.smArray[result.Terms] = smArray[i];
		result.Terms++;
	}
	for ( ; j < b.Terms; j++){
		result.smArray[result.Terms] = b.smArray[j];
		result.Terms++;
	}
	return result;
}

template <typename E> SparseMatrix<E> SparseMatrix<E>::Multiply(SparseMatrix<E> &b){
	SparseMatrix<E> result(Rows*b.Cols/2,Rows, b.Cols);//ʵ�ó�������ȷ���Ƚ�С�Ŀռ䣬�Ժ������·���
	if (Cols != b.Rows)	{
		cout << "Incompatible matrices" << endl;
		return result; 
	}
	int *rowSize = new int[b.Rows];		//����B ���з���Ԫ�ظ���
	int *rowStart = new int[b.Rows+1];	//����B ��������Ԫ�鿪ʼλ��
	E *temp = new E[b.Cols];			//�ݴ�ÿһ�м�����
	int i, Current, lastInResult, RowA, ColA, ColB;
	for (i = 0; i < b.Rows; i++) rowSize[i] = 0;
	for (i = 0; i < b.Terms; i++) rowSize[b.smArray[i].row]++;
	rowStart[0] = 0;					//B��i �з���Ԫ�ؿ�ʼλ��
	for (i = 1; i <= b.Rows; i++)
		rowStart[i] = rowStart[i-1]+rowSize[i-1];
	Current = 0; lastInResult = -1;		//a ɨ��ָ�뼰result ��ָ��
	while (Current < Terms){				//����result �ĵ�ǰ��temp	
		RowA = smArray[Current].row;	//��ǰ�е��к�
		for (i = 0; i < b.Cols; i++) temp[i] = 0;
		while (Current < Terms && smArray[Current].row == RowA){//������и�Ԫ��
			ColA = smArray[Current].col; //����A ��ǰɨ�赽Ԫ�ص��к�
			for (i = rowStart[ColA]; i < rowStart[ColA+1]; i++){
				ColB = b.smArray[i].col; //����B �����Ԫ�ص��к�
				temp[ColB] += smArray[Current].value*b.smArray[i].value;
			} //A��RowA ����B ��ColB �����
			Current++;
		}
		for (i = 0; i < b.Cols; i++){
			if (temp[i] != 0){			//��temp �еķ���Ԫ��ѹ����result ��ȥ			
				lastInResult++;
				result.smArray[lastInResult].row = RowA;//�кŹ̶�
				result.smArray[lastInResult].col = i;//�кŶ�Ӧtemp�±�
				result.smArray[lastInResult].value = temp[i];//tempԪ�ض�Ӧϡ�����Ԫ��ֵ
			}
		}
	}
	result.Rows = Rows;
	result.Cols = b.Cols;
	result.Terms = lastInResult+1;
	delete []rowSize;
	delete []rowStart;
	delete []temp;
	return result;
}