#ifndef ENGINE
#define ENGINE

#include <iostream>
#include <string>
#include "tree.hpp"
#include "driver.hpp"
#include "util.hpp"
using namespace std;

class Engine
{
public:
  Driver *driver;
  Engine() : driver(new Driver())
  {
  }
  void execute(TreeNode *root)
  {
    auto scope = driver->getScope();
    value val = handleStatements(root, scope);
    driver->printValue(val);
  }

private:
  value handleStatements(TreeNode *node, Scope *scope)
  {
    NodeIterator it = NodeIterator(node);
    value v;
    while (!it.isEmpty())
    {

      auto statement = it.get();
      v = handleStatement(&statement, scope);
      if (v.br > 0)
      {
        return v;
      }
      it.done();
    }
    return v;
  }
  value handleStatement(TreeNode *node, Scope *scope)
  {
    value res;
    res.use = "na";
    if (node == NULL)
    {
      return res;
    }
    // Handle statement type.
    switch (node->operation)
    {
    case OPERATIONS(EXPRESSION):
      res = resolveExpression(node->firstChild, scope);
      res.use = "expression";
      break;
    case OPERATIONS(DECLARATION):
      res = resolveDeclaration(node, scope);
      break;
    case OPERATIONS(LOOP):
      res = executeLoop(node, scope);
      break;
    case OPERATIONS(TRY_CATCH):
      res = executeTryCatch(node, scope);
      break;
    case OPERATIONS(AND_LOGIC):
      res = resolveLogic(node, scope);
      res.use = "bool";
      break;
    case OPERATIONS(IF_LOGIC):
      res = executeIf(node, scope);
      break;
    case OPERATIONS(IF_ELSE_LOGIC):
      res = executeIfElse(node, scope);
      break;
    case OPERATIONS(ASSIGNMENT):
      res = resolveAssignment(node, scope);
      break;
    case OPERATIONS(FUNCTION):
      res = executeFunction(node, scope);
      break;
    case OPERATIONS(FUNCTION_DEC):
      res = resolveFunctionDeclaration(node, scope);
      break;
    case OPERATIONS(BREAK):
      res.br = 1;
      break;
    case OPERATIONS(RETURN):
      if (node->firstChild != NULL)
      {
        res = resolveExpression(node->firstChild, scope);
      }
      res.br = 2;
      break;
    default:
      break;
    }
    return res;
  }

  value resolveExpression(TreeNode *node, Scope *scope)
  {
    if (node->val.br > 0)
    {
      return node->val;
    }
    if (node->operation == OPERATIONS(FUNCTION))
    {
      return executeFunction(node, scope);
    }
    if (node->operation == OPERATIONS(AND_LOGIC))
    {
      return resolveLogic(node, scope);
    }
    if (node->operation == OPERATIONS(CONSTANT))
    {
      return node->val;
    }
    if (node->operation == OPERATIONS(VARIABLE))
    {
      string name = node->val.v.s;
      value val = scope->getValue(node->val.v.s);
      if (val.use.compare("nil") == 0)
      {
        auto panic = driver->createPanic("Variable not found");
        return panic;
      }
      return val;
    }

    value left = resolveExpression(node->firstChild, scope);
    if (left.br > 0)
    {
      return left;
    }
    value right = resolveExpression(node->secondChild, scope);
    if (right.br > 0)
    {
      return right;
    }
    value res = node->mergeValues(left, right);
    return res;
  }
  value resolveAssignment(TreeNode *node, Scope *scope)
  {
    TreeNode *tn = new TreeNode();

    value res = resolveExpression(node->thirdChild, scope);
    value cur = scope->getValue(node->val.v.s);
    string temp = node->secondChild->val.v.s;
    string name = node->val.v.s;
    if (temp.compare("=") == 0)
    {
      if (!scope->updateValue(name, res))
      {
        return driver->createPanic("assign a undefined variable.");
      }
    }
    if (temp.compare("*=") == 0)
    {
      tn->operation = OPERATIONS(MULTIPLY);
      res = tn->mergeValues(cur, res);
      if (!scope->updateValue(name, res))
      {
        return driver->createPanic("assign a undefined variable.");
      }
    }
    if (temp.compare("/=") == 0)
    {
      tn->operation = OPERATIONS(DIVIDE);
      res = tn->mergeValues(cur, res);
      if (!scope->updateValue(name, res))
      {
        return driver->createPanic("assign a undefined variable.");
      }
    }
    if (temp.compare("-=") == 0)
    {
      tn->operation = OPERATIONS(SUB);
      res = tn->mergeValues(cur, res);
      if (!scope->updateValue(name, res))
      {
        return driver->createPanic("assign a undefined variable.");
      }
    }
    if (temp.compare("+=") == 0)
    {
      tn->operation = OPERATIONS(SUM);
      res = tn->mergeValues(cur, res);
      if (!scope->updateValue(name, res))
      {
        return driver->createPanic("assign a undefined variable.");
      }
    }
    if (temp.compare("%=") == 0)
    {
      tn->operation = OPERATIONS(MOD);
      res = tn->mergeValues(cur, res);
      if (!scope->updateValue(name, res))
      {
        return driver->createPanic("assign a undefined variable.");
      }
    }
    return NIL_VALUE;
  }

