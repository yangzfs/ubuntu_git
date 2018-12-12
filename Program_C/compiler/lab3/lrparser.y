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

%token <ival> NUMBER
%token <sval> TYPE ID STRING RETURN WHILE PRINT IF ELSE
%type  <pAst> program external_declaration assign_list assign function function_statement
%type  <pAst> parameter_list parameter intstr function_implement expr factor term
%type  <pAst> id type number string

%type  <pAst> statement_list statement return print while if else
%type  <pAst> loop_statement while_statement bool_expr
%type  <pAst> if_statement else_statement conditional_statement function_call if_condition

%right '='
%left  '+' '-' '*' '/' '<' '>'
%left  "=="

%%

program
    : external_declaration     {$$ = new_tree(NULL, $1, "program");}
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
    | id '=' expr {$$ = new_tree($1, $3, "=");}
    ;

expr
    : factor
    | expr '+' factor {$$ = new_tree($1, $3, "+");}
    | expr '-' factor {$$ = new_tree($1, $3, "-");}
    ;

factor
    : term
    | factor '*' term  {$$ = new_tree($1, $3, "*");}
    | factor '/' term  {$$ = new_tree($1, $3, "/");}
    ;

term
    : number {$$ = new_tree(NULL, $1, "term");}
    | id  {$$ = new_tree(NULL, $1, "term");}
    | string  {$$ = new_tree(NULL, $1, "term");}
    | function_call {$$ = new_tree(NULL, $1, "term");}
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
    | '{' statement_list '}' {$$ = new_tree(NULL, $2, "function_implement");}
    ;

statement_list
    : statement {$$ = new_tree(NULL, $1, "statement_list");}
    | statement_list statement {$$ = new_tree($1, $2, "statement_list");}
    ;

statement
    : type assign_list ';' {$$ = new_tree($1, $2, "statement");}
    | assign_list ';' {$$ = new_tree(NULL, $1, "statement");}
    | return expr ';' {$$ = new_tree($1, $2, "statement");}
    | print expr ';' {$$ = new_tree($1, $2, "statement");}
    | loop_statement {$$ = new_tree(NULL, $1, "statement");}
    | conditional_statement {$$ = new_tree(NULL, $1, "statement");}
    | function_call ';' {$$ = new_tree(NULL, $1, "statement");}
    ;

function_call
    : id '(' ')'  {$$ = new_tree(NULL, $1, "function_call");}
    | id '(' expr ')' {$$ = new_tree($1, $3, "function_call");}
    ;

loop_statement
    :while_statement '{' statement_list '}' {$$ = new_tree($1, $3, "loop_statement");}
    |while_statement '{' '}' {$$ = new_tree($1, NULL, "loop_statement");}
    ;

while_statement
    :while '(' bool_expr ')' {$$ = new_tree($1, $3, "while_statement");}
    ;

bool_expr
    : expr '>' expr {$$ = new_tree($1, $3, ">");}
    | expr '<' expr {$$ = new_tree($1, $3, "<");}
    | expr '==' expr {$$ = new_tree($1, $3, "==");}
    ;

conditional_statement
    : if_statement {$$ = new_tree($1, NULL, "conditional_statement");}
    | if_statement else_statement {$$ = new_tree($1, $2, "conditional_statement");}
    ;

if_statement
    : if_condition  statement {$$ = new_tree($1, $2, "if_statement");}
    | if_condition '{' statement_list '}' {$$ = new_tree($1, $3, "if_statement");}
    | if_condition '{' '}' {$$ = new_tree($1, NULL, "if_statement");}
    ;

if_condition
    : if '(' bool_expr ')' {$$ = new_tree($1, $3, "if_condition");}
    ;
else_statement
    : else statement {$$ = new_tree($1, $2, "else_statement");}
    | else '{' statement_list '}' {$$ = new_tree($1, $3, "else_statement");}
    | else '{' '}' {$$ = new_tree($1, NULL, "else_statement");}
    ;

return:RETURN {$$ = new_sval($1, "RETURN");}
    ;
print:PRINT {$$ = new_sval($1, "PRINT");}
    ;
while:WHILE {$$ = new_sval($1, "WHILE");}
    ;
if:IF {$$ = new_sval($1, "IF");}
    ;
else:ELSE {$$ = new_sval($1, "ELSE");}
    ;
type: TYPE {$$ = new_sval($1, "TYPE");}
    ;
id: ID {$$ = new_sval($1, "ID");}
    ;
string: STRING  {$$ = new_sval($1, "STRING");}
    ;
number: NUMBER  {$$ = new_ival($1, "NUMBER");}
    ;
%%
