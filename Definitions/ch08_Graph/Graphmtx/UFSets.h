#ifndef UFSETS
#define UFSETS
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;
const int DefaultSize1 = 30;

//�����еĸ����Ӽ��ϻ����ཻ
class UFSets{
public:
    UFSets(int sz = DefaultSize1);
	UFSets(UFSets &R);
	~UFSets(){
		delete []parent;
	}
    UFSets& operator = (UFSets &R);		//���������أ�ʵ�ּ��ϸ�ֵ
    void SimpleUnion(int Root1, int Root2);//�Ӽ��ϲ�
    int Find(int x);					//����x�ĸ�
    void WeightedUnion(int Root1, int Root2);//ѹ���߶ȵĺϲ��㷨
	int CollapsingFind(int i);			//ʹ���۵�����������㷨
	void output(ostream &out = cout);
	friend ostream& operator << (ostream &out, UFSets &R){
		int i;
		out << "\n" << string(70, '=');
		for (int j = 0; j <= (R.size-1)/10; j++){
			out << "\nNode:\t";
			for(i = 10*j; i < 10*(j+1) && i < R.size; i++){
				out << setw(6) << i;
			}
			cout << "\nParent:\t";
			for(i = 10*j; i < 10*(j+1) && i < R.size; i++){
				out << setw(6) << R.parent[i];
			}
			if (i < R.size){
				out << "\n" << string(70, '-');
			}
		}
		out << "\n" << string(70, '=') << "\n";
		return out;
	}
private:
    int *parent;						//����Ԫ������(˫�ױ�ʾ)
    int size;							//����Ԫ�ص���Ŀ
};
#endif
