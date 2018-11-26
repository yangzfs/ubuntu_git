%{  //Declarations
enum yyTokenType{ INT = 258, STR, RETURN, WHILE, VOID, IF, ELSE, PRINT, INTEGER
,FLOAT, STRING, IDENTIFIER, BOOL, SYMBOL, CHAR};
%}  //Definitions

IDENTIFIER  [a-zA-Z][a-zA-Z0-9_]*
SYMBOL      [`~!@#$%^&*()-_=+\[{\]}\|;:,<.>/?]
SYMBOL2     [!=<>+*/-]\=|\&{2}|\|{2}
ANNOTATION  \/{2}.*|\/\*(.|\n)*\*\/
STRING      \"[^\"]*\"
CHAR        \'[^']\'
FLOAT       ([1-9][0-9]*|0)\.[0-9]+
INTEGER     ([1-9][0-9]*|0)
SPACE       [ \n\t]

%%//Rules
"int"               {return INT;}
"str"               {return STR;}
"return"            {return RETURN;}
"while"             {return WHILE;}
"void"              {return VOID;}
"if"                {return IF;}
"else"              {return ELSE;}
"print"             {return PRINT;}
{INTEGER}           {return INTEGER;}
{FLOAT}             {return FLOAT;}
{STRING}            {return STRING;}
{IDENTIFIER}        {return IDENTIFIER;}
{SYMBOL}            {return SYMBOL;/*yytext[0]*/}
{SYMBOL2}           {return BOOL;}
{CHAR}              {return CHAR;/*yytext[1]*/}
{ANNOTATION}        {}
{SPACE}             {}

%%  //User functions
