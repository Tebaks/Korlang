#include <iostream>
#include "kvalue.hpp"
using namespace std;

int main()
{

  KValue k = KValue("Ahmet");
  KValue l = KValue("ÖZCAN");
  KValue t = k + l;
  cout << t.str << t.number << endl;
}