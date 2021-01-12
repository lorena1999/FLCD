%{
#include <stdio.h>
#include <stdlib.h>

#define YYDEBUG 1
%}

%token ID
%token CONSTANT
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

program : declaration_list
declaration_list : declaration decl_opt | stmt_list
declaration : decl1 const_opt ;
decl1 : LET ID COLON type
type : INTEGER | STRING
const_opt : LEFT_SQUARE_PARANTHESIS CONSTANT RIGHT_SQUARE_PARANTHESIS
decl_opt : declaration_list
stmt_list : stmt stmt_opt
stmt : assign_stmt | IO_stmt | struct_stmt
stmt_opt : stmt_list
assign_stmt : ID EQUAL expression ;
expression : B A
A : + B A
B : D C
C : * D C
D : F E
E : / F E
F : H G
G : - H G
H : LEFT_ROUND_PARANTHESIS expression RIGHT_ROUND_PARANTHESIS | term
term : CONSTANT | ID
struct_stmt : cmpd_stmt | if_stmt | while_stmt
cmpd_stmt : LEFT_CURLY_BRACKET stmt_list RIGHT_CURLY_BRACKET
if_stmt : IF condition cmpd_stmt
condition : expression relation expression
relation : LESS_THAN | EQUAL | GREATER_THAN
while_stmt : LEFT_ROUND_PARANTHESIS condition RIGHT_ROUND_PARANTHESIS cmpd_stmt



%%

yyerror(char *s)
{
	printf("%s\n", s);
}

extern FILE *yyin;

main(int argc, chaar **argv)
{
	if(argc>1)
		yyin=fopen(argv[1], "r");
	if((argc>2) && (!strcmp(argv[2], "-d")))
		yydebug=1;
	if(!yyparse())
		fprintf(stderr,"\t U GOOOOD !!!\n");
}
