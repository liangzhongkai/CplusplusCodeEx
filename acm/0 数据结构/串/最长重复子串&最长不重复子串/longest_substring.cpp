#include "stdafx.h"
#include "longest_substring.h"

#ifdef _LONGEST_SUBSTRING
//1 最长重复子串LRS=Longest Repeat Substring
//1.1 模拟
int comlen(char* p, char* q) {
    int len = 0;
    while (*p && *q && *p++ == *q++) {
        ++len;
    }
    return len;
}
void LRS_1(char* arr, int size) {
    int maxlen = 0;
    int index = -1;
    for (int i = 0; i < size; ++i) {
        for (int j = i + 1; j < size; ++j) {
            int len = comlen(arr + i, arr + j);
            if (len > maxlen) {
                maxlen = len;
                index = i;
            }
        }
    }
}


//1.2 KMP


//1.3 后缀数组



//2 最长不重复子串
//2.1 模拟
int LNRS_1(string s) {
    int hash[255];
    int maxlen = 0;
    int len = s.length();
    if (len == 1) {
        return 1;
    }
    for (int i = 0; i < len; ++i) {
        memset(hash, 0, sizeof(hash));
        int j;
        for (j = i; j < len; ++j) {
            int index = (int)s[j];
            if (hash[index] == 0) hash[index] = 1;
            else {
                if (j-i > maxlen)
                    maxlen = j-i;
                break;
            }
        }
        if (j == len) {
            if (j - i > maxlen)
                maxlen = j - i;
        }
    }
    return maxlen;
}
//2.2 DP
int LNRS_2(string s) {

}
//2.3 DP+hash


int main()
{
    string str = "abcabcbb";
    //string str = "bbbbbb";
    printf("%d\n", LNRS_1(str));
    return 0;
}
#endif
