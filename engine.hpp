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
    string s = val.use;
    if (s.compare("na") != 0)
      driver->printValue(val);
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
      break;
    case OPERATIONS(DECLARATION):
      resolveDeclaration(node);
      break;
    case OPERATIONS(LOOP):
      executeLoop(node);
      break;
    case OPERATIONS(AND_LOGIC):
      res = resolveLogic(node);
      break;
    case OPERATIONS(IF_LOGIC):
      executeIf(node);
      break;
    case OPERATIONS(IF_ELSE_LOGIC):
      executeIfElse(node);
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

  void executeLoop(TreeNode *node)
  {
    cout << "BEFORE LOOP" << endl;
    while (1)
    {
      handleStatements(node->firstChild);
    }
    cout << "AFTER LOOP" << endl;
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