#ifndef SINGLETON_H_
#define SINGLETON_H_

/*
from:  http://www.cnblogs.com/ccdev/archive/2012/12/19/2825355.html
ʵ�֣�1�������͹��캯��Ϊ˽��
          2���̰߳�ȫ����  ��ʼ��������ʱ�򣬱������߳�ȥnew�������
          3����ȡ�����ĺ���Ϊ��public, static, const
*/


/*
����ģʽ���������Ƿ���ø����ʵ�����ڳ���ʼʱ�ͻ����һ�������ʵ���������Ժ�����ش�ʵ����
�ɾ�̬��ʼ��ʵ����֤���̰߳�ȫ�ԣ�WHY��
��Ϊ��̬ʵ����ʼ���ڳ���ʼʱ����������֮ǰ�������߳��Ե��̷߳�ʽ����˳�ʼ�������ص��Ķ��߳����⡣
������������ϸ�ʱ��Ӧʹ������ģʽ������Ƶ����������
*/
class SingletonStatic
{
private:
    static const SingletonStatic* m_instance;
    SingletonStatic(){}
public:
    static const SingletonStatic* getInstance()
    {
        return m_instance;
    }
};

#endif