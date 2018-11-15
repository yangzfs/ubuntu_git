#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

void * childthread(void * arg)
{
  int i;
  for (i = 0;i < 10;i++)
  {
    printf("childthread message:%s\n", (char *)arg);
    sleep(1);
  }
  return 0;
}

int main(int argc,char** argv){
	pthread_t tid = 0;
  char str[100];
	printf("create childthread\n");
  sprintf(str,"str from parent");
  pthread_create(&tid,NULL,childthread,str);
	pthread_join(tid,NULL);
	printf("childthread exit\n");
  return 0;
}
