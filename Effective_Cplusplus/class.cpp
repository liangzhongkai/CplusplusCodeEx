#include <stdafx.h>

//1 �ڲ������󲿷֣�
//   �������� =�����罫���캯����Ϊ˽�У�ʵ�ֵ������̳�����Ҳ�����ǵ���
//   �߼����� =����Ա���� �� ��Ա����<����Ϊprivate>

//2 �ⲿ��;��
//   ��ֱ���Ƿ����ڶ�̬����, ���ǵ���
//   ��ֱ���̳з�ʽ
//   ˮƽ����Ԫ

//3 design class�Ŀ��ǵ�
//   ��α����� �� ����
//   ��ʼ�� �� ��ֵ ��ʲô��һ��
//   ���class��passed by value
//   �쳣����
//   �Ƿ��м̳�ͼϵ
//   ��class������ת��
//   ��Щ������Ǻ����
//   private��public��protected�Ļ���
//   �Ƿ�һ�㻯==template
//   ��˼�Ƿ������Ҫ���class

//4 �÷ǳ�Ա���������Ա��������������Ը���
class WebBrowser{
public:
    void clearA(){}
    void clearB(){}
    void clearAll(){                                     //��Ա��������clearBrowser��clearAll��װ�ԡ����Զ�Ҫ��
        clearA();
        clearB();
    }
};
void clearBrowser( WebBrowser& wb ){   //�ǳ�Ա����
    wb.clearA();
    wb.clearB();
}





