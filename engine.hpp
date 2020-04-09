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
    if (node->firstChild == NULL && node->secondChild == NULL)
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
  /**
   * @DEPRACETED
  */
  int resolveIntegerTree(TreeNode *node)
  {
    if (node->operation == OPERATIONS(CONSTANT))
    {
      return node->val.v.i;
    }
    if (node->operation == OPERATIONS(VARIABLE))
    {
      return driver->getInt(node->val.v.s);
    }
    int left = resolveIntegerTree(node->firstChild);
    int right = resolveIntegerTree(node->secondChild);

    switch (node->operation)
    {
    case OPERATIONS(SUM):
      return left + right;
    case OPERATIONS(MULTIPLY):
      return left * right;
    case OPERATIONS(DIVIDE):
      return left / right;
    case OPERATIONS(SUB):
      return left - right;
    default:
      return 0;
    }
  }
};

#endif