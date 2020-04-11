#ifndef SCOPE
#define SCOPE

#include <iostream>
#include <cstdlib>
#include <map>
#include <vector>

#include "bucket.hpp"
#include "tree.hpp"

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
  Bucket<value> values;
  Bucket<TreeNode> functions;
  Scope() : inner(vector<Scope>()),
            floats(Bucket<float>()),
            integers(Bucket<int>()),
            strings(Bucket<string>()),
            values(Bucket<value>()),
            functions(Bucket<TreeNode>())

  {
  }
};

#endif