#include "Singleton.h"
#include <windows.h>


//外部初始化 before invoke main
const SingletonStatic* SingletonStatic::m_instance = new SingletonStatic;

