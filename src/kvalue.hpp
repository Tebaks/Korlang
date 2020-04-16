#include <iostream>
#include <cstdlib>
#include <map>
#include <vector>
#include <string>
using namespace std;

enum ValueTypes
{
  NUMBER,
  STRING,
  NIL,
};

class KValue
{
public:
  ValueTypes type;
  float number;
  string str;
  KValue() : str(""), number(0.0), type(ValueTypes(NIL)) {}

  /*OPERATOR OVERLOADINGS*/
  KValue *operator+(KValue *kval)
  {
    KValue *res = new KValue();
    if (type == ValueTypes(STRING) && kval->type == ValueTypes(STRING))
    {
      res->type = ValueTypes(STRING);
      res->str = str + kval->str;
    }
    else if (type == ValueTypes(STRING) && kval->type == ValueTypes(NUMBER))
    {
      res->type = ValueTypes(STRING);
      string s = to_string(kval->number);
      res->str = str + s;
    }
    else
    {
      res->type = ValueTypes(NIL);
    }
    return res;
  }

  KValue *operator-(KValue *kval)
  {
    KValue *res = new KValue();
    if (type == ValueTypes(NUMBER) && kval->type == ValueTypes(NUMBER))
    {
      res->type = ValueTypes(NUMBER);
      res->number = number + kval->number;
    }
    else
    {
      res->type = ValueTypes(NIL);
    }
    return res;
  }
  KValue *operator*(KValue *kval)
  {
    KValue *res = new KValue();
    if (type == ValueTypes(NUMBER) && kval->type == ValueTypes(NUMBER))
    {
      res->type = ValueTypes(NUMBER);
      res->number = number * kval->number;
    }
    else
    {
      res->type = ValueTypes(NIL);
    }
    return res;
  }
  KValue *operator/(KValue *kval)
  {
    KValue *res = new KValue();
    if (type == ValueTypes(NUMBER) && kval->type == ValueTypes(NUMBER))
    {
      res->type = ValueTypes(NUMBER);
      res->number = number / kval->number;
    }
    else
    {
      res->type = ValueTypes(NIL);
    }
    return res;
  }

  KValue *operator+(float f)
  {
    if (type == ValueTypes(NUMBER))
    {
      this->number += f;
    }
    return this;
  }
  KValue *operator-(float f)
  {
    if (type == ValueTypes(NUMBER))
    {
      this->number -= f;
    }
    return this;
  }

  KValue *operator*(float f)
  {
    if (type == ValueTypes(NUMBER))
    {
      this->number *= f;
    }
    return this;
  }

  KValue *operator/(float f)
  {
    if (type == ValueTypes(NUMBER))
    {
      this->number /= f;
    }
    return this;
  }
  KValue *operator+(string s)
  {
    if (type == ValueTypes(STRING))
    {
      this->type = ValueTypes(STRING);
      this->str = str + s;
    }
    else if (type == ValueTypes(NUMBER))
    {
      this->type = ValueTypes(STRING);
      this->str = to_string(this->number) + s;
    }
    return this;
  }
};