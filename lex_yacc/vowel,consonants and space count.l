%{
    #include<stdio.h>
    int vow=0,cons=0,sp=0;
%}
%%
[aeiouAEIOU] {vow++;}
[ \t]   {sp++;}
[a-zA-z^aeiouAEIOU] {cons++;}
%%
int main(){
    yylex();
    printf("\nVowels:%d\nConsonants:%d\nSpace:%d\n",vow,cons,sp);
    return 0;
}
int yywrap(){
    return 1;
}
