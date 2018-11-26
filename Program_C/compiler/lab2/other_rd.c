//
//  main.c
//  CTLab2
//
//  Created by 周子骞 on 2018/10/20.
//  Copyright © 2018 周子骞. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

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
typedef struct _ast ast;
typedef struct _ast *past;
struct _ast{
    int ivalue;
    char svalue[100];
    char* nodeType;
    past left;
    past mid;
    past right;
};
extern int yylex();
extern int yylval;
extern char* yytext;
extern FILE* yyin;

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
past newAstNode();
past newNum(int value);
past newSTRING(char* value);
past newID(char* value);
past newINT();
past newSTR();
past newVOID();
past newIF(past left , past right);
past newWHILE(past left ,past right);
past newRETURN(past left);
past newPRINT(past left);
past newELSE(past left);
past newSCAN(past left);
past newCMP(past left ,past right);
past newASSIGN(past left ,past right);
past newList(past left ,past right);
past newExpr(int oper, past left,past right);
past node_id_list();
past node_primary_expr();
past node_expr_list();
past node_mul_expr();
past node_add_expr();
past node_cmp_expr();
past node_expr();
past node_expression_statement();
past node_statement_list();
past node_statement();
past node_type();
past node_parameter_list();
past node_declarator();
past node_intstr_list();
past node_initializer();
past node_declarator_list();
past node_external_declaration();
past node_program();
int tok;

void error(){
    printf("The statement is invalued!\n");
    exit(0);
}
void advance(){
    tok = yylex();
    printf("tok: %s\n",yytext);
}
void program(){
    external_declaration();
    while(tok != '\0'){
        external_declaration();
    }
}
void external_declaration(){
    type();
    declarator();
    decl_or_stmt();
}

void decl_or_stmt(){
    if(tok == '{')
    {
        advance();
        if(tok == '}')
            advance();
        else{
            statement_list();
            if(tok == '}')
                advance();
            else error();
        }
    }
    else if(tok == ','){
        advance();
        declarator_list();
        if(tok == ';')
            advance();
        else error();
    }
    else if(tok == ';')
        advance();
    else error();
}
void declarator_list(){
    declarator();
    while(tok == ','){
        advance();
        declarator();
    }
}
void intstr_list(){
    initializer();
    while(tok == ','){
        advance();
        initializer();
    }
}
void initializer(){
    if(tok == NUMBER)
        advance();
    else if(tok == STRING)
        advance();
    else error();
}
void declarator(){
    if(tok == ID){
        advance();
        if(tok == '('){
            advance();
            if(tok == ')')
                advance();
            else{
                parameter_list();
                if(tok == ')')
                    advance();
                else
                    error();
            }
        }
        else if(tok == '[' ){
            advance();
            if(tok == ']'){
                advance();
                if(tok == '='){
                    advance();
                    if(tok == '{'){
                        advance();
                        intstr_list();
                        if(tok == '}')
                            advance();
                        else
                            error();
                    }
                }
                else
                    error();
            }
            else{
                expr();
                if(tok == ']')
                    advance();
                else
                    error();
                if(tok == '='){
                    advance();
                    if(tok == '{'){
                        advance();
                        intstr_list();
                        if(tok == '}')
                            advance();
                        else
                            error();
                    }
                    else error();
                }
            }
        }
        else if(tok == '='){
            advance();
            expr();
        }
    }
    else error();
}
void parameter_list(){
    parameter();
    while(tok == ','){
        advance();
        parameter();
    }
}
void parameter(){
    type();
    if(tok == ID){
        advance();
    }
    else error();
}
void type(){
    if(tok == INT || tok == STR || tok == VOID)
        advance();
    else error();
}

