//XSI IPC 共享内存
#include<sys/ipc.h> //IPC命名管道
#include<sys/shm.h> //共享存储
  //int shmget(key_t key, size_t size, int shmflg);得到共享内存
#include<sys/types.h>
  //int shmat(inst shm_id, const void *shm_addr, int shmflg);连接共享内存
  //void *shmdt(const void *shmaddr);断开共享内存
  //int shmctl(int shmid, int cmd, struct shmid_ds* buf);控制共享内存
#include<sys/sem.h> //

#include<stdio.h>
#include<stdlib.h>
#include<string.h>



int main(int argc, char const *argv[])
{
  char * p;
  char s[] = "test";
  p = (char *)malloc(sizeof (s));
  strcpy(p, s);
  printf("%s", p);
  
  // key_t mykey = (key_t)1234;
  // printf("%d", (int)(0x5102000d));
  // pid_t pid1, pid2;
  //
  // int shmid = shmget(000, 50, IPC_CREAT|0666);
  // perror("shmget");
  //
  // int semid = semget((key_t)5678, 1, IPC_CREAT|0666);
  // perror("semget");
  //
  return 0;
}

// #define EXIT_ELSE_CONTINUE\
// {                         \
//   printf("exit \n");      \
//   exit(1);                \
// }                         \
// else                      \
//   printf("continue \n");
//
// struct sharedbuf
// {
//   char pool[100];
//   int flag;
// };
// int main(int argc, char const *argv[]) {
//   int shmid;
//   void * shm_addr = NULL;
//

// #include<stdio.h>
// #include<fcntl.h>
// #include<unistd.h>
// #include<errno.h>
// #include<stdlib.h>
// #include<sys/stat.h>
// #include<dirent.h>
// #include<string.h>
// #include<time.h>
// #include<pthread.h>
// #include<sys/sem.h>
// #include<sys/ipc.h>
//
// #define MYKEY 0x1a0a
// extern int error;
// enum{WHILE = 258, IF};
//
// typedef struct a
// {
//   int count;
// }ic, *ip;
//
// int main (void)
// {
//
//
//   // ip test = (ip) malloc (sizeof (ic));
//   // test->count = 1;
//   // printf("%d", test->count);
//   // int i = +1;
//   // printf("%d", i);
//   // printf("%d", WHILE);
//
//   // int semid;
//   // semid = semget(MYKEY, 1, IPC_CREAT|IPC_W|IPC_M);
//   // printf("semid = %d\n", semid);
//
//   // pthread_mutex_t mlock;
//   // printf("%d\n", mlock.__data.__count);
//   // pthread_mutex_init(&mlock, NULL);
//   // printf("%d\n", mlock.__data.__count);
//
// //   printf("%d",*(int *)number);
// //   printf("test\n");
// // }
// // int main(int argc, char const *argv[]) {
// //   int number = 10;
// //   pthread_t ph_tid;
// //   pthread_create(&ph_tid, NULL, ph, &number);
// //   pthread_join(ph_tid,NULL);
// //
//   // const char * p1 = "/path";
//   // const char * p2 = "/";
//   // const char * p3 = "test.c";
//   // char * p4 = (char *)malloc(strlen(p1)+strlen(p2)+strlen(p3)-5);
//   // sprintf(p4,"%s%s%s",p1,p2,p3);
//   // printf("%s", p4);
//
//   // char *path ="/home/zwz/桌面/ubuntu_git/Program_Java";
//   // char *path2 =(char *) malloc(10);
//   // strcpy(path2, path);
//   // //printf("%lu\n", strlen(path2));
//   // printf("%s\n", path2);
//
//   // int pid=10, i;
//   // for (i = 1; i < 10; i++)
//   // {
//   //   printf("pid:%d i:%d\n",pid,i);
//   //   if (i == 3)
//   //   {
//   //     pid = fork();
//   //   }
//   // }
//
//   // //int filedes;
//   // struct stat st;
//   // //filedes = open("/home/zwz/桌面/ubuntu_git/Program_C/UNIX_Linux/lab4/lab4.c",O_RDONLY);
//   //
//   // stat("/home/zwz/桌面/ubuntu_git/Program_C/UNIX_Linux/lab4/lab4.c",&st);
//   // printf("%d", st.st_mode );
//   // execl("/home/zwz/桌面/ubuntu_git/Program_C/UNIX_Linux/lab2/mycp"
//   // ,"./mycp"
//   // ,"/home/zwz/桌面/ubuntu_git/Program_C/test.c"
//   // ,"/home/zwz/桌面/",NULL);
//   // int i = strlen(argv[0]);
//   // printf("%d",argv[0][i+1]);
//   // char * p = "sssssssssssssss";
//   // printf("%ld  %ld\n" , sizeof(p), strlen(p));
//   // printf("%s\n", p);
//
//   // char * buf = getcwd(NULL,0);
//   // DIR * currentdir = opendir(buf);
//   // struct dirent * currentdp = readdir(currentdir);
//   // char * path = (char *)malloc (strlen(buf) +1+ strlen(currentdp->d_name));
//   // struct stat st;
//   // struct tm * tp;
//   // if (argv[1]!=NULL) printf("1");
//   // strcpy(path , buf);
//   // //strcat(path , "/");
//   // //strcat(path , currentdp->d_name);
//   // printf("%s\n", path);
//   // stat(path,&st);
//   //
//   // tp = localtime(&st.st_ctime);
//   // printf("%d-%d-%d", tp->tm_year+1900, tp->tm_mon, tp->tm_mday);
//   return 0;
// }
