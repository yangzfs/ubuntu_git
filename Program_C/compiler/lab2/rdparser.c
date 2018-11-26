#include<stdio.h>
#include<stdlib.h>
#include<string.h>

enum yyTokenType{ INT = 258, STR, RETURN, WHILE, VOID, IF, ELSE, PRINT, INTEGER
,FLOAT, STRING, IDENTIFIER, BOOL, SYMBOL, CHAR};

const char * test_path = "/home/zwz/windows/Users/12454/Desktop/linux/编译技术lab2/test.c";

typedef struct _ast
{
    int ivalue;
    char svalue[100];//可能需要修改
    char* nodeType;
    struct _ast* left;
    struct _ast* mid;//可能需要修改
    struct _ast* right;
}ast, *past;

extern int yylex();
extern int yylval;
extern char* yytext;
extern FILE* yyin;

#define SYMBOL_EQUALS              \
token==SYMBOL&&yytext[0]==


void advance();

past newAstNode();
past newINTEGER(int value);
past newSTRING(char* value);
past newIDENTIFIER(char* value);
past newINT();
past newSTR();
past newVOID();
past newIF(past left , past right);
past newWHILE(past left ,past right);
past newRETURN(past left);
past newPRINT(past left);
past newELSE(past left);
past newCMP(past left ,past right);
past newBOOL(past left ,past right);
past newList(past left ,past right);
past newExpr(int oper, past left,past right);
past newExtDecl(past t,past d,past ds);
past node_id_list();
past node_primary_expr();
past node_expr_list();
past node_mul_expr();
past node_add_expr();
past node_cmp_expr();
past node_expr();
past node_expression_statement();
past node_statement_list();
past node_statement();
past node_type();
past node_parameter();
past node_parameter_list();
past node_declarator();
past node_initializer();
past node_intstr_list();
past node_declarator_list();
past node_decl_or_stmt();
past node_external_declaration();
past node_program();
void showAst(past node, int nest);

int token;

int main(int argc, const char * argv[])
{
    // past rp = NULL;
    //
    // setbuf(stdout, NULL);
    // yyin = fopen(test_path, "r");
    // // advance();
    // // program();
    // // printf("PASS！\n");
    // rp = node_program();
    // printf("\n\n");
    // showAst(rp, 0);
    past a = NULL;
    while(1){
        printf("Please input expression!");
        a = node_program();
        showAst(a, 0);
    }
    printf("PASS！\n");

    return 0;
}

void advance()
{
  token = yylex();
  printf("\n<%d, %s>", token, yytext);
}

