#include "myls.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void printf_type(mode_t mode);
void printf_perm(mode_t mode);
void printf_link(nlink_t nlink);
void printf_usrname(uid_t uid);
void printf_grname(gid_t gid);
void printf_time(time_t mtime);
void printf_filename(struct dirent * dp);

int main(int argc, char const *argv[]) {
  char * buf;
  DIR * currentdir;
  struct dirent * currentdp;
  struct stat currentstat;

  int flaga, flagH, flagA; flaga = flagH = flagA = 0;
  int i;
  for(i = 1; argv[i] != NULL; i++) //有参数
  {
    if (strcmp(argv[i],"-a") == 0)
      flaga = 1;
    else if (strcmp(argv[i],"-H") == 0)
      flagH = 1;
    else if (strcmp(argv[i],"-A") == 0)
      flagA = 1;
    else
    {
      printf("no such parameter : %s\n", argv[i]);
      exit(0);
    }
  }
  if ( (buf = getcwd(NULL,0)) != NULL)
    printf("%s\n",buf);
  if ( (currentdir = opendir(buf)) == NULL)
  {
    printf("open directory fail\n");
    return 0;
  }
  while((currentdp = readdir(currentdir)) != NULL)
  {
    if (flagA == 1)
    {
      if (strcmp(currentdp->d_name,".") == 0)
        continue;
      if (strcmp(currentdp->d_name,"..") == 0)
        continue;
    }
    if(currentdp->d_name[0] != '.' || flaga == 1) //参数-a显示.
    {
      char * path = (char *)malloc (strlen(buf) +1+ strlen(currentdp->d_name));
      strcpy(path , buf);
      strcat(path , "/");
      strcat(path , currentdp->d_name);
      if (stat(path,&currentstat) == -1)
      {
        printf("get stat error\n");
        continue;
      }
      if (flagH == 1)
      {
        lstat(path,&currentstat);
      }//参数-H显示符号链接
      printf_type(currentstat.st_mode);
      printf_perm(currentstat.st_mode);
      printf_link(currentstat.st_nlink);
      printf_usrname(currentstat.st_uid);
      printf_grname(currentstat.st_gid);
      printf_time(currentstat.st_mtime);
      printf_filename(currentdp);
    }
  }
  closedir(currentdir);
  return 0;
}
void printf_type(mode_t mode)
{
  if (S_ISREG(mode))
    printf("-");
  else if (S_ISDIR(mode))
    printf("d");
  else if (S_ISCHR(mode))
    printf("c");
  else if (S_ISBLK(mode))
    printf("b");
  else if (S_ISFIFO(mode))
    printf("p");
  else if (S_ISLNK(mode))
    printf("l");
  else if (S_ISSOCK(mode))
    printf("s");
  else
    printf("TYPE ERROR!\n");
}
void printf_perm(mode_t mode)
{
  if ((S_IRUSR&mode) == S_IRUSR)
    printf("r");
  else
    printf("-");
  if ((S_IWUSR&mode) == S_IWUSR)
    printf("w");
  else
    printf("-");
  if ((S_IXUSR&mode) == S_IXUSR)
    printf("x");
  else
    printf("-");

  if ((S_IRGRP&mode) == S_IRGRP)
    printf("r");
  else
    printf("-");
  if ((S_IWGRP&mode) == S_IWGRP)
    printf("w");
  else
    printf("-");
  if ((S_IXGRP&mode) == S_IXGRP)
    printf("x");
  else
    printf("-");

  if ((S_IROTH&mode) == S_IROTH)
    printf("r");
  else
    printf("-");
  if ((S_IWOTH&mode) == S_IWOTH)
    printf("w");
  else
    printf("-");
  if ((S_IXOTH&mode) == S_IXOTH)
    printf("x");
  else
    printf("-");
}
void printf_link(nlink_t nlink)
{
  printf(" %lu", nlink);
}
void printf_usrname(uid_t uid)
{
  struct passwd *usr = getpwuid(uid);
  printf(" %s", usr->pw_name);
}
void printf_grname(gid_t gid)
{
  struct group *group = getgrgid(gid);
  printf(" %s", group->gr_name);
}
void printf_time(time_t mtime)
{
  struct tm * tp = localtime(&mtime);
  //char * tp2 = ctime(&mtime);
  //printf(" %s", tp2);
  printf(" %d-%d-%d ", tp->tm_year+1900, tp->tm_mon+1, tp->tm_mday);
}
void printf_filename(struct dirent * dp)
{
  printf(" %s\n", dp->d_name);
}
// 获取当前工作目录路径
// 打开目录
// 读取目录文件
// while 没有到达目录结尾
// 获取文件属性
// 解析文件属性
// 输出文件属性与文件名
// 关闭目录
