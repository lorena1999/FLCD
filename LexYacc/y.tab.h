/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

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
    HI = 258,
    BYE = 259,
    ID = 260,
    CONST = 261,
    IF = 262,
    WHILE = 263,
    LET = 264,
    WRITE = 265,
    READ = 266,
    COLON = 267,
    SEMICOLON = 268,
    DOT = 269,
    MULTIPLY = 270,
    DIVISION = 271,
    PLUS = 272,
    MINUS = 273,
    COMMA = 274,
    EQUAL = 275,
    LESS_THAN = 276,
    GREATER_THAN = 277,
    ASSIGNMENT = 278,
    LEFT_ROUND_PARANTHESIS = 279,
    RIGHT_ROUND_PARANTHESIS = 280,
    LEFT_SQUARE_PARANTHESIS = 281,
    RIGHT_SQUARE_PARANTHESIS = 282,
    LEFT_CURLY_BRACKET = 283,
    RIGHT_CURLY_BRACKET = 284,
    INTEGER = 285,
    STRING = 286
  };
#endif
/* Tokens.  */
#define HI 258
#define BYE 259
#define ID 260
#define CONST 261
#define IF 262
#define WHILE 263
#define LET 264
#define WRITE 265
#define READ 266
#define COLON 267
#define SEMICOLON 268
#define DOT 269
#define MULTIPLY 270
#define DIVISION 271
#define PLUS 272
#define MINUS 273
#define COMMA 274
#define EQUAL 275
#define LESS_THAN 276
#define GREATER_THAN 277
#define ASSIGNMENT 278
#define LEFT_ROUND_PARANTHESIS 279
#define RIGHT_ROUND_PARANTHESIS 280
#define LEFT_SQUARE_PARANTHESIS 281
#define RIGHT_SQUARE_PARANTHESIS 282
#define LEFT_CURLY_BRACKET 283
#define RIGHT_CURLY_BRACKET 284
#define INTEGER 285
#define STRING 286

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
