#ifndef tree
#include <iostream>
#include <cstdlib>
#define tree

enum OPERATIONS
{
    ASSIGN,
    SUM,
    MULTIPLY,
    DIVIDE,
    SUB,
    VARIABLE,
    CONSTANT,
    ROOT,
};
struct value
{
    union {
        int i;
        float f;
        char *s;
    } v;
    char *use;
};

class TreeNode
{
public:
    struct value val;
    OPERATIONS operation;
    TreeNode *firstChild;
    TreeNode *secondChild;
    TreeNode *thirdChild;
    TreeNode *fourthChild;

    TreeNode(value _val, OPERATIONS _ope, TreeNode *_n1, TreeNode *_n2, TreeNode *_n3, TreeNode *_n4)
    {
        this->val = _val;
        this->operation = _ope;
        this->firstChild = _n1;
        this->secondChild = _n2;
        this->thirdChild = _n3;
        this->fourthChild = _n4;
    }
    TreeNode(value _val, OPERATIONS _ope)
    {
        this->val = _val;
        this->operation = _ope;
    }
};
#endif
