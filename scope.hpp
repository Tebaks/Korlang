#ifndef SCOPE
#define SCOPE

#include <iostream>
#include <cstdlib>
#include <map>
#include <vector>

#include "bucket.hpp"
#include "tree.hpp"

using namespace std;

class Scope
{
private:
  vector<Scope> inner;
  Scope *parentScope;

public:
  Bucket<float> floats;
  Bucket<int> integers;
  Bucket<string> strings;
  Bucket<value> values;
  Bucket<TreeNode> functions;
  Scope() : inner(vector<Scope>()),
            floats(Bucket<float>()),
            integers(Bucket<int>()),
            strings(Bucket<string>()),
            values(Bucket<value>()),
            functions(Bucket<TreeNode>())

  {
  }

  Scope *fork()
  {
    auto res = new Scope();
    res->parentScope = this;
    return res;
  }

  value getValue(string name)
  {
    return this->values.getValue(name);
  }
  bool setValue(string name, value val)
  {
    if (!this->values.isExist(name))
    {
      this->values.setValue(name, val);
      return true;
    }
    return false;
  }
  void updateValue(string name, value val)
  {
    if (this->values.isExist(name))
    {
      this->values.updateValue(name, val);
    }
  }

  TreeNode getFunction(string name)
  {
    return this->functions.getValue(name);
  }

  void setFunction(string name, TreeNode node)
  {
    this->functions.setValue(name, node);
  }

  void destroy()
  {
  }
};

#endif