  value resolveLogic(TreeNode *node, Scope *scope)
  {

    if (node == NULL)
    {
      cout << "resolve logic null" << endl;
    }
    if (node->operation == OPERATIONS(VARIABLE))
    {
      return scope->getValue(node->val.v.s);
    }
    if (node->operation == OPERATIONS(CONSTANT))
    {

      return node->val;
    }
    if (node->operation == OPERATIONS(EXPRESSION))
    {
      return node->val;
    }
    if (node->secondChild == NULL)
    {
      return resolveLogic(node->firstChild, scope);
    }
    if (node->operation != OPERATIONS(AND_LOGIC) && node->operation != OPERATIONS(OR_LOGIC))
    {
      value left = resolveExpression(node->firstChild, scope);
      value right = resolveExpression(node->secondChild, scope);
      return node->mergeLogic(left, right);
    }
    value left = resolveLogic(node->firstChild, scope);
    value right = resolveLogic(node->secondChild, scope);
    return node->mergeLogic(left, right);
  }
  value resolveFunctionDeclaration(TreeNode *node, Scope *scope)
  {
    string name = node->val.v.s;
    scope->setFunction(name, node);
    return NIL_VALUE;
  }

  value resolveDeclaration(TreeNode *node, Scope *scope)
  {
    if (node == NULL)
    {
      return NIL_VALUE;
    }
    string name = node->secondChild->val.v.s;
    value val = resolveExpression(node->thirdChild, scope);
    if (!scope->setValue(name, val))
    {
      value pnc = driver->createPanic("Variable allready declared.");
      return pnc;
    }
    return NIL_VALUE;
  }
  value executeFunction(TreeNode *node, Scope *scope)
  {
    string funcName = node->val.v.s;

    // Check for system functions
    if (funcName.compare("print") == 0)
    {
      korlang_print(node, scope);
    }
    else
    {
      auto fnode = scope->getFunction(funcName);
      if (fnode.isNil())
      {
        return NIL_VALUE;
      }
      auto childScope = scope->fork();
      auto fi = NodeIterator(fnode.firstChild);
      auto pi = NodeIterator(node->firstChild);
      while (!pi.isEmpty() && !fi.isEmpty())
      {

        auto p = pi.get();
        auto f = fi.get();

        value lv = resolveExpression(&p, scope);
        string ln = f.val.v.s;
        childScope->setValue(ln, lv);

        fi.done();
        pi.done();
      }

      value v = handleStatements(fnode.secondChild, childScope);
      if (v.br == 2)
      {
        v.br = 0;
        return v;
      }
    }

    return NIL_VALUE;
  }
  void korlang_print(TreeNode *node, Scope *scope)
  {
    if (node->firstChild != NULL)
    {

      auto it = NodeIterator(node->firstChild);

      while (!it.isEmpty())
      {
        TreeNode t = it.get();
        if (node != NULL)
        {
          value val = resolveExpression(&t, scope);
          driver->printValueInline(val);
          cout << "  ";
        }
        it.done();
      }
      cout << endl;
    }
    else
    {
      cout << endl;
    }
  }
  value executeLoop(TreeNode *node, Scope *scope)
  {
    // if second child is null, it's a infinite loop
    if (node->secondChild == NULL)
    {
      while (1)
      {
        auto childScope = scope->fork();
        value tr = handleStatements(node->firstChild, childScope);
        if (tr.br == 1)
        {
          tr.br = 0;
          return tr;
        }
      }
    }
    // if thirth child is null, it's a while loop
    if (node->thirdChild == NULL)
    {
      value res = resolveLogic(node->firstChild, scope);
      while (res.v.i > 0)
      {
        auto childScope = scope->fork();
        value tr =
            handleStatements(node->secondChild, childScope);
        if (tr.br == 1)
        {
          tr.br = 0;
          return tr;
        }
        else if (tr.br > 0)
        {
          return tr;
        }
        res = resolveLogic(node->firstChild, scope);
      }
    }
    // otherwise, it's a for loop
    else
    {
      // Execute initial statement.
      handleStatement(node->firstChild, scope);
      // Execute logical expression.
      value res = resolveLogic(node->secondChild, scope);
      while (res.v.i > 0)
      {
        auto childScope = scope->fork();
        // handle statements
        value tr = handleStatements(node->fourthChild, childScope);
        if (tr.br == 1)
        {
          tr.br = 0;
          return tr;
        }
        else if (tr.br > 0)
        {
          return tr;
        }
        // Execute after loop statement.
        handleStatement(node->thirdChild, scope);
        // Update logic state
        res = resolveLogic(node->secondChild, scope);
      }
    }
    return NIL_VALUE;
  }

  value executeTryCatch(TreeNode *node, Scope *scope)
  {

    //Execute try
    auto childScope = scope->fork();
    value val = handleStatements(node->firstChild, childScope);
    if (val.br == 3)
    {
      auto childScope = scope->fork();
      val.br = 0;
      childScope->setValue("err", val);
      value resv = handleStatements(node->secondChild, childScope);
      cout << "br : " << resv.br << endl;
      return resv;
    }

    return val;
  }

  value executeIf(TreeNode *node, Scope *scope)
  {
    auto childScope = scope->fork();
    value v = resolveLogic(node->firstChild, scope);
    if (v.v.i > 0)
    {
      value v = handleStatements(node->secondChild, childScope);
      return v;
    }
    return NIL_VALUE;
  }
  value executeIfElse(TreeNode *node, Scope *scope)
  {
    value v = resolveLogic(node->firstChild, scope);
    if (v.v.i > 0)
    {
      handleStatements(node->secondChild, scope);
    }
    else
    {
      handleStatements(node->thirdChild, scope);
    }
    return NIL_VALUE;
  }
};

#endif