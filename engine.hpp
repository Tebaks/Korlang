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
    handleStatements(root);
  }

private:
  void handleStatements(TreeNode *node)
  {
    if (node == NULL)
    {
      return;
    }
    // Handle statements with bottom up prenciple
    handleStatements(node->firstChild);
    value val = handleStatement(node->secondChild);
    }
  value handleStatement(TreeNode *node)
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
      res = resolveExpression(node->firstChild);
      res.use = "expression";
      break;
    case OPERATIONS(DECLARATION):
      resolveDeclaration(node);
      break;
    case OPERATIONS(LOOP):
      executeLoop(node);
      break;
    case OPERATIONS(AND_LOGIC):
      res = resolveLogic(node);
      res.use = "bool";
      break;
    case OPERATIONS(IF_LOGIC):
      executeIf(node);
      break;
    case OPERATIONS(IF_ELSE_LOGIC):
      executeIfElse(node);
      break;
    case OPERATIONS(ASSIGNMENT):
      resolveAssignment(node);
      break;
    case OPERATIONS(FUNCTION):
      executeFunction(node);
      break;
    default:
      break;
    }
    return res;
  }

  value resolveExpression(TreeNode *node)
  {

    if (node->operation == OPERATIONS(CONSTANT))
    {
      return node->val;
    }
    if (node->operation == OPERATIONS(VARIABLE))
    {
      string name = node->val.v.s;
      return driver->getValue(node->val.v.s);
    }

    value left = resolveExpression(node->firstChild);
    value right = resolveExpression(node->secondChild);
    value res = node->mergeValues(left, right);
    return res;
  }
  void resolveAssignment(TreeNode *node)
  {
    TreeNode *tn = new TreeNode();

    value res = resolveExpression(node->thirdChild);
    value cur = driver->getValue(node->val.v.s);
    string temp = node->secondChild->val.v.s;
    string name = node->val.v.s;
    if (temp.compare("=") == 0)
    {
      driver->updateValue(name, res);
    }
    if (temp.compare("*=") == 0)
    {
      tn->operation = OPERATIONS(MULTIPLY);
      res = tn->mergeValues(cur, res);
      driver->updateValue(name, res);
    }
    if (temp.compare("/=") == 0)
    {
      tn->operation = OPERATIONS(DIVIDE);
      res = tn->mergeValues(cur, res);
      driver->updateValue(name, res);
    }
    if (temp.compare("-=") == 0)
    {
      tn->operation = OPERATIONS(SUB);
      res = tn->mergeValues(cur, res);
      driver->updateValue(name, res);
    }
    if (temp.compare("+=") == 0)
    {
      tn->operation = OPERATIONS(SUM);
      res = tn->mergeValues(cur, res);
      driver->updateValue(name, res);
    }
  }

  value resolveLogic(TreeNode *node)
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
      return resolveLogic(node->firstChild);
    }
    if (node->operation != OPERATIONS(AND_LOGIC) && node->operation != OPERATIONS(OR_LOGIC))
    {
      value left = resolveExpression(node->firstChild);
      value right = resolveExpression(node->secondChild);
      return node->mergeLogic(left, right);
    }
    value left = resolveLogic(node->firstChild);
    value right = resolveLogic(node->secondChild);
    return node->mergeLogic(left, right);
  }

  void resolveDeclaration(TreeNode *node)
  {
    if (node == NULL)
    {
      return;
    }
    string name = node->secondChild->val.v.s;
    value val = resolveExpression(node->thirdChild);
    driver->setValue(name, val);
  }
  void executeFunction(TreeNode *node)
  {
    string funcName = node->val.v.s;
    // Check for system functions

    if (funcName.compare("print") == 0)
    {
      korlang_print(node->firstChild);
    }
  }
  void korlang_print(TreeNode *node)
  {
    if (node != NULL)
    {
      value val = resolveExpression(node);
      driver->printValue(val);
    }
    else
    {
      cout << endl;
    }
  }
  void executeLoop(TreeNode *node)
  {
    // if second child is null, it's a infinite loop
    if (node->secondChild == NULL)
    {
      while (1)
      {
        handleStatements(node->firstChild);
      }
    }
    // if thirth child is null, it's a while loop
    if (node->thirdChild == NULL)
    {
      value res = resolveLogic(node->firstChild);
      while (res.v.i > 0)
      {
        handleStatements(node->secondChild);
        res = resolveLogic(node->firstChild);
      }
    }
    // otherwise, it's a for loop
    else
    {
      // Execute initial statement.
      handleStatement(node->firstChild);
      // Execute logical expression.
      value res = resolveLogic(node->secondChild);
      while (res.v.i > 0)
      {
        // handle statements
        handleStatements(node->fourthChild);
        // Execute after loop statement.
        handleStatement(node->thirdChild);
        // Update logic state
        res = resolveLogic(node->secondChild);
      }
    }
  }
  void executeIf(TreeNode *node)
  {
    value v = resolveLogic(node->firstChild);
    if (v.v.i > 0)
    {
      handleStatements(node->secondChild);
    }
  }
  void executeIfElse(TreeNode *node)
  {
    value v = resolveLogic(node->firstChild);
    if (v.v.i > 0)
    {
      handleStatements(node->secondChild);
    }
    else
    {
      handleStatements(node->thirdChild);
    }
  }
};

#endif