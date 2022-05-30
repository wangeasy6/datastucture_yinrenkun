#include "AString.h"
#include <cstring>
#include <cassert>
#include <iostream>
using namespace std;

AString::AString(int sz){
	maxSize = sz;             //maxsize�ǿ����ɴ�����󳤶�
	ch = new char[maxSize+1]; //Ϊ����������1���ֽ�
	assert(ch);
	curLength = 0;            //����ǰ���ȣ�������������
	ch[0] = '\0';
}

AString::AString(const char *init){
	int len = strlen(init);
	maxSize = (len > defaultSize)?len:defaultSize;
	ch = new char[maxSize+1];
	assert(ch);
	curLength = len;
	strcpy(ch,init);          //���ݽṹ��ѧ��д�����Ϊ��
}

AString::AString(const AString &ob){
	maxSize = ob.maxSize;
	ch = new char[maxSize+1];
	assert(ch);
	curLength = ob.curLength;
	strcpy(ch, ob.ch);
}

AString AString::substr(int pos, int len){
	//�Ӵ��е� pos ��λ����������ȡ len ���ַ��γ��Ӵ�����
	AString temp(maxSize);
	if (pos >= 0 && pos+len-1 < maxSize && len > 0){
		if (pos+len-1 >= curLength){
			len = curLength - pos; //��Ϊ�Ӵ����ܴﵽ����󴮳�
		}
		temp.curLength = len;
		for (int i = 0, j = pos; i < len; i++, j++){
			temp.ch[i] = ch[j];
		}
		temp.ch[len] = '\0';
	}
	return temp;
}

AString AString::operator () (int pos, int len){
	//�Ӵ��е� pos ��λ����������ȡ len ���ַ��γ��Ӵ�����
	AString temp(maxSize);
	if (pos >= 0 && pos+len-1 < maxSize && len > 0){
		if (pos+len-1 >= curLength){
			len = curLength - pos;
		}
		temp.curLength = len;
		for (int i = 0, j = pos; i < len; i++, j++){
			temp.ch[i] = ch[j];
		}
		temp.ch[len] = '\0';
	}
	return temp;
}

AString& AString::operator = (const AString &ob){
	if (&ob != this){
		delete []ch;              //�����
		maxSize=ob.maxSize;
		ch = new char[maxSize+1];
		assert(ch);
		curLength = ob.curLength;
		strcpy(ch,ob.ch);
	}
	else	cout << "�ַ�������ֵ����!\n";		
	return *this;
}

char& AString::operator [] (int i){	//�±���������أ�ȡ��ǰ��*this�ĵ�i���ַ�
	assert(i >= 0 && i < curLength);
	return ch[i];
}

AString AString::operator + (const AString& ob){
	int n = curLength + ob.curLength;
	int m = (maxSize >= n) ? maxSize : n;
	AString temp(m);

	temp.curLength = n;
	strcpy(temp.ch, ch);
	strcat(temp.ch, ob.ch);
	return temp;
}

AString& AString::operator += (const AString& ob){
	char *temp = ch;             //*this�ַ�����temp����
	int n = curLength + ob.curLength;
	int m = (maxSize >= n) ? maxSize : n;
	
	ch = new char[m+1];
	assert(ch);
	maxSize = m;
	curLength = n;
	strcpy(ch, temp);
	strcat(ch, ob.ch);
	delete []temp;
	return *this;
}

int AString::Find(AString &pat, int k)const{//�ӵ�K�����±꣩�ַ���ʼ
	int i, j, n = curLength, m = pat.curLength;
	for (i = k; i <= n-m; i++){ 
		for (j = 0; j < m; j++){
			if (ch[i+j] != pat.ch[j]) break;   //����ʧ��			
		}
		if (j == m)	return i;	//patΪ�ջ�patɨ����, ƥ��ɹ�
	}	
	return -1;	 //��*this���Ҳ�����
}

int AString::fastFind(AString &pat, int k, int next[])const{
	int posP = 0, posT = k;
	int lengthP = pat.curLength;	//ģʽ������
	int lengthT = curLength;		//Ŀ�괮����
	while (posP < lengthP && posT < lengthT){	//������ɨ��	
		if (posP == -1 || pat.ch[posP] == ch[posT]){//��Ӧ�ַ�ƥ��
			posP++;
			posT++;
		}
		else	posP = next[posP];   //��pat���˱Ƚ�λ��
	}		
	if (posP < lengthP) return -1;	//ƥ��ʧ��	
	else  return posT-lengthP;	//ƥ��ɹ�
}

void AString::getNext(int next[]){
	int j = 0, k = -1, lengthP = curLength;
	next[0] = -1;
	while (j < lengthP){
		if ( k == -1 || ch[j] == ch[k])	{
			j++;
			k++;
			next[j] = k;
		}
		else	k = next[k];
	}
}

// �ַ����滻������
// ��t�ǵ�ǰ�����Ӵ�������v�滻t�ڵ�ǰ���е����г��֣�
// ��t���ǵ�ǰ�����Ӵ�����ǰ�����ֲ��䡣
// �ú������ص�ǰ�������á�
AString& AString::replace(AString &t, AString &v){
	int *next = new int[t.Length()+1];//û��+1ʹ���г��磬����ʱ������
	t.getNext(next);
	int k = 0, j = 0;
	AString s2;
	while (k <= curLength - t.Length())	{
		j = fastFind(t, k, next);
		if ( j == -1 )	break;
		s2 = s2 + (*this)(k, j-k) + v;
		k = j + t.Length();
	}
	s2 += (*this)(k, curLength-k);
	*this = s2;
	delete []next;
	return *this;
}
