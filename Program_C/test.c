#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<errno.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<dirent.h>
#include<string.h>
#include<time.h>

extern int error;
int main(int argc, char const *argv[]) {
  const char * p1 = "/path";
  const char * p2 = "/";
  const char * p3 = "test.c";
  char * p4 = (char *)malloc(strlen(p1)+strlen(p2)+strlen(p3)-5);
  sprintf(p4,"%s%s%s",p1,p2,p3);
  printf("%s", p4);

  // char *path ="/home/zwz/桌面/ubuntu_git/Program_Java";
  // char *path2 =(char *) malloc(10);
  // strcpy(path2, path);
  // //printf("%lu\n", strlen(path2));
  // printf("%s\n", path2);

  // int pid=10, i;
  // for (i = 1; i < 10; i++)
  // {
  //   printf("pid:%d i:%d\n",pid,i);
  //   if (i == 3)
  //   {
  //     pid = fork();
  //   }
  // }

  // //int filedes;
  // struct stat st;
  // //filedes = open("/home/zwz/桌面/ubuntu_git/Program_C/UNIX_Linux/lab4/lab4.c",O_RDONLY);
  //
  // stat("/home/zwz/桌面/ubuntu_git/Program_C/UNIX_Linux/lab4/lab4.c",&st);
  // printf("%d", st.st_mode );
  // execl("/home/zwz/桌面/ubuntu_git/Program_C/UNIX_Linux/lab2/mycp"
  // ,"./mycp"
  // ,"/home/zwz/桌面/ubuntu_git/Program_C/test.c"
  // ,"/home/zwz/桌面/",NULL);
  // int i = strlen(argv[0]);
  // printf("%d",argv[0][i+1]);
  // char * p = "sssssssssssssss";
  // printf("%ld  %ld\n" , sizeof(p), strlen(p));
  // printf("%s\n", p);

  // char * buf = getcwd(NULL,0);
  // DIR * currentdir = opendir(buf);
  // struct dirent * currentdp = readdir(currentdir);
  // char * path = (char *)malloc (strlen(buf) +1+ strlen(currentdp->d_name));
  // struct stat st;
  // struct tm * tp;
  // if (argv[1]!=NULL) printf("1");
  // strcpy(path , buf);
  // //strcat(path , "/");
  // //strcat(path , currentdp->d_name);
  // printf("%s\n", path);
  // stat(path,&st);
  //
  // tp = localtime(&st.st_ctime);
  // printf("%d-%d-%d", tp->tm_year+1900, tp->tm_mon, tp->tm_mday);
  return 0;
}
