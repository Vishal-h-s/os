#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

//function for renaming
void rename_file(const char *source,const char*dest){
    if(rename(source,dest)!=0){
        perror("Error renaming file");
        exit(1);
    }
    printf("File renamed successfully : %s -> %s\n",source,dest);
}

//function for moving file
void move_file(const char*source,const char* dest){
    if(rename(source,dest)!=0){
        perror("Error moving file");
        exit(1);
    }
    printf("File moved successfully : %s -> %s\n",source,dest);
}

int main(int argc,char*argv[]){
    if(argc<2){
        fprintf(stderr,"Usage : %s [-r <source> <destination>] [-m <source> <destination>]\n",argv[0]);
        exit(1);
    }
    
    int opt;
    char *source=NULL,*dest=NULL;

    //parse command lime options
    while((opt=getopt(argc,argv,"rm"))!=-1){
        switch(opt){
            case 'r':
                if (argc<4){
                    fprintf(stderr,"Usage : %s -r <source> <destination>\n",argv[0]);
                    exit(1);
                }
                source=argv[2];dest=argv[3];
                rename_file(source,dest);
                break;
            case 'm':
                if(argc<4){
                    fprintf(stderr,"Usage :  %s -m <source> <destination>\n",argv[0]);
                    exit(1);
                }
                source=argv[2];dest=argv[3];
                move_file(source,dest);
                break;
            default:
                fprintf(stderr,"Usage : %s [-r <source> <destination>] [-m <source> <destination>]\n",argv[0]);
                exit(1);
        }
    }

    return 0;
}