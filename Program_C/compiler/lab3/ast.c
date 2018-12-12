#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include "ast.h"

void showAst(past node, int nest)
{
  if(node == NULL)
		return;

	int i = 0;
	for(i = 0; i < nest; i ++)
		printf("\t");
	if(strcmp(node->nodeType, "TYPE") == 0){
		printf("%s %s\n", node->nodeType, node->svalue);}
  else if (strcmp(node->nodeType, "ID") == 0){
    printf("%s %s\n", node->nodeType, node->svalue);}
  else if (strcmp(node->nodeType, "NUMBER") == 0){
    printf("%s %d\n", node->nodeType, node->ivalue);}
  else if (strcmp(node->nodeType, "STRING") == 0){
    printf("%s %s\n", node->nodeType, node->svalue);}
  else if (strcmp(node->nodeType, "+") == 0){
    printf("SYMBOL %s\n", node->nodeType); }
    else if (strcmp(node->nodeType, "-") == 0){
      printf("SYMBOL %s\n", node->nodeType);}
      else if (strcmp(node->nodeType, "*") == 0){
        printf("SYMBOL %s\n", node->nodeType);}
        else if (strcmp(node->nodeType, "/") == 0){
          printf("SYMBOL %s\n", node->nodeType);}
          else if (strcmp(node->nodeType, "=") == 0){
            printf("SYMBOL %s\n", node->nodeType);}
            else if (strcmp(node->nodeType, "<") == 0){
              printf("SYMBOL %s\n", node->nodeType);}
              else if (strcmp(node->nodeType, ">") == 0){
                printf("SYMBOL %s\n", node->nodeType);}
                else if (strcmp(node->nodeType, "==") == 0){
                  printf("SYMBOL %s\n", node->nodeType);}
    else if (strcmp(node->nodeType, "RETURN") == 0){
      printf("%s\n", node->nodeType);}
      else if (strcmp(node->nodeType, "WHILE") == 0){
        printf("%s\n", node->nodeType);}
        else if (strcmp(node->nodeType, "PRINT") == 0){
          printf("%s\n", node->nodeType);}
          else if (strcmp(node->nodeType, "IF") == 0){
            printf("%s\n", node->nodeType);}
            else if (strcmp(node->nodeType, "ELSE") == 0){
              printf("%s\n", node->nodeType);}
    else nest--;
    showAst(node->left, nest+1);
	  showAst(node->right, nest+1);
}

past newAstNode(void)
{
  //perror("newAstNode");
  past node =(past) malloc(sizeof (struct _ast));
  if(node == NULL)
  {
    printf("run out of memory.\n");
    exit(0);
  }
  memset(node, 0, sizeof(struct _ast));
  return node;
}
past new_sval(char * sval, char * type)
{
//  perror("new_sval");
  past var = newAstNode();
  var->nodeType = (char *)malloc(sizeof (type));
  var->svalue   = (char *)malloc(sizeof (sval));
  strcpy(var->nodeType, type);
  strcpy(var->svalue, sval);
  return var;
}
past new_ival(int ival, char * type)
{
//  perror("new_ival");
  past var = newAstNode();
  var->nodeType = (char *)malloc(sizeof (type));
  strcpy(var->nodeType, type);
  var->ivalue = ival;
  return var;
}
past new_tree(past left, past right, char * type)
{
//  perror("new_tree");
  past var = newAstNode();
  var->nodeType = (char *)malloc(sizeof (type));
  strcpy(var->nodeType, type);
  var->left = left;
  var->right = right;
  return var;
}
