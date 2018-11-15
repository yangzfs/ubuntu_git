#include<stdio.h>
#include<stdlib.h>

typedef struct stuinfo{
  char stuName[16]; //学生姓名
  int Age;  //年龄
}ElemType;
typedef struct node{
  ElemType data;
  struct node *next;
}ListNode,*ListPtr;

ListPtr CreateList(void);
ListPtr ListHead;
void PrintList(void);
void InsertList(void);
void FreeList(void);

int main(int argc,char *argv[])
{
  while(1)
  {
    printf("******************************************************\n"); //分隔符
    printf("1 Create List\t");
    printf("2 printf List\t");
    printf("3 Insert List\t");
    printf("4 Quit\n");
    printf("******************************************************\n"); //分隔符
    char command = getchar();
  //  printf("\n输入：%c\n" , command);
    while (getchar()!='\n'); //清除缓冲区内的输入
    switch (command) {
      case '1': ListHead = CreateList();
      break;
      case '2': PrintList();
      break;
      case '3': InsertList();
      break;
      case '4': FreeList();return 0;
      default : printf("Wrong Input\n");
    }
  }
}
ListPtr CreateList()
{
  ListPtr p = (ListPtr)malloc(sizeof (ListNode)); //大小应是节点而非节点指针的大小
  p->next = NULL;
  return p;
}
void PrintList()
{
  ListPtr p = ListHead->next;
  while(p!=NULL)
  {
    printf("Name:%s Age:%d\n" , p->data.stuName,p->data.Age);
    p = p->next;
  }
}
void InsertList()
{
  ElemType e;
  ListPtr p = (ListPtr)malloc(sizeof (ListNode));
  printf("Input student's name\n");
  scanf("%s", e.stuName);
//  printf("\n输入：%s\n\n" , e.stuName);
    while (getchar()!='\n'); //清除缓冲区内的输入
  printf("Input student's age\n");
  scanf("%d", &e.Age);
//  printf("\n输入: %d\n\n",  e.Age);
    while (getchar()!='\n'); //清除缓冲区内的输入
  p->data = e;
  p->next = ListHead -> next;
  ListHead -> next = p;
}
void FreeList(void)
{
  ListPtr p = ListHead , pn;
  do
  {
    pn = p->next;
    free(p);
    p = pn;
  }while(p!=NULL);
}
