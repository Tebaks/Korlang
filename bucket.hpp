#ifndef BUCKET
#define BUCKET

#include <iostream>
#include <map>
#include <string>

using namespace std;

template <typename T>
class Bucket
{
private:
  map<string, T> values;

public:
  Bucket() : values(map<string, T>()) {}
  T getValue(string name)
  {
    return values[name];
  }
  void setValue(string name, T val)
  {
    values.insert(pair<string, T>(name, val));
  }
  bool isExist(string name)
  {
    return false;
  }
};

#endif