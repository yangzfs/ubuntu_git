%{
enum yyTokenType{
INT = 258,
STR = 259,
VOID = 260,
NUMBER = 261,
STRING = 262,
ID = 263,
EOL = 264,
WHILE = 265,
IF = 266,
RETURN = 267,
PRINT = 268,
SCAN = 269,
CMP = 270,
ASSIGN = 271,
ELSE = 272
};
int yylval;
%}

ID [a-zA-Z_][a-zA-Z0-9_]*
STRING ["].*["]
ASSIGN [={1}]

%%

"//".* {}
"1" {yylval = atoi(yytext); return NUMBER;}
"{" |
"}" |
";" |
"," |
"=" |
"(" |
")" |
"[" |
"]" |
"+" |
"-" |
"*" |
"/" |
"%" |
"q" {return yytext[0];}
">" |
"<" {return CMP;}
"==" {return ASSIGN;}

while {return WHILE;}
if {return IF;}
return {return RETURN;}
print {return PRINT;}
scan {return SCAN;}
else {return ELSE;}
int {return INT;}
str {return STR;}
void {return VOID;}

{ID} {return ID;}
{STRING} {return STRING;}

[0-9]+ {yylval = atoi(yytext); return NUMBER;}

\n {}
[ \t] {}
.   {printf("Mystery character %c\n",*yytext);}

%%

int yyerror(char *s){
    fprintf(stderr,"error:%s\n",s);
    return 0;
}

int yywrap(){
    return 1;
}
