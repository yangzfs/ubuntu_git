#include"lab4.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main(int argc, char const *argv[]) {
  char *buf;
  DIR * currentdir;
  struct dirent * currentdp;
  struct stat currentstat;
  const char * destination = "/home/zwz/桌面/backup";
  const char * _r_copy_PATH = "/home/zwz/桌面/ubuntu_git/Program_C/UNIX_Linux/lab4/r_copy";
  const char * _r_copy_command = "./r_copy";
  const char * _mycp_PATH = "/home/zwz/桌面/ubuntu_git/Program_C/UNIX_Linux/lab2/mycp";
  const char * _mycp_command = "./mycp";

  if (argv[1] == NULL)// 获取当前工作目录路径
  {
    if ( (buf = getcwd(NULL,0)) != NULL){
      printf("copy ");
      printf("from:  %s\n",buf);
    }
  }else if (argv[2] == NULL)
  {
    buf = (char *)malloc(strlen(argv[1])+1);
    strcpy(buf, argv[1]);
    printf("-R copy ");
    printf("from: %s\n",buf);
  }else
  {
    printf("ERROR:too much command!\n");
    exit(0);
  }
  if ( (currentdir = opendir(buf)) == NULL)// 打开目录
  {
    printf("ERROR:open directory fail\n");
    return 0;
  }
  while((currentdp = readdir(currentdir)) != NULL)// 读取目录文件 // while 文件未结束
  {
    int pid_child;
    if(currentdp->d_name[0] != '.'){
      char * path = (char *)malloc (strlen(buf)+1+strlen(currentdp->d_name)+1);
      strcpy(path , buf);
      strcat(path , "/");
      strcat(path , currentdp->d_name);
      if (stat(path,&currentstat) == -1)// 获取文件属性
      {
        printf("get stat error\n");
        continue;
      }
      if (S_ISDIR(currentstat.st_mode))// 是一个目录 则返回读取目录文件 否则递归
      {
        pid_child = fork(); // 递归子进程
        if (pid_child == 0)
        {
          execl(_r_copy_PATH, _r_copy_command //该行为地址及命令
          , path, NULL);  //该行为参数
        }
      }
      else if (S_ISREG(currentstat.st_mode))//执行mycp
      {
        pid_child = fork();  // 复制子进程
        if (pid_child == 0)
        {
          execl(_mycp_PATH, _mycp_command //该行为地址及命令
          , path, destination, NULL); //该行为参数
        }
      }
      waitpid(pid_child,NULL,0);  //   阻塞等待子进程运行终止
    }
  }
  closedir(currentdir);// 关闭目录
  return 0;
}