void statement(){
    if(tok == IF){
        advance();
        if(tok == '('){
            expr();
            if(tok == ')'){
                advance();
                statement();
                if(tok == ELSE){
                    advance();
                    statement();
                }
            }
            else error();
        }
    }
    else if(tok == WHILE){
        advance();
        if(tok == '('){
            expr();
            if(tok == ')'){
                advance();
                statement();
            }
            else error();
        }
        else error();
    }
    else if(tok == RETURN){
        advance();
        if(tok == ';')
            advance();
        else{
            expr();
            if(tok == ';'){
                advance();
            }
            else error();
        }
    }
    else if(tok == PRINT){
        advance();
        if(tok == ';'){
            advance();
        }
        else{
            expr_list();
            if(tok == ';'){
                advance();
            }
            else error();
        }
    }
    else if(tok == SCAN){
        id_list();
        if(tok == ';'){
            advance();
        }
        else error();
    }
    else if(tok == '{'){
        advance();
        statement_list();
        if(tok == '}')
            advance();
        else error();
    }
    else if(tok == INT || tok == STR || tok == VOID){
        advance();
        declarator_list();
        if(tok == ';'){
            advance();
        }
        else error();
    }
    else
        expression_statement();
}
void statement_list(){
    statement();
    while(tok != '}'){
        statement();
    }
}
void expression_statement(){
    if(tok == ';')
        advance();
    else{
        expr();
        if(tok == ';')
            advance();
        else error();
    }
}
void expr(){
    cmp_expr();
}
void cmp_expr(){
    add_expr();
    while(tok == CMP){
        advance();
        add_expr();
    }
}
void add_expr(){
    mul_expr();
    while(tok == '+'||tok == '-'){
        advance();
        mul_expr();
    }
}
void mul_expr(){
    if(tok == '-'){
        advance();
        primary_expr();
    }
    else{
        primary_expr();
        while (tok == '*'||tok == '/'||tok == '%') {
            advance();
            primary_expr();
        }
    }
}
void primary_expr(){
    if(tok == NUMBER || tok == STRING)
        advance();
    else if(tok == '('){
        advance();
        expr();
        if(tok == ')');
        else error();
    }
    else if(tok == ID){
        advance();
        if (tok == '='){
            advance();
            expr();
        }
        else if (tok == '['){
            advance();
            expr();
            advance();
            if (tok == '=') {
                advance();
                expr();
            }
        }
        else if(tok == '('){
            advance();
            if(tok == ')')
                advance();
            else{
                expr_list();
                if(tok == ')'){
                    advance();
                }
                else error();
            }
        }
        else if(tok == ASSIGN){
            advance();
            expr();
        }
    }
}

void expr_list(){
    expr();
    while(tok == ','){
        advance();
        expr();
    }
}

void id_list(){
    if(tok == ID){
        advance();
        while(tok == ','){
            advance();
            id_list();
        }
    }
    else error();
}



past newAstNode()
{
    past node = malloc(sizeof(ast));
    if(node == NULL)
    {
        printf("run out of memory.\n");
        exit(0);
    }
    memset(node, 0, sizeof(ast));
    return node;
}

past newNum(int value)
{
    past var = newAstNode();
    var->nodeType = "intValue";
    var->ivalue = value;
    return var;
}

past newSTRING(char* value)
{
    past var = newAstNode();
    var->nodeType = "stringValue";
    strcpy(var->svalue, value);
    return var;
}

past newID(char* value)
{
    past var = newAstNode();
    var ->nodeType = "IDValue";
    strcpy(var->svalue, value);
    return var;
}

past newINT()
{
    past var = newAstNode();
    var ->nodeType = "int";
    return var;
}

past newSTR()
{
    past var = newAstNode();
    var ->nodeType = "str";
    return var;
}

past newVOID()
{
    past var = newAstNode();
    var ->nodeType = "void";
    return var;
}

past newIF(past left , past right)
{
    past var = newAstNode();
    var -> nodeType = "if";
    var ->left = left;
    var ->right = right;
    return var;
}

past newWHILE(past left ,past right)
{
    past var = newAstNode();
    var ->nodeType = "while";
    var ->left = left;
    var ->right = right;
    return var;
}

