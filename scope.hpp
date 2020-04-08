#include <iostream>
#include <cstdlib>
#include <map>
#include <vector>
#include "kvalue.hpp"

class Scope : public std::map<std::string, KValue>
{
private:
  std::vector<Scope> inner;
  Scope *parent;

public:
  Scope() : std::map<std::string, KValue>()
  {
  }
  Scope(Scope *s) : std::map<std::string, KValue>()
  {
    this->parent = s;
  }
};