/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_CALC_TAB_HPP_INCLUDED
# define YY_YY_CALC_TAB_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 8 "calc.ypp" /* yacc.c:1909  */

#include <cstdlib> // for atoi
#include <iostream>
#include <string>
#include <map>
#include "colorout.hpp"
#include "driver.hpp"
#include "tree.hpp"
#include "engine.hpp"
#define NOTHING		struct value temp;temp.use="none";

using namespace std;

//-- Lexer prototype required by bison
int yylex(); 

// Global variables for printing in pretty colors
extern colorout resout;
extern colorout errout;

#line 65 "calc.tab.hpp" /* yacc.c:1909  */

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    INT = 258,
    FLOAT = 259,
    STRING = 260,
    VAR = 261,
    IDEN = 262,
    BOOL = 263,
    OPA = 264,
    OPM = 265,
    LP = 266,
    RP = 267,
    STOP = 268,
    ASSGN = 269,
    AND = 270,
    OR = 271,
    GTH = 272,
    LTH = 273,
    GTHEQ = 274,
    LTHEQ = 275,
    EQ = 276,
    NEQ = 277,
    SOP = 278,
    EOP = 279,
    SOB = 280,
    EOB = 281,
    SOCB = 282,
    EOCB = 283,
    RETURN = 284,
    IF = 285,
    FOR = 286,
    ELSE = 287,
    WHILE = 288,
    FUNC = 289,
    KOR = 290,
    STRUCT = 291,
    RANGE = 292
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 55 "calc.ypp" /* yacc.c:1909  */

  int ival;
  float fval; 
  char sym;
  char* id;
  TreeNode *tval;

#line 123 "calc.tab.hpp" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_CALC_TAB_HPP_INCLUDED  */
