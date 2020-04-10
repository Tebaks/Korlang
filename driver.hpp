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
    cout << val.v.i << endl;
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
};

#endif
