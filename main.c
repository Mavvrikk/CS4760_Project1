#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/ipc.h>

void helpFunction()
{
    printf("The function call should go as follows: ./oss [-h] [-n proc] [-s simu] [-t iter]");
    printf("where -h displays this help function and terminates, proc is the number of processes you want to run, simu is the number of simultaneous");
    printf("processes that run and iter is the argument passed to the child processes.");
}
int forker(int firstArg, int secArg, int thirdArg, int counter)
{
    pid_t pid;
    if((counter-firstArg)==secArg){
        return (firstArg);
    }
    else if(firstArg > 0)
    {
        if ((pid = fork()) < 0)
        {
            perror("fork");
        }
        else if (pid == 0)
        {
            // char* args[]={"./worker,thirdArg,0"};
            //execlp(args[0],args[0],args[1],args[2]);
            
            /*CONTENTS OF WORKER FILE*/
           for(int k=0; k<=thirdArg;k++){
               
            printf("WORKER PID:%d PARENT PID:%d ITERATION: %d before sleeping\n", getpid(), getppid(), k);
            sleep(1);
            printf("WORKER PID:%d PARENT PID:%d ITERATION: %d after sleeping\n", getpid(), getppid(), k);
            /*CONTENTS OF WORKER FILE*/
            
           }
        }
        else if(pid > 0)
        {
            forker(firstArg - 1,secArg,thirdArg,counter);
        }
    }
    else
        return (0);

}
char *x = NULL;
char *y = NULL;
char *z = NULL;
 
int main(int argc, char** argv)
{
    int option;
    while((option=getopt(argc,argv, "n:s:t:h"))!=-1){
        switch(option){
            case 'h':
            helpFunction();
            return 0;
            case 'n':
            x = optarg;
            break;
            case 's':
            y = optarg;
            break;
            case 't': 
            z = optarg;
            break;
        }
    }
   int firstArg=0; // ints to hold argv args
   int secArg=0;
   int thirdArg=0;
   firstArg = atoi(x); // casting the argv to ints
   secArg = atoi(y);
   thirdArg = atoi(z);
   int exCess = forker(firstArg,secArg,thirdArg,firstArg);
   int status;
   pid_t pid;
    pid = wait(&status);
    printf("I waited\n");
    if (exCess>0){printf("There were excess \n");}
}

