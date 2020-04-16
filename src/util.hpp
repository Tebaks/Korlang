#ifndef UTIL
#define UTIL

#include <stack>
#include "tree.hpp"

using namespace std;

class StatementsBreaker
{
public:
  TreeNode *value;
  bool isReturn;
};

class NodeIterator
{
private:
  stack<TreeNode> s;

public:
  NodeIterator(TreeNode *root)
  {
    s = stack<TreeNode>();
    while (root != NULL)
    {
      if (root->secondChild != NULL)
      {
        s.push(*(root->secondChild));
      }
      root = root->firstChild;
    }
  }

  TreeNode get()
  {
    return s.top();
  }
  void done()
  {
    return s.pop();
  }

  bool isEmpty()
  {
    return s.size() == 0;
  }
};

#endif