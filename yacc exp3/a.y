%{
/* Yacc Program to check the validity of an arithmetic Expression that uses operators +, -, *, /
*/
#include<stdio.h>
#include<stdlib.h>
%}
%token NUM  ID
%left '+' '-'
%left '*' '/'
%%
e : e '+' e
|   e '-' e
|   e '*' e
|   e '/' e
|   '('e')'
| NUM
| ID         ;
%%
main()
{
printf(" Enter the expression:\n");
yyparse();
printf(" Valid Expression \n");
}
yyerror()
{
    printf(" Invalid Expresion!!!!\n"); exit(0);
}