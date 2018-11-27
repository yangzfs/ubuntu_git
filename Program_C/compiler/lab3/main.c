#include<stdio.h>

const char * test_path = "/home/zwz/桌面/ubuntu_git/Program_C/compiler/lab3/test2.c";

extern int yyparse();
extern int yylex();
extern FILE* yyin;

int main(int argc, char const *argv[])
{
  //yyin = fopen(test_path, "r");
  //while(yylex());
  while(yyparse());
  printf("past!\n");
  /* int a = 1;*/
  return 0;
}
