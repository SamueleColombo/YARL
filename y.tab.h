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

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    INTEGER = 258,
    REAL = 259,
    STRING = 260,
    BOOLEAN = 261,
    ID = 262,
    ASSIGN = 263,
    CREATE = 264,
    PROJECT = 265,
    SELECT = 266,
    UPDATE = 267,
    EXTEND = 268,
    RENAME = 269,
    JOIN = 270,
    READ = 271,
    WRITE = 272,
    AND = 273,
    OR = 274,
    NE = 275,
    GE = 276,
    LE = 277,
    NOT = 278,
    INTCONST = 279,
    REALCONST = 280,
    STRCONST = 281,
    BOOLCONST = 282,
    ERROR = 283,
    EQ = 284,
    GT = 285,
    LT = 286,
    PLUS = 287,
    MINUS = 288,
    TIMES = 289,
    OBELUS = 290,
    NEG = 291
  };
#endif
/* Tokens.  */
#define INTEGER 258
#define REAL 259
#define STRING 260
#define BOOLEAN 261
#define ID 262
#define ASSIGN 263
#define CREATE 264
#define PROJECT 265
#define SELECT 266
#define UPDATE 267
#define EXTEND 268
#define RENAME 269
#define JOIN 270
#define READ 271
#define WRITE 272
#define AND 273
#define OR 274
#define NE 275
#define GE 276
#define LE 277
#define NOT 278
#define INTCONST 279
#define REALCONST 280
#define STRCONST 281
#define BOOLCONST 282
#define ERROR 283
#define EQ 284
#define GT 285
#define LT 286
#define PLUS 287
#define MINUS 288
#define TIMES 289
#define OBELUS 290
#define NEG 291

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
