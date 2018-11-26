%{
#include<stdio.h>
const char * python_path = "/home/zwz/windows/Users/12454/Desktop/linux/编译技术lab1/python.py";
%}

IDENTIFIER  [a-zA-Z][a-zA-Z0-9_]*
KEYWORD     and|as|assert|break|class|continue|def|del|elif|else|except|exec|finally|for|from|global|if|import|in|is|lambda|not|or|pass|print|raise|return|try|while|with|yield
SYMBOL      [`~!@#$%^&*()-_=+\[{\]}\|;:,<.>/?]
SYMBOL2     [!=<>+*/-]\=|\&{2}|\|{2}
ANNOTATION  \'{3}(.|\n)*\'{3}|\#.*
STRING      \'[^\']*\'|\"[^\"]*\"
FLOAT       (\+|\-)?([1-9][0-9]*|0)\.[0-9]+
INTEGER     (\+|\-)?([1-9][0-9]*|0)
SPACE       [ \n\t]
%%

{KEYWORD}	   {printf("<KEYWORD, %s>\n",yytext);}
{IDENTIFIER} {printf("<IDENTIFIER, %s>\n", yytext);}
{ANNOTATION} {/*printf("<ANNOTATION, %s>\n", yytext);*/}
{STRING}     {printf("<STRING, %s>\n", yytext);}
{FLOAT}      {printf("<FLOAT, %s>\n", yytext);}
{SYMBOL}     {printf("<SYMBOL, %s>\n", yytext);}
{SYMBOL2}    {printf("<SYMBOL, %s>\n", yytext);}
{INTEGER}    {printf("<INTEGER, %s>\n", yytext);}
{SPACE}      {}
%%
int main(void)
{
  yyin = fopen(python_path, "r");
  while(yylex());
}
