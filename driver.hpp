#include <iostream>
#include <cstdlib>
#include <map>
#include "scope.hpp"

class Driver
{
private:
  Scope *scope;
  std::string message;

public:
  Driver(std::string msg) : message(msg), scope(new Scope()) {}
  void echo(char *str)
  {
    std::cout << "HELLO:" << str << std::endl;
  }
  /**
   * 
   * @param name : name of the variable
   * @param val : value of variable
   * @returns if an error occurs return false otherwise returns true
   * 
   */
  bool setValue(std::string name, int val)
  {
    (*scope).insert(std::pair<std::string, int>(name, val));
    return true;
  }
  /**
   * @param name : name of the variable
   * @returns value of variable by default 0.
   */
  int getValue(std::string name)
  {
    int val = (*scope)[name];
    return val;
  }
};
