// ջ�ĳ�����ඨ��
template <class T>
class StackWalk
{
public:
	virtual void Push(const T &x) = 0;	// ��Ԫ��x��ջ
	virtual bool Pop(T &x) = 0;			// ջ��Ԫ�س�ջ����x����
	virtual bool getTop(T &x) = 0;		// ��ȡջ����������x����
	virtual bool IsEmpty() const = 0;	// �ж�ջ�շ�
	virtual bool IsFull() const = 0;	// �ж�ջ����
	virtual int getSize() const = 0;	// ���ص�ǰջ�Ĵ�С
};