past newAstNode()
{
  past node =(past) malloc(sizeof(ast));
  if (node == NULL)
  {
    printf("ERROR: newAstNode");
    exit(0);
  }
  memset(node, 0, sizeof(ast));
  return node;
}
past newINTEGER(int value)
{
  past var = newAstNode();
  var -> nodeType = "INTEGER";
  var -> ivalue = value;
  return var;
}
past newSTRING(char* value)
{
  past var = newAstNode();
  var -> nodeType = "STRING";
  strcpy(var->svalue, value);
  return var;
}
past newIDENTIFIER(char* value)
{
  past var = newAstNode();
  var -> nodeType = "IDENTIFIER";
  strcpy(var->svalue, value);
  return var;
}
past newINT()
{
  past var = newAstNode();
  var -> nodeType = "INT";
  return var;
}
past newSTR()
{
  past var = newAstNode();
  var -> nodeType = "STR";
  return var;
}
past newVOID()
{
  past var = newAstNode();
  var -> nodeType = "VOID";
  return var;
}
past newIF(past left , past right)
{
  past var = newAstNode();
  var -> nodeType = "IF";
  var -> left = left;
  var -> right = right;
  return var;
}
past newWHILE(past left ,past right)
{
  past var = newAstNode();
  var -> nodeType = "WHILE";
  var -> left = left;
  var -> right = right;
  return var;
}
past newRETURN(past left)
{
  past var = newAstNode();
  var -> nodeType = "RETURN";
  var -> left = left;
  return var;
}
past newPRINT(past left)
{
  past var = newAstNode();
  var -> nodeType = "PRINT";
  var -> left = left;
  return var;
}
past newELSE(past left)
{
  past var = newAstNode();
  var -> nodeType = "ELSE";
  var -> left = left;
  return var;
}
past newCMP(past left ,past right)
{
  past var = newAstNode();
  var -> nodeType = "CMP";
  var -> left = left;
  var -> right = right;
  return var;
}
past newBOOL(past left ,past right)
{
  past var = newAstNode();
  var -> nodeType = "BOOL";
  var -> left = left;
  var -> right = right;
  return var;
}
past newList(past left ,past right)
{
  past var = newAstNode();
  var -> nodeType = "list";
  var -> left = left;
  var -> right = right;
  return var;
}
past newExpr(int oper, past left,past right)
{
  past var = newAstNode();
  var->nodeType = "expr";
  var->ivalue = oper;
  var->left = left;
  var->right = right;
  return var;
}
past newExtDecl(past t,past d,past ds)
{
  past var = newAstNode();
  var->nodeType = "external_declaration";
  var->left = t;
  var->mid = d;
  var->right = ds;
  return var;
}
past node_program()//1
{
  printf("1 ");//test1
  advance();
  past ext = node_external_declaration();
  past list = newList(NULL, ext);
  while(token != '\0')
  {
     ext = node_external_declaration();
     list = newList(list, ext);
  }
  return list;
}
past node_external_declaration()//2
{
  printf("2 ");//test2
  past result = NULL;
  past l = node_type();
  past m = node_declarator();
  past r = node_decl_or_stmt();

  result = newExtDecl(l, m, r);
  return result;
}
past node_decl_or_stmt()//3
{
  printf("3 ");//test3
  if (SYMBOL_EQUALS'{')
  {
    advance();
    if (SYMBOL_EQUALS'}')
    {
      advance();
      return NULL;
    }
    else
    {
      past result = node_statement_list();
      if (SYMBOL_EQUALS'}')
      {
        advance();
        return result;
      }
      else
      {
        printf("ERROR: node_decl_or_stmt 1\n");
        exit(0);
      }
    }
  }
  else if (SYMBOL_EQUALS',')
  {
    advance();
    past result = node_declarator_list();
    if (SYMBOL_EQUALS';')
    {
      advance();
      return result;
    }
    else
    {
      printf("ERROR: decl_or_stmt 2\n");
      exit(0);
    }
  }
  else if (SYMBOL_EQUALS';')
  {
    advance();
    return NULL;
  }
  else
  {
    printf("ERROR: decl_or_stmt 3\n");
    exit(0);
  }
}
past node_declarator_list()//4
{
  printf("4 ");//test4
  past result = newList(NULL, node_declarator());
  while(SYMBOL_EQUALS',')
  {
    advance();
    result = newList(result, node_declarator());
  }
  return result;
}
past node_intstr_list()//5
{
  printf("5 ");//test5
  past result = newList(NULL, node_declarator());
  while(SYMBOL_EQUALS',')
  {
    advance();
    result = newList(result, node_declarator());
  }
  return result;
}
past node_initializer()//6
{
  printf("6 ");//test6
  if (token == INTEGER)
  {
    past result = newINTEGER(atoi(yytext));
    advance();
    return result;
  }
  else if (token == STRING)
  {
    past result = newSTRING(yytext);
    advance();
    return result;
  }
  else
  {
    printf("ERROR: node_initializer\n");
    exit(0);
  }
}
past node_declarator()//7
{
  printf("7 ");//test7
  if (token == IDENTIFIER)
  {
    past r = newIDENTIFIER(yytext);
    advance();
    if (SYMBOL_EQUALS '(')
    {
      advance();
      if (SYMBOL_EQUALS ')')
      {
        advance();
        return r;
      }
      else
      {
        past result = newList(r, node_parameter_list());
        if (SYMBOL_EQUALS ')')
        {
          advance();
          return result;
        }
        else
        {
          printf("ERROR: node_declarator\n");
          exit(0);
        }
      }
    }
    else if (SYMBOL_EQUALS '[')
    {
      advance();
      if (SYMBOL_EQUALS ']')
      {
        advance();
        if (SYMBOL_EQUALS '=')
        {
          int oper = yytext[0];
          advance();
          if (SYMBOL_EQUALS '{')
          {
            advance();
            past result = newExpr(oper, r, node_intstr_list());
            if (SYMBOL_EQUALS '}')
            {
              advance();
              return result;
            }
          }
          else
          {
            printf("ERROR: node_declarator\n");
            exit(0);
          }
        }
        else
        {
          return r;
        }
      }
      else
      {
        past result = newList(r, node_expr());
        if (SYMBOL_EQUALS ']')
        {
          advance();
          if (SYMBOL_EQUALS '=')
          {
            int oper = yytext[0];
            advance();
            if (SYMBOL_EQUALS '{')
            {
              advance();
              result = newExpr(oper, result, node_intstr_list());
              if (SYMBOL_EQUALS '}')
              {
                advance();
                return result;
              }
            }
          }
          else
          {
            return result;
          }
        }
        else
        {
          printf("ERROR: declarator\n");
          exit(0);
        }
        if (SYMBOL_EQUALS '=')
        {
          advance();
          if (SYMBOL_EQUALS '{')
          {
            advance();
            node_intstr_list();
            if (SYMBOL_EQUALS '}') advance();
            else
            {
              printf("ERROR: node_declarator\n");
              exit(0);
            }
          }
          else
          {
            printf("ERROR: node_declarator\n");
            exit(0);
          }
        }
      }
    }
    else if (SYMBOL_EQUALS '=')
    {
      int oper = yytext[0];
      advance();
      past result = newExpr(oper, r, node_expr());
      return result;
    }
  }
  else
  {
    printf("ERROR: node_declarator\n");
    exit(0);
  }
}
past node_parameter_list()//8
{
  printf("8 ");//test8
  past result = newList(NULL, node_parameter());
  while(SYMBOL_EQUALS ',')
  {
    advance();
    result = newList(result, node_parameter());
  }
  return result;
}
past node_parameter()//9
{
  printf("9 ");//test9
  if (token == INT || token == STR || token == VOID)
  {
    past result = node_type();
    if (token == IDENTIFIER)
    {
      result = newList(result, newIDENTIFIER(yytext));
      advance();
      return result;
    }
    else
    {
      printf("ERROR: node_parameter\n");
      exit(0);
    }
  }
}
past node_type()//10
{
  printf("10 ");//test10
  if (token == INT)
  {
    advance();
    past result = newINT();
    return result;
  }
  else if (token == STR)
  {
    advance();
    past result = newSTR();
    return result;
  }
  else if (token == VOID)
  {
    advance();
    past result = newVOID();
    return result;
  }
  else
  {
    printf("ERROR: type\n");
    exit(0);
  }
}
past node_statement()//11
{
  printf("11 ");//test11
  if (token == IF)
  {
    advance();
    if (SYMBOL_EQUALS '(')
    {
      advance();
      past t = node_expr();
      if (SYMBOL_EQUALS ')')
      {
        advance();
        past s1 = node_statement();
        past result = newIF(t, s1);
        if (token == ELSE)
        {
          advance();
          past s2 = newELSE(node_statement());
          result = newList(result, s2);
          return result;
        }
        else
        {
          return result;
        }
      }
      else
      {
        printf("ERROR: statement 1\n");
        exit(0);
      }
    }
  }
  else if (token == WHILE)
  {
    advance();
    if (SYMBOL_EQUALS '(')
    {
      advance();
      past t = node_expr();
      if (SYMBOL_EQUALS ')')
      {
        advance();
        past result = newWHILE(t, node_statement());
        return result;
      }
      else
      {
        printf("ERROR: statement 2\n");
        exit(0);
      }
    }
    else
    {
      printf("ERROR: statement 3\n");
      exit(0);
    }
  }
  else if (token == RETURN)
  {
    advance();
    if (SYMBOL_EQUALS ';')
    {
      advance();
      past result = newRETURN(NULL);
      return result;
    }
    else
    {
      past result = newRETURN(node_expr());
      if (SYMBOL_EQUALS ';')
      {
        advance();
        return result;
      }
      else
      {
        printf("ERROR: statement 4\n");
        exit(0);
      }
    }
  }
  else if (token == PRINT)
  {
    advance();
    if (SYMBOL_EQUALS ';')
    {
      advance();
      past result = newPRINT(NULL);
      return result;
    }
    else
    {
      past result = newPRINT(node_expr_list());
      if (SYMBOL_EQUALS ';')
      {
        advance();
        return result;
      }
      else
      {
        printf("ERROR: statement 5\n");
        exit(0);
      }
    }
  }
  else if (SYMBOL_EQUALS '{')
  {
    advance();
    past result = newList(NULL, node_statement_list());
    if (SYMBOL_EQUALS '}')
    {
      advance();
      return result;
    }
    else
    {
      printf("ERROR: statement 6\n");
      exit(0);
    }
  }
  else if (token == INT)
  {
    advance();
    past result = newList(newINT(), node_declarator_list());
    if (SYMBOL_EQUALS ';')
    {
      advance();
      return result;
    }
    else
    {
      printf("ERROR: statement 7\n");
      exit(0);
    }
  }
  else if (token == STR)
  {
    advance();
    past result = newList(newSTR(), node_declarator_list());
    if (SYMBOL_EQUALS ';')
    {
      advance();
      return result;
    }
    else
    {
      printf("ERROR: statement 7\n");
      exit(0);
    }
  }
  else if (token == VOID)
  {
    advance();
    past result = newList(newVOID(), node_declarator_list());
    if (SYMBOL_EQUALS ';')
    {
      advance();
      return result;
    }
    else
    {
      printf("ERROR: statement 7\n");
      exit(0);
    }
  }
  else
  {
    past result = node_expression_statement();
    return result;
  }
}
past node_statement_list()//12
{
  printf("12 ");//test12
  past ext = node_statement();
  past list = newList(NULL, ext);
  while( !(SYMBOL_EQUALS '}') )
  {
    ext = node_statement();
    list = newList(list, ext);
  }
  return list;
}
past node_expression_statement()//13
{
  printf("13 ");//test13
  if (SYMBOL_EQUALS ';')
  {
    advance();
    return NULL;
  }
  else
  {
    past result = newList(NULL, node_expr());
    if (SYMBOL_EQUALS ';')
    {
      advance();
      return result;
    }
    else
    {
      printf("ERROR: expression_statement\n");
      exit(0);
    }
  }
}
past node_expr()//14
{
  printf("14 ");//test14
  past result = newList(NULL, node_cmp_expr());
  return result;
}
past node_cmp_expr()//15
{
  printf("15 ");//test15
  past result = newList(NULL, node_add_expr());
  while ( (SYMBOL_EQUALS '<') || (SYMBOL_EQUALS '>') )
  {
    advance();
    result = newCMP(result, node_add_expr());
  }
  return result;
}
past node_add_expr()//16
{
  printf("16 ");//test16
  past result = newList(NULL, node_mul_expr());
  while( (SYMBOL_EQUALS '+') || (SYMBOL_EQUALS '-') )
  {
    advance();
    result = newList(result, node_mul_expr());
  }
  return result;
}
past node_mul_expr()//17
{
  printf("17 ");//test11
  if (SYMBOL_EQUALS '-')
  {
    advance();
    past result = newList(NULL, node_primary_expr());
    return result;
  }
  else
  {
    past result = newList(NULL, node_primary_expr());
    while((SYMBOL_EQUALS '*') || (SYMBOL_EQUALS '/') || (SYMBOL_EQUALS '%'))
    {
      advance();
      result = newList(result, node_primary_expr());
    }
    return result;
  }
}
past node_expr_list()//18
{
  printf("18 ");//test11
  past result = newList(NULL, node_expr());
    while (SYMBOL_EQUALS ',')
    {
        advance();
        result = newList(result, node_expr());
    }
    return result;
}
past node_id_list()//19
{
  printf("19");//test11
  if (token == IDENTIFIER)
  {
    past result = newList(NULL, newIDENTIFIER(yytext));
    advance();
    while(SYMBOL_EQUALS ',')
    {
      advance();
      past result = newList(result, newIDENTIFIER(yytext));
      advance();
    }
    return result;
  }
  else
  {
    printf("ERROR: id_list\n");
    exit(0);
  }
}
past node_primary_expr()//20
{
  printf("20 ");//test11
  if (token == INTEGER)
  {
    past result = newList(NULL, newINTEGER(atoi(yytext)));
    advance();
    return result;
  }
  else if (SYMBOL_EQUALS '(')
  {
    advance();
    past result = newList(NULL, node_expr());
    advance();
    if (SYMBOL_EQUALS ')')//可能需要修改
    {
      advance();
      return result;
    }
    else
    {
      printf("ERROR: primary_expr\n");
      exit(0);
    }
  }
  else if (token == IDENTIFIER)
  {
    past result = newList(NULL, newIDENTIFIER(yytext));
    advance();
    if (SYMBOL_EQUALS '=')
    {
      int oper = yytext[0];
      advance();
      result = newExpr(oper, result, node_expr());
      return result;
    }
    else if (SYMBOL_EQUALS '[')
    {
      advance();
      result = newList(result, node_expr());
      advance();
      if (SYMBOL_EQUALS '=')
      {
        int oper = yytext[0];
        advance();
        result = newExpr(oper, result, node_expr());
        return result;
      }
    }
    else if (SYMBOL_EQUALS '(')
    {
      advance();
      if (SYMBOL_EQUALS ')')
      {
        advance();
        return result;
      }
      else
      {
        result = newList(result, node_expr_list());
        if (SYMBOL_EQUALS ')')
        {
          advance();
          return result;
        }
        else
        {
          printf("ERROR: primary_expr\n");
          exit(0);
        }
      }
    }
    else if (token == BOOL)
    {
      advance();
      result = newBOOL(result, node_expr());
      return result;
    }
  }
  else if (token == STRING)
  {
    past result = newList(NULL, newSTRING(yytext));
    advance();
    return result;
  }
  else
  {
    printf("ERROR: node_primary_expr");
    exit(0);
  }
}

