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
  bool isKorScope;
  Bucket<value> values;
  Bucket<TreeNode> functions;
  Scope() : inner(vector<Scope>()),
            values(Bucket<value>()),
            functions(Bucket<TreeNode>())

  {
  }

  Scope *getKorScope()
  {
    if (isKorScope)
    {
      return this;
    }
    else if (parentScope != NULL)
    {
      return parentScope->getKorScope();
    }
    return this;
  }

  string createArrayValueName(string base, int index)
  {
    string s = to_string(index);
    return base + "$" + s;
  }
  Scope *fork()
  {
    auto res = new Scope();
    res->parentScope = this;
    return res;
  }

  value getValue(string name)
  {

    if (this->values.isExist(name))
    {
      value val = this->values.getValue(name);
      return val;
    }
    else if (this->parentScope != NULL)
    {
      return this->parentScope->getValue(name);
    }
    return NIL_VALUE;
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
  bool updateValue(string name, value val)
  {
    if (this->values.isExist(name))
    {
      this->values.updateValue(name, val);
      return true;
    }
    else if (this->parentScope != NULL)
    {
      return this->parentScope->updateValue(name, val);
    }
    return false;
  }

  bool deleteValue(string name)
  {
    if (values.isExist(name))
    {
      values.deleteValue(name);
      return true;
    }
    else if (parentScope != NULL)
    {
      return parentScope->deleteValue(name);
    }

    return false;
  }
  TreeNode getFunction(string name)
  {
    if (functions.isExist(name))
    {
      auto res = this->functions.getValue(name);
      return res;
    }
    else if (this->parentScope != NULL)
    {
      return this->parentScope->getFunction(name);
    }
    return NIL_TREE_NODE;
  }

  bool setFunction(string name, TreeNode *node)
  {
    if (!functions.isExist(name))
    {
      this->functions.setValue(name, *node);
      return true;
    }
    return false;
  }

  bool setArrayValue(string name, int index, value val)
  {
    string n = createArrayValueName(name, index);
    return setValue(n, val);
  }
  bool updateArrayValue(string name, int index, value val)
  {
    string n = createArrayValueName(name, index);
    return updateValue(n, val);
  }
  value getArrayValue(string name, int index)
  {
    string n = createArrayValueName(name, index);
    return getValue(n);
  }
};

#endif