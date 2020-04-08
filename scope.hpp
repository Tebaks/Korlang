#ifndef SCOPE
#define SCOPE
#include <iostream>
#include <cstdlib>
#include <map>
#include <vector>

#include "bucket.hpp"

using namespace std;

class Scope
{
private:
  vector<Scope> inner;
  Scope *parentScope;

public:
  Bucket<float> floats;
  Bucket<int> integers;
  Bucket<string> strings;
  Scope() : inner(vector<Scope>()),
            floats(Bucket<float>()),
            integers(Bucket<int>()),
            strings(Bucket<string>())
  {
  }
};

#endif