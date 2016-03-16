#include <stdafx.h>

//1 取代define的小函数
template<typename T>
inline void callWithMax( const T& a, const T& b ){
    f( a > b ? a : b );
}


