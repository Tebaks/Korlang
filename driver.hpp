#ifndef DRIVER_
#define DRIVER_

#include <iostream>
#include <cstdlib>
#include <map>
#include <string>
#include "scope.hpp"
#include "bucket.hpp"

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
};

#endif
