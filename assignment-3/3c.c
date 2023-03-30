#define _XOPEN_SOURCE_EXTENDED 1
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

int main()
{   
    pid_t id, gid, cid;
    int i;
    int status;
    int id2;
    char *args[] = {"./3a", "a", NULL};

    id = fork();

    switch(id)
    {
        case 0:
            setpgid(0,0);
            for (i = 0; i < 3; i++)
            {
                id2 = fork();
                switch(id2)
                {
                    case -1:
                        perror("Fork failed");
                        exit(1);
                        break;
                    case 0:
                        execvp(args[0], args);
                        break;
                    default:      
                        signal(SIGINT, SIG_IGN);
                        cid = waitpid(id2, &status, 0);
                        printf("%d zakonczyl prace\n", cid);
                        break;
                } 

            }
            break;

        default:
            sleep(2);
            gid = getpgid(id);
            while(waitpid(id, &status, WNOHANG) == 0)
            {
                killpg(gid, SIGINT);
                sleep(1);
            }
            //waitpid(id, &status, 0);
            break;
        }
        return 0;
}
