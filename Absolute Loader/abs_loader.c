#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void main(){
    FILE *f=fopen("object.txt","r");
    int i,address;
    if(!f){
        printf("Cannot open input file\n");
    }
    char line[100],pname[20],plength[10],start[10],opcode[50],tstart[10],tlen[10],byte[3],*token;
    while(fgets(line,sizeof(line),f)){
        if(line[0]=='H'){
            sscanf(line,"H^%[^^]^%[^^]^%s",pname,start,plength);
            printf("Program Name:%s\nLength:%s\nStart address:%s\n",pname,plength,start);
        }
        else if(line[0]=='T'){
            sscanf(line,"T^%[^^]^%[^^]^%s",tstart,tlen,opcode);
            address=(int)strtol(tstart,NULL,16);
            token=strtok(opcode,"^");
            printf("Address\tContent\n");
            while(token!=NULL){
                for(i=0;i<strlen(token);i+=2){
                    byte[0]=token[i];
                    byte[1]=token[i+1];
                    byte[2]='\0';
                    printf("%04X\t%s\n",address++,byte);
                }
                token=strtok(NULL,"^");
            }
        }
    }
    fclose(f);
}
