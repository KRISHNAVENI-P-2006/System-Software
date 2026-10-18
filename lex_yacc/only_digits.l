%{
    #include<stdio.h>
%}
%%
^[0-9]+$ {printf("True\n");}
^.*$ {printf("False\n");}
[ \t\n] ;
%%
int main(){
    yylex();
    return 0;
}
int yywrap(){
    return 1;
}
