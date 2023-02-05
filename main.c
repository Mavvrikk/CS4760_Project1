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
int forker(int totaltoLaunch, int simulLimit, char iterTotal, int totalLaunched)
{
    pid_t pid;
    if(totalLaunched==simulLimit){
        return (totaltoLaunch);
    }
    else if(totaltoLaunch > 0)
    {
        if ((pid = fork()) < 0)
        {
            perror("fork");
        }
        else if (pid == 0)
        {
            char* args[]={"./worker",iterTotal,0};
            execlp(args[0],args[0],args[1],args[2]);
            
        /*CONTENTS OF WORKER FILE
        
           for(int k=0; k<=iterTotal;k++){
               
            printf("WORKER PID:%d PARENT PID:%d ITERATION: %d before sleeping\n", getpid(), getppid(), k);
            sleep(1);
            printf("WORKER PID:%d PARENT PID:%d ITERATION: %d after sleeping\n", getpid(), getppid(), k);
            exit(0);
           }
           
        */
        }
        else if(pid > 0)
        {
            forker(totaltoLaunch - 1, simulLimit, iterTotal, totalLaunched + 1);
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
   int totaltoLaunch=0; // int to hold -n arg
   int simulLimit=0; // int to hold -s arg
   int iterTotal=0; // int to pass to worker (-t arg)
   int totalLaunched=0; // int to count total children launched
   totaltoLaunch = atoi(x); // casting the argv to ints
   simulLimit = atoi(y);
   iterTotal = (z);
   int exCess = forker(totaltoLaunch,simulLimit,iterTotal,totalLaunched);
   int status;
   pid_t pid;
    pid = wait(&status);
    printf("I waited\n");
    if (exCess>0){printf("There were excess %d \n", exCess);}
    for(exCess;exCess>0;exCess--){
        forker(1,1,iterTotal,totalLaunched);
        pid = wait(&status);
    }
    
    return(0);
}





