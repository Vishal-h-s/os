#include<stdio.h>
#include<stdlib.h>

int main(int argc,char *argv[]){
    if(argc<2){
        printf("Usage: %s <filename>\n",argv[0]);
        return 1;
    }

    FILE * file = fopen(argv[1],"r");
    if(file == NULL){
        perror("Error opening file");
        return 1;
    }

    char buffer[256];
    while(fgets(buffer,sizeof(buffer),file)!=NULL){
        printf("%s",buffer);
    }
    fclose(file);
    return 0;
}