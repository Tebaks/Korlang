#ifndef ENGINE
#define ENGINE

#include <iostream>
#include <string>
#include <libgen.h>
#include <thread>
#include <future>
#include <unistd.h>
#define GetCurrentDir getcwd
#include "tree.hpp"
#include "korlang.tab.hpp"
#include "driver.hpp"
#include "util.hpp"
using namespace std;

class Engine
{
public:
  Driver *driver;
  Engine() : driver(new Driver()), args(vector<char *>())
  {
  }
  void execute(TreeNode *root)
  {
    auto scope = driver->getScope();

    string fNames[] = {"print", "append", "len", "array", "random", "input", "sleep", "int", "float", "panic"};
    for (int x = 0; x < sizeof(fNames) / sizeof(fNames[0]); x++)
    {
      driver->createfString(fNames[x], scope);
    }

    for (int i = 0; i < args.size(); ++i)
    {
      string name = "argv";
      value val;
      val.use = "string";
      val.v.s = args[i];
      scope->setArrayValue(name, i, val);
    }
    value argv;
    argv.use = "array";
    argv.v.i = args.size();
    scope->setValue("argv", argv);
    value val = handleStatements(root, scope);
    //driver->printValue(val);
  }
  void add(int argc, char **argv)
  {
    for (int i = 0; i < argc; ++i)
    {
      args.push_back(argv[i]);
    }
  }

private:
  TreeNode *tempNode;
  vector<char *> args;
  value handleStatements(TreeNode *node, Scope *scope)
  {
    NodeIterator it = NodeIterator(node);
    value v;
    while (!it.isEmpty())
    {

      auto statement = it.get();
      v = handleStatement(&statement, scope);
      if (v.br > 0)
      {

        return v;
      }
      if (tempNode != NULL)
      {
        handleStatement(tempNode, scope);
        tempNode = NULL;
      }
      it.done();
    }
    return v;
  }
  value handleStatement(TreeNode *node, Scope *scope)
  {
    value res;
    res.use = "na";
    if (node == NULL)
    {
      return res;
    }
    // Handle statement type.
    switch (node->operation)
    {
    case OPERATIONS(EXPRESSION):
      res = resolveExpression(node->firstChild, scope);
      res.use = "expression";

      break;
    case OPERATIONS(DECLARATION):
      res = resolveDeclaration(node, scope);
      break;
    case OPERATIONS(LOOP):
      res = executeLoop(node, scope);
      break;
    case OPERATIONS(IMPORT_STMT):
      res = resolveImportStatement(node, scope);
      break;
    case OPERATIONS(TRY_CATCH):
      res = executeTryCatch(node, scope);
      break;
    case OPERATIONS(AND_LOGIC):
      res = resolveLogic(node, scope);
      res.use = "bool";
      break;
    case OPERATIONS(IF_LOGIC):
      res = executeIf(node, scope);
      break;
    case OPERATIONS(IF_ELSE_LOGIC):
      res = executeIfElse(node, scope);
      break;
    case OPERATIONS(ASSIGNMENT):
      res = resolveAssignment(node, scope);
      break;
    case OPERATIONS(ARR_ASSIGNMENT):
      res = resolveArrAssignment(node, scope);
      break;
    case OPERATIONS(FUNCTION):
      res = executeFunction(node, scope);
      break;
    case OPERATIONS(ARRAY_DEF):
      res = resolveArrayDef(node, scope);
      break;
    case OPERATIONS(FUNCTION_DEC):
      res = resolveFunctionDeclaration(node, scope);
      break;
    case OPERATIONS(KOR_STMT):
      resolveKorStatement(node, scope);
      break;
    case OPERATIONS(EXTRACT_STMT):
      resolveExternStatement(node, scope);
      break;
    case OPERATIONS(OBJECT_DEF):
      resolveObjectDef(node, scope);
      break;
    case OPERATIONS(DOT_CALL):
      resolveDotCall(node, scope);
      break;
    case OPERATIONS(KORCON):
      executeKorcon(node, scope);
      break;
    case OPERATIONS(BREAK):
      res.br = 1;
      break;
    case OPERATIONS(RETURN):
      if (node->firstChild != NULL)
      {
        res = resolveExpression(node->firstChild, scope);
      }
      res.br = 2;
      break;
    default:
      break;
    }
    return res;
  }

