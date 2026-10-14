#include<stdio.h>
#include<string.h>
#include<ctype.h>

char postfix[20],expr[20],op[10],arg1[10][3],arg2[10][3],result[10][3];
int o=0,a1=0,a2=0,res=0,stacklen,id=0;

int precedence (char c){
    if(c=='*')return 5;
    if(c=='/')return 4;
    if(c=='+')return 3;
    if(c=='-')return 2;
    if(c=='=')return 1;
    return 0;
}

void post(){
    int i,k=0,s=-1;
    char ch,stack[10];
    for(i=0;expr[i]!='\0';i++){
        ch=expr[i];
        if(ch=='('){
            stack[++s]=ch;
        }else if(ch==')'){
            while(stack[s]!='('){
                postfix[k++]=stack[s--];
            }
            s--;
        }else if(isalpha(ch)){
            postfix[k++]=ch;
        }else {
            if(precedence(stack[s])>=precedence(ch)){
                while(precedence(stack[s])>=precedence(ch)){
                    postfix[k++]=stack[s--];
                }
                
            }
            stack[++s]=ch;
        }
    }
    while(s>=0){
        postfix[k++]=stack[s--];
    }
    postfix[k]='\0';
    printf("\nPostfix: %s\n",postfix);
}

void tac(){
    char stack[10][3],a[3],b[3];
    int i,s=-1;
    char ch;
    printf("\n3 address code\n");
    for(i=0;postfix[i]!='\0';i++){
        ch=postfix[i];
        if(isalpha(ch)){
            stack[++s][0]=ch;
            stack[s][1]='\0';
        }else{
            strcpy(b,stack[s--]);
            strcpy(a,stack[s--]);
            strcpy(arg1[a1++],a);
            strcpy(arg2[a2++],b);
            op[o++]=ch;
            sprintf(result[res],"t%d",++id);
            printf("t%d = %s %c %s\n",id,a,ch,b);
            strcpy(stack[++s],result[res++]);
        }
    }
    stacklen=o;
}

int main(){
    int i;
    char a[5],b[5];
    printf("Enter expression : ");
    scanf("%s",expr);

    post();

    tac();

    printf("\nQuadruples\nIndex\tOperator\tArg1\tArg2\tResult\n");
    for(i=0;i<stacklen;i++){
        printf("(%d)\t%c\t\t%s\t%s\t%s\n",i,op[i],arg1[i],arg2[i],result[i]);
    }

    printf("\nTriples\nIndex\tOperator\tArg1\tArg2\n");
    for(i=0;i<stacklen;i++){
        if(strlen(arg1[i])>1){
            sprintf(a,"(%d)",(arg1[i][1]-'0')-1);
        }else strcpy(a,arg1[i]);
        if(strlen(arg2[i])>1){
            sprintf(b,"(%d)",(arg2[i][1]-'0')-1);
        }else strcpy(b,arg2[i]);
        printf("(%d)\t%c\t\t%s\t%s\n",i,op[i],a,b);
    }

    printf("\nIndirect Triples\nIndex\tOperator\tArg1\tArg2\n");
    int start=20,stable[id];
    for(i=0;i<id;i++)stable[i]=start++;

    for(i=0;i<stacklen;i++){
        if(strlen(arg1[i])>1){
            sprintf(a,"(%d)",stable[(arg1[i][1]-'0')-1]);
        }else strcpy(a,arg1[i]);
        if(strlen(arg2[i])>1){
            sprintf(b,"(%d)",stable[(arg2[i][1]-'0')-1]);
        }else strcpy(b,arg2[i]);
        printf("(%d)\t%c\t\t%s\t%s\n",i,op[i],a,b);
    }
    printf("\nStatement Table\n#\tStatement\n");
    for(i=0;i<id;i++)printf("%d\t%d\n",i,stable[i]);
}
