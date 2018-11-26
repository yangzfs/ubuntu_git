#include<stdio.h>
#include<stdlib.h>

enum yyTokenType{ INT = 258, STR, RETURN, WHILE, VOID, IF, ELSE, PRINT, INTEGER
,FLOAT, STRING, IDENTIFIER, BOOL, SYMBOL, CHAR};

const char * test_path = "/home/zwz/windows/Users/12454/Desktop/linux/编译技术lab2/test.c";

extern int yylex();
extern int yylval;
extern char* yytext;
extern FILE* yyin;

#define SYMBOL_EQUALS              \
token==SYMBOL&&yytext[0]==

void advance();
void program();
void external_declaration();
void decl_or_stmt();
void declarator_list();
void intstr_list();
void initializer();
void declarator();
void parameter_list();
void parameter();
void type();
void statement();
void statement_list();
void expression_statement();
void expr();
void cmp_expr();
void add_expr();
void mul_expr();
void primary_expr();
void expr_list();
void id_list();

int token;

int main(int argc, const char * argv[])
{
    setbuf(stdout, NULL);
    yyin = fopen(test_path, "r");
    advance();
    program();
    printf("PASS！\n");
    return 0;
}

void advance()
{
  token = yylex();
  printf("<%d, %s>\n", token, yytext);
}
void program()
{
  external_declaration();
  while(token != '\0') external_declaration();
}
void external_declaration()
{
  type();
  declarator();
  decl_or_stmt();
}

void decl_or_stmt()
{
  if (SYMBOL_EQUALS'{')
  {
    advance();
    if (SYMBOL_EQUALS'}')
      advance();
    else
    {
      statement_list();
      if (SYMBOL_EQUALS'}')
        advance();
      else
      {
        printf("ERROR: decl_or_stmt\n");
        exit(0);
      }
    }
  }
  else if (SYMBOL_EQUALS',')
  {
    advance();
    declarator_list();
    if (SYMBOL_EQUALS';')
      advance();
    else
    {
      printf("ERROR: decl_or_stmt\n");
      exit(0);
    }
  }
  else if (SYMBOL_EQUALS';')
    advance();
  else
  {
    printf("ERROR: decl_or_stmt!\n");
    exit(0);
  }
}
void declarator_list()
{
  declarator();
  while(SYMBOL_EQUALS',')
  {
    advance();
    declarator();
  }
}
void intstr_list()
{
  initializer();
  while(SYMBOL_EQUALS',')
  {
    advance();
    initializer();
  }
}
void initializer()
{
  if (token == INTEGER || token == STRING) advance();
  else
  {
    printf("ERROR: initializer\n");
    exit(0);
  }
}
void declarator()
{
  if (token == IDENTIFIER)
  {
    advance();
    if (SYMBOL_EQUALS '(')
    {
      advance();
      if (SYMBOL_EQUALS ')')
      {
        advance();
      }
      else
      {
        parameter_list();
        if (SYMBOL_EQUALS ')')
        {
          advance();
        }
        else
        {
          printf("ERROR: declarator\n");
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
          advance();
          if (SYMBOL_EQUALS '{')
          {
            advance();
            intstr_list();
            if (SYMBOL_EQUALS '}') advance();
            else
            {
              printf("ERROR: declarator\n");
              exit(0);
            }
          }
        }
        else
        {
          printf("ERROR: declarator\n");
          exit(0);
        }
      }
      else
      {
        expr();
        if (SYMBOL_EQUALS ']') advance();
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
            intstr_list();
            if (SYMBOL_EQUALS '}') advance();
            else
            {
              printf("ERROR: declarator\n");
              exit(0);
            }
          }
          else
          {
            printf("ERROR: declarator\n");
            exit(0);
          }
        }
      }
    }
    else if (SYMBOL_EQUALS '=')
    {
      advance();
      expr();
    }
  }
  else
  {
    printf("ERROR: declarator\n");
    exit(0);
  }
}
void parameter_list()
{
  parameter();
  while(SYMBOL_EQUALS ',')
  {
    advance();
    parameter();
  }
}
void parameter()
{
  type();
  if (token == IDENTIFIER) advance();
  else
  {
    printf("ERROR: parameter\n");
    exit(0);
  }
}
void type()
{
  if (token == INT || token == STR || token == VOID) advance();
  else
  {
    printf("ERROR: type\n");
    exit(0);
  }
}

