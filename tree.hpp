#ifndef tree
#include <iostream>
#include <cstdlib>
#define tree
#define NIL_TREE_NODE TreeNode(true);
#define NIL_VALUE      \
    {                  \
        0, "nil", 0, 1 \
    }

using namespace std;

enum OPERATIONS
{
    NIL,
    ASSIGN,
    TRY_CATCH,
    DECLARATION,
    SUM,
    EXPRESSION, //5
    MULTIPLY,
    DIVIDE,
    MOD,
    SUB,
    VARIABLE, //10
    CONSTANT,
    ROOT,
    ASSIGNMENT_OPERATOR,
    STMT_LIST,
    LOOP, //15
    LOGIC,
    EQ_LOGIC,
    NEQ_LOGIC,
    LTH_LOGIC,
    GTH_LOGIC, //20
    GTHEQ_LOGIC,
    LTHEQ_LOGIC,
    AND_LOGIC,
    OR_LOGIC,
    IF_LOGIC,
    IF_ELSE_LOGIC,
    ASSIGNMENT,
    FUNCTION,
    FUNCTION_DEC,
    VAR_NAME,
    VAR_LIST,
    PARAMETERS,
    BREAK,
    RETURN,
    INC_DEC,
    POST_INC,
    POST_DEC,
    COMM,
};
struct value
{
    union {
        int i;
        float f;
        const char *s;

    } v;
    string use;
    int br = 0;
    bool init = 0;
};

class TreeNode
{
private:
    bool isNilNode = false;

public:
    struct value val;
    OPERATIONS operation;
    TreeNode *firstChild;
    TreeNode *secondChild;
    TreeNode *thirdChild;
    TreeNode *fourthChild;

    TreeNode() {}
    TreeNode(bool isNil) : isNilNode(isNil) {}
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

    value mergeLogic(value x, value y)
    {
        value res;
        res.v.i = 0;
        if (operation == OPERATIONS(LTH_LOGIC) && x.v.i < y.v.i)
        {
            res.v.i = 1;
        }
        if (operation == OPERATIONS(GTH_LOGIC) && x.v.i > y.v.i)
        {
            res.v.i = 1;
        }
        if (operation == OPERATIONS(GTHEQ_LOGIC) && x.v.i >= y.v.i)
        {
            res.v.i = 1;
        }
        if (operation == OPERATIONS(LTHEQ_LOGIC) && x.v.i <= y.v.i)
        {
            res.v.i = 1;
        }
        if (operation == OPERATIONS(EQ_LOGIC) && x.v.i == y.v.i)
        {
            res.v.i = 1;
        }
        if (operation == OPERATIONS(NEQ_LOGIC) && x.v.i != y.v.i)
        {
            res.v.i = 1;
        }
        if (operation == OPERATIONS(AND_LOGIC) && ((x.v.i > 0) && (y.v.i > 0)))
        {
            res.v.i = 1;
        }
        if (operation == OPERATIONS(OR_LOGIC) && ((x.v.i > 0) || (y.v.i > 0)))
        {
            res.v.i = 1;
        }
        res.use = "boolean";
        return res;
    }
    value mergeValues(value x, value y)
    {
        value res;
        res.use = x.use;
        //TODO : check value.use before operations.
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
            //res.v.f = x.v.f / y.v.f;
        }
        if (operation == OPERATIONS(MOD))
        {
            res.v.i = x.v.i % y.v.i;
        }

        return res;
    }

    void log()
    {
        cout << this->val.v.i << "  " << this->val.v.f << "  " << this->operation << endl;
    }

    bool isNil()
    {
        return this->isNilNode;
    }
};

#endif