past newRETURN(past left)
{
    past var = newAstNode();
    var ->nodeType = "return";
    var ->left = left;
    return var;
}

past newPRINT(past left)
{
    past var = newAstNode();
    var ->nodeType = "print";
    var ->left = left;
    return var;
}

past newELSE(past left)
{
    past var = newAstNode();
    var->nodeType = "else";
    var ->left = left;
    return var;
}

past newSCAN(past left)
{
    past var = newAstNode();
    var->nodeType = "scan";
    var ->left = left;
    return var;
}

past newCMP(past left ,past right)
{
    past var = newAstNode();
    var->nodeType = "cmp";
    var ->left  = left;
    var ->right = right;
    return var;
}

past newASSIGN(past left ,past right)
{
    past var = newAstNode();
    var->nodeType = "assign";
    var ->left = left;
    var ->right = right;
    return var;
}

past newList(past left ,past right)
{
    past var = newAstNode();
    var->nodeType = "a";
    var ->left = left;
    var ->right = right;
    return var;
}

past newExpr(int oper, past left,past right)
{
    past var = newAstNode();
    var->nodeType = "expr";
    var->ivalue = oper;
    var->left = left;
    var->right = right;
    return var;
}

past newExtDecl(past t,past d,past ds){
    past var = newAstNode();
    var->nodeType = "a";
    var->left = t;
    var->mid = d;
    var->right = ds;
    return var;
}

past node_id_list()
{
    past result =newList(NULL,newID(yytext));
    advance();
    while (tok ==',') {
        advance();
        past result = newList(result,newID(yytext));
        advance();
    }
    return result;

}

past node_primary_expr()
{
    if (tok==ID) {
        past result = newList(NULL,newID(yytext));
        advance();
        if (tok=='(') {
            advance();
            if (tok==')') {
                advance();
                return result;
            }
            else {
                result = newList(result,node_expr_list());
                if(tok == ')') {
                    advance();
                    return result;
                }
                else {printf("error,%d\n",__LINE__);exit(0);}

            }
        }
        else if(tok == ASSIGN){
            advance();
            result = newASSIGN(result,node_expr());
            return result;
        }
        else if (tok == '=') {
            int oper = tok;
            advance();
            result = newExpr((char)oper,result,node_expr());
            return result;
        }
        else if (tok =='['){
            advance();
            result = newList(result,node_expr());
            if(tok == ']'){
                advance();
                if (tok =='=') {
                    int oper = tok;
                    advance();
                    result = newExpr(oper,result,node_expr());
                    return result;
                }
                else return result;
            }
            else {printf("error,%d\n",__LINE__);exit(0);}
        }
        else return result;
    }
    if(tok == '('){
        advance();
        past result = newList(NULL,node_expr());
        advance();
        if(tok == ')'){
            advance();
            return result;
        }
        else {printf("error,%d\n",__LINE__);exit(0);}
    }
    if (tok ==NUMBER) {
        past result = newList(NULL,newNum(yylval));
        advance();
        return result;
    }
    if (tok == STRING) {
        past result = newList(NULL,newSTRING(yytext));
        advance();
        return result;
    }
    else{
        printf("ERROR:%d",__LINE__);
        exit(0);
    }
}

past node_expr_list(){
    past result = newList(NULL,node_expr());
    while (tok ==',') {
        advance();
        result = newList(result,node_expr());
    }
    return result;
}

past node_mul_expr(){
    if (tok == '-') {
        advance();
        past result = newList(NULL,node_primary_expr());
        return result;
    }
    else{
        past result = newList(NULL,node_primary_expr());
        while(tok =='*'||tok =='/' || tok =='%'){
            advance();
            result = newList(result,node_primary_expr());
        }
        return result;
    }
}

past node_add_expr(){
    past result = newList(NULL,node_mul_expr());
    while (tok == '+'||tok =='-') {
        advance();
        result = newList(result,node_mul_expr());
    }
    return result;
}

