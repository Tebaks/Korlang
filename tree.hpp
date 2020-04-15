#ifndef tree
#include <iostream>
#include <cstdlib>
#define tree
#define NIL_TREE_NODE TreeNode(true);
#define NIL_VALUE          \
    {                      \
        0, "nil", "", 0, 1 \
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
    IF_LOGIC, //25
    IF_ELSE_LOGIC,
    ASSIGNMENT,
    FUNCTION,
    FUNCTION_DEC,
    VAR_NAME, //30
    VAR_LIST,
    PARAMETERS,
    BREAK,
    RETURN,
    INC_DEC, //35
    POST_INC,
    POST_DEC,
    COMM,
    ARRAY_DEF,
    ARRAY_ELEM, //40
    ARR_ASSIGNMENT,
    KOR_STMT,
    IMPORT_STMT,
    EXTRACT_STMT,
    OBJECT_DEF, //45
    PAIR,
    PAIRS,
};
struct value
{
    union {
        int i;
        float f;
        const char *s;

    } v;
    string use;
    string sval;
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

        if (operation == OPERATIONS(LTH_LOGIC))
        {

            if (x.use.compare("float") == 0 && y.use.compare("float") == 0)
            {
                if (x.v.f < y.v.f)
                {
                    res.v.i = 1;
                }
            }
            if (x.use.compare("integer") == 0 && y.use.compare("float") == 0)
            {
                if (x.v.i < y.v.f)
                {
                    res.v.i = 1;
                }
            }
            if (x.use.compare("float") == 0 && y.use.compare("integer") == 0)
            {
                if (x.v.f < y.v.i)
                {
                    res.v.i = 1;
                }
            }
            if (x.use.compare("integer") == 0 && y.use.compare("integer") == 0)
            {
                if (x.v.i < y.v.i)
                {
                    res.v.i = 1;
                }
            }
        }
        if (operation == OPERATIONS(GTH_LOGIC))
        {
            if (x.use.compare("float") == 0 && y.use.compare("float") == 0)
            {
                if (x.v.f > y.v.f)
                {
                    res.v.i = 1;
                }
            }
            if (x.use.compare("integer") == 0 && y.use.compare("float") == 0)
            {
                if (x.v.i > y.v.f)
                {
                    res.v.i = 1;
                }
            }
            if (x.use.compare("float") == 0 && y.use.compare("integer") == 0)
            {
                if (x.v.f > y.v.i)
                {
                    res.v.i = 1;
                }
            }
            if (x.use.compare("integer") == 0 && y.use.compare("integer") == 0)
            {
                if (x.v.i > y.v.i)
                {
                    res.v.i = 1;
                }
            }
        }
        if (operation == OPERATIONS(GTHEQ_LOGIC))
        {
            if (x.use.compare("float") == 0 && y.use.compare("float") == 0)
            {
                if (x.v.f >= y.v.f)
                {
                    res.v.i = 1;
                }
            }
            if (x.use.compare("integer") == 0 && y.use.compare("float") == 0)
            {
                if (x.v.i >= y.v.f)
                {
                    res.v.i = 1;
                }
            }
            if (x.use.compare("float") == 0 && y.use.compare("integer") == 0)
            {
                if (x.v.f >= y.v.i)
                {
                    res.v.i = 1;
                }
            }
            if (x.use.compare("integer") == 0 && y.use.compare("integer") == 0)
            {
                if (x.v.i >= y.v.i)
                {
                    res.v.i = 1;
                }
            }
        }
        if (operation == OPERATIONS(LTHEQ_LOGIC))
        {
            if (x.use.compare("float") == 0 && y.use.compare("float") == 0)
            {
                if (x.v.f <= y.v.f)
                {
                    res.v.i = 1;
                }
            }
            if (x.use.compare("integer") == 0 && y.use.compare("float") == 0)
            {
                if (x.v.i <= y.v.f)
                {
                    res.v.i = 1;
                }
            }
            if (x.use.compare("float") == 0 && y.use.compare("integer") == 0)
            {
                if (x.v.f <= y.v.i)
                {
                    res.v.i = 1;
                }
            }
            if (x.use.compare("integer") == 0 && y.use.compare("integer") == 0)
            {
                if (x.v.i <= y.v.i)
                {
                    res.v.i = 1;
                }
            }
        }
        if (operation == OPERATIONS(EQ_LOGIC))
        {
            if (x.use.compare("boolean") == 0 && y.use.compare("boolean") == 0)
            {
                if (x.v.i == y.v.i)
                {
                    res.v.i = 1;
                }
            }
            if (x.use.compare("string") == 0 && y.use.compare("string") == 0)
            {

                if (x.sval == "")
                {
                    x.sval = x.v.s;
                }
                if (y.sval == "")
                {
                    y.sval = y.v.s;
                }
                if (x.sval.compare(y.sval) == 0)
                {
                    res.v.i = 1;
                }
            }
            if (x.use.compare("float") == 0 && y.use.compare("float") == 0)
            {
                if (x.v.f == y.v.f)
                {
                    res.v.i = 1;
                }
            }
            if (x.use.compare("integer") == 0 && y.use.compare("float") == 0)
            {
                if (x.v.i == y.v.f)
                {
                    res.v.i = 1;
                }
            }
            if (x.use.compare("float") == 0 && y.use.compare("integer") == 0)
            {
                if (x.v.f == y.v.i)
                {
                    res.v.i = 1;
                }
            }
            if (x.use.compare("integer") == 0 && y.use.compare("integer") == 0)
            {
                if (x.v.i == y.v.i)
                {
                    res.v.i = 1;
                }
            }
        }
        if (operation == OPERATIONS(NEQ_LOGIC))
        {
            if (x.use.compare("boolean") == 0 && y.use.compare("boolean") == 0)
            {
                if (x.v.i != y.v.i)
                {
                    res.v.i = 1;
                }
            }
            if (x.use.compare("string") == 0 && y.use.compare("string") == 0)
            {

                if (x.sval == "")
                {
                    x.sval = x.v.s;
                }
                if (y.sval == "")
                {
                    y.sval = y.v.s;
                }
                if (x.sval.compare(y.sval) == 1)
                {
                    res.v.i = 1;
                }
            }
            if (x.use.compare("float") == 0 && y.use.compare("float") == 0)
            {
                if (x.v.f != y.v.f)
                {
                    res.v.i = 1;
                }
            }
            if (x.use.compare("integer") == 0 && y.use.compare("float") == 0)
            {
                if (x.v.i != y.v.f)
                {
                    res.v.i = 1;
                }
            }
            if (x.use.compare("float") == 0 && y.use.compare("integer") == 0)
            {
                if (x.v.f != y.v.i)
                {
                    res.v.i = 1;
                }
            }
            if (x.use.compare("integer") == 0 && y.use.compare("integer") == 0)
            {
                if (x.v.i != y.v.i)
                {
                    res.v.i = 1;
                }
            }
        }
        if (operation == OPERATIONS(AND_LOGIC))
        {

            if (x.v.i && y.v.i)
            {
                res.v.i = 1;
            }
        }
        if (operation == OPERATIONS(OR_LOGIC))
        {
            if (x.v.i || y.v.i)
            {
                res.v.i = 1;
            }
        }
        res.use = "boolean";
        return res;
    }
    value mergeValues(value x, value y)
    {
        value res;
        res.use = x.use;
        if (x.use.compare("string") == 0 || y.use.compare("string") == 0)
        {
            res.use = "string";
        }
        //TODO : check value.use before operations.
        if (operation == OPERATIONS(SUM))
        {
            if (res.use.compare("string") == 0)
            {
                //cout << "x.v.s: " << x.v.s << " y.v.s: " << y.v.s << endl;
                x.sval = x.v.s;
                y.sval = y.v.s;
                //TODO : solve integer concat bug
                if (x.use.compare("integer") == 0)
                {
                    x.sval = to_string(x.v.i);
                    x.use = "string";
                }
                if (y.use.compare("integer") == 0)
                {
                    y.sval = to_string(y.v.i);
                    y.use = "string";
                }
                //cout << "x.sval: " << x.sval << " y.sval: " << y.sval << endl;
                res.sval = x.sval + y.sval;
                //cout << "res.sval: " << res.sval << endl;
            }
            else if (x.use.compare("integer") == 0 && y.use.compare("integer") == 0)
            {
                res.v.i = x.v.i + y.v.i;
            }
            else
            {
                res.v.f = x.v.f + y.v.f;
            }
        }
        if (operation == OPERATIONS(SUB))
        {
            if ((x.use.compare("integer") != 0 && x.use.compare("float") != 0) && (y.use.compare("integer") != 0 && y.use.compare("float") != 0))
            {
                return NIL_VALUE; //driver->createPanic("Subtraction with incompatible type.");
            }
            if (res.use.compare("integer") == 0)
            {
                res.v.i = x.v.i - y.v.i;
            }
            else
            {
                res.v.f = x.v.f - y.v.f;
            }
        }
        if (operation == OPERATIONS(MULTIPLY))
        {

            if ((x.use.compare("integer") != 0 && x.use.compare("float") != 0) && (y.use.compare("integer") != 0 && y.use.compare("float") != 0))
            {
                return NIL_VALUE; //driver->createPanic("Multiplication with incompatible type.");
            }
            if (res.use.compare("integer") == 0)
            {
                res.v.i = x.v.i * y.v.i;
            }
            else
            {
                res.v.f = x.v.f * y.v.f;
            }
        }
        if (operation == OPERATIONS(DIVIDE))
        {

            if ((x.use.compare("integer") != 0 && x.use.compare("float") != 0) && (y.use.compare("integer") != 0 && y.use.compare("float") != 0))
            {
                return NIL_VALUE; //driver->createPanic("Division with incompatible type.");
            }
            if (y.v.i == 0)
            {
                return NIL_VALUE; //driver->createPanic("Division with zero.");
            }
            if (res.use.compare("integer") == 0)
            {
                res.v.i = x.v.i / y.v.i;
            }
            else
            {
                res.v.f = x.v.f / y.v.f;
            }
        }
        if (operation == OPERATIONS(MOD))
        {
            if ((x.use.compare("integer") != 0 && x.use.compare("float") != 0) && (y.use.compare("integer") != 0 && y.use.compare("float") != 0))
            {
                return NIL_VALUE; //driver->createPanic("Modulus with incompatible type.");
            }
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
