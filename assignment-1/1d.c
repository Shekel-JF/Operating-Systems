#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    int i = 0;
    int orgid = getpid();
    int id = 0;
    int stat;

    for (i = 0; i < 4; i = i + 1)
    {
        id = fork();
        switch (id)
        {
            case -1:
                perror("fork error");
                exit(1);
            case 0:
			    sleep(getpid() - orgid);
				printf("UID: %d\n", getuid());
                printf("GID: %d\n", getgid());
                printf("Proces potomny: %d\n", getpid());
            	printf("PPID: %d\n", getppid());
                printf("GID: %d\n", getpgid(0));
                break;

            default:
			    printf("UID: %d\n", getuid());
                printf("GID: %d\n", getgid());
                printf("Proces macierzysty: %d\n", getpid());
        	    printf("PPID: %d\n", getppid());
                printf("PGID: %d\n", getpgid(0));
               
        }
    }
    exit(1);
}