past node_cmp_expr(){
    past result = newList(NULL,node_add_expr());
    while (tok == CMP) {
        advance();
        result = newCMP(result,node_add_expr());
    }
    return result;
}

past node_expr(){
    past result = newList(NULL,node_cmp_expr());
    return result;
}

past node_expression_statement(){
    if (tok ==';') {
        advance();
        return NULL;
    }
    else {
        past result = newList(NULL,node_expr());
        if(tok ==';'){
            advance();
            return result;
        }
        else {printf("error,%d\n",__LINE__);exit(0);}
    }

}

past node_statement_list(){
    past ext = node_statement();
    past list = newList(NULL,ext);
    while(tok != '}')
    {
        ext = node_statement();
        list = newList(list,ext);
    }
    return list;

}

past node_statement(){
    if(tok == '{'){
        advance();
        past result = newList(NULL,node_statement_list());
        if(tok == '}'){
            advance();
            return result;
        }
        else {printf("error,%d\n",__LINE__);exit(0);}
    }
    else if(tok == IF){
        advance();
        if(tok =='('){
            advance();
            past t = node_expr();
            if(tok == ')'){
                advance();
                past s1 = node_statement();
                past result = newIF(t,s1);
                if(tok == ELSE){
                    advance();
                    past s2 = newELSE(node_statement());
                    result = newList(result,s2);
                    return result;
                }
                else return result;
            }
            else {printf("error,%d\n",__LINE__);exit(0);}
        }
        else {printf("error,%d\n",__LINE__);exit(0);}
    }
    else if(tok == WHILE){
        advance();
        if(tok =='('){
            advance();
            past t = node_expr();
            if(tok ==')'){
                advance();
                past result = newWHILE(t,node_statement());
                return result;
            }
            else {printf("error,%d\n",__LINE__);exit(0);}
        }
        printf("error,%d\n",__LINE__);
        exit(0);
    }
    else if(tok ==RETURN){
        advance();
        if (tok ==';') {
            advance();
            past result = newRETURN(NULL);
            return  result;
        }
        else{
            past result = newRETURN(node_expr());
            if(tok ==';'){
                advance();
                return result;
            }
            else {printf("error,%d\n",__LINE__);exit(0);}
        }
    }
    else if(tok == PRINT){
        advance();
        if(tok ==';'){
            advance();
            past result = newPRINT(NULL);
            return result;
        }
        else {
            past result = newPRINT(node_expr_list());
            if(tok ==';'){
                advance();
                return result;
            }
            else {printf("error,%d\n",__LINE__);exit(0);}
        }
    }
    else if(tok ==SCAN){
        advance();
        past result = newSCAN(node_id_list());
        if(tok == ';') {
            advance();
            return result;
        }
        else {printf("error,%d\n",__LINE__);exit(0);}
    }
    else if (tok == INT){
        advance();
        past result = newList(newINT(),node_declarator_list());
        if(tok == ';'){
            advance();
            return result;
        }
        else {printf("error,%d\n",__LINE__);exit(0);}
    }
    else if (tok == STR){
        advance();
        past result = newList(newSTR(),node_declarator_list());
        if(tok ==';'){
            advance();
            return result;
        }
        else {printf("error,%d\n",__LINE__);exit(0);}
    }
    else if(tok ==VOID){
        advance();
        past result = newList(newVOID(),node_declarator_list());
        if(tok ==';'){
            advance();
            return result;
        }
        else {printf("error,%d\n",__LINE__);exit(0);}
    }
    else {
        past result = node_expression_statement();
        return result;
    }

}

past node_type(){
    if(tok ==INT){
        advance();
        past result = newINT();
        return result;
    }
    else if(tok ==STR){
        advance();
        past result = newSTR();
        return result;
    }
    else if (tok ==VOID){
        advance();
        past result = newVOID();
        return result;
    }
    else {printf("error,%d\n",__LINE__);exit(0);}
}

