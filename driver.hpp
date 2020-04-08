#include <iostream>
#include <cstdlib>
#include <map>
#include "scope.hpp"
#include "kvalue.hpp"

class Driver
{
private:
  Scope *scope;
  std::string message;

public:
  Driver() : scope(new Scope()) {}
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
  bool setValue(std::string name, KValue val)
  {
    (*scope).insert(std::pair<std::string, KValue>(name, val));
    return true;
  }

  /**
   * 
   * @param name : name of the variable
   * @param val : value of variable
   * @returns if an error occurs return false otherwise returns true
   * 
   */
  bool updateValue(std::string name, KValue val)
  {
    (*scope).insert(std::pair<std::string, KValue>(name, val));
    return true;
  }

  /**
   * @param name : name of the variable
   * @returns value of variable by default 0.
   */
  KValue getValue(std::string name)
  {
    KValue val = (*scope)[name];
    return val;
  }
};
