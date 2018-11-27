%{  //Declarations

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "ast.h"
/*#include "lrparser.tab.h"*/

void yyerror(char *);

%}  //Definitions

ID          [a-zA-Z][a-zA-Z0-9_]*
NUMBER      [0-9]+
SYMBOL      [;,(){}]
OPERATOR    [+\-*/=<>]|={2}
SPACE       [ \t\n]
TYPE        int|str|void
STRING      \"[^"]*\"
ANNOTATION  \/{2}.*
%%//Rules

return          {printf("<return ,%s>\n", yytext);}
while           {printf("<while ,%s>\n", yytext);}
print           {printf("<print ,%s>\n", yytext);}
if          		{printf("<if ,%s>\n", yytext);}
else          	{printf("<else ,%s>\n", yytext);}
{TYPE}          {printf("<type ,%s>\n", yytext);}
{ID}            {printf("<id ,%s>\n", yytext);}
{STRING}				{printf("<string ,%s>\n", yytext);}
{NUMBER}        {printf("<number ,%s>\n", yytext);}
{SYMBOL}        {printf("<symbol ,%s>\n", yytext);}
{OPERATOR}      {printf("<operator ,%s>\n", yytext);}
{SPACE}         {}
{ANNOTATION}    {}
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
}
