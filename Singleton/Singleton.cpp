#include "Singleton.h"
#include <windows.h>


//�ⲿ��ʼ�� before invoke main
const SingletonStatic* SingletonStatic::m_instance = new SingletonStatic;

