typedef struct _ast ast;
typedef struct _ast *past;
struct _ast{
  int ivalue;
  char * svalue;
  char * nodeType;
  past left;
  past right;
};

void showAst(past node, int nest);
past newAstNode(void);
past new_sval(char * sval, char * type);
past new_ival(int ival, char * type);
past new_tree(past left, past right, char * type);