past node_parameter(){
    if(tok==INT||tok == STR ||tok == VOID)
    {
        past result = node_type();
        if(tok == ID)
        {result = newList(result,newID(yytext));
            advance();
            return result;
        }
        else {printf("error,%d\n",__LINE__);exit(0);}
    }
    else {printf("error,%d\n",__LINE__);exit(0);}


}

past node_parameter_list(){
    past result = newList(NULL,node_parameter());
    while (tok ==',') {
        advance();
        result = newList(result,node_parameter());
    }
    return result;
}

past node_declarator(){
    if(tok == ID){
        past t = newID(yytext);
        advance();
        if(tok == '='){
            int oper = tok;
            advance();
            past result = newExpr(oper,t,node_expr());
            return result;
        }
        else if(tok =='(')
        {
            advance();
            if(tok ==')')
            {
                advance();
                return t;
            }
            else
            {
                past result = newList(t,node_parameter_list());
                if(tok ==')'){
                    advance();
                    return result;
                }
                else{printf("error,%d\n",__LINE__);
                    exit(0);
                }
            }
        }
        else if(tok =='['){
            advance();
            if(tok ==']'){
                advance();
                if(tok =='='){
                    int oper = tok;
                    advance();
                    if(tok =='{'){
                        advance();
                        past result = newExpr(oper,t,node_intstr_list());
                        if(tok =='}'){
                            advance();
                            return result;
                        }
                        else{printf("error,%d\n",__LINE__);
                            exit(0);
                        }
                    }
                    else {printf("error,%d\n",__LINE__);exit(0);}
                }
                else{
                    return t;
                }
            }
            else{
                past result = newList(t,node_expr());
                if(tok ==']'){
                    advance();
                    if(tok =='='){
                        int oper = tok;
                        advance();
                        if(tok =='{'){
                            advance();
                            result = newExpr(oper,result,node_intstr_list());
                            if(tok =='}')
                            {
                                advance();
                                return result;
                            }
                            else{printf("error,%d\n",__LINE__);
                                exit(0);
                            }
                        }
                        else {printf("error,%d\n",__LINE__);exit(0);}
                    }
                    else{
                        return result;
                    }
                }
                else{printf("error,%d\n",__LINE__);
                    exit(0);
                }
            }

        }
        else {
            return t;}
    }
    else exit(0);
}

past node_initializer(){
    if(tok ==NUMBER){
        past result = newNum(yylval);
        advance();
        return result;
    }
    else if(tok ==STRING){
        past result = newSTRING(yytext);
        advance();
        return result;
    }
    else {
        printf("error,%d\n",__LINE__);exit(0);}
}

past node_intstr_list(){
    past result = newList(NULL,node_initializer());
    while (tok ==',') {
        advance();
        result = newList(result,node_initializer());
    }
    return result;
}

past node_declarator_list(){
    past result = newList(NULL,node_declarator());
    while (tok ==',') {
        advance();
        result = newList(result,node_declarator());
    }
    return result;
}

past node_decl_or_stmt(){
    if(tok =='{'){
        advance();
            if(tok =='}'){
                advance();
            return NULL;
        }
        else{
            past result = node_statement_list();
            if(tok =='}'){
                advance();
                return result;
            }
            else {printf("error,%d\n",__LINE__);
                exit(0);}
        }
    }
    else if(tok ==','){
        advance();
        past result = node_declarator_list();
        if(tok ==';'){
            advance();
            return result;
        }
        else {printf("error,%d\n",__LINE__);
            exit(0);}
    }
    else if(tok ==';'){
        advance();
        return NULL;
    }
    else if(tok == 'q'){
        printf("输入结束\n");
        exit(0);
    }
    else {    printf("error,%d\n",__LINE__);
        exit(0);}
}

