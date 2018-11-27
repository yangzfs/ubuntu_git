#include "lab7"

#define MUTEX_KEY 0x1a0a
#define SHM_KEY   0x1a0b
#define BUFFER_NUM 5
#define BUFFER_SIZE 100

const char * producerN_path = "/home/zwz/桌面/ubuntu_git/Program_C/UNIX_Linux/lab7/producerN.txt";

struct BufferPool
{
  char Buffer[BUFFER_NUM][BUFFER_SIZE];
};
