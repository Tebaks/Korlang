#ifndef ENGINE
#define ENGINE

#include <iostream>
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
    cout << "gotcha" << endl;
    /*
    root = root->firstChild;
    if (root->operation == OPERATIONS(ASSIGN))
    {
      resolveAssign(root);
    }
    else
    {
      int r = resolveIntegerTree(root);
      cout << r << endl;
    }*/
  }

private:
  void resolveAssign(TreeNode *node)
  {
    string name = node->secondChild->val.v.s;
    int val;
    if (node->thirdChild->operation == OPERATIONS(CONSTANT))
    {
      val = node->thirdChild->val.v.i;
    }
    else if (node->thirdChild->operation == OPERATIONS(VARIABLE))
    {
      string tname = node->thirdChild->val.v.s;
      val = driver->getInt(tname);
    }
    else
    {
      val = resolveIntegerTree(node->thirdChild);
    }
    driver->setInt(name, val);
  }
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