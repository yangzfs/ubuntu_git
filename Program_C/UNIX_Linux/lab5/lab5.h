#include<pthread.h>
  //int pthread_create(pthread_t * restrict tidp, //指向线程id的指针
  //                   const pthread_attr_t * restrict attr, //指定线程属性
  //                   void * (*start_rtn) (void*), //线程的启动例程函数指针
    // void *start_rtn(void * arg)
  //                   void * restrict arg); //向线程的启动例程传递信息的参数
  //void pthread_exit(void *rval_ptr);
  //int pthread_join(pthread_t thread, void **rval_ptr); //父线程阻塞直到thread子线程终止

//编译时加入参数 -lpthread //pthread 不是linux默认库
//gcc file.c -lpthread -o file
#include<unistd.h>
#include<dirent.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