past node_external_declaration(){
    past result = NULL;
    past t = node_type();
    past d = node_declarator();
    past ds = node_decl_or_stmt();

    result = newExtDecl(t, d, ds);
    return result;
}
past node_program(){
    advance();
    past ext = node_external_declaration();
    past list = newList(NULL,ext);
    while (tok != 'q') {
        ext = node_external_declaration();
        list = newList(list,ext);
    }
    return list;
}

void showAst(past node, int nest)
{
    if(node == NULL)
        return;


    if(strcmp(node->nodeType, "intValue") == 0){
        int i = 0;
        for(i = 0; i < nest; i ++)
            printf("  ");
        printf("%s %d\n", node->nodeType,node->ivalue);
    }
    else if(strcmp(node->nodeType, "expr") == 0){
        int i = 0;
        for(i = 0; i < nest; i ++)
            printf("  ");
        printf("%s '%c'\n", node->nodeType, (char)node->ivalue);
    }
    else if(strcmp(node->nodeType, "while") == 0){
        int i = 0;
        for(i = 0; i < nest; i ++)
            printf("  ");
        printf("%s\n", node->nodeType);
    }
    else if(strcmp(node->nodeType, "return") == 0){
        int i = 0;
        for(i = 0; i < nest; i ++)
            printf("  ");
        printf("%s\n", node->nodeType);}
    else if(strcmp(node->nodeType, "print") == 0){
        int i = 0;
        for(i = 0; i < nest; i ++)
            printf("  ");
        printf("%s\n", node->nodeType);}
    else if(strcmp(node->nodeType, "int") == 0){
        int i = 0;
        for(i = 0; i < nest; i ++)
            printf("  ");
        printf("%s\n", node->nodeType);}
    else if(strcmp(node->nodeType, "str") == 0){
        int i = 0;
        for(i = 0; i < nest; i ++)
            printf("  ");
        printf("%s\n", node->nodeType);}
    else if(strcmp(node->nodeType, "void") == 0){
        int i = 0;
        for(i = 0; i < nest; i ++)
            printf("  ");
        printf("%s\n", node->nodeType);}
    else if(strcmp(node->nodeType, "if") == 0){
        int i = 0;
        for(i = 0; i < nest; i ++)
            printf("  ");
        printf("%s\n", node->nodeType);}
    else if(strcmp(node->nodeType, "assign") == 0){
        int i = 0;
        for(i = 0; i < nest; i ++)
            printf("  ");
        printf("%s\n", node->nodeType);}
    else if(strcmp(node->nodeType, "else") == 0){
        int i = 0;
        for(i = 0; i < nest; i ++)
            printf("  ");
        printf("%s\n", node->nodeType);}
    else if(strcmp(node->nodeType, "scan") == 0){
        int i = 0;
        for(i = 0; i < nest; i ++)
            printf("  ");
        printf("%s\n", node->nodeType);}
    else if(strcmp(node->nodeType, "cmp") == 0){
        int i = 0;
        for(i = 0; i < nest; i ++)
            printf("  ");
        printf("%s\n", node->nodeType);}
    else if(strcmp(node->nodeType, "stringValue") == 0){
        int i = 0;
        for(i = 0; i < nest; i ++)
            printf("  ");
        printf("%s %s\n", node->nodeType, node->svalue);}
    else if(strcmp(node->nodeType, "IDValue") == 0){
        int i = 0;
        for(i = 0; i < nest; i ++)
            printf("  ");
        printf("%s %s\n", node->nodeType, node->svalue);}
    showAst(node->left, nest+1);
    showAst(node->mid, nest+1);
    showAst(node->right, nest+1);

}


int main(int argc, const char * argv[]) {
    //setbuf(stdout, NULL);
    //yyin = fopen("/home/zwz/windows/Users/12454/Desktop/linux/编译技术lab2/test.c", "r");
    past a = NULL;
    while(1){
        printf("Please input expression!");
        a = node_program();
        showAst(a, 0);
    }
    printf("PASS！\n");
    return 0;
}
