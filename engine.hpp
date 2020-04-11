#ifndef ENGINE
#define ENGINE

#include <iostream>
#include <string>
#include "tree.hpp"
#include "driver.hpp"

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
    handleStatements(root, scope);
  }

private:
  void handleStatements(TreeNode *node, Scope *scope)
  {
    if (node == NULL)
    {
      return;
    }
    // Handle statements with bottom up prenciple
    handleStatements(node->firstChild, scope);
    value val = handleStatement(node->secondChild, scope);
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
      resolveDeclaration(node, scope);
      break;
    case OPERATIONS(LOOP):
      executeLoop(node, scope);
      break;
    case OPERATIONS(AND_LOGIC):
      res = resolveLogic(node, scope);
      res.use = "bool";
      break;
    case OPERATIONS(IF_LOGIC):
      executeIf(node, scope);
      break;
    case OPERATIONS(IF_ELSE_LOGIC):
      executeIfElse(node, scope);
      break;
    case OPERATIONS(ASSIGNMENT):
      resolveAssignment(node, scope);
      break;
    case OPERATIONS(FUNCTION):
      executeFunction(node, scope);
      break;
    default:
      break;
    }
    return res;
  }

  value resolveExpression(TreeNode *node, Scope *scope)
  {

    if (node->operation == OPERATIONS(CONSTANT))
    {
      return node->val;
    }
    if (node->operation == OPERATIONS(VARIABLE))
    {
      string name = node->val.v.s;
      return scope->getValue(node->val.v.s);
    }

    value left = resolveExpression(node->firstChild, scope);
    value right = resolveExpression(node->secondChild, scope);
    value res = node->mergeValues(left, right);
    return res;
  }
  void resolveAssignment(TreeNode *node, Scope *scope)
  {
    TreeNode *tn = new TreeNode();

    value res = resolveExpression(node->thirdChild, scope);
    value cur = scope->getValue(node->val.v.s);
    string temp = node->secondChild->val.v.s;
    string name = node->val.v.s;
    if (temp.compare("=") == 0)
    {
      scope->updateValue(name, res);
    }
    if (temp.compare("*=") == 0)
    {
      tn->operation = OPERATIONS(MULTIPLY);
      res = tn->mergeValues(cur, res);
      scope->updateValue(name, res);
    }
    if (temp.compare("/=") == 0)
    {
      tn->operation = OPERATIONS(DIVIDE);
      res = tn->mergeValues(cur, res);
      scope->updateValue(name, res);
    }
    if (temp.compare("-=") == 0)
    {
      tn->operation = OPERATIONS(SUB);
      res = tn->mergeValues(cur, res);
      scope->updateValue(name, res);
    }
    if (temp.compare("+=") == 0)
    {
      tn->operation = OPERATIONS(SUM);
      res = tn->mergeValues(cur, res);
      scope->updateValue(name, res);
    }
  }

  value resolveLogic(TreeNode *node, Scope *scope)
  {

    if (node == NULL)
    {
      cout << "resolve logic null" << endl;
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

  void resolveDeclaration(TreeNode *node, Scope *scope)
  {
    if (node == NULL)
    {
      return;
    }
    string name = node->secondChild->val.v.s;
    value val = resolveExpression(node->thirdChild, scope);
    scope->setValue(name, val);
  }
  void executeFunction(TreeNode *node, Scope *scope)
  {
    string funcName = node->val.v.s;
    // Check for system functions

    if (funcName.compare("print") == 0)
    {
      korlang_print(node->firstChild, scope);
    }
  }
  void korlang_print(TreeNode *node, Scope *scope)
  {
    if (node != NULL)
    {
      value val = resolveExpression(node, scope);
      driver->printValue(val);
    }
    else
    {
      cout << endl;
    }
  }
  void executeLoop(TreeNode *node, Scope *scope)
  {
    // if second child is null, it's a infinite loop
    if (node->secondChild == NULL)
    {
      while (1)
      {
        handleStatements(node->firstChild, scope);
      }
    }
    // if thirth child is null, it's a while loop
    if (node->thirdChild == NULL)
    {
      value res = resolveLogic(node->firstChild, scope);
      while (res.v.i > 0)
      {
        handleStatements(node->secondChild, scope);
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
        // handle statements
        handleStatements(node->fourthChild, scope);
        // Execute after loop statement.
        handleStatement(node->thirdChild, scope);
        // Update logic state
        res = resolveLogic(node->secondChild, scope);
      }
    }
  }
  void executeIf(TreeNode *node, Scope *scope)
  {
    auto childScope = scope->fork();
    value v = resolveLogic(node->firstChild, scope);
    if (v.v.i > 0)
    {
      handleStatements(node->secondChild, childScope);
    }
  }
  void executeIfElse(TreeNode *node, Scope *scope)
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
  }
};

#endif