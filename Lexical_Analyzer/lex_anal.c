#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
int idcount=-1;
char type[10];
struct identifier{
    char name[20],kind[15],type[15],scope[15];
    int id,address;
}symtab[20];

int isKeyword(char word[]){
    char keywords[10][10]={"int","float","char","double","const","return","while","for","if","else"};
    for(int i=0;i<10;i++){
        if(!strcmp(keywords[i],word)){
           if(!strcmp(word,"int") || !strcmp(word,"float")||!strcmp(word,"char"))
            strcpy(type,word);
            return 1;}
    }
    return 0;
}
int isop(char ch){
    return ch=='+' || ch=='-' || ch=='*' || ch=='/' || ch=='=' ||ch=='%' ||ch=='^'|| ch=='<' ||ch=='>'||ch=='!' ;
}
void insert(char name[],int id,char kind[],char typee[],char scope[],int address){
    symtab[id].id=id;
    strcpy(symtab[id].name,name);
    strcpy(symtab[id].kind,kind);
    strcpy(symtab[id].type,typee);
    strcpy(symtab[id].scope,scope);
    symtab[id].address=address;
}
int present(char name[]){
    for(int i=0;i<=idcount;i++){
        if(!strcmp(symtab[i].name,name))return i;
    }
    return -1;
}
int main(){
    FILE *f=fopen("input.txt","r");
    char ch,word[10],kind[15],scope[15];
    int line=1,i,addr=1000,depth=0;
    if(!f){
        printf("Couldnt read input file");
        return 0;
    }
    while((ch=fgetc(f))!=EOF){
        if(ch=='\n'){line++;continue;}
        if(isspace(ch)){continue;}      

        //identifier or keyword

        if(ch=='_' || isalpha(ch)){
            i=0;
            word[i++]=ch;
            while((ch=fgetc(f))!=EOF && isalnum(ch)){
                word[i++]=ch;
            }
            word[i]='\0';
            if(ch!=EOF)ungetc(ch,f);
            if(isKeyword(word)){
                printf("%s\t%d\tKeyword\n",word,line);
            }else{
                int ind=present(word);
                if(ind!=-1){
                    printf("%s\t%d\tIdentifier,%d\n",word,line,ind);
                }else{
                    int temp=0;
                    strcpy(kind,"Variable");
                    while((ch=fgetc(f))!=EOF){
                        temp++;
                        if(isspace(ch))continue;
                        if(ch=='('){strcpy(kind,"Function");}
                        break;
                    }
                    
                        ungetc(ch,f);
                    
                    if(depth>0)strcpy(scope,"Local");
                    else strcpy(scope,"Global");
                    if(strlen(type)>0){
                        insert(word,++idcount,kind,type,scope,addr);
                        addr++;
                    }
                    printf("%s\t%d\tIdentifier,%d\n",word,line,idcount);
                }
            }
            continue;
        }

        //integer const

        if(isdigit(ch)){
            i=0;
            word[i++]=ch;
            while((ch=fgetc(f))!=EOF && isdigit(ch)){
                word[i++]=ch;
            }
            word[i]='\0';
            if(ch!=EOF)ungetc(ch,f);
            printf("%s\t%d\tInteger Constant\n",word,line);
            continue;
        }

        //char const

        if(ch=='"'){
            i=0;
            word[i++]=ch;
            while((ch=fgetc(f))!=EOF && ch!='"'){
                word[i++]=ch;
            }
            if(ch=='"'){
                word[i]='\0';
                printf("%s\t%d\tCharacter Constant\n",word,line);
            }
            continue;
        }

        //operator

        if(isop(ch)){
            char chh=ch;
            if((ch=fgetc(f))!=EOF && isop(ch)){
                printf("%c%c\t%d\tRelational Operator\n",chh,ch,line);
            }
            if(!isop(ch)){
                ungetc(ch,f);
                printf("%c\t%d\tOperator\n",chh,line);
            }
            continue;
        }
        if(ch=='{')depth++;
        if(ch=='}')depth--;
        if(ch=='{' || ch=='}' || ch=='(' || ch==')' || ch=='[' || ch==']' || ch==';' || ch==',' || ch=='.' ||ch==':' ){
            printf("%c\t%d\tDelimiter\n",ch,line);
        }
    }
    printf("\nSYMTAB\nName\tId\tKind\t\tType\tScope\tAddress\n");
    for(i=0;i<=idcount;i++){
        printf("%s\t%d\t%s\t%s\t%s\t%04X\n",symtab[i].name,symtab[i].id,symtab[i].kind,symtab[i].type,symtab[i].scope,symtab[i].address);
    }
}
