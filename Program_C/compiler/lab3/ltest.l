%{  //Declarations

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void yyerror(char *);

%}  //Definitions

ID          [a-zA-Z][a-zA-Z0-9_]*
NUMBER      [0-9]+
SYMBOL      [;,(){}]
OPERATOR    [=+*/-<>]|={2}
SPACE       [ \n\t]
TYPE        int|str|void
STRING      \"[^"]*\"
KEYWORD     return|while|print|if|else
ANNOTATION  \/{2}.*
%%//Rules

{KEYWORD}       {printf("<KEYWORD, %s>\n", yytext);}
{TYPE}          {printf("<TYPE, %s>\n", yytext);}
{ID}            {printf("<ID, %s>\n", yytext);}
{STRING}				{printf("<STRING, %s>\n", yytext);}
{NUMBER}        {printf("<NUMBER, %d>\n", atoi(yytext));}
{SYMBOL}        {printf("<SYMBOL, %s>\n", yytext);}
{OPERATOR}      {printf("<OPERATOR, %s>\n", yytext);}
{SPACE}         {}
{ANNOTATION}    {printf("<ANNOTATION, %s>\n", yytext);}
.               {yyerror("invalid character");}

%%  //User functions
void yyerror(char *s)
{
	printf("%s\n", s);
}
int yywrap(void)
{
  return 1;
}
int main(void)
{
  while(yylex());
  return 0;
}
