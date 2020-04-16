
#include "engine.hpp"
#include "korlang.tab.hpp"

using namespace std;

int main(int argc, char **argv)
{
  Engine *engine = new Engine();
  argc--;
  argv++;
  engine->add(argc, argv);
  char *filename = argv[0];
  // open a file handle to a particular file:
  FILE *myfile = fopen(filename, "r");
  TreeNode *root = getRoot(myfile);
  engine->execute(root);
  argc--;
  argv++;
}