  value resolveImportStatement(TreeNode *node, Scope *scope)
  {
    const char *fname = node->val.v.s;
    char exePath[PATH_MAX];
    ssize_t count = readlink("/proc/self/exe", exePath, PATH_MAX);
    char *path = dirname(exePath);
    strcat(path, "/");
    strcat(path, fname);
    FILE *file = fopen(path, "r");
    if (!file)
    {
      char ccwd[PATH_MAX];
      GetCurrentDir(ccwd, PATH_MAX);
      strcat(ccwd, "/");
      strcat(ccwd, fname);
      file = fopen(fname, "r");
    }

    TreeNode *nr = getRoot(file);
    auto childscope = scope->fork();
    handleStatements(nr, scope);
    return NIL_VALUE;
  }
  value resolveDotCall(TreeNode *node, Scope *scope)
  {
    auto it = new NodeIterator(node);
    auto n = it->get();
    value cur = scope->getValue(n.val.sval);
    it->done();
    while (!it->isEmpty())
    {
      auto n = it->get();
      cur = scope->getObjectValue(cur.sval, n.val.sval);
      it->done();
    }
    return cur;
  }
  value resolveExpression(TreeNode *node, Scope *scope)
  {
    if (node->val.br > 0)
    {
      return node->val;
    }
    if (node->operation == OPERATIONS(DOT_CALL))
    {
      return resolveDotCall(node, scope);
    }
    if (node->operation == OPERATIONS(INC_DEC))
    {
      return resolveIncDec(node, scope);
    }
    if (node->operation == OPERATIONS(ARRAY_ELEM))
    {
      return resolveArrayElem(node, scope);
    }
    if (node->operation == OPERATIONS(FUNCTION))
    {
      return executeFunction(node, scope);
    }
    if (node->operation == OPERATIONS(AND_LOGIC))
    {
      return resolveLogic(node, scope);
    }
    if (node->operation == OPERATIONS(CONSTANT))
    {
      return node->val;
    }
    if (node->operation == OPERATIONS(AN_FUNC_DEC))
    {
      string functionID = driver->generateFunctionID();
      driver->setFunctionScope(functionID, scope->fork());
      scope->setFunction(functionID, node);
      value temp;
      temp.use = "function";
      temp.sval = functionID;
      return temp;
    }
    if (node->operation == OPERATIONS(VARIABLE))
    {
      string name = node->val.v.s;
      value val = scope->getValue(node->val.v.s);

      if (val.use.compare("nil") == 0)
      {
        auto panic = driver->createPanic("Variable not found");
        return panic;
      }
      return val;
    }

    value left = resolveExpression(node->firstChild, scope);
    if (left.br > 0)
    {
      return left;
    }
    value right = resolveExpression(node->secondChild, scope);
    if (right.br > 0)
    {
      return right;
    }
    value res = node->mergeValues(left, right);

    return res;
  }

  value resolveObjectDef(TreeNode *node, Scope *scope)
  {
    string name = node->val.v.s;
    string objName = driver->generatingObjectID();

    auto it = NodeIterator(node->firstChild);
    while (!it.isEmpty())
    {
      auto n = it.get();
      value v = resolveExpression(n.firstChild, scope);
      string vn = n.val.v.s;
      scope->setObjectValue(objName, vn, v);
      it.done();
    }
    value t;
    t.use = "object";
    t.sval = objName;
    scope->setValue(name, t);
    return t;
  }

  value resolveArrayDef(TreeNode *node, Scope *scope)
  {
    string name = node->val.v.s;
    string arrName = driver->generatingArrID();
    int i = 0;
    auto it = NodeIterator(node->firstChild);
    while (!it.isEmpty())
    {
      auto n = it.get();

      value v = resolveExpression(&n, scope);
      scope->setArrayValue(arrName, i, v);
      it.done();
      i++;
    }
    // set base value as an array value
    value t;
    t.use = "array";
    t.sval = arrName;
    driver->setArraySize(arrName, i);
    scope->setValue(name, t);
    return t;
  }
  value resolveArrayElem(TreeNode *node, Scope *scope)
  {
    string vname = node->val.v.s;
    value hnd = scope->getValue(vname);
    string name = hnd.sval;
    value ind = resolveExpression(node->firstChild, scope);
    if (ind.use.compare("integer") == 0)
    {
      return scope->getArrayValue(name, ind.v.i);
    }
    if (ind.use.compare("string") == 0)
    {
      return scope->getObjectValue(name, ind.v.s);
    }
    cout << "not int " << ind.use << endl;
    return NIL_VALUE;
  }

