#ifndef BITSET_H
#define BITSET_H

#include <cassert>
#include <iostream>
using namespace std;
const int DefaultSize = 50;

// T Ӧ��Ϊ��������
template<typename T>class bitSet{
//��λ�������洢����Ԫ��, ����Ԫ�صķ�Χ��0��
//setSize-1֮�䡣�������16λ�޷��Ŷ�����ʵ��
public:
	bitSet(int sz = DefaultSize);
	bitSet(const bitSet<T> &R);
	~bitSet();
	bool getMember(const T &x);				//ȡ����Ԫ��x
	void putMember(const T &x, int v);			//��vֵ�޸ļ���Ԫ��x
	void makeEmpty();
	bool addMember(const T &x);					//�����³�Աx
	bool delMember(const T &x);					//ɾ���ϳ�Աx
	bitSet<T>& operator = (const bitSet<T> &R);	
	bitSet<T> operator + (const bitSet<T> &R);
	bitSet<T> operator * (const bitSet<T> &R);
	bitSet<T> operator - (const bitSet<T> &R);
	bool Contains(const T &x);                  //��x�Ƿ񼯺�this�ĳ�Ա
	bool subSet(bitSet<T> &R);					//��this�Ƿ�R���Ӽ�
	bool operator == (bitSet<T> &R);		    //�м���this��R���

	friend istream& operator >> (istream &in, bitSet<T> &R){
		T item;
		while (!in.eof()){
			in >> item;
			if (item < 0){
				break;
			}
			R.addMember(item);
		}
		in.clear();
		return in;
	}
	friend ostream& operator << (ostream &out, bitSet<T> &R)	{
		out << "{";
		int i = 0;
		while (i < R.setSize){
			if (R.getMember(i)){
				out << i++;
				break;
			}
			i++;
		}
		for (; i < R.setSize; ++i){
			if (R.getMember(i)){
				out << ", " << i;
			}
		}
		out << "}" << endl;
		return out;
	}

private:
	int setSize;				//���ϴ�С
	int vectorSize;				//λ�����С
	unsigned short *bitVector;	//�洢����Ԫ�ص�λ����
};

template <typename T>bitSet<T>::bitSet(int sz){
	setSize = sz;
	assert(setSize > 0);
	vectorSize = (setSize+15)>>4;//��Ϊ16��֮1���������β
	bitVector = new unsigned short [vectorSize];
	assert(bitVector);
	for (int i = 0; i < vectorSize; i++){
		bitVector[i] = 0;
	}
}

//���ƹ��캯��
template <typename T>bitSet<T>::bitSet(const bitSet<T> &R){
	setSize = R.setSize;
	vectorSize = R.vectorSize;
	bitVector = new unsigned short [vectorSize];
	assert(bitVector);
	for (int i = 0; i < vectorSize; i++)	{
		bitVector[i] = R.bitVector[i];
	}
}

template <typename T>bitSet<T>::~bitSet(){
	delete []bitVector;
}

template <typename T>void bitSet<T>::makeEmpty(){//��ռ���
	for (int i = 0; i < vectorSize; i++)	{
		bitVector[i] = 0;
	}
}

template <typename T>bool bitSet<T>::Contains(const T &x){//�����Ƿ����x
	return getMember(x);
}

//��ȡ����Ԫ��x
template <typename T>bool bitSet<T>::getMember(const T &x){
	int ad = x/16, id = x%16;
	unsigned short elem = bitVector[ad];
	return ((elem >> (15-id)) & 1);
}

//��ֵv���뼯��Ԫ��x
template <typename T>void bitSet<T>::putMember(const T &x, int v){
	int ad = x/16, id = x%16;
	unsigned short elem = bitVector[ad];
	int temp = elem >> (15-id);
	if (temp%2 == 0 && v == 1){
		temp = temp+1;
	}
	else if (temp%2 == 1 && v == 0){
			temp = temp-1;
		}
	bitVector[ad] = (temp<<(15-id)) | (((1<<(15-id)) - 1) & elem);		//�ͻ�
}

template <typename T>bool bitSet<T>::addMember(const T &x){
	assert (x >= 0 && x < setSize);
	if (getMember(x) == 0){//x��Ӧλ��0�����ڣ����ȥ
		putMember(x, 1);
		return true;
	}
	return false;
}

template <typename T>bool bitSet<T>::delMember(const T &x){
	assert(x >= 0 && x < setSize);
	if (getMember(x) == 1){//x��Ӧλ��1���ڣ�ɾ��
		putMember(x, 0);
		return true;
	}
	return false;
}

template<typename T>bitSet<T>& bitSet<T>::operator = (const bitSet<T> &R){
	if (this != &R){
		setSize = R.setSize;
		vectorSize = R.vectorSize;
		delete []bitVector;
		bitVector = new unsigned short [vectorSize];
		assert(bitVector);
		for (int i = 0; i < vectorSize; i++){//���������԰�����Ԫ�أ�����Ҳ���ذ�λ����
			bitVector[i] = R.bitVector[i];
		}
	}
	return *this;
}

//�󼯺�this��R�Ĳ�
template<typename T>bitSet<T> bitSet<T>::operator + (const bitSet<T> &R){//���ð�λ�����
	assert(vectorSize == R.vectorSize); //����setSize��׼ȷ
	bitSet<T> temp(setSize);
	for (int i = 0; i < vectorSize; i++){
		temp.bitVector[i] = bitVector[i] | R.bitVector[i];
	}
	return temp;
}

//�󼯺�this��R�Ľ�
template <typename T>bitSet<T> bitSet<T>::operator * (const bitSet<T> &R){	//���ð�λ�����
	assert (vectorSize == R.vectorSize);
	bitSet<T> temp(setSize);
	for (int i = 0; i < vectorSize; i++){
		temp.bitVector[i] = bitVector[i] & R.bitVector[i];
	}
	return temp;
}

//�󼯺�this��R�Ĳ�
template <typename T>bitSet<T> bitSet<T>::operator - (const bitSet<T> &R){	//*this��R�İ�λ�����а�λ�����
	assert(vectorSize == R.vectorSize); 
	bitSet<T> temp(setSize);
	for (int i = 0; i < vectorSize; i++){
		temp.bitVector[i] =	bitVector[i] & ~R.bitVector[i];
	}
	return temp;
}

//��this�Ƿ�R���Ӽ�
template <typename T>bool bitSet<T>::subSet(bitSet<T> &R){
	assert (setSize == R.setSize);
	for (int i = 0; i < vectorSize; i++){
		if (bitVector[i] & ~R.bitVector[i]){//*this��R�Ĳ�Ϊ0
			return false;
		}
	}
	return true;	
}

//�м���this��R���
template <typename T>
bool bitSet<T>::operator == (bitSet<T> &R){
	if (vectorSize != R.vectorSize)	{
		return false;
	}
	for (int i = 0; i < vectorSize; i++){
		if (bitVector[i] != R.bitVector[i]){//ÿһ������Ԫ�ض���ͬ��ע�����һ������Ԫ��δ�õ�λ��ҲӦ����ͬ��ͨ��ȫΪ0
			return false;
		}
	}
	return true;
}
#endif
