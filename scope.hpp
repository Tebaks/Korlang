#include <iostream>
#include <cstdlib>
#include <map>
#include <vector>

class Scope : public std::map<std::string, int>
{
private:
  std::vector<Scope> inner;
  Scope *parentScope;

public:
  Scope() : std::map<std::string, int>()
  {
  }
};