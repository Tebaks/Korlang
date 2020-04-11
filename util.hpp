#ifndef UTIL
#define UTIL

#include <stack>
#include "tree.hpp"

using namespace std;

class ParamIterator
{
private:
  stack<TreeNode> s;

public:
  ParamIterator(TreeNode *root)
  {
    s = stack<TreeNode>();
    while (root != NULL)
    {
      s.push(*(root->secondChild));
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