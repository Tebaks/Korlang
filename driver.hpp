#ifndef DRIVER_
#define DRIVER_

#include <bits/stdc++.h>
#include <iostream>
#include <cstdlib>
#include <map>
#include <string>
#include <sstream>
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
      if (val.sval == "")
      {
        cout << val.v.s;
      }
      else
      {
        cout << val.sval;
      }
    }
  }
  value korlang_input(value v, Scope *scope)
  {
    value res;

    string s;
    cout << v.v.s;
    getline(cin, s);

    res.use = "string";
    res.sval = s;
    return res;
  }
  value korlang_invokePanic(value v, Scope *scope)
  {
    if (v.use.compare("string") == 0)
    {
      return createPanic(v.v.s);
    }
    else
    {
      return createPanic("");
    }
  }

  value korlang_len(value v, Scope *scope)
  {
    if (v.use.compare("array") == 0)
    {
      value temp;
      temp.v.i = v.v.i;
      temp.use = "integer";
      return temp;
    }

    return NIL_VALUE;
  }
  value korlang_toInt(value v, Scope *scope)
  {

    // if value is a string;
    if (v.use.compare("string") == 0)
    {
      int i = 0;
      if (v.sval == "")
      {
        auto c = v.v.s;
        i = atoi(c);
      }
      else
      {
        string s = v.sval;
        i = stoi(s);
      }
      v.v.i = i;
      v.use = "integer";
      return v;
    }
    else if (v.use.compare("float") == 0)
    {
    }
    else if (v.use.compare("nil") == 0)
    {
    }

    return v;
  }
};

#endif
