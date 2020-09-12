%{
/* Yacc Program to check the validity of an arithmetic Expression that uses operators +, -, *, /
*/
#include "y.tab.h"
%}
%%
[0-9]+(\.[0-9]+)?     		{ return NUM;}
[a-zA-Z_][_a-zA-Z0-9]* 	{ return ID; }
[\t] 				;
\n 				return 0;
.				return yytext[0];
%%
yywrap()
{}