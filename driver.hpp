#ifndef DRIVER_
#define DRIVER_

#include <iostream>
#include <cstdlib>
#include <map>
#include <string>
#include "scope.hpp"
#include "colorout.hpp"
#include "bucket.hpp"
#include "tree.hpp"

extern colorout errout;

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

  void printValue(value val)
  {
    printValueInline(val);
    cout << endl;
  }

  value createPanic(const char *message)
  {
    value res;
    res.use = "string";
    res.v.s = message;
    res.br = 3;
    return res;
  }

  void printValueInline(value val)
  {
    string s = val.use;
    if (val.br == 3)
    {
      errout << "ERR! " << val.v.s << endl;
    }
    else if (s.compare("integer") == 0)
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
};

#endif
