#ifndef ENGINE
#define ENGINE

#include <iostream>
#include "tree.hpp"

using namespace std;

class Engine
{
public:
  int count;
  Engine() : count(0)
  {
  }
  void execute(TreeNode *root)
  {
    int res = resolveIntegerTree(root->firstChild);
    cout << res << endl;
    }

private:
  int resolveIntegerTree(TreeNode *node)
  {
    if (node->operation == OPERATIONS(CONSTANT))
    {
      return node->val.v.i;
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