void statement()
{
  if (token == IF)
  {
    advance();
    if (SYMBOL_EQUALS '(')
    {
      expr();
      if (SYMBOL_EQUALS ')')
      {
        advance();
        statement();
        if (token == ELSE)
        {
          advance();
          statement();
        }
      }
      else
      {
        printf("ERROR: statement 1\n");
        exit(0);
      }
    }
  }
  else if (token == WHILE)  //有问题
  {
    advance();
    if (SYMBOL_EQUALS '(')
    {
      expr();
      if (SYMBOL_EQUALS ')')
      {
        advance();
        statement();
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
    if (SYMBOL_EQUALS ';') advance();
    else
    {
      expr();
      if (SYMBOL_EQUALS ';') advance();
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
    if (SYMBOL_EQUALS ';') advance();
    else
    {
      expr_list();
      if (SYMBOL_EQUALS ';') advance();
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
    statement_list();
    if (SYMBOL_EQUALS '}') advance();
    else
    {
      printf("ERROR: statement 6\n");
      exit(0);
    }
  }
  else if (token == INT || token == STR || token == VOID)
  {
    advance();
    declarator_list();
    if (SYMBOL_EQUALS ';') advance();
    else
    {
      printf("ERROR: statement 7\n");
      exit(0);
    }
  }
  else expression_statement();
}
void statement_list()
{
  statement();
  while( !(SYMBOL_EQUALS '}') ) statement();
}
void expression_statement()
{
  if (SYMBOL_EQUALS ';') advance();
  else
  {
    expr();
    if (SYMBOL_EQUALS ';') advance();
    else
    {
      printf("ERROR: expression_statement\n");
      exit(0);
    }
  }
}
void expr()
{
  cmp_expr();
}
void cmp_expr()
{
  add_expr();
  while ( (SYMBOL_EQUALS '<') || (SYMBOL_EQUALS '>') )
  {
    advance();
    add_expr();
  }
}
void add_expr()
{
  mul_expr();
  while( (SYMBOL_EQUALS '+') || (SYMBOL_EQUALS '-') )
  {
    advance();
    mul_expr();
  }
}
void mul_expr()
{
  if (SYMBOL_EQUALS '-')
  {
    advance();
    primary_expr();
  }
  else
  {
    primary_expr();
    while((SYMBOL_EQUALS '*') || (SYMBOL_EQUALS '/') || (SYMBOL_EQUALS '%'))
    {
      advance();
      primary_expr();
    }
  }
}
void primary_expr()
{
  if (token == INTEGER || token == STRING) advance();
  else if (SYMBOL_EQUALS '(')
  {
    advance();
    expr();
    if (SYMBOL_EQUALS ')');//可能需要修改
    else
    {
      printf("ERROR: primary_expr\n");
      exit(0);
    }
  }
  else if (token == IDENTIFIER)
  {
    advance();
    if (SYMBOL_EQUALS '=')
    {
      advance();
      expr();
    }
    else if (SYMBOL_EQUALS '[')
    {
      advance();
      expr();
      advance();
      if (SYMBOL_EQUALS '=')
      {
        advance();
        expr();
      }
    }
    else if (SYMBOL_EQUALS '(')
    {
      advance();
      if (SYMBOL_EQUALS ')') advance();
      else
      {
        expr_list();
        if (SYMBOL_EQUALS ')') advance();
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
      expr();
    }
  }
}
void expr_list()
{
  expr();
  while(SYMBOL_EQUALS ',')
  {
    advance();
    expr();
  }
}
void id_list()
{
  if (token == IDENTIFIER)
  {
    advance();
    while(SYMBOL_EQUALS ',')
    {
      advance();
      id_list();
    }
  }
  else
  {
    printf("ERROR: id_list\n");
    exit(0);
  }
}
