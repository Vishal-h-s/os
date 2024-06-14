#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

#include<time.h>
clock_t start;
void print_elapsed_time(){
    clock_t end=clock();
    double time_spent=(double)(end-start)/CLOCKS_PER_SEC * 1000;
    printf("pid=%d Time elapsed: %f ms\n",getpid(),time_spent);
}
int main (){
    print_elapsed_time();
    start=clock();

    int shared_variable=42;
    print_elapsed_time();
    pid_t pid=vfork();
    print_elapsed_time();
    if(pid<0){
        print_elapsed_time();
        perror("vfork failed");
        return 1;
    }else if (pid == 0){
        print_elapsed_time();
        printf("pid=%d Child before change - shared_variable=%d\n",getpid(),shared_variable);
        shared_variable=100;
        printf("Child after change - shared_variable=%d\n",shared_variable);
        print_elapsed_time();
        _exit(0);
    }else{//in vfork, parent resumes after child exits(terminates)
    print_elapsed_time();
    printf("pid=%d Parent after child(pid=%d) exit - shared_variable=%d\n",getpid(),pid,shared_variable);
    // no need to explicitly call wait() or waitpid() as parent resumes after child exits
    }
    print_elapsed_time();
    return 0;
}