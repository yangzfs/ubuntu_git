#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>

#define MAXBUF 256

#define BUF_GET                    \
buf[i++] = ch;
#define UPDATE_CH                  \
ch = next_ch;                      \
next_ch = fgetc(fp);

#define BUF_CHECK                  \
if (i == MAXBUF)                   \
{                                  \
  printf("buf is full!\n");        \
  exit(0);                         \
}

//enum {IDENTIFIER = 1, INTEGER, SYMBOL, FLOAT, KEYWORD, STRING};
const char * keywords[] = {"and", "as", "assert", "break", "class", "continue"
, "def", "del", "elif", "else", "except", "exec", "finally", "for", "from"
, "global", "if", "import", "in", "is", "lambda", "not", "or", "pass", "print"
, "raise", "return", "try", "while", "with", "yield"
, 0};
// typedef struct
// {
//   int charClass;
//   void *elem;
// }morpheme;

const char * destination = "/home/zwz/桌面/ubuntu_git/Program_C/compiler/lab1/result.txt";
const char * python_path = "/home/zwz/windows/Users/12454/Desktop/linux/编译技术lab1/python.py";

void parameter_check(int argc);
void fp_check(FILE * fp);
void lexer(FILE * fp);
int iskeyword(char * letter);
FILE * result; //输出

int main(int argc, char const *argv[])
{
  FILE * fp;
  //parameter_check(argc);
  fp = fopen(python_path, "r");
  result = fopen(destination, "w+");
  fp_check(fp);
  fp_check(result);
  lexer(fp);
  fclose(fp);
  fclose(result);
  return 0;
}
void parameter_check(int argc)
{
  if (argc < 2)
  {
    printf("ERROR: too few parameters!\n");
    exit(0);
  }
  else if (argc > 2)
  {
    printf("ERROR: too much parameters!\n");
    exit(0);
  }
}
void fp_check(FILE * fp)
{
    if (fp == NULL)
    {
      printf("ERROR: can not open file.\n");
      exit(0);
    }
}
void lexer(FILE * fp)
{
  char ch, next_ch;
  ch = fgetc(fp);
  next_ch = fgetc(fp);
  while(ch != EOF)
  {
    char buf[MAXBUF];
    int i;

    for(i = 0; i < MAXBUF; i++)
      buf[i] = '\0';
    i = 0;

    if (isalpha(ch)) //identifier keyword
    {
      do
      {
        BUF_GET;
        UPDATE_CH;
        BUF_CHECK;
      } while(isalpha(ch) || isdigit(ch) || ch == '_');
      if (iskeyword(buf))
      {
        printf("<KEYWORD, %s>\n", buf);
        fprintf(result, "<KEYWORD, %s>\n", buf);
        continue;
      }
      else
      {
        printf("<IDENTIFIER, %s>\n", buf);
        fprintf(result, "<IDENTIFIER, %s>\n", buf);
        continue;
      }
    }
    else if (isdigit(ch))
    {
      do
      {
        BUF_GET;
        UPDATE_CH;
        BUF_CHECK;
      } while(isdigit(ch));

      if (ch == '.')
      {
        BUF_GET;
        UPDATE_CH;
        do
        {
          BUF_GET;
          UPDATE_CH;
          BUF_CHECK;
        } while(isdigit(ch));
        printf("<FLOAT, %s>\n", buf);
        fprintf(result, "<FLOAT, %s>\n", buf);
        continue;
      }
      printf("<INTEGER, %s>\n", buf);
      fprintf(result, "<INTEGER, %s>\n", buf);
      continue;
    }
    else if (ch == '#') //annotation
    {
      do
      {
        BUF_GET;
        UPDATE_CH;
        BUF_CHECK;
      } while(ch != '\n');
      printf("<ANNOTATION, %s>\n", buf);
      continue;
    }
    else if (ch == '"') //string
    {
      do
      {
        if (ch == '\\')  //特殊情况\'
        {
          UPDATE_CH;
          BUF_GET;
          UPDATE_CH;
          BUF_CHECK;
        }
        BUF_GET;
        UPDATE_CH;
        BUF_CHECK;
      } while(ch != '"');
      BUF_GET;
      UPDATE_CH;
      printf("<STRING, %s>\n", buf);
      fprintf(result, "<STRING, %s>\n", buf);
      continue;
    }
    else if (ch == '\'') //string
    {
      do
      {
        if (ch == '\\') // 特殊字符\'
        {
          UPDATE_CH;
          BUF_GET;
          UPDATE_CH;
          BUF_CHECK;
        }
        BUF_GET;
        UPDATE_CH;
        BUF_CHECK;
      } while(ch != '\'');
      BUF_GET;
      UPDATE_CH;

      if (ch == '\'' && buf[1] == '\'')
      {
        while(1)
        {
          BUF_GET;
          UPDATE_CH;
          if (i >= 7)
          {
            if (buf[i-1] == '\'' && buf[i-2] == '\'' && buf[i-3] == '\'')
            break;
          }
        }
        printf("<ANNOTATION, %s>\n", buf);
        continue;
      }
      printf("<STRING, %s>\n", buf);
      fprintf(result, "<STRING, %s>\n", buf);
      continue;
    }
    else if ( ch == '.' ||  ch == '~' || ch == ',' || ch == '?' || ch == ';'
    || ch == ':' || ch == '^' || ch == '(' || ch == ')' || ch == '[' || ch == ']'
    || ch == '{' || ch == '}')/*不存在歧义*/
    {
      BUF_GET;
      UPDATE_CH;
      printf("<SYMBOL, %s>\n", buf);
      fprintf(result, "<SYMBOL, %s>\n", buf);
      continue;
    }
    else if (ch == '<' || ch == '>' || ch == '!' || ch == '='
    || ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%')/*存在下一位歧义*/
    {
      if (next_ch == '=')
      {
        BUF_GET;
        UPDATE_CH;
        BUF_GET;
        UPDATE_CH;
      }
      else if ( (ch == '+' || ch == '-') && isdigit(next_ch))
      {
        do
        {
          BUF_GET;
          UPDATE_CH;
        }while(isdigit(ch));
        if (ch == '.')
        {
          BUF_GET;
          UPDATE_CH;
          do
          {
            BUF_GET;
            UPDATE_CH;
          } while(isdigit(ch));
          printf("<FLOAT, %s>\n", buf);
          fprintf(result, "<FLOAT, %s>\n", buf);
          continue;
        }
        else
        {
          printf("<INTEGER, %s>\n", buf);
          fprintf(result, "<INTEGER, %s>\n", buf);
          continue;
        }
      }
      else
      {
        BUF_GET;
        UPDATE_CH;
      }
      printf("<SYMBOL, %s>\n", buf);
      fprintf(result, "<SYMBOL, %s>\n", buf);
      continue;
    }
    else if (ch == '&' || ch == '|')
    {
      if (next_ch == ch)
      {
        BUF_GET;
        UPDATE_CH;
        BUF_GET;
        UPDATE_CH;
      }
      else
      {
        BUF_GET;
        UPDATE_CH;
      }
      printf("<SYMBOL, %s>\n", buf);
      fprintf(result, "<SYMBOL, %s>\n", buf);
      continue;
    }

    UPDATE_CH;
  }
}
int iskeyword(char * letter)
{
  int i;
  for(i = 0; keywords[i] != 0; i++)
  {
    if (strcmp(keywords[i], letter) == 0)
      return 1;
  }
  return 0;
}
