#include<sys/ipc.h> //IPC命名管道
#include<sys/shm.h> //共享存储
  //int shmget(key_t key, size_t size, int shmflg);得到共享内存
#include<sys/types.h>
  //int shmat(inst shm_id, const void *shm_addr, int shmflg);连接共享内存
  //void *shmdt(const void *shmaddr);断开共享内存
  //int shmctl(int shmid, int cmd, struct shmid_ds* buf);控制共享内存
#include<sys/sem.h> //信号量集

//三种IPC（Inter-Process Communication进程间通信）
//称为XSI(X/Open System Interface) IPC：消息队列 信号量 共享内存

//1.信号量 ：semaphore
  // 实质上是(资源)计数器
  // 只有两种操作P操作（申请资源）和V操作（释放资源）
  // 可以用与互斥(mutex)、资源计数(resource)、同步(特殊的互斥)
  // #include<sts/sem.h>
  // 创建或获取函数semget 从键获得标识符
  // 改变（PV操作）函数semop 用信号量标识符间接改变
    /*struct sembuf{
        unsigned short sem_num;//信号量的序号
        short          sem_op; //信号量的操作
        short          sem_flg;//信号量的操作标识
      }*/
  // 控制函数semctl 用信号量标识符间接控制
    /*union semun
    {
      int			val;	//信号量的值
      struct semid_ds *buf;	//信号量集合信息
      unsigned short  *array;//信号量值的数组
      struct seminfo  *__buf;//信号量限制信息
    };*/
  // 信号量是有限资源 程序退出仍然在系统中存在

//2.共享内存 ：shared memory
  //#include<sys/shm.h>
  //创建或获取函数shmget 从键获得标识符
  //连接函数shmat 进程将共享内存连接到它的地址空间函数
  //控制函数shmctl 用共享内存标识符间接控制
  //断接函数shmdt 进程将共享内存聪它的地址空间函数断开连接

//3.消息队列
  //#include<sys/msh.h>
