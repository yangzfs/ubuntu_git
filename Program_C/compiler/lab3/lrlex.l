%{  //Declarations

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "ast.h"
#include "lrparser.tab.h"

void yyerror(char *);

%}  //Definitions

ID          [a-zA-Z][a-zA-Z0-9_]*
NUMBER      [0-9]+
SYMBOL      [;,(){}]|[=+*/\-<>]|={2}
SPACE       [ \t\n]
TYPE        int|str|void
STRING      \"[^"]*\"
ANNOTATION  \/{2}.*
%%//Rules

return          {yylval.sval = (char *)malloc(sizeof (yytext));strcpy(yylval.sval, yytext);return RETURN;}
while           {yylval.sval = (char *)malloc(sizeof (yytext));strcpy(yylval.sval, yytext);return WHILE;}
print           {yylval.sval = (char *)malloc(sizeof (yytext));strcpy(yylval.sval, yytext);return PRINT;}
if          		{yylval.sval = (char *)malloc(sizeof (yytext));strcpy(yylval.sval, yytext);return IF;}
else          	{yylval.sval = (char *)malloc(sizeof (yytext));strcpy(yylval.sval, yytext);return ELSE;}
{TYPE}          {yylval.sval = (char *)malloc(sizeof (yytext));strcpy(yylval.sval, yytext);return TYPE;}
{ID}            {yylval.sval = (char *)malloc(sizeof (yytext));strcpy(yylval.sval, yytext);return ID;}
{STRING}				{yylval.sval = (char *)malloc(sizeof (yytext));strcpy(yylval.sval, yytext);return STRING;}
{NUMBER}        {yylval.ival = atoi(yytext); return NUMBER;}
{SYMBOL}        {                            return *yytext;}
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
