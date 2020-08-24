/* Program to read a c program as a input file and analyze it to determine identifiers, keywords and operators*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

char buffer[100];
int key = 0;
int id = 0, keyword = 1,op=0;
char found_id[10][10];
int result=-1;
char found_operator[10];
int op_result = -1;

int isKeyword(char buffer[]){
    char keywords[33][10] = {
                                "auto","break","case","char","const","continue","default",
                                "do","double","else","enum","extern","float","for","goto",
                                "if","int","long","register","return","short","signed",
                                "sizeof","static","struct","switch","typedef","union",
                                "unsigned","void","volatile","while","main"
                            };

    int i, flag = 0;
    for(i = 0; i < 33; ++i)
    {
        if(strcmp(keywords[i], buffer) == 0)
            {
                flag = 1;
                break;
            }
    }
    return flag;
}

void checkIfIdentifierPresent(char buffer[]){
    for(int i =0;i<id;i++)
    {
        if(strcmp(buffer,found_id[i])==0)
        {
            result = i;
        }
    }
}

void joinString(char c){
    buffer[key++] = c;
}

int main()
{
    char ch;
    char operators[20];
    char variables[20][20];
    char bfr[20][20];
    int constants[20];
    int ascii[500] = {0};
    int number = 0;
    int i, j = -1, k = -1, l = -1, n = 0,q=0;
    int pr[10] = {0}, m;
    int counter = 0;

    printf("\n\n————– LEXICAL ANALYZER ————–\n\n");

    FILE *fp;
    fp = fopen("input.txt", "r");

    if(fp==NULL)
    {
        printf("Error reading the input program from file \n");
        exit(0);
    }
    else{
        printf("Input program read successfully\n\n");
        while((ch = fgetc(fp)) != EOF)
        {
            ascii[counter] = (int)ch;
            counter++;
        }

        fclose(fp);
        fp = fopen("input.txt", "r");
        counter = 0;

        while((ch = fgetc(fp)) != EOF)
        {
            if(isdigit(ch))
            {
                while(isdigit(ch))
                {
                    number = 10 * number + ascii[counter] - '0';
                    ch = fgetc(fp);
                    counter++;
                }

                j++;
                constants[j]=number;
                number=0;
            }

            if( isalpha(ch) )
            {
                while( isalpha(ch) || isdigit(ch) || ch=='_' )
                {
                    k++;
                    variables[m][k]=ch;
                    ch = fgetc(fp);
                    counter++;
                }
        
                m++;
                pr[n]=k;
                n++;
                k=-1;
            }

            if(ch=='+' ||ch=='-'||ch=='/'||ch=='*'|| ch=='='|| ch=='^')
            {
                l++;
                operators[l]= ch;
            }

            counter++;
        }
    }
    
    printf("tokens generated:\n\n");

    for(i=0;i<=j;i++)
    {
        printf("\t%d\t\tNumber\n",constants[i]);
    }

    for(i=0;i<m;i++)
    {
        for(j=0;j<=pr[i];j++)
        {
            char temp = variables[i][j];
            joinString(temp);
        }
        if(isKeyword(buffer)){
            printf("\t%s\t\tKeyword\n",buffer);
            keyword++;
        }
        else{
            if(id==0)
            {
                strcpy(found_id[0],buffer);
                printf("\t%s\t\t(Identifier, %d)\n",buffer,id+1);
                id++;
            }
            else{
                checkIfIdentifierPresent(buffer);
                if(result==-1)
                {
                    printf("\t%s\t\t(Identifier, %d)\n",buffer,id+1);
                    id++;
                }
                else{
                    printf("\t%s\t\t(Identifier, %d)\n",buffer,result+1);
                    id++;
                }
                
            }
        }
        memset ( buffer, 0, 100 );
        key = 0;
    }


    printf("\n\n————– END OF LEXICAL ANALYZER ————\n\n");

    fclose(fp);
    return 0;
}