void showAst(past node, int nest)
{
  if(node == NULL) return;
  if(strcmp(node->nodeType, "INTEGER") == 0)
  {
    int i = 0;
    for(i = 0; i < nest; i ++) printf("  ");
    printf("%s %d\n", node->nodeType,node->ivalue);
  }
  else if(strcmp(node->nodeType, "expr") == 0)
  {
    int i = 0;
    for(i = 0; i < nest; i ++) printf("  ");
    printf("%s '%c'\n", node->nodeType, (char)node->ivalue);
  }
  else if(strcmp(node->nodeType, "WHILE") == 0)
  {
    int i = 0;
    for(i = 0; i < nest; i ++) printf("  ");
    printf("%s\n", node->nodeType);
  }
  else if(strcmp(node->nodeType, "RETURN") == 0)
  {
    int i = 0;
    for(i = 0; i < nest; i ++) printf("  ");
    printf("%s\n", node->nodeType);
  }
  else if(strcmp(node->nodeType, "PRINT") == 0)
  {
    int i = 0;
    for(i = 0; i < nest; i ++) printf("  ");
    printf("%s\n", node->nodeType);
  }
  else if(strcmp(node->nodeType, "INT") == 0)
  {
    int i = 0;
    for(i = 0; i < nest; i ++) printf("  ");
    printf("%s\n", node->nodeType);
  }
  else if(strcmp(node->nodeType, "STR") == 0)
  {
    int i = 0;
    for(i = 0; i < nest; i ++) printf("  ");
    printf("%s\n", node->nodeType);
  }
  else if(strcmp(node->nodeType, "VOID") == 0)
  {
    int i = 0;
    for(i = 0; i < nest; i ++) printf("  ");
    printf("%s\n", node->nodeType);
  }
  else if(strcmp(node->nodeType, "IF") == 0)
  {
    int i = 0;
    for(i = 0; i < nest; i ++) printf("  ");
    printf("%s\n", node->nodeType);
  }
  else if(strcmp(node->nodeType, "BOOL") == 0)
  {
    int i = 0;
    for(i = 0; i < nest; i ++) printf("  ");
    printf("%s\n", node->nodeType);
  }
  else if(strcmp(node->nodeType, "ELSE") == 0)
  {
    int i = 0;
    for(i = 0; i < nest; i ++) printf("  ");
    printf("%s\n", node->nodeType);
  }
  else if(strcmp(node->nodeType, "CMP") == 0)
  {
    int i = 0;
    for(i = 0; i < nest; i ++) printf("  ");
    printf("%s\n", node->nodeType);
  }
  else if(strcmp(node->nodeType, "STRING") == 0)
  {
    int i = 0;
    for(i = 0; i < nest; i ++) printf("  ");
    printf("%s %s\n", node->nodeType, node->svalue);
  }
  else if(strcmp(node->nodeType, "IDENTIFIER") == 0)
  {
    int i = 0;
    for(i = 0; i < nest; i ++) printf("  ");
    printf("%s %s\n", node->nodeType, node->svalue);
  }
  else
  showAst(node->left, nest+1);
  showAst(node->mid, nest+1);
  showAst(node->right, nest+1);
}
