#ifndef DRIVER_
#define DRIVER_

#include <iostream>
#include <cstdlib>
#include <map>
#include <string>
#include "scope.hpp"
#include "bucket.hpp"
#include "tree.hpp"

using namespace std;

class Driver
{
private:
  Scope *scope;

public:
  Driver() : scope(new Scope()) {}

  Scope *getScope()
  {
    return this->scope;
  }
  int getInt(string name)
  {
    return scope->integers.getValue(name);
  }
  bool setInt(string name, int val)
  {
    scope->integers.setValue(name, val);
    return true;
  }

  float getFloat(string name)
  {
    return scope->floats.getValue(name);
  }
  bool setFloat(string name, float val)
  {
    scope->floats.setValue(name, val);
    return true;
  }

  string getString(string name)
  {
    return scope->strings.getValue(name);
  }
  bool setInt(string name, string val)
  {
    scope->strings.setValue(name, val);
    return true;
  }

  void printValue(value val)
  {
    printValueInline(val);
    cout << endl;
  }

  void printValueInline(value val)
  {
    string s = val.use;
    if (s.compare("integer") == 0)
    {
      cout << val.v.i;
    }
    else if (s.compare("boolean") == 0)
    {
      if (val.v.i > 0)
      {
        cout << "true";
      }
      else
      {
        cout << "false";
      }
    }
    else if (s.compare("string") == 0)
    {
      cout << val.v.s;
    }
    else
    {
      cout << val.use;
    }
  }

  value getValue(string name)
  {
    return scope->values.getValue(name);
  }
  bool setValue(string name, value val)
  {
    if (!scope->values.isExist(name))
    {
      scope->values.setValue(name, val);
      return true;
    }
    return false;
  }
  void updateValue(string name, value val)
  {
    if (scope->values.isExist(name))
    {
      scope->values.updateValue(name, val);
    }
  }

  TreeNode getFunction(string name)
  {
    return scope->functions.getValue(name);
  }

  void setFunction(string name, TreeNode node)
  {
    scope->functions.setValue(name, node);
  }
};

#endif
