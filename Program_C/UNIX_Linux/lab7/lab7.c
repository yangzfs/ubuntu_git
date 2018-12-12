#include"lab7.h"
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<fcntl.h>
#include<string.h>

#define MUTEX_KEY 0x1a0a
#define SHM_KEY   0x1a0b
#define BUFFER_NUM 5
#define BUFFER_SIZE 100

const char * producerN_path = "/home/zwz/桌面/ubuntu_git/Program_C/UNIX_Linux/lab7/producerN.txt";
const char * consumerN_path = "/home/zwz/桌面/ubuntu_git/Program_C/UNIX_Linux/lab7/consumerN.txt";

struct BufferPool
{
  char Buffer[BUFFER_NUM][BUFFER_SIZE];
  int Index[BUFFER_NUM];
};
union semun
{
	int			val;	/*信号量的值*/
	struct semid_ds *buf;	/*信号量集合信息*/
	unsigned short  *array;/*信号量值的数组*/
	struct seminfo  *__buf;/*信号量限制信息*/
};

void init_mutex(void);
void init_shm(void);

int semaphore_p(int sem_id);
int semaphore_v(int sem_id);
void show_sem(int sem_id);
void show_buf(struct BufferPool * bufp);

void producer(void);
void consumer(void);

int filedes1, filedes2;

int main(int argc, char const *argv[])
{
  pid_t pro1, pro2, con1, con2;
  init_mutex();//初始化互斥信号量
  init_shm();//初始化共享内存

  filedes1 = open(producerN_path, O_RDONLY);//打开producerN.txt
  filedes2 = open(consumerN_path, O_RDWR);//打开consumerN.txt

  pro1 = fork();
  if (pro1 == 0)
  {
    producer();
    return 0;
  }
  pro2 = fork();
  if (pro2 == 0)
  {
    producer();
    return 0;
  }
  con1 = fork();
  if (con1 == 0)
  {
    consumer();
    return 0;
  }
  con2 = fork();
  if (con2 == 0)
  {
    consumer();
    return 0;
  }
  waitpid(con1, NULL, 0);
  waitpid(con2, NULL, 0);

  return 0;
}
void init_mutex(void)
{
  int mutex_id;
  mutex_id = semget(MUTEX_KEY, 1, IPC_CREAT|0666); //创建互斥信号量
  //  perror("init_mutex->semget");

  union semun sem_union;
  sem_union.val = 1;
  semctl(mutex_id, 0, SETVAL, sem_union);
  //  perror("init_mutex->semctl");
}
void init_shm(void)
{
  int shm_id;
  struct BufferPool * bufp;
  shm_id = shmget(SHM_KEY, sizeof(struct BufferPool), IPC_CREAT|0666);//创建共享内存
  //  perror("init_shm->shmget");
  bufp = (struct BufferPool *)shmat(shm_id, NULL, 0);//共享内存映射到进程
  //  perror("init_shm->shmat");

  int i, j;
  for (i = 0; i < BUFFER_NUM; i++)
  {
    bufp->Index[i] = 0;//空
    for(j = 0; j < BUFFER_SIZE; j++)
    {
      bufp->Buffer[i][j] = '\0';
    }
  }
}
int semaphore_p(int sem_id)
{
  struct sembuf sb;
  sb.sem_num = 0;
  sb.sem_op = -1;
  sb.sem_flg = SEM_UNDO;
  if (semop(sem_id, &sb, 1) == -1)
  {
    perror("semop");
    return -1;
  }
  return 0;
}
int semaphore_v(int sem_id)
{
  struct sembuf sb;
  sb.sem_num = 0;
  sb.sem_op = 1;
  sb.sem_flg = SEM_UNDO;
  if (semop(sem_id, &sb, 1) == -1)
  {
    perror("semop");
    return -1;
  }
  return 0;
}
void show_sem(int sem_id)
{
  printf("value:%d\n", semctl(sem_id, 0, GETVAL));
}
void producer(void)
{
  int mutex_id, shm_id;
  struct BufferPool * bufp;
  char buf[BUFFER_SIZE + 1];

  mutex_id = semget(MUTEX_KEY, 1, IPC_CREAT|0666); //创建互斥信号量
    //perror("producer->semget");
  shm_id = shmget(SHM_KEY, sizeof(struct BufferPool), IPC_CREAT|0666);//创建共享内存
    //perror("producer->shmget");
  bufp = (struct BufferPool *)shmat(shm_id, NULL, 0);//共享内存映射到进程
    //perror("producer->shmat");

  read(filedes1, buf, BUFFER_SIZE);
  //perror("producer->read");

  while(1)
  {
    int i;
    semaphore_p(mutex_id);
    for (i = 0; i < BUFFER_NUM; i++)
    {
      if (bufp->Index[i] == 0)
      {
        strncpy(bufp->Buffer[i], buf, BUFFER_SIZE);
        bufp->Index[i] = 1;
        break;
      }
    }
    if (i == BUFFER_NUM)//buf没有空余，没有成功生产
    {
      semaphore_v(mutex_id);
      sleep(rand()%3);
    }
    else
    {
      semaphore_v(mutex_id);
      if (read(filedes1, buf, BUFFER_SIZE) != BUFFER_SIZE)
      {
        exit(0);
      }
    }
  }
}
void consumer(void)
{
  int mutex_id, shm_id;
  struct BufferPool * bufp;
  char buf[BUFFER_SIZE + 1];

  mutex_id = semget(MUTEX_KEY, 1, IPC_CREAT|0666); //创建互斥信号量
  //  perror("consumer->semget");
  shm_id = shmget(SHM_KEY, sizeof(struct BufferPool), IPC_CREAT|0666);//创建共享内存
  //  perror("consumer->shmget");
  bufp = (struct BufferPool *)shmat(shm_id, NULL, 0);//共享内存映射到进程
  //  perror("consumer->shmat");

  int sleep_time = 0;
  while(1)
  {
    int i;
    semaphore_p(mutex_id);
    if (sleep_time > 10)
    {
      char ch;
      printf("\nq to quit[q/others]");
      scanf("%c", &ch);
      while(getchar()!='\n'); //清空输入
      if (ch == 'q')
      {
        semaphore_v(mutex_id);
        break;
      }
    }
    for (i = 0; i < BUFFER_NUM; i++)
    {
      if (bufp->Index[i] == 1)
      {
        //show_buf(bufp);//test
        strncpy(buf, bufp->Buffer[i], BUFFER_SIZE);
        bufp->Index[i] = 0;
        break;
      }
    }
    if (i == BUFFER_NUM) //buf没有资源，没有成功消费
    {
      semaphore_v(mutex_id);
      sleep(rand()%3);
      sleep_time++;
    }
    else
    {
      printf("%s", buf);
      write(filedes2, buf, BUFFER_SIZE);
      semaphore_v(mutex_id);
    }
  }
}
void show_buf(struct BufferPool * bufp)
{
  int i;
  for(i = 0; i < BUFFER_NUM; i++)
  {
    printf("number:%d\tBuffer:%lu\n", i, strlen(bufp->Buffer[i]));
    printf("Index:%d\nBuffer:%s\n", bufp->Index[i], bufp->Buffer[i]);
  }
}
