#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>

int main(int argc, char const *argv[]) {
  pid_t pid_child,wait_return;
  pid_child=fork();
  if (pid_child<0) printf("Error occured on forking.\n");
  else if (pid_child == 0)
  {
    sleep(10);
    exit(0);
  }
  do{
    wait_return = waitpid(pid_child,NULL,WNOHANG);
    if (wait_return == 0)
    {
      printf("No child exited\n");
      sleep(1);
    }
  }while(wait_return == 0);

  if(wait_return == pid_child)
    printf("successfullyget child %d\n",wait_return);
    else printf("some error occured\n");
  // printf("entering main process---\n");
  // if (fork() == 0)
  // {
  //   execl("/bin/ls","ls","-l",NULL);
  //   printf("exiting main process ---- \n");
  // }
  // pid_t pid;
  // pid = fork();
  // if (pid == -1)
  //   printf("fork error\n");
  //   else if (pid == 0)
  //   {
  //     printf("the returned value is %d\n", pid);
  //     printf("in child process!!\n");
  //     printf("My PID is %d\n",getpid());
  //   }
  //   else
  //   {
  //     printf("the returned value is %d\n", pid);
  //     printf("in father process!!\n");
  //     printf("My PID is %d\n",getpid());
  //   }
  return 0;
}
