#include<stdio.h>
#include<stdlib.h>
#include<dirent.h>
#include<unistd.h>
int main(int argc,char*argv[]){

    char* path=argc>1?argv[1]:".";

    DIR * dir = opendir(path);
    if(dir==NULL){
        perror("Error opening directory");
        return 1;
    }

    struct dirent*entry;
    printf("pid=%d\n",getpid());
    while((entry=readdir(dir))!=NULL){
        printf("%s\t",entry->d_name);
    }printf("\n");

    

    closedir(dir);
    return 0;
}