  value resolveIncDec(TreeNode *node, Scope *scope)
  {
    if (node->firstChild->operation == OPERATIONS(POST_INC))
    {
      struct value temp;
      temp.v.s = "+=";
      temp.use = "string";
      TreeNode *tree1 = new TreeNode(temp, OPERATIONS(ASSIGNMENT_OPERATOR));

      struct value temp1;
      temp1.use = "integer";
      temp1.v.i = 1;
      TreeNode *tree2 = new TreeNode(temp1, OPERATIONS(CONSTANT));

      struct value temp2;
      temp2.use = "identifier";
      temp2.v.s = node->val.v.s;
      tempNode = new TreeNode(temp2, OPERATIONS(ASSIGNMENT), NULL, tree1, tree2, NULL);
    }

    return scope->getValue(node->val.v.s);
  }

  value resolveKorStatement(TreeNode *node, Scope *scope)
  {
    auto sn = node->firstChild;
    scope->isKorScope = true;
    Scope *cs = scope->fork();
    value v = handleStatements(sn, cs);
    scope->isKorScope = false;
    if (v.br > 0)
    {
      return v;
    }
    return NIL_VALUE;
  }

  value resolveExternStatement(TreeNode *node, Scope *scope)
  {
    auto sc = scope->getKorScope();
    string name = node->val.sval;
    value val = scope->getValue(name);
    scope->deleteValue(name);
    sc->setValue(name, val);
    return NIL_VALUE;
  }

  value resolveArrAssignment(TreeNode *node, Scope *scope)
  {

    string pn = scope->getValue(node->firstChild->val.v.s).sval;
    value v = resolveExpression(node->firstChild->firstChild, scope);
    value res = resolveExpression(node->thirdChild, scope);
    string temp = node->secondChild->val.v.s;
    if (v.use.compare("integer") == 0)
    {
      string name = scope->createArrayValueName(pn, v.v.i);
      value cur = scope->getValue(name);
      if (cur.use.compare("nil") == 0)
      {
        return driver->createPanic("Index out of bounds.");
      }
      return makeAssignment(cur, res, name, temp, scope);
    }
    if (v.use.compare("string") == 0)
    {
      if (v.sval == "")
      {
        v.sval = v.v.s;
      }
      string name = scope->createObjectValueName(pn, v.sval);
      value cur = scope->getValue(name);
      if (cur.use.compare("nil") == 0)
      {
        if (temp.compare("=") == 0)
        {
          scope->setObjectValue(pn, v.sval, res);
          return scope->getValue(name);
        }

        return driver->createPanic("Index out of bounds.");
      }
      return makeAssignment(cur, res, name, temp, scope);
    }
    return NIL_VALUE;
  }

  value resolveAssignment(TreeNode *node, Scope *scope)
  {

    value res = resolveExpression(node->thirdChild, scope);
    value cur = scope->getValue(node->val.v.s);
    string temp = node->secondChild->val.v.s;
    string name = node->val.v.s;
    return makeAssignment(cur, res, name, temp, scope);
  }

  value makeAssignment(value cur, value res, string name, string temp, Scope *scope)
  {
    TreeNode *tn = new TreeNode();

    if (temp.compare("=") == 0)
    {
      if (!scope->updateValue(name, res))
      {
        return driver->createPanic("assign a undefined variable.");
      }
    }
    if (temp.compare("*=") == 0)
    {
      tn->operation = OPERATIONS(MULTIPLY);
      res = tn->mergeValues(cur, res);
      if (!scope->updateValue(name, res))
      {
        return driver->createPanic("assign a undefined variable.");
      }
    }
    if (temp.compare("/=") == 0)
    {
      tn->operation = OPERATIONS(DIVIDE);
      res = tn->mergeValues(cur, res);
      if (!scope->updateValue(name, res))
      {
        return driver->createPanic("assign a undefined variable.");
      }
    }
    if (temp.compare("-=") == 0)
    {
      tn->operation = OPERATIONS(SUB);
      res = tn->mergeValues(cur, res);
      if (!scope->updateValue(name, res))
      {
        return driver->createPanic("assign a undefined variable.");
      }
    }
    if (temp.compare("+=") == 0)
    {
      tn->operation = OPERATIONS(SUM);
      res = tn->mergeValues(cur, res);
      if (!scope->updateValue(name, res))
      {
        return driver->createPanic("assign a undefined variable.");
      }
    }
    if (temp.compare("%=") == 0)
    {
      tn->operation = OPERATIONS(MOD);
      res = tn->mergeValues(cur, res);
      if (!scope->updateValue(name, res))
      {
        return driver->createPanic("assign a undefined variable.");
      }
    }
    return NIL_VALUE;
  }

