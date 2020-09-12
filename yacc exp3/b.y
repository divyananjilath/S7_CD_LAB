%{

    #include<stdio.h>

    int valid=1;

%}

%token digit letter

%%

start : letter s

s :     letter s

      | digit s

      |

      ;

%%

int yyerror()

{

    printf("\nNot valid!\n");

    valid=0;

    return 0;

}

int main()

{

    printf("\nEnter a variable name:");

    yyparse();

    if(valid)

    {

        printf("\nValid!\n");

    }

}