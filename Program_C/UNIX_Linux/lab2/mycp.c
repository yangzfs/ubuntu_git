#include "lab2.h"
#define MAXBUF 1024
#define MAXBYTE 8192
#include<sys/stat.h>

int main(int argc, char const *argv[]) {
  int path1, path2;
  int filedes1, filedes2, excl, bufsize;
  char * buf;
  char * path2_;
  struct stat st1,st2;
  char *dname = NULL;

  path1 = 1;// 获取源文件路径
  stat(argv[path1],&st1);
  if (S_ISDIR(st1.st_mode)) {
    printf("error!\n""%s ""is a directory!\n",argv[path1]); exit(0);} //判断源文件路径是否是目录
  filedes1 = open(argv[path1],O_RDONLY);// 打开源文件
  if (filedes1 == -1) {perror(argv[path1]); exit(0);};

  bufsize = st1.st_size;
  // bufsize = lseek(filedes1,SEEK_SET,SEEK_END);
  // lseek(filedes1,0,SEEK_SET);//文件偏移量重置为0
  buf = (char *)malloc(bufsize);

  path2 = 2;// 获取目标文件路径
  path2_ = (char *)malloc(strlen(argv[path1]) + strlen(argv[path2]));
  strcpy(path2_,argv[path2]);
  stat(argv[path2],&st2);
  if (S_ISDIR(st2.st_mode))  //判断目标文件路径是否是目录
  {
    int i = strlen(argv[path1]), j = 0;
    dname = (char *)malloc(i);

    while(argv[path1][i] != '/') i--;
    while(argv[path1][i] != '\0')
    {
      dname[j] = argv[path1][i];
      i++;j++;
    }
    dname[j] = '\0';
    strcat(path2_,dname);
  }

  excl = open(path2_,O_CREAT|O_EXCL, 00777&st1.st_mode);// 打开目标文件
  if (excl == -1) //文件存在的情况
  {
    printf("\t%s already exists\n",dname);
    while(1) //覆盖或合并
    {
      char ch;
      printf("\tdo you want to overwrite or merge?[o/m]");
      ch = getchar();
      while(getchar()!='\n'); //清空缓冲区

      if (ch == 'o' || ch == 'O')
      {
        filedes2 = open(path2_,O_RDWR|O_TRUNC); //覆盖
        break;
      }
      else if (ch == 'm' || ch == 'M')
      {
        filedes2 = open(path2_,O_RDWR|O_APPEND); //合并
        break;
      }
      else
        puts("error input!");
    }
  }
  else
    filedes2 = open(path2_,O_RDWR); //文件不存在的情况
  read(filedes1,buf,bufsize);// 源文件读取一定数据写到缓冲区
  write(filedes2,buf,bufsize);// 缓冲区写入目标文件
  // 源文件读取是否完成
  close(filedes1);// 关闭源文件
  close(filedes2);// 关闭目标文件
  return 0;
}
