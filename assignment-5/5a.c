#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>


int main()
{

    char *args1[] = {"./5-kons.x", NULL};
    char *args2[] = {"./5-prod.x", NULL};

    if (mkfifo("potok", 0644) == -1)
    {
        perror("Blad przy tworzeniu potoku");
    }

    switch (fork())
    {
        case 0:
            execv(args1[0], args1);
            break;
    
        default:
            execv(args2[0], args2);
            break;
    }
    return 0;
}
