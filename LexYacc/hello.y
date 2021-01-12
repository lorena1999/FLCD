%{
#include <stdio.h>
#include <stdlib.h>

int yylex(void);
int yyerror(const char *s);

%}

%token HI
%token BYE

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
declaration : decl1 const_opt SEMICOLON ;
decl1 : LET ID COLON type ;
type : INTEGER | STRING ;
const_opt : LEFT_SQUARE_PARANTHESIS CONST RIGHT_SQUARE_PARANTHESIS | eps ;
decl_opt : declaration_list | eps ;
stmt_list : stmt stmt_opt ;
stmt : assign_stmt | IO_stmt | struct_stmt ;
stmt_opt : stmt_list | eps ;
assign_stmt : ID EQUAL expression SEMICOLON ;
expression : B A ;
A : PLUS B A | eps ;
B : D C ;
C : MULTIPLY D C | eps ;
D : F E ;
E : DIVISION F E | eps ;
F : H G ;
G : MINUS H G | eps ;
H : LEFT_ROUND_PARANTHESIS expression RIGHT_ROUND_PARANTHESIS | term ;
term : CONST | ID ;
struct_stmt : cmpd_stmt | if_stmt | while_stmt ;
cmpd_stmt : LEFT_CURLY_BRACKET stmt_list RIGHT_CURLY_BRACKET ;
if_stmt : IF LEFT_ROUND_PARANTHESIS condition RIGHT_ROUND_PARANTHESIS cmpd_stmt ;
condition : expression relation expression ;
relation : LESS_THAN | GREATER_THAN ;
while_stmt : WHILE LEFT_ROUND_PARANTHESIS condition RIGHT_ROUND_PARANTHESIS cmpd_stmt ;
IO_stmt : READ LEFT_ROUND_PARANTHESIS ID RIGHT_ROUND_PARANTHESIS SEMICOLON | WRITE LEFT_ROUND_PARANTHESIS term RIGHT_ROUND_PARANTHESIS SEMICOLON ;
program : declaration_list ;
declaration_list : declaration decl_opt | stmt_list ;
