#include<unistd.h>//P6 char *getcwd(char*buf,size_t size) buf需要释放
                  //P6 char *get_current_dir_name(void) buf需要释放 ??
#include<dirent.h>//P7 DIR * opendir(const char *name)
                  //P7 int closedir(DIR *dir)
#include<sys/types.h>
#include<dirent.h>//P8 struct dirent * readdir(DIR * dir)
/* struct dirent
// {
//   ino_t d_ino; i节点号
//   off_t d_off;
//   usigned short d_reclen;
//   usigned char d_type;
//   char d_name[256]
// };
*/
#include<sys/stat.h>
// int stat(const char*path, struct stat*buf); 读取链接的文件属性
// int lstat(const char*path, struct stat*buf); 读取文件属性
// struct stat {
//   mode_t     st_mode;    文件类型与访问权限
//   ino_t      st_ino;     i节点号
//   dev_t      st_dev;     文件使用的设备号
//   dev_t      st_rdev;    设备文件的设备号
//   nlink_t    st_nlink;   文件的硬链接数
//   uid_t      st_uid;     文件所有者用户ID
//   gid_t      st_gid;     文件所有者组ID
//   off_t      st_size;    文件大小（以字节为单位）
//   time_t     st_atime;   最后一次访问该文件的时间
//   time_t     st_mtime;   最后一次修改该文件的时间
//   time_t     st_ctime;   最后一次改变该文件状态的时间
//   blksize_t st_blksize;  包含该文件的磁盘块的大小
//   blkcnt_t   st_blocks;  该文件所占的磁盘块数
// };
// 是否为普通文件:		S_ISREG(st_mode)
// 是否为目录文件		S_ISDIR(st_mode)
// 是否为字符设备	          S_ISCHR(st_mode)
// 是否为块设备		S_ISBLK(st_mode)
// 是否为FIFO		S_ISFIFO(st_mode)
// 是否为套接字		S_ISSOCK(st_mode)
// 是否为符号连接		S_ISLNK(st_mode)  S_ISLINK是错误的
// S_IRWXU     00700     文件所有者的权限值组合
// S_IRUSR     00400       文件所有者具可读取权限
// S_IWUSR     00200      文件所有者具可写入权限
// S_IXUSR     00100       文件所有者具可执行权限
// S_IRWXG     00070      用户组的权限值组合
// S_IRGRP     00040       用户组具可读取权限
// S_IWGRP     00020      用户组具可写入权限
// S_IXGRP     00010       用户组具可执行权限
// S_IRWXO     00007      其他用户的权限值组合
// S_IROTH     00004       其他用户具可读取权限
// S_IWOTH     00002      其他用户具可写入权限
// S_IXOTH     00001       其他用户具可执行权限
#include<pwd.h>//P16 struct passwd* getpwuid(uid_t uid)  输入用户id，返回用户属性信息
// struct passwd{
//       char *pw_name;       /* 用户名*/
//       char *pw_passwd;     /* 密码.*/
//       __uid_t pw_uid;      /* 用户ID.*/
//       __gid_t pw_gid;      /*组ID.*/
//       char *pw_gecos;      /*真实名*/
//       char *pw_dir;        /* 主目录.*/
//       char *pw_shell;      /*使用的shell*/};
#include<grp.h>//P17 struct group*getgrgid(gid_t gid); 输出用户组id，返回用户组属性信息
// struct group{
//   char *gr_name; /*组名称*/
//   char *gr_passwd; /* 组密码*/
//   gid_t gr_gid; /*组ID*/
//   char **gr_mem; /*组成员账号*/ }
#include<time.h>//struct tm* localtiome(const time_t*lock)
                //char * ctime(const time_t*timep)
