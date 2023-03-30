#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

int main()
{
    pid_t id;
    char *program = "./3a";
    char *arg1 = "a";
    id = fork();

    switch (id)
    {
        case 0: // potomny
            execl(program, program , arg1, NULL);
            break;
    
        default: // macierzysty
    	    sleep(2);
            if (kill(id, 0) == 3)
            {
                perror("Proces potomny nie istnieje\n");
                exit(1);
            }
                kill(id, SIGINT);
    
        break;
    }
    return 0;
}
