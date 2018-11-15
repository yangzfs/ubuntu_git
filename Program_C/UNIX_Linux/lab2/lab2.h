#include<fcntl.h> //P9 打开或创建文件函数open
#include<unistd.h> //P10 从文件中读数据函数read
                  //P11 向打开的文件中写数据write
                  //P12 关闭打开的文件close
                  //P13 设置或查询文件当前位置lseek
#include<errno.h>
extern int errno;    //P15 错误信息errorno
#include<string.h> //P16 将errnum转化成字符串
#include<stdio.h>  //P16 输出errorno对应错误
#include<stdlib.h>