  value resolveLogic(TreeNode *node, Scope *scope)
  {
    if (node == NULL)
    {
      cout << "resolve logic null" << endl;
    }
    if (node->operation == OPERATIONS(VARIABLE))
    {
      auto v = scope->getValue(node->val.v.s);
      if (v.use.compare("nil") == 0)
      {
        return driver->createPanic("Logic resolve error: variable not found.");
      }
      return v;
    }
    if (node->operation == OPERATIONS(CONSTANT))
    {
      return node->val;
    }
    if (node->operation == OPERATIONS(EXPRESSION))
    {
      return resolveExpression(node, scope);
    }
    if (node->secondChild == NULL)
    {
      return resolveLogic(node->firstChild, scope);
    }
    if (node->operation != OPERATIONS(AND_LOGIC) && node->operation != OPERATIONS(OR_LOGIC))
    {
      value left = resolveExpression(node->firstChild, scope);
      if (left.br > 0)
      {
        return left;
      }
      value right = resolveExpression(node->secondChild, scope);
      if (right.br > 0)
      {
        return right;
      }
      return node->mergeLogic(left, right);
    }
    value left = resolveLogic(node->firstChild, scope);
    value right = resolveLogic(node->secondChild, scope);
    return node->mergeLogic(left, right);
  }
  value resolveFunctionDeclaration(TreeNode *node, Scope *scope)
  {
    string name = node->val.v.s;
    string funcID = driver->generateFunctionID();
    value val;
    val.use = "function";
    val.sval = funcID;
    driver->setFunctionScope(funcID, (scope->fork()));
    scope->setFunction(funcID, node);
    scope->setValue(name, val);
    return NIL_VALUE;
  }

