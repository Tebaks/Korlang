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
    cout << "bucket " << name << endl;
    values.insert(pair<string, T>(name, val));
  }
  bool isExist(string name)
  {
    return values.find(name) != values.end();
  }
  void updateValue(string name, T val)
  {
    values[name] = val;
  }
};

#endif