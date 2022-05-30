#ifndef ASTRING_H
#define ASTRING_H
#include <cstring>
#include <iostream>
using namespace std;

const int defaultSize=128;
class AString{
private:
	char *ch;
	int curLength;
	int maxSize;
public:
	AString(int sz = defaultSize);
	AString(const char *init );
	AString(const AString &ob);
	~AString(){
		delete []ch;
	}
	int Length()const{
		return curLength;
	}
	AString substr(int pos, int len);
	AString operator()(int pos, int len);	//ȡ�Ӵ�
	bool operator == (AString &ob)const	{
		return strcmp(ch, ob.ch) == 0;
	}
	bool operator != (AString &ob)const{
		return strcmp (ch, ob.ch) != 0;
	}
	bool operator !()const{                //�жϴ��Ƿ�Ϊ��
		return curLength == 0;
	} 
	AString& operator = (const AString &ob);
	AString& operator += (const AString &ob);
	AString operator + (const AString &ob);
	char& operator [](int i);
	int Find(AString &pat, int k)const;//�ڵ�ǰ����k���ַ����pat����ģʽƥ�䣬BF��
	int fastFind(AString &pat, int k, int next[])const;//KMP��
	void getNext(int next[]);//�Ե�ǰģʽ(*yhis)����next����
	AString& replace(AString &t, AString &v);//�û�
	friend ostream& operator << (ostream &out, const AString &str)	{
		out << str.ch;
		return out;
	}
	friend istream& operator >> (istream &in, AString &str)	{
		in >> str.ch;
		str.curLength = strlen(str.ch);
		return in;
	}
};
#endif
