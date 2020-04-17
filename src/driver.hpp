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
  int arr = 0;
  int obj = 0;
  int func = 0;
  Bucket<Scope *> functionScopes;
  Bucket<int> arraySizes;

public:
  Driver() : scope(new Scope()), functionScopes(Bucket<Scope *>()) {}

  string generatingArrID()
  {
    arr++;
    return "arr$" + to_string(arr);
  }

  string generateFunctionID()
  {
    func++;
    return "func$" + to_string(func);
  }

  void setFunctionScope(string name, Scope *scope)
  {
    functionScopes.setValue(name, scope);
  }

  Scope *getFunctionScope(string name)
  {
    return functionScopes.getValue(name);
  }

  string generatingObjectID()
  {
    obj++;
    return "obj$" + to_string(obj);
  }

  Scope *getScope()
  {
    return this->scope;
  }
  void updateFunctionScope(string name, Scope *scope)
  {
    functionScopes.updateValue(name, scope);
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
  value createfString(string fName, Scope *scope)
  {
    value temp;
    temp.use = "string";
    temp.sval = fName;
    scope->setValue(fName, temp);
    return NIL_VALUE;
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
    else if (s.compare("float") == 0)
    {
      cout << val.v.f;
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

  value korlang_makeArray(value v, Scope *scope)
  {
    if (v.use.compare("integer") != 0)
    {
      return NIL_VALUE;
    }
    value temp;
    temp.use = "integer";
    temp.v.i = 0;
    int n = v.v.i;
    string id = generatingArrID();
    for (int i = 0; i < n; i++)
    {
      scope->setArrayValue(id, i, temp);
    }
    value res;
    res.use = "array";
    res.sval = id;
    res.v.i = n;
    arraySizes.setValue(id, n);
    return res;
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
  value setArraySize(string arrName, int value)
  {
    arraySizes.setValue(arrName, value);
    return NIL_VALUE;
  }
  value getArraySize(string arrName)
  {
    struct value val;
    val.use = "integer";
    val.v.i = arraySizes.getValue(arrName);
    return val;
  }

  value korlang_len(value v, Scope *scope)
  {
    if (v.use.compare("array") == 0)
    {
      value temp;
      temp.v.i = arraySizes.getValue(v.sval);
      temp.use = "integer";
      return temp;
    }

    return NIL_VALUE;
  }
  value korlang_random(value v, Scope *scope)
  {
    srand(time(0));
    value temp;
    temp.v.i = rand();
    temp.use = "integer";
    return temp;
  }
  value korlang_append(value arrayVal, value val, Scope *scope)
  {

    string arrayID = arrayVal.sval;
    int arrayLast = arraySizes.getValue(arrayID);
    scope->setArrayValue(arrayID, arrayLast, val);
    arraySizes.updateValue(arrayID, arrayLast + 1);
    return arrayVal;
  }
  value korlang_toFloat(value v, Scope *scope)
  {
    if (v.use.compare("string") == 0)
    {
      float f = 0;
      if (v.sval == "")
      {
        auto c = v.v.s;
        f = atof(c);
      }
      else
      {
        string s = v.sval;
        f = stof(s);
      }
      v.v.f = f;
      v.use = "float";
      return v;
    }
    else if (v.use.compare("integer") == 0)
    {
      float f = static_cast<float>(v.v.i);
      v.v.f = f;
      v.use = "float";
      return v;
    }
    else if (v.use.compare("nil") == 0)
    {
    }
    return v;
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
      int i = 0;
      i = static_cast<int>(v.v.f);
      v.v.i = i;
      v.use = "integer";
      return v;
    }
    else if (v.use.compare("nil") == 0)
    {
    }

    return v;
  }
};

#endif
