#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>


void handle_ignore(int sig)
{
    printf("Przechwycono sygnal %d\n", sig);

}

int main(int argc, char const *argv[])
{
    if ( argc == 1 )
    {
        printf("Blad: nie podano zadnego argumentu.\n");
        exit(1);
    }

    if ( argc > 2 )
    {
        printf("Podano za duzo argumentow.\n");
        exit(1);
    }

    switch (*argv[1])
    {
        case 'i':
            signal(SIGINT, SIG_IGN);
            pause();
    
        case 'd':
            pause();
    
        case 'a':
            signal(SIGINT, handle_ignore);
            pause();
            break;
    }
    return 0;
}
