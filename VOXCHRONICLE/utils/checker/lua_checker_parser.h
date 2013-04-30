/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     AND = 258,
     BREAK = 259,
     DO = 260,
     ELSE = 261,
     ELSEIF = 262,
     END = 263,
     FALSE = 264,
     FOR = 265,
     FUNCTION = 266,
     IF = 267,
     IN = 268,
     LOCAL = 269,
     NIL = 270,
     NOT = 271,
     OR = 272,
     REPEAT = 273,
     RETURN = 274,
     THEN = 275,
     TRUE = 276,
     UNTIL = 277,
     WHILE = 278,
     CONCAT = 279,
     ELLIPSES = 280,
     EQ = 281,
     GE = 282,
     LE = 283,
     NE = 284,
     SPECIAL = 285,
     SPECIAL_CONST = 286,
     SPECIAL_NUMBER = 287,
     NUMBER = 288,
     STRING = 289,
     IDENTIFIER = 290,
     UNARY_OPERATOR = 291
   };
#endif
/* Tokens.  */
#define AND 258
#define BREAK 259
#define DO 260
#define ELSE 261
#define ELSEIF 262
#define END 263
#define FALSE 264
#define FOR 265
#define FUNCTION 266
#define IF 267
#define IN 268
#define LOCAL 269
#define NIL 270
#define NOT 271
#define OR 272
#define REPEAT 273
#define RETURN 274
#define THEN 275
#define TRUE 276
#define UNTIL 277
#define WHILE 278
#define CONCAT 279
#define ELLIPSES 280
#define EQ 281
#define GE 282
#define LE 283
#define NE 284
#define SPECIAL 285
#define SPECIAL_CONST 286
#define SPECIAL_NUMBER 287
#define NUMBER 288
#define STRING 289
#define IDENTIFIER 290
#define UNARY_OPERATOR 291




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 139 "lua_checker.y"
{
  char *string;			// Also used for identifiers
  double number;
  bool is_constant;		// For opt_const
  struct TypeInfo *type_info;
}
/* Line 1529 of yacc.c.  */
#line 128 "lua_checker_parser.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
} YYLTYPE;
# define yyltype YYLTYPE /* obsolescent; will be withdrawn */
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


