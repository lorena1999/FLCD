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

eps : {printf("eps\n");} ;
declaration : decl1 const_opt SEMICOLON {printf("declaraion\n");} ;
decl1 : LET ID COLON type {printf("decl1\n");} ;
type : INTEGER | STRING {printf("type\n");} ;
const_opt : LEFT_SQUARE_PARANTHESIS CONST RIGHT_SQUARE_PARANTHESIS | eps {printf("const_opt\n");} ;
decl_opt : declaration_list | eps {printf("decl_opt\n");} ;
stmt_list : stmt stmt_opt {printf("stmt_list\n");} ;
stmt : assign_stmt | IO_stmt | struct_stmt {printf("stmt\n");} ;
stmt_opt : stmt_list | eps {printf("stmt_opt\n");} ;
assign_stmt : ID EQUAL expression SEMICOLON {printf("assign_stmt\n");} ;
expression : B A {printf("expression\n");} ;
A : PLUS B A | eps {printf("A\n");} ;
B : D C {printf("B\n");} ;
C : MULTIPLY D C | eps {printf("C\n");} ;
D : F E {printf("D\n");} ;
E : DIVISION F E | eps {printf("E\n");} ;
F : H G {printf("F\n");} ;
G : MINUS H G | eps {printf("G\n");} ;
H : LEFT_ROUND_PARANTHESIS expression RIGHT_ROUND_PARANTHESIS | term {printf("H\n");} ;
term : CONST | ID {printf("term\n");} ;
struct_stmt : cmpd_stmt | if_stmt | while_stmt {printf("struct_stmt\n");} ;
cmpd_stmt : LEFT_CURLY_BRACKET stmt_list RIGHT_CURLY_BRACKET {printf("cmpd_stmt\n");} ;
if_stmt : IF LEFT_ROUND_PARANTHESIS condition RIGHT_ROUND_PARANTHESIS cmpd_stmt {printf("if_stmt\n");} ; 
condition : expression relation expression {printf("condition\n");} ;
relation : LESS_THAN | GREATER_THAN {printf("relation\n");} ;
while_stmt : WHILE LEFT_ROUND_PARANTHESIS condition RIGHT_ROUND_PARANTHESIS cmpd_stmt {printf("while_stmt\n");} ;
IO_stmt : READ LEFT_ROUND_PARANTHESIS ID RIGHT_ROUND_PARANTHESIS SEMICOLON | WRITE LEFT_ROUND_PARANTHESIS term RIGHT_ROUND_PARANTHESIS SEMICOLON {printf("IO_stmt\n");} ;
program : declaration_list {printf("program\n");} ;
declaration_list : declaration decl_opt | stmt_list {printf("declaration_list\n");} ;
