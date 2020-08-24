/*Lexical analyzer  program done by Akshay KH*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <stdbool.h>
#include<ctype.h>

char identifier[20][20];
int id=0;

bool isDelimiter(char ch) 
{ 
	if (ch == ' ' || ch == '+' || ch == '-' || ch == '*' || 
		ch == '/' || ch == ',' || ch == ';' || ch == '>' || 
		ch == '<' || ch == '=' || ch == '(' || ch == ')' ||
		ch == '[' || ch == ']' || ch == '{' || ch == '}' || ch == '\n')
			return (true);		 
	return (false); 
}
 
int isKeyword(char buffer[]){
	char keywords[35][10] = {"auto","break","case","char","const","continue","default",
							"do","double","else","enum","extern","float","for","goto",
							"if","int","long","register","return","short","signed",
							"sizeof","static","struct","switch","typedef","union",
							"unsigned","void","volatile","while","main","printf","scanf"};
	int i, flag = 0;
	
	for(i = 0; i < 35; ++i){
		if(strcmp(keywords[i], buffer) == 0){
			flag = 1;
			break;
		}
	}
	
	return flag;
}
 
int main(){
char ch, buffer[15],operators[] = {'+','-','*','/','%','=','>','<','!'};
	FILE *fp;
	int i,j=0,k,l,f1,f2;
	
	fp = fopen("input.txt","r");
	
	if(fp == NULL){
		printf("error while opening the file\n");
		exit(0);
	}
	
	while((ch = fgetc(fp)) != EOF){
   		for(i = 0; i < 9; ++i){
   			if(ch == operators[i])
   				printf("\t%c\toperator\n", ch);
   		}   		
		if(isalnum(ch)||ch == '"')
			buffer[j++] = ch;			
   		else if((isDelimiter(ch)==true) && (j != 0)){
   				buffer[j] = '\0';
   				j = 0;   				   				
   				if(isKeyword(buffer) == 1)
   					printf("\t%s\tkeyword\n", buffer);
   				else{
					k=0;l=0;f1=0;f2=0;
					char arry[15]= {'\0'};
					char number[15]= {'\0'};
					for (int i=0; buffer[i]!= '\0'; i++){
							if (isalpha(buffer[i]) != 0 || buffer[i] == '"') 
							{arry[k]=buffer[i];k++;f1=1;} 					  
							else if (isdigit(buffer[i]) != 0) 
							{number[l]=buffer[i];l++;f2=1;}
					}
					if(f1==1){
						int len = strlen(arry);
						if(arry[0] == '"' && arry[len-1] == '"')
							printf("\t%s\tliteral\n", arry);
						else{
							int found = 0;
						for(int i=0; i < id; i++)
							if(strcmp(identifier[i],arry)==0)
							{printf("\t%s\t(identifier,%d)\t\n",identifier[i], i);found=1;break;}	
						if(found==0){
						strcpy(identifier[id],arry);
						printf("\t%s\t(identifier,%d)\t\n",identifier[id], id);	
						id++;}
						}						
					}
					if(f2==1)
						printf("\t%s\tnumber\n", number);
				}
   					
   		}   		
	}
	
	fclose(fp);
	
	return 0;
}