#include"lab6.h"
#include<stdio.h>
#define PH_NUM 10

pthread_mutex_t mlock[PH_NUM];

void *philosopher(void * arg);
void philosopher_create(void);

void chopstick_init(void);
void chopstick_destroy(void);

void takechopstick(int number);
void putchopstick(int number);

int server(int number);

int main(int argc, char const *argv[])
{
  chopstick_init();
  philosopher_create();
  chopstick_destroy();

  return 0;
}

void *philosopher(void * arg)
{
  int number = *(int *)arg;
  while(1)
  {
    printf("philosopher %d is thinking\n", number);
    sleep(2);
    while(1)
    {
      if (server(number) == 0)                          //plan b
      {
        takechopstick(number);
        takechopstick( (number + 1) % PH_NUM);
        break;
      }
      else
        sleep(1);
      //takechopstick(number);
    //  if (pthread_mutex_trylock( &mlock[(number + 1) % PH_NUM] ) == 0 )   //plan a
    //  {
    //    putchopstick(number);
    //    sleep(1.5);
    //    continue;
    //  }
    //  break;
    }
    //takechopstick((number + 1) % PH_NUM);
    printf("philosopher %d is eating\n", number);
    putchopstick(number);
    putchopstick((number + 1) % PH_NUM );
  }
}
void philosopher_create(void)
{
  pthread_t ph_tid[PH_NUM];
  int num[PH_NUM];
  int i;

  for (i = 0; i < PH_NUM; i++)
    num[i] = i;
  for (i = 0; i < PH_NUM; i++)
    pthread_create(&ph_tid[i], NULL, philosopher, &num[i]);

  pthread_join(ph_tid[0], NULL);
}
void chopstick_init(void)
{
  int i;
  for (i = 0; i < PH_NUM; i++)
  {
    pthread_mutex_init(&mlock[i], NULL);
  }
}
void chopstick_destroy(void)
{
  int i;
  for (i = 0; i < PH_NUM; i++)
    pthread_mutex_destroy(&mlock[i]);
}
void takechopstick(int number)
{
  pthread_mutex_lock(&mlock[number]);
}
void putchopstick(int number)
{
  pthread_mutex_unlock(&mlock[number]);
}
int server(int number)
{
  if (mlock[number].__data.__count == 0 && mlock[number].__data.__count == 0)
    return 0;
  else
    return 1;
}
