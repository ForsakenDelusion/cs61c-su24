## 一些C函数

函数原型： char*strcpy（char*dest，const char*src）   //将src复制到dest字符数组中
头  文  件：#include <string.h>
返  回  值：char* 类型，返回的是第一个参数的值，即目的数组的首地址；

注 意：

1、strcpy只用于字符串复制，遇到‘\0’时停止，还会复制字符串的结束符'\0'； 所以源字符串必须         以’\0’结束，也会将源字符串的’\0’拷贝到目标空间
2、目标空间必须可变
3、如果参数dest所指的内存空间不够大，可能会造成缓冲溢出的错误情况，在编写程序时需特别       留意，或者用strncpy()来代替

与strncpy的区别
1、strcpy() 函数用来复制字符串；strncpy()用来复制字符串的前n个字符，所以要多传一个参数n

     大家可以对比一下两个函数原型：

    char *strcpy(char *dest, const char *src);

    char * strncpy(char *dest, const char *src, size_t n);

2、不像strcpy()，strncpy()不会向dest追加结束标记'\0'

