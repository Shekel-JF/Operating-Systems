#include "obsluga.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

sem_t *adres;

void przerwanie(int sig)
{
    zniszcz_semafor(adres, "/semafor");
}

void wyjscie()
{
    zniszcz_semafor(adres, "/semafor");
}

int main()
{
    adres = otworz_semafor("/semafor");
    signal(SIGINT, przerwanie);
    atexit(wyjscie);
    int count = 3;
    pid_t id;
    int status;    
    FILE *plik = fopen("numer.txt", "w");
    fprintf(plik, "%d", 0);
    fclose(plik);

    for (int i = 0; i < count; i++)
    {
        switch (fork())
        {
            case 0:
                execl("wykluczenie.x", "wyklucznie.x", NULL);
                break;
        
            default:
                break;
        }
    }
    while ((id = wait(&status)) > 0);

}
