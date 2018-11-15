#include"lab5.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

const char * destination = "/home/zwz/桌面/backup";

void * myls(void * arg);
void * mycp(void * arg);

int main(int argc, char const *argv[]) {
  pthread_t ls_tid;
  char *buf = NULL;

  buf = getcwd(NULL,0);

  pthread_create(&ls_tid, NULL, myls, buf);
  pthread_join(ls_tid,NULL);

  return 0;
}

void * myls(void * arg)
{
  DIR * currentdir;
  struct dirent * currentdp;
  struct stat currentstat;
  if ( (currentdir = opendir((char *)arg)) == NULL)
  {
    printf("ERROR:open directory fail\n");
    return 0;
  }
  while((currentdp = readdir(currentdir)) != NULL)
  {
    pthread_t cp_tid, ls_tid;
    if (currentdp->d_name[0] != '.')
    {
      char * path = (char *)malloc(strlen((char *)arg)+1+strlen(currentdp->d_name)+1);
      sprintf(path, "%s/%s", (char *)arg, currentdp->d_name);
      if (stat(path, &currentstat) == -1)
      {
        printf("get stat error\n");
        continue;
      }
      if (S_ISDIR(currentstat.st_mode))
      {
        pthread_create(&ls_tid, NULL, myls, path);
        pthread_join(ls_tid,NULL);
      }
      else if (S_ISREG(currentstat.st_mode))
      {
        pthread_create(&cp_tid, NULL, mycp, path);
        pthread_join(cp_tid, NULL);
      }
      else
      {
        printf("ERROR:%s\n", currentdp->d_name);
        continue;
      }
    }
  }
  closedir(currentdir);
  return 0;
}
void * mycp(void * arg)
{
  struct stat st;
  int i = strlen((char*)arg), j = 0;
  char * dname = (char *)malloc(i);
  char * path1 = (char *)malloc(strlen((char *)arg));
  char * path2 = (char *)malloc(strlen((char *)arg) + strlen(destination));
  char * buf = NULL;
  int excl, filedes1, filedes2;

  strcpy(path1, (char *)arg);
  while(path1[i] != '/') i--;
  while(path1[i] != '\0')
  {
    dname[j] = path1[i];
    i++;j++;
  }
  dname[j] = '\0';
  sprintf(path2, "%s%s", destination, dname);

  stat(path1, &st);
  buf = (char *)malloc (st.st_size);
  excl = open(path2, O_CREAT|O_EXCL, 00777&st.st_mode);

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
        filedes2 = open(path2,O_RDWR|O_TRUNC); //覆盖
        break;
      }
      else if (ch == 'm' || ch == 'M')
      {
        filedes2 = open(path2,O_RDWR|O_APPEND); //合并
        break;
      }
      else
        puts("error input!");
    }
  }
  else
    filedes2 = open(path2,O_RDWR); //文件不存在的情况
  filedes1 = open(path1,O_RDONLY);
  read(filedes1, buf, st.st_size);
  write(filedes2, buf, st.st_size);
  close(filedes1);
  close(filedes2);

  return 0;
}
