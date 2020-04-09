#ifndef tree
#include <iostream>
#include <cstdlib>
#define tree

using namespace std;

enum OPERATIONS
{
    NIL,
    ASSIGN,
    DECLARATION,
    SUM,
    EXPRESSION,
    MULTIPLY,
    DIVIDE,
    SUB,
    VARIABLE,
    CONSTANT,
    ROOT,
    ASSIGNMENT_OPERATOR,
    STMT_LIST,
    LOOP,
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
    value mergeValues(value x, value y)
    {
        value res;
        if (operation == OPERATIONS(SUM))
        {
            res.v.i = x.v.i + y.v.i;
            res.v.f = x.v.f + y.v.f;
            //TODO: add string summaiton
        }
        if (operation == OPERATIONS(SUB))
        {
            res.v.i = x.v.i - y.v.i;
            res.v.f = x.v.f - y.v.f;
        }
        if (operation == OPERATIONS(MULTIPLY))
        {

            res.v.i = x.v.i * y.v.i;
            //res.v.f = x.v.f * y.v.f;
        }
        if (operation == OPERATIONS(DIVIDE))
        {

            res.v.i = x.v.i / y.v.i;
            //res.v.f = x.v.f * y.v.f;
        }

        return res;
    }

    void log()
    {
        cout << this->val.v.i << "  " << this->val.v.f << "  " << this->operation << endl;
    }
};

#endif
