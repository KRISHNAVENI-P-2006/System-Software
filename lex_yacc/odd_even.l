%{
    #include<stdio.h>
%}
%%
[0-9]+ {int n=atoi(yytext);
        if(n%2==0)printf("Even\n");
        else printf("Odd\n");}
%%
int main(){
    yylex();
    return 0;
}
int yywrap(){return 1;}
