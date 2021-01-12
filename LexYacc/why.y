%{
#include <stdio.h>
#include <stdlib.h>

int yylex(void);
int yyerror(const char *s);

%}

%token ID
%token CONST
%token IF
%token WHILE
%token LET
%token WRITE
%token READ
%token COLON
%token SEMICOLON
%token DOT
%token MULTIPLY
%token DIVISION
%token PLUS
%token MINUS
%token COMMA
%token EQUAL
%token LESS_THAN
%token GREATER_THAN
%token ASSIGNMENT
%token LEFT_ROUND_PARANTHESIS
%token RIGHT_ROUND_PARANTHESIS
%token LEFT_SQUARE_PARANTHESIS
%token RIGHT_SQUARE_PARANTHESIS
%token LEFT_CURLY_BRACKET
%token RIGHT_CURLY_BRACKET
%token INTEGER
%token STRING

%start program

%%

eps : ;
type : INTEGER | STRING;
decl1 : LET ID COLON type ;
const_opt : LEFT_SQUARE_PARANTHESIS CONST RIGHT_SQUARE_PARANTHESIS | eps;
declaration : decl1 const_opt SEMICOLON ;
decl_opt : declaration_list | eps ;	    
stmt : assign_stmt ;
expression : B A ;
A : PLUS B A | eps ;	   
B : D C   
assign_stmt : ID EQUAL expression SEMICOLON ;      	    
stmt_opt : stmt_list | eps ;
stmt_list : stmt stmt_opt ;      	 
declaration_list : declaration decl_opt | stmt_list ;	  
program : declaration_list ;