  value resolveDeclaration(TreeNode *node, Scope *scope)
  {
    if (node == NULL)
    {
      return NIL_VALUE;
    }
    string name = node->secondChild->val.v.s;
    value val = resolveExpression(node->thirdChild, scope);
    if (!scope->setValue(name, val))
    {
      value pnc = driver->createPanic("Variable allready declared.");
      return pnc;
    }
    return val;
  }
  value executeKorcon(TreeNode *node, Scope *scope)
  {
    return NIL_VALUE;
  }
  value executeFunction(TreeNode *node, Scope *scope)
  {
    bool isID = false;
    value expVal = resolveExpression(node->secondChild, scope);
    if (expVal.use.compare("function") == 0)
    {
      isID = true;
    }
    if (expVal.sval == "")
    {
      expVal.sval = expVal.v.s;
    }

    string funcName = expVal.sval;

    // Check for system functions
    if (funcName.compare("print") == 0)
    {
      korlang_print(node, scope);
      return NIL_VALUE;
    }
    else if (funcName.compare("sleep") == 0)
    {
      value val = resolveExpression(node->firstChild->secondChild, scope);
      if (val.use.compare("integer") == 0)
      {
        std::this_thread::sleep_for(std::chrono::seconds(val.v.i));
      }
      return NIL_VALUE;
    }
    else if (funcName.compare("int") == 0)
    {
      value val = resolveExpression(node->firstChild->secondChild, scope);
      return driver->korlang_toInt(val, scope);
    }
    else if (funcName.compare("append") == 0)
    {
      value val = resolveExpression(node->firstChild->secondChild, scope);
      value arrayVal = resolveExpression(node->firstChild->firstChild->secondChild, scope);
      return driver->korlang_append(arrayVal, val, scope);
    }
    else if (funcName.compare("float") == 0)
    {
      value val = resolveExpression(node->firstChild->secondChild, scope);
      return driver->korlang_toFloat(val, scope);
    }
    else if (funcName.compare("input") == 0)
    {
      value val = resolveExpression(node->firstChild->secondChild, scope);
      return driver->korlang_input(val, scope);
    }
    else if (funcName.compare("panic") == 0)
    {
      value val = resolveExpression(node->firstChild->secondChild, scope);
      return driver->korlang_invokePanic(val, scope);
    }
    else if (funcName.compare("len") == 0)
    {
      value val = resolveExpression(node->firstChild->secondChild, scope);
      return driver->korlang_len(val, scope);
    }
    else if (funcName.compare("random") == 0)
    {
      return driver->korlang_random(NIL_VALUE, scope);
    }
    else if (funcName.compare("array") == 0)
    {
      value val = resolveExpression(node->firstChild->secondChild, scope);
      return driver->korlang_makeArray(val, scope);
    }

    else
    {
      auto fid = scope->getValue(funcName).sval;
      if (isID)
      {
        fid = funcName;
      }
      auto fnode = scope->getFunction(fid);
      if (fnode.isNil())
      {
        cout << "fnode boş" << endl;
        return driver->createPanic("Function not found");
      }
      auto childScope = driver->getFunctionScope(fid);
      auto fi = NodeIterator(fnode.firstChild);
      auto pi = NodeIterator(node->firstChild);
      while (!pi.isEmpty() && !fi.isEmpty())
      {

        auto p = pi.get();
        auto f = fi.get();

        value lv = resolveExpression(&p, scope);
        string ln = f.val.v.s;
        childScope->setValue(ln, lv);

        fi.done();
        pi.done();
      }
      value v = handleStatements(fnode.secondChild, childScope);

      if (v.br > 0)
      {
        if (v.br == 2)
        {
          v.br = 0;
        }
        return v;
      }
    }

    return NIL_VALUE;
  }
  void korlang_print(TreeNode *node, Scope *scope)
  {
    if (node->firstChild != NULL)
    {

      auto it = NodeIterator(node->firstChild);

      while (!it.isEmpty())
      {
        TreeNode t = it.get();
        if (node != NULL)
        {
          value val = resolveExpression(&t, scope);
          if (val.use.compare("array") == 0)
          {
            string aname = val.sval;
            cout << "[ ";
            for (int x = 0; x < driver->getArraySize(aname).v.i; x++)
            {
              driver->printValueInline(scope->getArrayValue(aname, x));
              cout << "  ";
            }
            cout << " ]" << endl;
          }
          driver->printValueInline(val);
        }
        it.done();
      }
      cout << endl;
    }
    else
    {
      cout << endl;
    }
  }
  value executeLoop(TreeNode *node, Scope *scope)
  {
    // if second child is null, it's a infinite loop
    if (node->secondChild == NULL)
    {
      while (1)
      {
        auto childScope = scope->fork();
        value tr = handleStatements(node->firstChild, childScope);
        if (tr.br == 1)
        {
          tr.br = 0;
          return tr;
        }
      }
    }
    // if thirth child is null, it's a while loop
    if (node->thirdChild == NULL)
    {
      value res = resolveLogic(node->firstChild, scope);
      while (res.v.i > 0)
      {
        auto childScope = scope->fork();
        value tr =
            handleStatements(node->secondChild, childScope);
        if (tr.br == 1)
        {
          tr.br = 0;
          return tr;
        }
        else if (tr.br > 0)
        {
          return tr;
        }
        res = resolveLogic(node->firstChild, scope);
      }
    }
    // otherwise, it's a for loop
    else
    {
      auto childScope = scope->fork();
      // Execute initial statement.
      handleStatement(node->firstChild, childScope);
      // Execute logical expression.
      value res = resolveLogic(node->secondChild, childScope);
      while (res.v.i > 0)
      {
        auto cscope = childScope->fork();
        // handle statements
        value tr = handleStatements(node->fourthChild, cscope);
        if (tr.br == 1)
        {
          tr.br = 0;
          return tr;
        }
        else if (tr.br > 0)
        {
          return tr;
        }
        // Execute after loop statement.
        handleStatement(node->thirdChild, cscope);
        if (tempNode != NULL)
        {
          handleStatement(tempNode, cscope);
          tempNode = NULL;
        }
        // Update logic state
        res = resolveLogic(node->secondChild, childScope);
      }
    }
    return NIL_VALUE;
  }

  value executeTryCatch(TreeNode *node, Scope *scope)
  {

    //Execute try
    auto childScope = scope->fork();
    value val = handleStatements(node->firstChild, childScope);
    if (val.br == 3)
    {
      auto childScope = scope->fork();
      val.br = 0;
      childScope->setValue("err", val);
      value resv = handleStatements(node->secondChild, childScope);
      return resv;
    }

    return val;
  }

  value executeIf(TreeNode *node, Scope *scope)
  {
    auto childScope = scope->fork();
    value v = resolveLogic(node->firstChild, scope);
    if (v.v.i > 0)
    {
      value v = handleStatements(node->secondChild, childScope);
      return v;
    }
    return NIL_VALUE;
  }
  value executeIfElse(TreeNode *node, Scope *scope)
  {
    value v = resolveLogic(node->firstChild, scope);
    if (v.v.i > 0)
    {
      handleStatements(node->secondChild, scope);
    }
    else
    {
      handleStatements(node->thirdChild, scope);
    }
    return NIL_VALUE;
  }
};

#endif