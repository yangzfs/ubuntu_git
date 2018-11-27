%{

#include<stdio.h>
#include<string.h>
#include "ast.h"
extern int yylex();
extern void yyerror(char *);

%}

%union{
  int    ival;
  char * sval;
  past	 pAst;
};

%token <ival> NUMBER KEYWORD
%token <sval> TYPE ID STRING
%type  <pAst> program external_declaration assign_list assign function function_statement
%type  <pAst> parameter_list parameter intstr function_implement
%type  <pAst> id type number string
%right '='
%left  '+' '-' '*' '/' '<' '>'
%left  "=="

%%

program
    : external_declaration     {$$ = new_tree(NULL, $1, "program");showAst($1, 0);}
    | program external_declaration {$$ = new_tree($1, $2, "program");showAst($2, 0);}
    ;

external_declaration
    : type assign_list ';' {$$ = new_tree($1, $2, "external_declaration");}
    | type function    {$$ = new_tree($1, $2, "external_declaration");}
    ;

assign_list
    : assign   {$$ = new_tree(NULL, $1, "assign_list");}
    | assign_list ',' assign  {$$ = new_tree($1, $3, "assign_list");}
    ;

assign
    : id  {$$ = new_tree($1, NULL, "assign");}
    | id '=' number {$$ = new_tree($1, $3, "assign");}
    | id '=' string {$$ = new_tree($1, $3, "assign");}
    ;

function
    : function_statement function_implement{$$ = new_tree($1, $2, "function");}
    ;

function_statement
    : id parameter_list {$$ = new_tree($1, $2, "function_statement");}
    ;

parameter_list
    : '(' ')'   {$$ = NULL;}
    | '(' parameter ')' {$$ = new_tree(NULL, $2, "parameter_list");}
    ;

parameter
    : intstr {$$ = new_tree(NULL, $1, "parameter");}
    | parameter ',' intstr {$$ = new_tree($1, $3, "parameter");}
    ;

intstr
    : type id{$$ = new_tree($1, $2, "intstr");}
    ;

function_implement
    : '{' '}'  {$$ = new_tree(NULL, NULL, "function_implement");}

type: TYPE {$$ = new_sval($1, "TYPE");}
    ;
id: ID {$$ = new_sval($1, "ID");}
    ;
string: STRING  {$$ = new_sval($1, "STRING");}
    ;
number: NUMBER  {$$ = new_ival($1, "NUMBER");}
    ;
%%
